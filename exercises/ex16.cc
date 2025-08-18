/*
Jisung Lee
jisung@uw.edu
*/

#include "SocketUtils.h"
#include <iostream>
#include <unistd.h>

const int BUF = 4096;

void handle(int c) {
  char b[BUF];
  while (1) {
    ssize_t r = ReadAll(c, b, BUF);
    if (r <= 0) break;
    if (write(1, b, r) != r) throw std::runtime_error("write failed");
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage error" << "\n";
    return EXIT_FAILURE;
  }
  try {
    int p = std::stoi(argv[1]);
    int s = CreateSocket(p);
    int c = AcceptConnection(s);
    handle(c);
    close(c);
    close(s);
  } catch (const std::exception& e) {
    std::cerr << "error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}