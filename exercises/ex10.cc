#include <iostream>
#include "Vector.h"

using namespace vector333;
using namespace std;

int main() {
  Vector v1;
  Vector v2(1.0, 2.0, 3.0);
  Vector v3(v2);

  cout << "v1: " << v1 << endl;
  cout << "v2: " << v2 << endl;
  cout << "v3: " << v3 << endl;

  // assignment
  Vector v4;
  v4 = v2;
  cout << "v4 assigned to v2: " << v4 << endl;

  // arithmetics
  Vector v5(2.0, -2.0, 4.0);
  Vector v6(1.0, 2.0, 1.0);

  cout << "\narithmetic operations" << endl;
  cout << v5 << " + " << v6 << " = " << (v5 + v6) << endl;
  cout << v5 << " - " << v6 << " = " << (v5 - v6) << endl;
  cout << v5 << " * " << v6 << " = " << (v5 * v6) << endl;

  // multiply
  double k = 5.5;
  cout << "\nscalar multiplication" << endl;
  cout << v5 << " * " << k << " = " << (v5 * k) << endl;
  cout << k << " * " << v5 << " = " << (k * v5) << endl;

  Vector v7(1.0, 1.0, 1.0);
  v7 += v5;
  cout << "\nv += v:" << endl;
  cout << "v7 += " << v5 << " = " << v7 << endl;
  v7 -= v6;
  cout << "v7 -= " << v6 << " = " << v7 << endl;

  return 0;
}