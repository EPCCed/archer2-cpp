#ifndef CPPEX_VECTOR_HPP
#define CPPEX_VECTOR_HPP

#include <cmath>

#include "vertex.hpp"

class Vertex;

/** A three-dimensional vector defined by two vertices.
 *
 * This class represents the vector from one `Vertex` to another and
 * provides common vector operations such as magnitude, dot product,
 * and cross product.
 */
class Vector {
 private:
  /** Construct a vector directly from its components.
   *
   * @param x The X component.
   * @param y The Y component.
   * @param z The Z component.
   */
  Vector(double x, double y, double z);

 public:
  /** X component of the vector. */
  const double x = 0;

  /** Y component of the vector. */
  const double y = 0;

  /** Z component of the vector. */
  const double z = 0;

  /** Construct a vector from two vertices.
   *
   * The resulting vector points from `v1` to `v2`.
   *
   * @param v1 The start vertex.
   * @param v2 The end vertex.
   */
  Vector(Vertex v1, Vertex v2);

  /** Compute the length of the vector.
   *
   * @return The Euclidean magnitude of the vector.
   */
  double magnitude() const;

  /** Compute the cross product with another vector.
   *
   * @param other_vector The vector to cross with.
   * @return A vector perpendicular to both operands.
   */
  Vector cross(Vector other_vector) const;

  /** Compute the dot product with another vector.
   *
   * @param other_vector The vector to dot with.
   * @return The scalar dot product.
   */
  double dot(Vector other_vector) const;
};

#endif
