#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define FPS 2 // 2 프레임/초
#define IMG_WIDTH 1280
#define IMG_HEIGHT 720
#define NUM_CHANNELS 2
#define IMAGE_COUNT_PER_SECOND 2
#define IMAGE_SAVE_INTERVAL 0.5 // 0.5초 간격으로 이미지 저장

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
    pthread_mutex_t *mutex;
    gboolean running;
} StreamData;

StreamData stream_data[NUM_CHANNELS];
pthread_t threads[NUM_CHANNELS];
pthread_mutex_t lock;

static void on_new_sample(GstAppSink *appsink, gpointer user_data) {
    GstSample *sample;
    GstBuffer *buffer;
    GstMapInfo map;
    cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3); // OpenCV에서 사용하는 이미지 객체
    StreamData *stream = (StreamData *)user_data;

    sample = gst_app_sink_pull_sample(appsink);
    buffer = gst_sample_get_buffer(sample);

    if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        if (map.size == IMG_WIDTH * IMG_HEIGHT * 3) {
            memcpy(img.data, map.data, map.size);

            // 이미지 저장을 위한 시퀀스 번호 계산
            time_t now = time(NULL);
            if (difftime(now, stream->last_save_time) >= IMAGE_SAVE_INTERVAL) {
                // 0.5초가 지났다면 시퀀스 번호 증가
                stream->sequence_number++;
                stream->last_save_time = now;

                char filename[128];
                sprintf(filename, "%d_ch%d_%d.jpg", stream->thread_id, stream->channel_id, stream->sequence_number);
                if (cv::imwrite(filename, img)) {
                    printf("Thread %d, Channel %d: Saved image as %s\n", stream->thread_id, stream->channel_id, filename);
                } else {
                    printf("Thread %d, Channel %d: Failed to save image as %s\n", stream->thread_id, stream->channel_id, filename);
                }
            }
        } else {
            printf("Thread %d, Channel %d: Buffer size mismatch. Expected %d, got %zu\n", 
                   stream->thread_id, stream->channel_id, IMG_WIDTH * IMG_HEIGHT * 3, map.size);
        }

        gst_buffer_unmap(buffer, &map);
    } else {
        g_printerr("Thread %d, Channel %d: Buffer mapping failed.\n", stream->thread_id, stream->channel_id);
    }

    gst_sample_unref(sample);
}

static void *stream_thread(void *arg) {
    StreamData *stream = (StreamData *)arg;
    GstStateChangeReturn ret;

    printf("Thread %d, Channel %d: Starting pipeline...\n", stream->thread_id, stream->channel_id);

    ret = gst_element_set_state(stream->pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Thread %d, Channel %d: Unable to start pipeline.\n", stream->thread_id, stream->channel_id);
        return NULL;
    }

    printf("Thread %d, Channel %d: Connected to appsink signal.\n", stream->thread_id, stream->channel_id);
    
    g_signal_connect(stream->appsink, "new-sample", G_CALLBACK(on_new_sample), stream);

    stream->running = TRUE;
    while (stream->running) {
        usleep(500000); // 0.5초 대기
    }

    gst_element_set_state(stream->pipeline, GST_STATE_NULL);
    return NULL;
}

static GstElement *create_pipeline(const gchar *rtsp_url) {
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

int main() {
    gst_init(NULL, NULL);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_CHANNELS; i++) {
        stream_data[i].channel_id = i;
        stream_data[i].thread_id = i + 1;
        stream_data[i].sequence_number = 0;
        stream_data[i].last_save_time = time(NULL); // 현재 시간으로 초기화
        stream_data[i].mutex = &lock;
        stream_data[i].pipeline = create_pipeline(RTSP_URLS[i]);
        stream_data[i].appsink = gst_bin_get_by_name(GST_BIN(stream_data[i].pipeline), "sink");
        stream_data[i].running = FALSE;

        printf("Creating thread %d for Channel %d...\n", i + 1, i);
        int res = pthread_create(&threads[i], NULL, stream_thread, &stream_data[i]);
        if (res != 0) {
            g_printerr("Thread %d, Channel %d: pthread_create failed with error code %d\n", i + 1, i, res);
            return -1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_CHANNELS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    for (int i = 0; i < NUM_CHANNELS; i++) {
        gst_element_set_state(stream_data[i].pipeline, GST_STATE_NULL);
        gst_object_unref(stream_data[i].pipeline);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}