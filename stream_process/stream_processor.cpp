#include <Python.h>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <queue>
#include <string>
#include <vector>

static std::vector<std::string> RTSP_URLS;
static int IMG_WIDTH = 1280;
static int IMG_HEIGHT = 720;
static int FRAMES_PER_SECOND = 2;  // 채널당 1초에 2장씩 저장
static int NUM_CHANNELS = 0;
static int IMAGE_QUEUE_SIZE = 100;

typedef struct {
    GstElement *pipeline;
    GstElement *appsink;
    int channel_id;
    time_t last_save_time;
    int frames_stored;
    gboolean running;
} StreamData;

typedef struct {
    cv::Mat image;
    int channel_id;
    time_t timestamp;
} FrameData;

static std::queue<FrameData> image_queue;
static pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

static StreamData *stream_data = nullptr;
static pthread_t *threads = nullptr;

static void on_new_sample(GstAppSink *appsink, gpointer user_data) {
    GstSample *sample;
    GstBuffer *buffer;
    GstMapInfo map;
    cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3);

    sample = gst_app_sink_pull_sample(appsink);
    buffer = gst_sample_get_buffer(sample);

    if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        gsize expected_size = static_cast<gsize>(IMG_WIDTH) * IMG_HEIGHT * 3;
        if (map.size == expected_size) {
            memcpy(img.data, map.data, map.size);

            StreamData *stream = (StreamData *)user_data;
            time_t current_time = time(NULL);

            // 1초에 채널당 2장의 프레임만 큐에 넣기 위한 조건문
            if (difftime(current_time, stream->last_save_time) >= 1.0) {
                stream->last_save_time = current_time;
                stream->frames_stored = 0;
            }

            if (stream->frames_stored < FRAMES_PER_SECOND) {
                FrameData frame_data;
                frame_data.image = img.clone();
                frame_data.channel_id = stream->channel_id;
                frame_data.timestamp = current_time;

                pthread_mutex_lock(&queue_mutex);
                std::queue<FrameData>::size_type queue_size = image_queue.size();
                if (queue_size < static_cast<std::queue<FrameData>::size_type>(IMAGE_QUEUE_SIZE)) {
                    image_queue.push(frame_data);
                    pthread_cond_signal(&queue_cond);
                }
                pthread_mutex_unlock(&queue_mutex);

                stream->frames_stored++;
            }
        }
        gst_buffer_unmap(buffer, &map);
    }

    gst_sample_unref(sample);
}

static void* stream_thread(void *arg) {
    StreamData *stream = (StreamData *)arg;
    GstStateChangeReturn ret;

    ret = gst_element_set_state(stream->pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        return NULL;
    }

    g_signal_connect(stream->appsink, "new-sample", G_CALLBACK(on_new_sample), stream);

    stream->running = TRUE;
    stream->frames_stored = 0;
    stream->last_save_time = time(NULL);

    while (stream->running) {
        usleep(500000);  // 0.5초 대기
    }

    gst_element_set_state(stream->pipeline, GST_STATE_NULL);
    gst_object_unref(stream->pipeline);
    return NULL;
}

// static GstElement* create_pipeline(const gchar *rtsp_url) {
//     GstElement *pipeline, *source, *sink;
//     GstCaps *caps;

//     pipeline = gst_parse_launch(
//         "rtspsrc name=source ! rtph264depay ! avdec_h264 ! videoconvert ! appsink name=sink",
//         NULL);

//     source = gst_bin_get_by_name(GST_BIN(pipeline), "source");
//     g_object_set(source, "location", rtsp_url, NULL);

//     sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");
//     caps = gst_caps_new_simple("video/x-raw",
//                                "format", G_TYPE_STRING, "RGB",
//                                "width", G_TYPE_INT, IMG_WIDTH,
//                                "height", G_TYPE_INT, IMG_HEIGHT,
//                                NULL);
//     g_object_set(sink, "caps", caps, "emit-signals", TRUE, NULL);
//     gst_caps_unref(caps);

//     return pipeline;
// }

static GstElement* create_pipeline(const gchar *rtsp_url) {
    GstElement *pipeline, *source, *capsfilter, *appsink;
    GstCaps *caps;

    pipeline = gst_parse_launch(
        "rtspsrc name=source ! rtph264depay ! avdec_h264 ! videoconvert ! videoscale ! capsfilter name=capsfilter ! appsink name=sink",
        NULL);

    source = gst_bin_get_by_name(GST_BIN(pipeline), "source");
    g_object_set(source, "location", rtsp_url, NULL);

    capsfilter = gst_bin_get_by_name(GST_BIN(pipeline), "capsfilter");
    caps = gst_caps_new_simple("video/x-raw",
                               "format", G_TYPE_STRING, "RGB",
                               "width", G_TYPE_INT, IMG_WIDTH,
                               "height", G_TYPE_INT, IMG_HEIGHT,
                               NULL);
    g_object_set(capsfilter, "caps", caps, NULL);
    gst_caps_unref(caps);

    appsink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");
    g_object_set(appsink, "emit-signals", TRUE, NULL);

    return pipeline;
}


