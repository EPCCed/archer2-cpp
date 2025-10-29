#include <vector>

#include "matrix.hpp"
#include "test.hpp"
#include "range.hpp"

morton::matrix<int> make_filled(int N) {
  morton::matrix<int> mat(N);

  // Fill with standard C array layout 1D index
  for (auto i: range(N))
    for (auto j: range(N))
      mat(i, j) = i*N + j;
  return mat;
}

// M = matrix<int> or const matrix<int>
template <int N, typename M>
bool check_mat(M& mat) {
  // Matrix contains:
  //  0  4  8 12
  //  1  5  9 13
  //  2  6 10 14
  //  3  7 11 15

  // This will store the count of elements visited before the current
  // and so should be the Morton index of the element.
  int z = 0;
  auto it = mat.begin();
  for (; it != mat.end(); ++it, ++z) {
    uint32_t i, j;
    morton::decode(z, i, j);
    int expect = i*N + j;
    TEST_ASSERT_EQUAL(expect, *it);

    TEST_ASSERT_EQUAL(i, it.x());
    TEST_ASSERT_EQUAL(j, it.y());
  }
  TEST_ASSERT_EQUAL(N*N, z);

  return true;
}

bool test_mut_iter() {
  constexpr int N = 4;
  auto mat = make_filled(N);
  return check_mat<N>(mat);
}

// Do the same for the const iterator
bool test_const_iter() {
  const int N = 4;
  const morton::matrix<int>& mat = make_filled(N);
  return check_mat<N>(mat);
}

bool test_rev_iter() {
  const int N = 4;
  const morton::matrix<int>& mat = make_filled(N);

  int z = N*N;
  auto it = mat.end();
  for (; it != mat.begin();) {
    // We want to run the below for it == mat.begin() and then finish
    // so move decrement inside the body.
    --it;
    --z;

    uint32_t i, j;
    morton::decode(z, i, j);

    int expect = i*N + j;
    TEST_ASSERT_EQUAL(expect, *it);

    TEST_ASSERT_EQUAL(i, it.x());
    TEST_ASSERT_EQUAL(j, it.y());
  }
  TEST_ASSERT_EQUAL(0, z);
  return true;
}

int main() {
  RUN_TEST(test_mut_iter);
  RUN_TEST(test_const_iter);
  RUN_TEST(test_rev_iter);
  return 0;
}
