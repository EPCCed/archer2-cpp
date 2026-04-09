#ifndef CPPEX_ELEMENT_HPP
#define CPPEX_ELEMENT_HPP

#include <vector>

#include "vertex.hpp"

class Element {
 protected:
  std::vector<Vertex> vertices;
  Element(std::vector<Vertex> vertices) : vertices(vertices) {}

 public:
  /**
   * Get the number of vertices in the element.
   *
   * @return The number of vertices.
   */
  int getNumVertices() const {
    // We could return the size of the vertices vector here, but since this is a base class and we
    // expect derived classes to have a fixed number of vertices, we'll return 0 and leave this for
    // them to override for now.
    return 0;
  }

  /**
   * Get the number of dimensions of the element.
   *
   * @return The number of dimensions.
   */
  int getNumDims() const { return 0; }

  /**
   * Get the vertices of the element.
   *
   * @return A constant reference to the vector of vertices.
   */
  const std::vector<Vertex>& getVertices() const { return vertices; }
};

/**
 * Base class for 2D geometric elements.
 */
class Element2D : public Element {
 protected:
  Element2D(std::vector<Vertex> vertices) : Element(vertices) {}

 public:
  int getNumDims() const { return 2; }

  double area() const {
    return 0;
  };
};

/**
 * Base class for 3D geometric elements.
 */
class Element3D : public Element {
 protected:
  Element3D(std::vector<Vertex> vertices) : Element(vertices) {}

 public:
  int getNumDims() const { return 3; }

  double surfaceArea() const {
    return 0;
  }

  double volume() const {
    return 0;
  }
};

#endif
