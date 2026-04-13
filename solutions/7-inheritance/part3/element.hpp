#ifndef CPPEX_ELEMENT_HPP
#define CPPEX_ELEMENT_HPP

#include <vector>

#include "vertex.hpp"

/**
 * Base class for geometric elements defined by a set of vertices.
 */
class Element {
 protected:
  std::vector<Vertex> vertices;

  /**
   * Construct an element from a vector of vertices.
   *
   * @param vertices The vertices that define the element.
   */
  Element(std::vector<Vertex> vertices) : vertices(vertices) {}

 public:
  /**
   * Get the number of vertices in the element.
   *
   * @return The number of vertices.
   */
  virtual int getNumVertices() const = 0;

  /**
   * Get the number of dimensions of the element.
   *
   * @return The number of dimensions.
   */
  virtual int getNumDims() const = 0;

  /**
   * Get the vertices of the element.
   *
   * @return A constant reference to the vector of vertices.
   */
  const std::vector<Vertex>& getVertices() const {
    return vertices;
  }
};

/**
 * Base class for 2D geometric elements.
 */
class Element2D : public Element {
 protected:
  /**
   * Construct a 2D element from a vector of vertices.
   *
   * @param vertices The vertices that define the 2D element.
   */
  Element2D(std::vector<Vertex> vertices) : Element(vertices) {}

 public:
  /**
   * Get the number of dimensions (always 2 for 2D elements).
   *
   * @return 2
   */
  int getNumDims() const {
    return 2;
  }

  /**
   * Compute the area of the 2D element.
   *
   * @return The area of the element.
   */
  virtual double area() const = 0;
};

/**
 * Base class for 3D geometric elements.
 */
class Element3D : public Element {
 protected:
  /**
   * Construct a 3D element from a vector of vertices.
   *
   * @param vertices The vertices that define the 3D element.
   */
  Element3D(std::vector<Vertex> vertices) : Element(vertices) {}

 public:
  /**
   * Get the number of dimensions (always 3 for 3D elements).
   *
   * @return 3
   */
  int getNumDims() const {
    return 3;
  }

  /**
   * Compute the surface area of the 3D element.
   *
   * @return The surface area of the element.
   */
  virtual double surfaceArea() const = 0;

  /**
   * Compute the volume of the 3D element.
   *
   * @return The volume of the element.
   */
  virtual double volume() const = 0;
};

#endif
