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

        net_recv(buf_recv, BUFLEN);

        fprintf(stdout, "Result: %s\n", buf_recv);

        net_fini();

        return 0;
}
