/*
Jisung Lee
jisung@uw.edu
*/

#include "SocketUtils.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>

int CreateSocket(int p) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) throw std::runtime_error("socket failed");

  int opt = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(p);

  if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    close(s);
    throw std::runtime_error("bind failed");
  }
  if (listen(s, 5) < 0) {
    close(s);
    throw std::runtime_error("listen failed");
  }
  return s;
}

int AcceptConnection(int s) {
  struct sockaddr_in caddr;
  socklen_t len = sizeof(caddr);
  int c = accept(s, (struct sockaddr*)&caddr, &len);
  if (c < 0) throw std::runtime_error("accept failed");
  return c;
}

ssize_t ReadAll(int fd, void* b, size_t n) {
  size_t t = 0;
  while (t < n) {
    ssize_t r = read(fd, (char*)b + t, n - t);
    if (r == -1) {
      if (errno == EINTR) continue;
        return -1;
      }
      if (r == 0) break;
      t += r;
  }
  return t;
}