#ifndef CPPEX_TRIANGLE_HPP
#define CPPEX_TRIANGLE_HPP

#include "element.hpp"
#include "vector.hpp"

/**
 * A triangle in two-dimensional space.
 *
 * This class represents a triangle defined by three vertices and provides
 * methods to compute the area.
 */
class Triangle : public Element2D {
 public:
  /**
   * Construct a triangle from three vertices.
   *
   * @param v1 The first vertex.
   * @param v2 The second vertex.
   * @param v3 The third vertex.
   */
  Triangle(Vertex v1, Vertex v2, Vertex v3) : Element2D({v1, v2, v3}) {}

  /**
   * Get the number of vertices in the triangle.
   *
   * @return 3
   */
  int getNumVertices() const override {
    return 3;
  }

  /**
   * Compute the area of the triangle.
   *
   * The area is calculated using the cross product of vectors formed by the vertices:
   * 
   * |AB x AC| / 2.0
   * 
   * where AB and AC are vectors from the first vertex to the second and third vertices, respectively.
   *
   * @return The area of the triangle.
   */
  double area() const override {
    Vector AB{vertices[0], vertices[1]};
    Vector AC{vertices[0], vertices[2]};
    return AB.cross(AC).magnitude() / 2.0;
  }
};

#endif
