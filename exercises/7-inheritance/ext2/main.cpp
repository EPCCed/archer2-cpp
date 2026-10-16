#include <iostream>
#include <string>

#include "element.hpp"
#include "tetrahedron.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

void print(const std::string& name, const Tetrahedron& element) {
  std::cout << name << ": {" << std::endl;
  std::cout << "  numVertices: " << element.getNumVertices() << std::endl;
  std::cout << "  numDims: " << element.getNumDims() << std::endl;
  std::cout << "  surfaceArea: " << element.surfaceArea() << std::endl;
  std::cout << "  volume: " << element.volume() << std::endl;
  std::cout << "  vertices: " << std::endl;
  for (const auto& vertex : element.getVertices()) {
    std::cout << "    [ " << vertex.x << ", " << vertex.y << ", " << vertex.z << " ]" << std::endl;
  }
  std::cout << "}" << std::endl;
}

int main() {
  Vertex v1 = Vertex(0, 0, 0);
  Vertex v2 = Vertex(0, 3, 0);
  Vertex v3 = Vertex(4, 0, 0);
  Vertex v4 = Vertex(0, 0, 5);

  Tetrahedron tet1 = Tetrahedron(v1, v2, v3, v4);
  print("Tetrahedron", tet1);
}
