#ifndef MORTON_MATRIX_HPP
#define MORTON_MATRIX_HPP

#include <cassert>
#include <memory>
#include <iterator>
#include <type_traits>
#include "bits.hpp"

namespace morton {
  // Forward declare the iterator template
  template<class T> class matrix_iterator;
  
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
    using iterator = matrix_iterator<T>;
    using const_iterator = matrix_iterator<const T>;
    
    matrix() : _rank(0) {
    }
    
    matrix(uint32_t r) : _rank(r), _data(new T[r*r]) {
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
      std::copy(begin(), end(), ans.begin());
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

    // TODO: implement functions to get iterators to first and
    //        just-past-the-last elements in the matrix
    // Mutable iterators
    iterator begin() {
    }
    iterator end() {
    }

    // TODO: as above, but const
    // Const iterators
    const_iterator begin() const {
    }
    const_iterator end() const {
    }

  private:
    // rank of matrix
    uint32_t _rank;
    // Data storage
    // Note using array version of unique_ptr
    std::unique_ptr<T[]> _data;
  };

  // Note we inherit from std::iterator<stuff>.
  // This basically ensures our iterator has the right traits to work
  // efficiently with the standard library.
  // See http://en.cppreference.com/w/cpp/iterator/iterator

  // I've decided this should be a bidirectional iterator - i.e. you
  // can move back and forwards. You only need to implement a handful
  // of the methods, the rest follow from code I've done.

  // It could relatively easily be changed to a random access iterator
  // by adding a few more operations - see:
  // https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
  template<class T>
  class matrix_iterator :
    public std::iterator<std::bidirectional_iterator_tag,
			 T, int64_t, T*, T&> {
  public:
    // TODO
    // Default constructor
    matrix_iterator();

    // Note: must provide copy c'tor, copy assign
    // TODO: Decide if the default copy/move/destruct behaviour is
    //       going to be OK.
    
    // TODO
    // Get the x/y coordinates of the current element
    uint32_t x() const {
    }
    uint32_t y() const {
    }
    
    // Comparison operators. Note these are inline non-member friend
    // functions.
    friend bool operator==(const matrix_iterator& a, const matrix_iterator& b) {
      // TODO
    }
    // Note this can be done in terms of the above
    friend bool operator!=(const matrix_iterator& a, const matrix_iterator& b) {
      return !(a == b);
    }

    // Dereference operator
    T& operator*() {
      // TODO
    }

    // Preincrement operator
    matrix_iterator& operator++() {
      // TODO
    }
    // TODO
    // Predecrement operator
    matrix_iterator& operator--() {
      // TODO
    }      
    
  private:
    // TODO: declare and define appropriate constructor(s) to create
    //       iterators pointing into a matrix's data.
    // matrix_iterator(...);

    // Other constructors should probably not be publicly visible, so
    // we need to allow matrix<T> access.
    friend matrix<typename std::remove_const<T>::type>;

    // TODO: Define data members as needed

  };

}
#endif
