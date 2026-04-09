#include <iostream>

#include "vertex.hpp"

Vertex::Vertex(double x, double y, double z) : x(x), y(y), z(z) {}

Vertex Vertex::add(const Vector& vector) const {
  return Vertex{x + vector.x, y + vector.y, z + vector.z};
}
