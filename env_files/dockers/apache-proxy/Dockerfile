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
    && apt-get clean

RUN apt-get install -y net-tools nmap curl vim 
#RUN apt-get install -y flex
#RUN apt-get install -y cron

#Install the Apache server
COPY httpd-2.0.45.tar.gz /tmp/
WORKDIR /tmp 
RUN tar xzf httpd-2.0.45.tar.gz && \ 
    cd httpd-2.0.45 && \
    ./configure --prefix=/usr/local/apache2 --enable-proxy --enable-proxy-http --enable-cache --enable-disk-cache --enable-headers&&\
    make && \
    make install
   

# vi /usr/local/apache2/conf/httpd.conf 
# change group #-1 to group nobody
#RUN sed -i "s/Group #-1/Group nobody/g" "/usr/local/apache2/conf/httpd.conf"

RUN groupadd nobody
COPY httpd.conf /usr/local/apache2/conf/

#COPY crontab /tmp/
#RUN crontab /tmp/crontab

COPY index.html.en /usr/local/apache2/htdocs/
# COPY showname /usr/local/apache2/cgi-bin/
RUN mkdir -p /usr/local/apache2/proxy
RUN chown -R nobody:nobody /usr/local/apache2/proxy
RUN chmod 777 /usr/local/apache2/proxy

EXPOSE 8080

#Start apache 
CMD ["/usr/local/apache2/bin/httpd","-DFOREGROUND"]
#ENTRYPOINT ["/usr/local/apache2/bin/apachectl start"]
