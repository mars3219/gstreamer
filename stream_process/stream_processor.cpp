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
#include <ctime>
#include <chrono>

static std::vector<std::string> RTSP_URLS;
static int IMG_WIDTH = 1280;
static int IMG_HEIGHT = 720;
static int SAVE_FRAMES_PER_SECOND = 2;  // 초당 저장할 프레임 
static int NUM_CHANNELS = 0;
static int IMAGE_QUEUE_SIZE = 100;

typedef struct {
    GstElement *pipeline;
    GstElement *appsink;
    int channel_id;
    time_t last_save_time;
    int frames_stored;
    gboolean running;
    int restart_attempts;  // 재시작 시도 횟수
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

// 현재 시간 밀리초 단위로 반환
double get_current_time_ms() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

static void on_new_sample(GstAppSink *appsink, gpointer user_data) {
    GstSample *sample;
    GstBuffer *buffer;
    GstMapInfo map;
    cv::Mat img;

    sample = gst_app_sink_pull_sample(appsink);
    buffer = gst_sample_get_buffer(sample);

    if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        // GStreamer 캡슐에서 비디오 스트림의 실제 크기를 얻어옴
        GstCaps *caps = gst_sample_get_caps(sample);
        GstStructure *structure = gst_caps_get_structure(caps, 0);
        gint width, height;

        // 구조체에서 비디오 크기 정보 추출
        if (!gst_structure_get_int(structure, "width", &width) ||
            !gst_structure_get_int(structure, "height", &height)) {
            g_print("Failed to get width and height from caps.\n");
            gst_buffer_unmap(buffer, &map);
            gst_sample_unref(sample);
            return;
        }

        gsize expected_size = static_cast<gsize>(width) * height * 3;

        if (map.size == expected_size) {
            img.create(height, width, CV_8UC3);
            memcpy(img.data, map.data, map.size);

            StreamData *stream = (StreamData *)user_data;
            double current_time_ms = get_current_time_ms();

            // 프레임 간격 계산
            double frame_interval = 1000.0 / SAVE_FRAMES_PER_SECOND;  // 1초에 저장할 프레임 간격 (밀리초 단위)
            double time_since_last_save = current_time_ms - stream->last_save_time;

            // 프레임을 균등하게 저장 (초당 지정된 프레임 수만큼)
            if (time_since_last_save >= frame_interval) {
                stream->last_save_time = current_time_ms;

                FrameData frame_data;
                frame_data.image = img.clone();
                frame_data.channel_id = stream->channel_id;
                frame_data.timestamp = static_cast<time_t>(current_time_ms / 1000); // UNIX 타임으로 변환

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

static void restart_pipeline(StreamData *stream) {

    // 기존 파이프라인 정지 및 해제
    if (stream->pipeline) {
        gst_element_set_state(stream->pipeline, GST_STATE_NULL);
        gst_object_unref(stream->pipeline);
        gst_object_unref(stream->appsink);
    }

    while (true) {
        stream->restart_attempts++;
        g_print("Reinitializing pipeline for channel %d, attempt %d\n", stream->channel_id, stream->restart_attempts);

        // 새 파이프라인 생성
        stream->pipeline = create_pipeline(RTSP_URLS[stream->channel_id].c_str());
        if (!stream->pipeline) {
            g_print("Failed to create pipeline for channel %d.\n", stream->channel_id);
            continue;
        }

        stream->appsink = gst_bin_get_by_name(GST_BIN(stream->pipeline), "sink");
        g_signal_connect(stream->appsink, "new-sample", G_CALLBACK(on_new_sample), stream);
        
        GstStateChangeReturn ret = gst_element_set_state(stream->pipeline, GST_STATE_PLAYING);

        // 파이프라인을 실행 상태로 전환
        if (ret == GST_STATE_CHANGE_FAILURE) {
            g_print("Failed to set pipeline to PLAYING for channel %d.\n", stream->channel_id);
            continue;
        } else {
            break;
        }
    }

    stream->restart_attempts = 0;
    g_print("Pipeline restarted successfully for channel %d\n", stream->channel_id);
}

static void* stream_thread(void *arg) {
    StreamData *stream = (StreamData *)arg;
    GstStateChangeReturn ret;
    GstBus *bus;
    GstMessage *msg;

    stream->restart_attempts = 0;

    ret = gst_element_set_state(stream->pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        return NULL;
    }

    bus = gst_element_get_bus(stream->pipeline);

    g_signal_connect(stream->appsink, "new-sample", G_CALLBACK(on_new_sample), stream);

    stream->running = TRUE;
    stream->frames_stored = 0;
    stream->last_save_time = time(NULL);

    while (stream->running) {
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                         (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
        
        if (msg != NULL) {
            GError *err;
            gchar *debug_info;

            switch (GST_MESSAGE_TYPE(msg)) {
                case GST_MESSAGE_ERROR:
                    gst_message_parse_error(msg, &err, &debug_info);
                    g_print("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
                    g_print("Debugging information: %s\n", debug_info ? debug_info : "none");

                    g_clear_error(&err);
                    g_free(debug_info);

                    restart_pipeline(stream);  // 파이프라인 재구성
                    bus = gst_element_get_bus(stream->pipeline);
             
                    break;

                case GST_MESSAGE_EOS:
                    g_print("End of stream for channel %d. Restarting pipeline.\n", stream->channel_id);
                    restart_pipeline(stream);  // 파이프라인 재구성
                    bus = gst_element_get_bus(stream->pipeline);
                  
                    break;

                default:
                    break;
            }
            gst_message_unref(msg);
        }

        usleep(30000);  // 0.03초 대기
    }

    gst_object_unref(bus);
    gst_element_set_state(stream->pipeline, GST_STATE_NULL);
    gst_object_unref(stream->pipeline);
    return NULL;
}

static PyObject* set_stream_config(PyObject* self, PyObject* args) {
    PyObject *url_list;
    PyObject *item;
    Py_ssize_t size;
    int width, height, sfps;

    if (!PyArg_ParseTuple(args, "Oiii", &url_list, &width, &height, &sfps)) {
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
    SAVE_FRAMES_PER_SECOND = sfps;
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