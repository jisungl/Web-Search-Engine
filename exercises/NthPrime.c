/*
Jisung Lee
jisung@uw.edu
*/

#include "NthPrime.h"
#include <stdbool.h>
#include <math.h>

// true if n = prime, false otherwise
static bool isPrime(int64_t n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
    
  for (int64_t i = 3; i * i <= n; i += 2) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int64_t NthPrime(int16_t n) {
  if (n == 1) return 2;
    
  int64_t curr = 1;
  int16_t count = 1;
    
  while (count < n) {
    curr += 2;
    if (isPrime(curr)) {
      count++;
    }
  }
    
  return curr;
}