#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net.h"

static int sk;
static struct sockaddr addr;
static socklen_t addrlen;

int
net_init(char *port)
{
        int status;
        struct addrinfo hints;
        struct addrinfo *res;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;

        if ((status = getaddrinfo(NULL, port, &hints, &res)) != 0) {
                // TODO print something?
                goto err_addrinfo;
        }

        fprintf(stderr, "getaddrinfo returned %s\n",
                        inet_ntoa(((struct sockaddr_in *)res->ai_addr)->sin_addr));

        addr = *(res->ai_addr);
        addrlen = res->ai_addrlen;

        freeaddrinfo(res);

        if ((sk = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                // TODO print something?
                goto err_socket;
        }
        if (-1 == (bind(sk, &addr, addrlen))) {
                // TODO print something?
                goto err_bind;
        }

        return 0;

err_bind:
err_socket:
err_addrinfo:

        return -1;
}

void
net_fini(void)
{
        if (sk >= 0)
                close(sk);
}

ssize_t
net_recv(void *buf, size_t len)
{
        ssize_t n;
        struct sockaddr_storage from;
        socklen_t fromlen;

        n = recvfrom(sk, buf, len, 0, (struct sockaddr *)&from, &fromlen);

        return n;
}

ssize_t
net_sendto(void *buf, size_t len, char *host, char *port)
{
        ssize_t n;
        int status;
        struct addrinfo hints, *dest;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;

        if ((status = getaddrinfo(host, port, &hints, &dest)) != 0) {
                fprintf(stderr, "Fail at %s:%d\n", __FILE__, __LINE__);
                goto err_addrinfo;
        }

        n = sendto(sk, buf, len, 0, dest->ai_addr, dest->ai_addrlen);

        freeaddrinfo(dest);

        if (n != len) {
                perror("Sending udp packet");
                return -1;
        }
        return 0;

err_addrinfo:
        return -1;
}
