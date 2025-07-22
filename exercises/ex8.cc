/*
Jisung Lee
jisung@uw.edu
*/

#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

// prints all factors of n in increasing order
void factors(int n) {
  for (int i = 1; i <= n; ++i) {
    if (n % i == 0) {
      cout << i << " ";
    }
  }
  cout << endl;
}

int main() {
  int n;

  cout << "Which positive integer would you like me to factorize? ";
  cin >> n;

  if (!cin) {
    cerr << "input positive integer" << endl;
    return EXIT_FAILURE;
  }

  if (n <= 0) {
    cerr << "input must be positive" << endl;
    return EXIT_FAILURE;
  }

  factors(n);

  return 0;
}