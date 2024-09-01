#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// 스트림을 위한 데이터 구조체
typedef struct {
    GstElement *pipeline;
    GstElement *sink;
} StreamData;

// 프레임을 처리하는 함수
void* process_stream(void* arg) {
    StreamData *data = (StreamData*)arg;
    GstSample *sample;

    while (TRUE) {
        sample = gst_app_sink_pull_sample(GST_APP_SINK(data->sink));
        if (sample) {
            // 여기서 프레임을 처리합니다.
            printf("Frame received from stream\n");

            gst_sample_unref(sample);
        }

        // 0.5초 대기 -> 1초에 2프레임
        usleep(500000);
    }

    return NULL;
}

// 파이프라인 생성 및 RTSP 스트리밍 처리
StreamData* create_rtsp_pipeline(const char* rtsp_url) {
    GstElement *pipeline, *src, *depay, *decode, *conv, *sink;
    GstCaps *caps;

    // 파이프라인 생성
    pipeline = gst_pipeline_new(NULL);
    src = gst_element_factory_make("rtspsrc", "source");
    depay = gst_element_factory_make("rtph264depay", "depay");
    decode = gst_element_factory_make("avdec_h264", "decode");
    conv = gst_element_factory_make("videoconvert", "conv");
    sink = gst_element_factory_make("appsink", "sink");

    if (!pipeline || !src || !depay || !decode || !conv || !sink) {
        g_printerr("Failed to create elements\n");
        return NULL;
    }

    // 파이프라인에 요소들을 추가
    gst_bin_add_many(GST_BIN(pipeline), src, depay, decode, conv, sink, NULL);

    // 요소들 연결
    if (!gst_element_link_many(depay, decode, conv, sink, NULL)) {
        g_printerr("Failed to link elements\n");
        return NULL;
    }

    // 소스 설정
    g_object_set(src, "location", rtsp_url, NULL);
    g_signal_connect(src, "pad-added", G_CALLBACK(gst_element_link_pads), depay);

    // appsink 설정
    caps = gst_caps_new_simple("video/x-raw", "format", G_TYPE_STRING, "RGB", NULL);
    g_object_set(sink, "caps", caps, "emit-signals", TRUE, "sync", FALSE, NULL);
    gst_caps_unref(caps);

    // 파이프라인을 재생 상태로 설정
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // StreamData 구조체 생성 및 반환
    StreamData *data = g_new0(StreamData, 1);
    data->pipeline = pipeline;
    data->sink = sink;

    return data;
}

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    // RTSP URL 설정
    const char *rtsp_url1 = "rtsp://127.0.0.1:8554/stream";
    const char *rtsp_url2 = "rtsp://127.0.0.1:8562/stream";

    // 파이프라인 생성
    StreamData *stream1 = create_rtsp_pipeline(rtsp_url1);
    StreamData *stream2 = create_rtsp_pipeline(rtsp_url2);

    if (!stream1 || !stream2) {
        g_printerr("Failed to create RTSP pipelines\n");
        return -1;
    }

    // 쓰레드 생성
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, process_stream, stream1);
    pthread_create(&thread2, NULL, process_stream, stream2);

    // 메인 루프 대기
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 파이프라인 정리
    gst_element_set_state(stream1->pipeline, GST_STATE_NULL);
    gst_element_set_state(stream2->pipeline, GST_STATE_NULL);

    gst_object_unref(stream1->pipeline);
    gst_object_unref(stream2->pipeline);

    g_free(stream1);
    g_free(stream2);

    gst_deinit();

    return 0;
}
