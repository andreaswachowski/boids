FROM ubuntu:24.04
# vi: tw=0

# Use this to test out Ubuntu-specific issues when developing on MacOS.
# (Dockerfile.ci is a smaller version for the CI pipeline.)

# From
# https://github.com/banach-space/llvm-tutor/blob/main/Dockerfile_ubuntu_apt:
# As `tzdata` gets installed automatically (AFAIK, Python depends on it), it
# will interrupt the set-up with a question about the time-zone to use. However,
# this is a non-interactive sessions and that won't work. Work around it by
# setting the time-zone here.
ENV TZ=Europe/Berlin
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y \
    sudo \
    git \
    cmake \
    man-db \
    ninja-build \
    build-essential \
    python3-minimal python3-pip \
    vim \
    wget \
    libzstd-dev \
    software-properties-common \
    libspdlog-dev libgtest-dev libcli11-dev \
    && rm -rf /var/lib/apt/lists/* \
    && yes | /usr/bin/unminimize



RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/llvm-snapshot.gpg
RUN apt-add-repository "deb http://apt.llvm.org/noble/ llvm-toolchain-noble-18 main"
RUN apt-get update
RUN apt-get install -y llvm-18 llvm-18-dev llvm-18-tools clang-18
RUN apt-get install -y python3-setuptools cpanminus

WORKDIR /tmp


RUN cpanm Capture::Tiny DateTime Devel::Cover Digest::MD5 File::Spec JSON::XS Memory::Process Module::Load::Conditional Scalar::Util Time::HiRes TimeDate
RUN wget https://github.com/linux-test-project/lcov/releases/download/v2.3/lcov-2.3.tar.gz
RUN tar -xzf lcov-2.3.tar.gz
WORKDIR /tmp/lcov-2.3
RUN make install
RUN lcov --version

RUN echo "set -o vi" >> /root/.bashrc

WORKDIR /boids
COPY . .
ENV PATH="${PATH}:/usr/lib/llvm-18/bin"
RUN echo "export PATH=$PATH:/usr/lib/llvm-18/bin" >> ~/.bashrc
RUN mkdir Debug && cd Debug && cmake -DCMAKE_BUILD_TYPE=Debug ..
RUN cd Debug && CMAKE_BUILD_TYPE=Debug cmake --build .
# RUN cd Debug && CMAKE_BUILD_TYPE=Debug cmake --build . -t coverage
