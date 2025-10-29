#ifndef MORTON_MATRIX_HPP
#define MORTON_MATRIX_HPP

#include <cassert>
#include <memory>
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
    // Default initialisation of unique_ptr is OK
    matrix() : _rank(0) {
    }

    matrix(uint32_t r)
      : _rank(r), _data(new T[r*r]) 
    {
      // Check it's a power of 2. Could consider throwing an
      // exception, but these are not in the syllabus!
      assert((r & (r-1)) == 0);
    }

    // Implicit copying is not allowed
    matrix(const matrix& other) = delete;
    matrix& operator=(const matrix& other) = delete;

    // Moving is allowed
    // Default is ok because of choice to use unique_ptr to manage data storage
    matrix(matrix&& other) noexcept = default;
    matrix& operator=(matrix&& other) noexcept = default;

    // Destructor
    // Default ok because of unique_ptr
    ~matrix() = default;

    // Create a new matrix with contents copied from this one
    matrix duplicate() const {
      matrix ans(_rank);
      std::copy(data(), data() + size(), ans.data.get());
      return ans;
    }

    // Get rank size
    uint32_t rank() const {
      return _rank;
    }

    // Get total size
    uint64_t size() const {
      return uint64_t(_rank) * uint64_t(_rank);
    }

    // Const element access
    const T& operator()(uint32_t i, uint32_t j) const {
      auto z = encode(i, j);
      return _data[z];
    }

    // Mutable element access
    T& operator()(uint32_t i, uint32_t j) {
      auto z = encode(i, j);
      return _data[z];
    }

    // Raw data access (const and mutable versions)
    const T* data() const {
      return _data.get();
    }
    T* data() {
      return _data.get();
    }

    
  private:
    // rank of matrix
    uint32_t _rank;
    // Data storage
    // Note using array version of unique_ptr
    std::unique_ptr<T[]> _data;
  };
  
}
#endif
