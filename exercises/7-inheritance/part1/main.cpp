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
 * Print the properties of a 2D element.
 * 
 * @param element The element to print.
 */
void print(const std::string& name, const Element2D& element) {
  std::cout << name << ": {" << std::endl;
  std::cout << "  numVertices: " << element.getNumVertices() << std::endl;
  std::cout << "  numDims: " << element.getNumDims() << std::endl;
  std::cout << "  area: " << element.area() << std::endl;
  printVertices(element);
  std::cout << "}" << std::endl;
}

/**
 * Print the properties of a 3D element.
 * 
 * @param tetrahedron The element to print.
 */
void print(const std::string& name, const Element3D& element) {
  std::cout << name << ": {" << std::endl;
  std::cout << "  numVertices: " << element.getNumVertices() << std::endl;
  std::cout << "  numDims: " << element.getNumDims() << std::endl;
  std::cout << "  surfaceArea: " << element.surfaceArea() << std::endl;
  std::cout << "  volume: " << element.volume() << std::endl;
  printVertices(element);
  std::cout << "}" << std::endl;
}

int main() {
  Vertex v1 {0, 0, 0};
  Vertex v2 {0, 3, 0};
  Vertex v3 {4, 0, 0};
  Vertex v4 {0, 0, 5};

  // TODO: Construct a 2D element using vertices v1, v2, and v3.
  // Element2D element2d {{v1, v2, v3}};

  // TODO: Print:
  //   - the number of vertices in the 2D element
  //   - the number of dimensions of the 2D element
  //   - the area of the 2D element  (expected to be 0)
  //   - the vertices of the 2D element

  // print("2D Element", element2d);


  // TODO: Construct a 3D element using vertices v1, v2, v3, and v4.
  // Element3D element3d {{v1, v2, v3, v4}};

  // TODO: Print:
  //   - the number of vertices in the 3D element
  //   - the number of dimensions of the 3D element
  //   - the surface area of the 3D element  (expected to be 0)
  //   - the volume of the 3D element  (expected to be 0)
  //   - the vertices of the 3D element

  // print("3D Element", element3d);
}
