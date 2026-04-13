#include <iostream>
#include <string>

#include "element.hpp"
#include "tetrahedron.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

void printVertices(const Element& element) {
  std::cout << "  vertices: " << std::endl;
  for (const auto& vertex : element.getVertices()) {
    std::cout << "    [ " << vertex.x << ", " << vertex.y << ", " << vertex.z << " ]" << std::endl;
  }
}

void print(const std::string& name, const Triangle& element) {
  std::cout << name << ": {" << std::endl;
  std::cout << "  numVertices: " << element.getNumVertices() << std::endl;
  std::cout << "  numDims: " << element.getNumDims() << std::endl;
  std::cout << "  area: " << element.area() << std::endl;
  printVertices(element);
  std::cout << "}" << std::endl;
}

void print(const std::string& name, const Tetrahedron& element) {
  std::cout << name << ": {" << std::endl;
  std::cout << "  numVertices: " << element.getNumVertices() << std::endl;
  std::cout << "  numDims: " << element.getNumDims() << std::endl;
  std::cout << "  surfaceArea: " << element.surfaceArea() << std::endl;
  std::cout << "  volume: " << element.volume() << std::endl;
  std::cout << "  material: " << element.describe() << std::endl;
  printVertices(element);
  std::cout << "}" << std::endl;
}

int main() {
  Vertex v1 {0, 0, 0};
  Vertex v2 {0, 3, 0};
  Vertex v3 {4, 0, 0};
  Vertex v4 {0, 0, 5};

  Triangle triangle {v1, v2, v3};
  print("Triangle", triangle);

  Material steel {"Steel", 7850};
  Tetrahedron tetrahedron {v1, v2, v3, v4, steel};
  print("Tetrahedron", tetrahedron);
}
