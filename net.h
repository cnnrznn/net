#ifndef _NET_H
#define _NET_H

int
net_init(char *port);

void
net_fini(void);

ssize_t
net_recv(void *buf, size_t len);

ssize_t
net_sendto(void *buf, size_t len, char *host, char *port);

#endif /* _NET_H */
