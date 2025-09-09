FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

# Install ARM GCC toolchain and utilities
RUN apt-get update && apt-get install -y \
    gcc-arm-none-eabi \
    gdb-arm-none-eabi \
    make \
    cmake \
    openocd \
    build-essential \
    git \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . /workspace

CMD ["sh", "-c", "make clean && make"]
