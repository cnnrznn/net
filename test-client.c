#include <stddef.h>
#include <stdio.h>

#include "net.h"

#define PORT "3333"
#define BUFLEN 1024

int main()
{
        char buf_send[BUFLEN] = { 0 };
        char buf_recv[BUFLEN] = { 0 };

        net_init(PORT);

        sprintf(buf_send, "Hello from Cambridge!");
        fprintf(stderr, "net_sendto = %ld\n",
                        net_sendto(buf_send, BUFLEN, "35.237.247.180", PORT));

        net_fini();

        return 0;
}
