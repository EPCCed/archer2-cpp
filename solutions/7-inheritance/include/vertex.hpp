#ifndef CPPEX_VERTEX_HPP
#define CPPEX_VERTEX_HPP

#include <iostream>

#include "vector.hpp"

class Vector;

/**
 * A point in three-dimensional space.
 *
 * This class represents a vertex with x, y, and z coordinates.
 */
class Vertex {
 public:
  /** The X coordinate of the vertex. */
  const double x = 0;

  /** The Y coordinate of the vertex. */
  const double y = 0;

  /** The Z coordinate of the vertex. */
  const double z = 0;

  /**
   * Construct a vertex at the specified coordinates.
   *
   * @param x The X coordinate.
   * @param y The Y coordinate.
   * @param z The Z coordinate.
   */
  Vertex(double x, double y, double z);

  /**
   * Add a vector to this vertex to produce a new vertex.
   *
   * @param vector The vector to add to this vertex.
   * @return The new vertex.
   */
  Vertex add(const Vector& vector) const;
};

#endif
