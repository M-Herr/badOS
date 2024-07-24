FROM ubuntu:20.04


ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    clang \
    llvm \
    lld \
    nasm \
    qemu \
    git \
    wget \
    curl \
    xz-utils \
    bzip2 \
    make \
    autoconf \
    automake \
    libtool \
    texinfo \
    grub-common \
    grub-pc-bin \
    grub-efi-amd64-bin \
    xorriso \
    mtools

VOLUME /root/env
WORKDIR /root/env

# Default command to run when the container starts
CMD ["/bin/bash"]


