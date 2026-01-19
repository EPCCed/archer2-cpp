#ifndef MORTON_MATRIX_HPP
#define MORTON_MATRIX_HPP

#include <cassert>
#include "bits.hpp"

namespace morton {

  // 2D square matrix that stores data in Morton order
  //
  // NB:
  // 
  //  - This simple implementation requires that the size be a power
  //    of 2 (or zero indicating an empty matrix)
  // 
  //  - The matrix does not need to be resizeable
  //
  //  - The matrix must not be implicitly copiable, must use explicit
  //    duplicate member function
  template<class T>
  class matrix {
  public:
    // TODO - anything needed?
    matrix() : _rank(0) {
    }

    // TODO - allocate some memory
    matrix(uint32_t r)
    {
      // Check it's a power of 2. Could consider throwing an
      // exception, but these are not in the syllabus!
      assert((r & (r-1)) == 0);
    }

    // Implicit copying is not allowed
    matrix(const matrix& other) = delete;
    matrix& operator=(const matrix& other) = delete;

    // Moving is allowed
    // TODO - will the default implementations be OK?
    matrix(matrix&& other) noexcept;
    matrix& operator=(matrix&& other) noexcept;

    // Destructor
    // TODO - will the default implemenation be OK?
    ~matrix();

    // Create a new matrix with contents copied from this one
    matrix duplicate() const {
      // TODO
    }

    // Get rank size
    uint32_t rank() const {
      return _rank;
    }

    // Get total size
    uint64_t size() const {
      return uint64_t(_rank) * uint64_t(_rank);
    }

    // TODO
    // Const element access
    const T& operator()(uint32_t i, uint32_t j) const;

    // TODO
    // Mutable element access
    T& operator()(uint32_t i, uint32_t j);

    // TODO
    // Raw data access (const and mutable versions)
    const T* data() const;
    T* data();

    
  private:
    // rank of matrix
    uint32_t _rank;
    // Data storage
    // TODO - choose how to store data and manage that memory
  };
  
}
#endif
