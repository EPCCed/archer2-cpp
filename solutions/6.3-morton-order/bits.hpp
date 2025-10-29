#ifndef MORTON_BITS_HPP
#define MORTON_BITS_HPP
#include <cstdint>

namespace morton {
  // Go from bit pattern like
  //       abcd
  // to:
  //   0a0b0c0d
  inline uint64_t split(const uint32_t a) {
    uint64_t x = a;
    x = (x | x << 16) & 0x0000ffff0000ffffUL;
    x = (x | x <<  8) & 0x00ff00ff00ff00ffUL;
    x = (x | x <<  4) & 0x0f0f0f0f0f0f0f0fUL;
    x = (x | x <<  2) & 0x3333333333333333UL;
    x = (x | x <<  1) & 0x5555555555555555UL;
    return x;
  }

  // Reverse the above
  inline uint32_t pack(const uint64_t z) {
    uint64_t x = z;
    x &= 0x5555555555555555UL;
    x = x >> 1 | x;
    x &= 0x3333333333333333UL;
    x = x >> 2 | x;
    x &= 0x0f0f0f0f0f0f0f0fUL;
    x = x >> 4 | x;
    x &= 0x00ff00ff00ff00ffUL;
    x = x >> 8 | x;
    x &= 0x0000ffff0000ffffUL;
    x = x >> 16| x;
    return x;
  }

  // Compute the 2d Morton code for a pair of indices
  inline uint64_t encode(const uint32_t x, const uint32_t y) {
    return split(x) | split(y) << 1;
  }

  // Compute the 2 indices from a Morton index
  inline void decode(const uint64_t z, uint32_t& x, uint32_t& y) {
    uint64_t i = z;
    x = pack(i);
    uint64_t j = z >> 1;
    y = pack(j);
  }

  const uint64_t odd_bit_mask = 0x5555555555555555UL;
  const uint64_t even_bit_mask = 0xaaaaaaaaaaaaaaaaUL;

  // Move from (i, j) -> (i - 1, j)
  inline uint64_t dec_x(const uint64_t z) {
    return (((z & odd_bit_mask) - 1) & odd_bit_mask) | (z & even_bit_mask);
  }
  // Move from (i, j) -> (i + 1, j)
  inline uint64_t inc_x(const uint64_t z) {
    return (((z | even_bit_mask) + 1) & odd_bit_mask) | (z & even_bit_mask);
  }

  // Move from (i, j) -> (i, j - 1)
  inline uint64_t dec_y(const uint64_t z) {
    return (z & odd_bit_mask) | (((z & even_bit_mask) - 1) & even_bit_mask);
  }
  // Move from (i, j) -> (i, j + 1)
  inline uint64_t inc_y(const uint64_t z) {
    return (z & odd_bit_mask) | (((z | odd_bit_mask) + 1) & even_bit_mask);
  }

}
#endif
