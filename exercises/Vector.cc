#include "Vector.h"

namespace vector333 {

// constructor
Vector::Vector() {
  data_ = new double[3];
  data_[0] = 0;
  data_[1] = 0;
  data_[2] = 0;
}

// constructor w/ parameters
Vector::Vector(const double x, const double y, const double z) {
  data_ = new double[3];
  data_[0] = x;
  data_[1] = y;
  data_[2] = z;
}

// copy constructor
Vector::Vector(const Vector &v) {
  data_ = new double[3];
  data_[0] = v.data_[0];
  data_[1] = v.data_[1];
  data_[2] = v.data_[2];
}

// destructor
Vector::~Vector() {
  delete[] data_;
}

// assignment operator
Vector &Vector::operator=(const Vector &v) {
  if (this != &v) {
    data_[0] = v.data_[0];
    data_[1] = v.data_[1];
    data_[2] = v.data_[2];
  }
  return *this;
}

// addition
Vector &Vector::operator+=(const Vector &v) {
  data_[0] += v.data_[0];
  data_[1] += v.data_[1];
  data_[2] += v.data_[2];
  return *this;
}

// subtraction
Vector &Vector::operator-=(const Vector &v) {
  data_[0] -= v.data_[0];
  data_[1] -= v.data_[1];
  data_[2] -= v.data_[2];
  return *this;
}

// vector addition
Vector Vector::operator+(const Vector &v) const {
  return Vector(data_[0] + v.data_[0], data_[1] + v.data_[1], data_[2] + v.data_[2]);
}

// vector subtraction
Vector Vector::operator-(const Vector &v) const {
  return Vector(data_[0] - v.data_[0], data_[1] - v.data_[1], data_[2] - v.data_[2]);
}

// dot product
double operator*(const Vector &a, const Vector &b) {
  return a.data_[0] * b.data_[0] + a.data_[1] * b.data_[1] + a.data_[2] * b.data_[2];
}

// vector * double
Vector operator*(const Vector &v, const double c) {
  return Vector(v.data_[0] * c, v.data_[1] * c, v.data_[2] * c);
}

// double * vector
Vector operator*(const double c, const Vector &v) {
  return v * c;
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
  out << "(" << v.data_[0] << "," << v.data_[1] << "," << v.data_[2] << ")";
  return out;
}

}  // namespace vector333