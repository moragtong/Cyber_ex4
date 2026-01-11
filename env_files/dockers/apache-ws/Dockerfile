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
    ./configure --prefix=/usr/local/apache2 &&\
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
COPY 67607 /usr/local/apache2/htdocs/
RUN chmod -R 644 /usr/local/apache2/htdocs/67607
RUN chown -R nobody:nobody /usr/local/apache2/htdocs/67607

COPY 1 /usr/local/apache2/htdocs
RUN chmod -R 644 /usr/local/apache2/htdocs/1
RUN chown -R nobody:nobody /usr/local/apache2/htdocs/1

COPY 67607.html /usr/local/apache2/htdocs/
RUN chmod -R 644 /usr/local/apache2/htdocs/67607.html
RUN chown -R nobody:nobody /usr/local/apache2/htdocs/67607.html

COPY page_to_poison.html /usr/local/apache2/htdocs/
RUN chmod -R 644 /usr/local/apache2/htdocs/page_to_poison.html
RUN chown -R nobody:nobody /usr/local/apache2/htdocs/page_to_poison.html

COPY poison.html /usr/local/apache2/htdocs/
RUN chmod -R 644 /usr/local/apache2/htdocs/poison.html
RUN chown -R nobody:nobody /usr/local/apache2/htdocs/poison.html

COPY 1.html /usr/local/apache2/htdocs
RUN chmod -R 644 /usr/local/apache2/htdocs/1.html
RUN chown -R nobody:nobody /usr/local/apache2/htdocs/1.html

COPY doomle.html /usr/local/apache2/htdocs/
COPY course_selector /usr/local/apache2/cgi-bin/
RUN chmod -R 755 /usr/local/apache2/cgi-bin/course_selector
RUN chown -R nobody:nobody /usr/local/apache2/cgi-bin/course_selector
COPY showname /usr/local/apache2/cgi-bin/

# Install PHP
#COPY php-5.2.17.tar.gz /tmp/
#WORKDIR /tmp
#RUN tar xzf php-5.2.17.tar.gz && \
#    cd php-5.2.17 && \
#    ls
#    ./configure --disable-all

#    ./configure --with-apxs2=/usr/local/apache2/bin/apxs 
#    make && \
#    make install && \
#    cp php.ini-dist /usr/local/lib/php.ini

#Configure and use PHP
#RUN echo 'LoadModule php5_module modules/libphp5.so' >> /usr/local/#apache2/conf/httpd.conf && \ 
#    echo 'AddHandler php5-script .php' >> /usr/local/apache2/conf/#httpd.conf && \
#    echo 'DirectoryIndex index.php index.html' >> /usr/local/apache2# conf/httpd.conf


EXPOSE 80

#Start apache 
CMD ["/usr/local/apache2/bin/httpd","-DFOREGROUND"]
#ENTRYPOINT ["/usr/local/apache2/bin/apachectl start"]


