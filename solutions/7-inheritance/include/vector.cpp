#include <cmath>

#include "vector.hpp"

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

Vector::Vector(Vertex v1, Vertex v2) : x(v2.x - v1.x), y(v2.y - v1.y), z(v2.z - v1.z) {}

double Vector::magnitude() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vector Vector::cross(Vector other_vector) const {
  return Vector{
    y * other_vector.z - z * other_vector.y,
    z * other_vector.x - x * other_vector.z,
    x * other_vector.y - y * other_vector.x
  };
}

double Vector::dot(Vector other_vector) const {
  return x * other_vector.x + y * other_vector.y + z * other_vector.z;
}
