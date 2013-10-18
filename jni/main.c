#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define REQUEST "GET http://karr.yath.de/~yath/clock.cgi HTTP/1.1\r\n" \
                "Host: karr.yath.de\r\n" \
                "User-Agent: foo\r\n\r\n"

#define error(fmt...) do { fprintf(stderr, ##fmt); _exit(1); } while(0)
int main(int argc, char **argv) {
    int sock;
    struct sockaddr_in sa;
    char buf[4096];
    int port;
    int ret;

    if (argc != 3)
        error("Usage: $0 <addr> <port>\n", argv[0]);

    printf("creating socket\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sa.sin_family = AF_INET;
    if (!(port = atoi(argv[2])))
        error("Invalid port\n");
    sa.sin_port = htons(port);
    if (!inet_pton(AF_INET, argv[1], &sa.sin_addr))
        error("Invalid address\n");

    printf("connecting\n");
    if (connect(sock, &sa, sizeof(sa)) < 0)
        error("Unable to connect: %s\n", strerror(errno));
   
    printf("writing\n");
    ret = write(sock, REQUEST, sizeof(REQUEST)-1);
    if (ret < 0)
        error("write error: %s\n", strerror(errno));

    if (ret != sizeof(REQUEST)-1)
        error("short write (%d)\n", ret);

    printf("reading\n");
    while ((ret = read(sock, buf, sizeof(buf))) > 0) {
        write(1, buf, ret);
    }

    if (ret < 0)
        error("Read error: %s\n", strerror(errno));

    return 0;
}
