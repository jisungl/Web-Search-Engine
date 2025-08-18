/*
Jisung Lee
jisung@uw.edu
*/

#ifndef SOCKETUTILS_H
#define SOCKETUTILS_H

#include <string>
#include <sys/socket.h>

// creates socket
int CreateSocket(int port);

// accepts connection from listening socket
int AcceptConnection(int listen_fd);

// reads count number of bytes from fd into buf
ssize_t ReadAll(int fd, void* buf, size_t count);

#endif // SOCKETUTILS_H