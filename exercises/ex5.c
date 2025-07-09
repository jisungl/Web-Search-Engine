/*
Jisung Lee
jisung@uw.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "NthPrime.h"

int main(int argc, char** argv) {
  int16_t test_cases[] = {1, 5, 10, 20};
  int numTests = sizeof(test_cases) / sizeof(test_cases[0]);
    
  for (int i = 0; i < numTests; i++) {
    int16_t n = test_cases[i];
    int64_t prime = NthPrime(n);
    printf("%" PRId16 "-th prime number: %" PRId64 "\n", n, prime);
  }
    
  return 0;
}