#ifndef CPPEX_TETRAHEDRON_HPP
#define CPPEX_TETRAHEDRON_HPP

#include "element.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include "vertex.hpp"

/**
 * A tetrahedron in three-dimensional space.
 *
 * This class represents a tetrahedron defined by four vertices and provides
 * methods to compute the surface area and volume.
 * 
 * TODO: Implement the Tetrahedron class that inherits from Element3D and provides implementations for the getNumVertices(), surfaceArea() and volume() methods.
 */
class Tetrahedron {

  // TODO: Construct a tetrahedron from four vertices.

  // TODO: Implement the getNumVertices() method to return the number of vertices in the tetrahedron (i.e. 4).

  // TODO: Implement the surfaceArea() method to return the surface area of the tetrahedron.
  // HINT: Use the Triangle class to compute the area of each face of the tetrahedron and sum them up.

  // TODO: Implement the volume() method to return the volume of the tetrahedron.
  // 
  // The volume is calculated using the scalar triple product formula:
  // 
  // |(AB x AC) . AD| / 6.0
  // 
  // where AB, AC and AD are vectors from the first vertex to the second, third and fourth vertices, respectively.
};

#endif
