#include <gst/gst.h>
#include <gst/app/gstappsink.h>

GstFlowReturn new_sample_callback(GstElement *appsink, gpointer user_data) {
    GstSample *sample;
    GstBuffer *buffer;
    gsize size;

    // Pull the sample from AppSink
    sample = gst_app_sink_pull_sample(GST_APP_SINK(appsink));
    buffer = gst_sample_get_buffer(sample);

    // Get the size of the buffer
    size = gst_buffer_get_size(buffer);

    // Allocate memory for the data and copy it from the buffer
    guint8 *data = (guint8*)g_malloc(size);
    gst_buffer_extract(buffer, 0, data, size);

    // Process the data here (e.g., save to a file or perform further processing)

    // Free the allocated memory
    g_free(data);

    // Release the sample
    gst_sample_unref(sample);

    return GST_FLOW_OK;
}

int main(int argc, char *argv[]) {
    GstElement *pipeline, *source, *appsink, *rtph264depay, *h264parse, *avdec_h264, *videoconvert, *autovideosink;
    GMainLoop *loop;

    // Initialize GStreamer
    gst_init(&argc, &argv);

    // default pipelin
    // gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/stream ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! autovideosink

    // Create the GStreamer pipeline
    pipeline = gst_pipeline_new("rtsp-pipeline");

    // Create the RTSP source element
    source = gst_element_factory_make("rtspsrc", "rtsp-source");

    // Set the RTSP stream URI
    // g_object_set(G_OBJECT(source), "location", "rtsp://admin:1qkf_086\\!@192.168.10.32:554/Streaming/Channels/101", NULL);
    g_object_set(G_OBJECT(source), "location", "rtsp://127.0.0.1:8554/stream", NULL);

    // // Create the AppSink element
    // appsink = gst_element_factory_make("appsink", "app-sink");

    // Create the additional elements
    rtph264depay = gst_element_factory_make("rtph264depay", "rtph264depay");
    h264parse = gst_element_factory_make("h264parse", "h264parse");
    avdec_h264 = gst_element_factory_make("avdec_h264", "avdec_h264");
    videoconvert = gst_element_factory_make("videoconvert", "videoconvert");
    autovideosink = gst_element_factory_make("autovideosink", "autovideosink");

    // // Configure the AppSink to emit the "new-sample" signal
    // g_object_set(G_OBJECT(appsink), "emit-signals", TRUE, NULL);
    // g_signal_connect(appsink, "new-sample", G_CALLBACK(new_sample_callback), NULL);

    // Add elements to the pipeline
    gst_bin_add(GST_BIN(pipeline), source);
    gst_bin_add(GST_BIN(pipeline), rtph264depay);
    gst_bin_add(GST_BIN(pipeline), h264parse);
    gst_bin_add(GST_BIN(pipeline), avdec_h264);
    gst_bin_add(GST_BIN(pipeline), videoconvert);
    gst_bin_add(GST_BIN(pipeline), autovideosink);
    // gst_bin_add(GST_BIN(pipeline), appsink);

    // Link the elements
    if (!gst_element_link_many(source, rtph264depay, h264parse, avdec_h264, videoconvert, autovideosink, NULL)) {
        g_error("Failed to link elements");
        return -1;
    }

    // Create the GMainLoop
    loop = g_main_loop_new(NULL, FALSE);

    // Set the pipeline state to PLAYING
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Start the GMainLoop
    g_main_loop_run(loop);

    // Clean up
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    g_main_loop_unref(loop);

    return 0;
}