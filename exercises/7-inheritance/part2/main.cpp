#include <iostream>
#include <string_view>

#include "element.hpp"
#include "tetrahedron.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

/**
 * Print the vertices of an element.
 * 
 * @param element The element whose vertices to print.
 */
void printVertices(const Element& element) {
  std::cout << "  vertices: " << std::endl;
  for (const auto& vertex : element.getVertices()) {
    std::cout << "    [ " << vertex.x << ", " << vertex.y << ", " << vertex.z << " ]" << std::endl;
  }
}

/**
 * Print the properties of a triangle.
 * 
 * @param triangle The triangle to print.
 */
void print(const std::string& name, const Triangle& triangle) {
  std::cout << name << ": {" << std::endl;
  std::cout << "  numVertices: " << triangle.getNumVertices() << std::endl;
  std::cout << "  numDims: " << triangle.getNumDims() << std::endl;
  std::cout << "  area: " << triangle.area() << std::endl;
  printVertices(triangle);
  std::cout << "}" << std::endl;
}

/**
 * Print the properties of a tetrahedron.
 * 
 * @param tetrahedron The tetrahedron to print.
 */
void print(const std::string& name, const Tetrahedron& tetrahedron) {
  std::cout << name << ": {" << std::endl;
  std::cout << "  numVertices: " << tetrahedron.getNumVertices() << std::endl;
  std::cout << "  numDims: " << tetrahedron.getNumDims() << std::endl;
  std::cout << "  surfaceArea: " << tetrahedron.surfaceArea() << std::endl;
  std::cout << "  volume: " << tetrahedron.volume() << std::endl;
  printVertices(tetrahedron);
  std::cout << "}" << std::endl;
}

int main() {
  Vertex v1 {0, 0, 0};
  Vertex v2 {0, 3, 0};
  Vertex v3 {4, 0, 0};
  Vertex v4 {0, 0, 5};

  // TODO: Construct a triangle using vertices v1, v2, and v3.
  // Triangle triangle {v1, v2, v3};

  // TODO: Print:
  //   - the number of vertices in the triangle
  //   - the number of dimensions of the triangle
  //   - the area of the triangle  (expected to be 6)
  //   - the vertices of the triangle

  // print("Triangle", triangle);


  // TODO: Construct a tetrahedron using vertices v1, v2, v3, and v4.
  // Tetrahedron tetrahedron {v1, v2, v3, v4};

  // TODO: Print:
  //   - the number of vertices in the tetrahedron
  //   - the number of dimensions of the tetrahedron
  //   - the surface area of the tetrahedron  (expected to be 37.3654)
  //   - the volume of the tetrahedron  (expected to be 10)
  //   - the vertices of the tetrahedron

  // print("Tetrahedron", tetrahedron);
}
