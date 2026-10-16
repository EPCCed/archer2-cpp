#ifndef CPPEX_TRIANGLE_HPP
#define CPPEX_TRIANGLE_HPP

#include "element.hpp"
#include "vector.hpp"
#include "vertex.hpp"

/**
 * A triangle in two-dimensional space.
 *
 * This class represents a triangle defined by three vertices and provides
 * methods to compute the area.
 * 
 * TODO: Implement the Triangle class that inherits from Element2D and provides implementations for the getNumVertices() and area() methods.
 */
class Triangle {

  // TODO: Construct a triangle from three vertices.

  // TODO: Implement the getNumVertices() method to return the number of vertices in the triangle (i.e. 3).

  // TODO: Implement the area() method to return the area of the triangle.
  //
  // The area is calculated using the cross product of vectors formed by the vertices:
  //
  // |AB x AC| / 2.0
  //
  // where AB and AC are vectors from the first vertex to the second and third vertices, respectively.
};

#endif
