FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Install CA certificates first (required for git clone over HTTPS)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
  && update-ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# Install build tools + raylib dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    vim\
    cmake \
    pkg-config \
    libasound2-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libxcursor-dev \
    libxinerama-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libwayland-dev \
    libxkbcommon-dev \
  && rm -rf /var/lib/apt/lists/*

# Build and install raylib
RUN git clone --depth 1 https://github.com/raysan5/raylib.git /opt/raylib \
  && cmake -S /opt/raylib -B /opt/raylib/build -DBUILD_SHARED_LIBS=ON \
  && cmake --build /opt/raylib/build -j \
  && cmake --install /opt/raylib/build \
  && ldconfig \
  && rm -rf /opt/raylib

WORKDIR /workspace

CMD ["/bin/bash"]
