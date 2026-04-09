#include <iostream>
#include <string_view>

#include "element.hpp"
#include "tetrahedron.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

int main() {
  Vertex v1 {0, 0, 0};
  Vertex v2 {0, 3, 0};
  Vertex v3 {4, 0, 0};
  Vertex v4 {0, 0, 5};

  // TODO: Construct a triangle using vertices v1, v2, and v3.

  // TODO: Print:
  //   - the number of vertices in the triangle
  //   - the number of dimensions of the triangle
  //   - the area of the triangle  (expected to be 6)
  //   - the vertices of the triangle


  // TODO: Construct a tetrahedron using vertices v1, v2, v3, and v4.

  // TODO: Print:
  //   - the number of vertices in the tetrahedron
  //   - the number of dimensions of the tetrahedron
  //   - the surface area of the tetrahedron  (expected to be 37.3654)
  //   - the volume of the tetrahedron  (expected to be 10)
  //   - the vertices of the tetrahedron
}
