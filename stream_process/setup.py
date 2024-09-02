from setuptools import setup, Extension
import subprocess

# Get pkg-config flags for a given package
def get_pkg_config_flags(package_name):
    try:
        compile_flags = subprocess.check_output(['pkg-config', '--cflags', package_name]).decode().strip()
        link_flags = subprocess.check_output(['pkg-config', '--libs', package_name]).decode().strip()
        return compile_flags.split(), link_flags.split()
    except subprocess.CalledProcessError as e:
        print(f"Error with pkg-config: {e}")
        return [], []

# Retrieve compile and link flags
gstreamer_cflags, gstreamer_libs = get_pkg_config_flags('gstreamer-1.0')
glib_cflags, glib_libs = get_pkg_config_flags('glib-2.0')
opencv_cflags, opencv_libs = get_pkg_config_flags('opencv4')
gst_app_cflags, gst_app_libs = get_pkg_config_flags('gstreamer-app-1.0')

# Python does not use pkg-config, manually specify
python_include_dir = '/usr/include/python3.8'
python_lib_dir = '/usr/lib/x86_64-linux-gnu'

# Aggregate all flags
include_dirs = [python_include_dir] + gstreamer_cflags + glib_cflags + opencv_cflags + gst_app_cflags
library_dirs = [python_lib_dir]
libraries = ['gstreamer-1.0', 'gstapp-1.0', 'glib-2.0', 'opencv_core', 'opencv_imgproc', 'opencv_highgui']
extra_link_args = gstreamer_libs + glib_libs + opencv_libs + gst_app_libs + ['-lpython3.8']

module = Extension(
    'stream_processor',
    sources=['stream_processor1.cpp'],
    language='c++',
    include_dirs=include_dirs,
    library_dirs=library_dirs,
    libraries=libraries,
    extra_compile_args=gstreamer_cflags + glib_cflags + opencv_cflags + gst_app_cflags,
    extra_link_args=extra_link_args
)

setup(
    name='stream_processor',
    version='1.0',
    description='Python interface for stream processing',
    ext_modules=[module]
)
