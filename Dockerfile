ARG CUDA="11.7.1"
ARG CUDNN="8"
ARG TYPE="devel"
ARG VERSION="20.04"


FROM nvidia/cuda:${CUDA}-cudnn${CUDNN}-${TYPE}-ubuntu${VERSION}

ARG TZ=Asia/Seoul
ENV TZ=$TZ
ENV GSTREAMER /workspace/

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive \
    && apt-get -y --no-install-recommends install \
    # 런타임 라이브러리 및 실행 파일
    libgstreamer1.0-0 \
    libgstreamer-plugins-base1.0-0 \
    libgstreamer-plugins-bad1.0-0 \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-base-apps \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-libav \
    gstreamer1.0-tools \
    # 개발용 헤더파일
    libgstreamer1.0-dev \
    libglib2.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer-plugins-good1.0-dev \
    libgstreamer-plugins-bad1.0-dev \
    # 디버깅용 심볼파일
    libgstreamer1.0-0-dbg \
    gstreamer1.0-plugins-base-dbg \
    gstreamer1.0-plugins-good-dbg \
    gstreamer1.0-plugins-ugly-dbg \
    gstreamer1.0-plugins-bad-dbg \
    gstreamer1.0-libav-dbg \
    # 기타 유틸파일
    gstreamer1.0-alsa gstreamer1.0-gl \
    gstreamer1.0-gtk3 gstreamer1.0-qt5 \
    gstreamer1.0-pulseaudio \
    build-essential manpages-dev vim wget curl git python3-pip \
    pkg-config ninja-build flex bison equivs devscripts gdb \
    python3-dev python-dev

RUN python3 -m pip install meson
RUN pip install cmake==3.27.2 numpy


WORKDIR ${GSTREAMER}