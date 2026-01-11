FROM ubuntu:24.04

ENV DEBIAN_FRONEND=noninteractive
ENV APACHE_VERSION=2.0.45

RUN apt-get update &&\
    apt-get install -y \
    build-essential \
    libpcre3 \
    libpcre3-dev \
    libxml2-dev \
    tar \
    libtool \ 
    zlib1g-dev \ 
    libsctp-dev \
    libapr1-dev \
    libaprutil1-dev \
    libjpeg-dev \
    libpng-dev \
    libonig-dev \
    net-tools \ 
    nmap \ 
    curl \ 
    vim \ 
    make \ 
    libssl-dev \
    libc-dev \
    libc6-dev \
    libcurl4-openssl-dev \
    iputils-ping \
    tcpdump \ 
    iproute2 \
    gdb \
    && apt-get clean

WORKDIR /tmp 


