#define PY_SSIZE_T_CLEAN
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

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720
#define NUM_CHANNELS 2
#define IMAGE_QUEUE_SIZE 10

const gchar *RTSP_URLS[NUM_CHANNELS] = {
    "rtsp://127.0.0.1:8554/stream",
    "rtsp://127.0.0.1:8562/stream"
};

typedef struct {
    GstElement *pipeline;
    GstElement *appsink;
    int channel_id;
    int thread_id;
    int sequence_number;
    time_t last_save_time;
    gboolean running;
} StreamData;

static std::queue<cv::Mat> image_queue;
static pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

static StreamData stream_data[NUM_CHANNELS];
static pthread_t threads[NUM_CHANNELS];

static void on_new_sample(GstAppSink *appsink, gpointer) {
    GstSample *sample;
    GstBuffer *buffer;
    GstMapInfo map;
    cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3);

    sample = gst_app_sink_pull_sample(appsink);
    buffer = gst_sample_get_buffer(sample);

    if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        if (map.size == IMG_WIDTH * IMG_HEIGHT * 3) {
            memcpy(img.data, map.data, map.size);

            pthread_mutex_lock(&queue_mutex);
            if (image_queue.size() < IMAGE_QUEUE_SIZE) {
                image_queue.push(img.clone());
                pthread_cond_signal(&queue_cond);
            }
            pthread_mutex_unlock(&queue_mutex);
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

    g_signal_connect(stream->appsink, "new-sample", G_CALLBACK(on_new_sample), NULL);

    stream->running = TRUE;
    while (stream->running) {
        usleep(500000);
    }

    gst_element_set_state(stream->pipeline, GST_STATE_NULL);
    gst_object_unref(stream->pipeline); // Release reference to the pipeline
    return NULL;
}

static GstElement* create_pipeline(const gchar *rtsp_url) {
    GstElement *pipeline, *source, *sink;
    GstCaps *caps;

    pipeline = gst_parse_launch(
        "rtspsrc name=source ! rtph264depay ! avdec_h264 ! videoconvert ! appsink name=sink",
        NULL);

    source = gst_bin_get_by_name(GST_BIN(pipeline), "source");
    g_object_set(source, "location", rtsp_url, NULL);

    sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");
    caps = gst_caps_new_simple("video/x-raw",
                               "format", G_TYPE_STRING, "RGB",
                               "width", G_TYPE_INT, IMG_WIDTH,
                               "height", G_TYPE_INT, IMG_HEIGHT,
                               NULL);
    g_object_set(sink, "caps", caps, "emit-signals", TRUE, NULL);
    gst_caps_unref(caps);

    return pipeline;
}

// 새로운 함수: 큐에서 프레임을 가져오는 함수
static PyObject* get_next_frame(PyObject* self, PyObject* args) {
    cv::Mat img;

    pthread_mutex_lock(&queue_mutex);
    if (image_queue.empty()) {
        pthread_mutex_unlock(&queue_mutex);
        Py_RETURN_NONE;  // 큐가 비어 있을 경우
    }

    img = image_queue.front();
    image_queue.pop();
    pthread_mutex_unlock(&queue_mutex);

    // 이미지 데이터를 Python 객체로 변환
    PyObject* py_array = PyBytes_FromStringAndSize(reinterpret_cast<const char*>(img.data), img.total() * img.elemSize());
    return py_array;
}

static PyObject* start_stream_processing(PyObject* self, PyObject* args) {
    gst_init(NULL, NULL);

    for (int i = 0; i < NUM_CHANNELS; i++) {
        stream_data[i].channel_id = i;
        stream_data[i].thread_id = i + 1;
        stream_data[i].sequence_number = 0;
        stream_data[i].last_save_time = time(NULL);
        stream_data[i].pipeline = create_pipeline(RTSP_URLS[i]);
        stream_data[i].appsink = gst_bin_get_by_name(GST_BIN(stream_data[i].pipeline), "sink");
        stream_data[i].running = FALSE;

        pthread_create(&threads[i], NULL, stream_thread, &stream_data[i]);
    }

    Py_RETURN_NONE;
}

static PyObject* stop_stream_processing(PyObject* self, PyObject* args) {
    for (int i = 0; i < NUM_CHANNELS; i++) {
        stream_data[i].running = FALSE;
        pthread_join(threads[i], NULL);
        gst_object_unref(stream_data[i].appsink); // Release reference to the appsink
    }

    pthread_mutex_destroy(&queue_mutex);
    pthread_cond_destroy(&queue_cond);

    Py_RETURN_NONE;
}

static PyMethodDef StreamProcessorMethods[] = {
    {"start_stream_processing",  start_stream_processing, METH_VARARGS, "Start stream processing."},
    {"stop_stream_processing",   stop_stream_processing,  METH_VARARGS, "Stop stream processing."},
    {"get_next_frame",            get_next_frame,         METH_VARARGS, "Get the next frame from the queue."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef streamprocessormodule = {
    PyModuleDef_HEAD_INIT,
    "stream_processor",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                  or -1 if the module keeps state in global variables */
    StreamProcessorMethods
};

PyMODINIT_FUNC PyInit_stream_processor(void) {
    return PyModule_Create(&streamprocessormodule);
}
