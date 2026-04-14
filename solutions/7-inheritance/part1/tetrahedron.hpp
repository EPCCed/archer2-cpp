#ifndef CPPEX_TETRAHEDRON_HPP
#define CPPEX_TETRAHEDRON_HPP

#include <iostream>

#include "element.hpp"
#include "triangle.hpp"
#include "vector.hpp"

/**
 * A tetrahedron in three-dimensional space.
 *
 * This class represents a tetrahedron defined by four vertices and provides
 * methods to compute the surface area and volume.
 */
class Tetrahedron : public Element3D {
 public:
  /**
   * Construct a tetrahedron from four vertices.
   *
   * @param v1 The first vertex.
   * @param v2 The second vertex.
   * @param v3 The third vertex.
   * @param v4 The fourth vertex.
   */
  Tetrahedron(Vertex v1, Vertex v2, Vertex v3, Vertex v4) : Element3D({v1, v2, v3, v4}) {}

  /**
   * Get the number of vertices in the tetrahedron.
   *
   * @return 4
   */
  int getNumVertices() const {
    return 4;
  }

  /**
   * Compute the surface area of the tetrahedron.
   *
   * The surface area is calculated as the sum of the areas of the four triangular faces.
   *
   * @return The surface area.
   */
  double surfaceArea() const {
    Triangle ABC{vertices[0], vertices[1], vertices[2]};
    Triangle ABD{vertices[0], vertices[1], vertices[3]};
    Triangle ACD{vertices[0], vertices[2], vertices[3]};
    Triangle BCD{vertices[1], vertices[2], vertices[3]};
    return ABC.area() + ABD.area() + ACD.area() + BCD.area();
  }

  /**
   * Compute the volume of the tetrahedron.
   *
   * The volume is calculated using the scalar triple product formula:
   * 
   * |(AB x AC) . AD| / 6.0
   * 
   * where AB, AC and AD are vectors from the first vertex to the second, third and fourth vertices, respectively.
   *
   * @return The volume.
   */
  double volume() const {
    Vector AB{vertices[0], vertices[1]};
    Vector AC{vertices[0], vertices[2]};
    Vector AD{vertices[0], vertices[3]};
    return abs(AB.cross(AC).dot(AD)) / 6.0;
  }
};

#endif
