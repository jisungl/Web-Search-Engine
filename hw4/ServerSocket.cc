/*
 * Copyright ©2025 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2025 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

using std::string;

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int *const listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd"
  // and set the ServerSocket data member "listen_sock_fd_"

  // STEP 1:
  addrinfo h;
  memset(&h, 0, sizeof(h));

  // validate family
  if (ai_family != AF_INET && ai_family != AF_INET6 && ai_family != AF_UNSPEC) return false;

  h.ai_family = ai_family;
  h.ai_socktype = SOCK_STREAM;
  h.ai_flags = AI_PASSIVE;
  h.ai_protocol = IPPROTO_TCP;

  // resolve address
  addrinfo *res = nullptr;
  char pbuf[16];
  snprintf(pbuf, sizeof(pbuf), "%d", port_);
  if (getaddrinfo(nullptr, pbuf, &h, &res) != 0) return false;

  int fd = -1;
  for (addrinfo *cur = res; cur != nullptr; cur = cur->ai_next) {
    fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
    if (fd < 0) continue;

    // reuse port
    int opt = 1;
    Verify333(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == 0);

    // bind attempt
    if (bind(fd, cur->ai_addr, cur->ai_addrlen) == 0) {
      sock_family_ = cur->ai_family;
      break;
    }
    close(fd);
    fd = -1;
  }

  freeaddrinfo(res);

  // listen check
  if (fd < 0) return false;
  if (listen(fd, SOMAXCONN) != 0) {
    close(fd);
    return false;
  }

  listen_sock_fd_ = fd;
  *listen_fd = fd;
  return true;
}

bool ServerSocket::Accept(int *const accepted_fd,
                          string *const client_addr,
                          uint16_t *const client_port,
                          string *const client_dns_name,
                          string *const server_addr,
                          string *const server_dns_name) const {
  // STEP 2:
  sockaddr_storage tmp;
  socklen_t tlen = sizeof(tmp);
  sockaddr *sa = reinterpret_cast<sockaddr*>(&tmp);
  int cfd = -1;
  while (1) {
    cfd = accept(listen_sock_fd_, sa, &tlen);
    if (cfd < 0) {
      if (errno == EAGAIN || errno == EINTR) continue;
      return false;
    }
    break;
  }
  if (cfd < 0) return false;
  *accepted_fd = cfd;

  // client address / dns
  if (sa->sa_family == AF_INET) {
    char buf[INET_ADDRSTRLEN];
    auto *in4 = reinterpret_cast<sockaddr_in*>(sa);
    inet_ntop(AF_INET, &(in4->sin_addr), buf, INET_ADDRSTRLEN);
    *client_addr = string(buf);
    *client_port = htons(in4->sin_port);
  } else {
    char buf[INET6_ADDRSTRLEN];
    auto *in6 = reinterpret_cast<sockaddr_in6*>(sa);
    inet_ntop(AF_INET6, &(in6->sin6_addr), buf, INET6_ADDRSTRLEN);
    *client_addr = string(buf);
    *client_port = htons(in6->sin6_port);
  }

  // client dns
  char host[1024];
  Verify333(getnameinfo(sa, tlen, host, sizeof(host), nullptr, 0, 0) == 0);
  *client_dns_name = string(host);

  // server address / dns
  char hbuf[1024];
  hbuf[0] = '\0';
  if (sock_family_ == AF_INET) {
    sockaddr_in srv;
    socklen_t slen = sizeof(srv);
    char abuf[INET_ADDRSTRLEN];
    getsockname(cfd, reinterpret_cast<sockaddr*>(&srv), &slen);
    inet_ntop(AF_INET, &srv.sin_addr, abuf, INET_ADDRSTRLEN);
    getnameinfo(reinterpret_cast<const sockaddr*>(&srv), slen, hbuf, sizeof(hbuf), nullptr, 0, 0);
    *server_addr = string(abuf);
    *server_dns_name = string(hbuf);
  } else {
    sockaddr_in6 srv;
    socklen_t slen = sizeof(srv);
    char abuf[INET6_ADDRSTRLEN];
    getsockname(cfd, reinterpret_cast<sockaddr*>(&srv), &slen);
    inet_ntop(AF_INET6, &srv.sin6_addr, abuf, INET6_ADDRSTRLEN);
    getnameinfo(reinterpret_cast<const sockaddr*>(&srv), slen, hbuf, sizeof(hbuf), nullptr, 0, 0);
    *server_addr = string(abuf);
    *server_dns_name = string(hbuf);
  }

  return true;
}

}  // namespace hw4