static PyObject* set_stream_config(PyObject* self, PyObject* args) {
    PyObject *url_list;
    PyObject *item;
    Py_ssize_t size;
    int width, height, fps;

    if (!PyArg_ParseTuple(args, "Oiii", &url_list, &width, &height, &fps)) {
        return NULL;
    }

    if (!PyList_Check(url_list)) {
        PyErr_SetString(PyExc_TypeError, "URL list must be a list");
        return NULL;
    }

    size = PyList_Size(url_list);
    RTSP_URLS.clear();
    for (Py_ssize_t i = 0; i < size; i++) {
        item = PyList_GetItem(url_list, i);
        if (PyUnicode_Check(item)) {
            RTSP_URLS.push_back(PyUnicode_AsUTF8(item));
        } else {
            PyErr_SetString(PyExc_TypeError, "All items in the URL list must be strings");
            return NULL;
        }
    }

    NUM_CHANNELS = RTSP_URLS.size();
    IMG_WIDTH = width;
    IMG_HEIGHT = height;
    FRAMES_PER_SECOND = fps;
    IMAGE_QUEUE_SIZE = 100;

    Py_RETURN_NONE;
}

static PyObject* get_next_frame(PyObject* self, PyObject* args) {
    FrameData frame_data;

    pthread_mutex_lock(&queue_mutex);
    if (image_queue.empty()) {
        pthread_mutex_unlock(&queue_mutex);
        Py_RETURN_NONE;
    }

    frame_data = image_queue.front();
    image_queue.pop();
    pthread_mutex_unlock(&queue_mutex);

    PyObject* py_array = PyBytes_FromStringAndSize(reinterpret_cast<const char*>(frame_data.image.data), frame_data.image.total() * frame_data.image.elemSize());
    PyObject* py_tuple = PyTuple_Pack(3, py_array, PyLong_FromLong(frame_data.channel_id), PyLong_FromLong(frame_data.timestamp));
    return py_tuple;
}

static PyObject* start_stream_processing(PyObject* self, PyObject* args) {
    gst_init(NULL, NULL);

    if (NUM_CHANNELS == 0) {
        PyErr_SetString(PyExc_RuntimeError, "No channels configured");
        return NULL;
    }

    stream_data = new StreamData[NUM_CHANNELS];
    threads = new pthread_t[NUM_CHANNELS];

    for (int i = 0; i < NUM_CHANNELS; i++) {
        stream_data[i].channel_id = i;
        stream_data[i].pipeline = create_pipeline(RTSP_URLS[i].c_str());
        stream_data[i].appsink = gst_bin_get_by_name(GST_BIN(stream_data[i].pipeline), "sink");
        stream_data[i].running = FALSE;

        pthread_create(&threads[i], NULL, stream_thread, &stream_data[i]);
    }

    Py_RETURN_NONE;
}

static PyObject* stop_stream_processing(PyObject* self, PyObject* args) {
    if (stream_data == nullptr || threads == nullptr) {
        Py_RETURN_NONE;
    }

    for (int i = 0; i < NUM_CHANNELS; i++) {
        stream_data[i].running = FALSE;
        pthread_join(threads[i], NULL);
        gst_object_unref(stream_data[i].appsink);
    }

    delete[] stream_data;
    delete[] threads;

    pthread_mutex_destroy(&queue_mutex);
    pthread_cond_destroy(&queue_cond);

    Py_RETURN_NONE;
}

static PyMethodDef StreamProcessorMethods[] = {
    {"set_stream_config",       set_stream_config,       METH_VARARGS, "Set stream configuration."},
    {"start_stream_processing",  start_stream_processing, METH_VARARGS, "Start stream processing."},
    {"stop_stream_processing",   stop_stream_processing,  METH_VARARGS, "Stop stream processing."},
    {"get_next_frame",            get_next_frame,         METH_VARARGS, "Get the next frame from the queue."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef streamprocessormodule = {
    PyModuleDef_HEAD_INIT,
    "stream_processor",
    NULL,
    -1,
    StreamProcessorMethods
};

PyMODINIT_FUNC PyInit_stream_processor(void) {
    return PyModule_Create(&streamprocessormodule);
}