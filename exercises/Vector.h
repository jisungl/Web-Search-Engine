#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

namespace vector333 {

class Vector {
 public:
  // constructors
  Vector();
  Vector(const double x, const double y, const double z);
  Vector(const Vector &v);

  // destructor
  ~Vector();

  // assignment operators
  Vector &operator=(const Vector &v);
  Vector &operator+=(const Vector &v);
  Vector &operator-=(const Vector &v);

  // arithmetic operators
  Vector operator+(const Vector &v) const;
  Vector operator-(const Vector &v) const;

  friend double operator*(const Vector &a, const Vector &b);  // dot product
  friend Vector operator*(const Vector &v, const double k);   // scalar mult
  friend Vector operator*(const double k, const Vector &v);
  friend std::ostream &operator<<(std::ostream &out, const Vector &v);

 private:
  double *data_;
};

}  // namespace vector333

#endif  // VECTOR_H