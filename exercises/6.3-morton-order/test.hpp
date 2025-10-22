#ifndef MORTON_TEST_HPP
#define MORTON_TEST_HPP

#include <iostream>

// A few macros to help with basic unit testing

// (Don't want to introduce any dependencies by using a framework)

#define TEST_ASSERT_EQUAL(expected, actual)			\
  if (expected != actual) {					\
    std::cerr << "FAIL! Expected '" << expected			\
	      << "' Got '" << actual << "'" << std::endl;	\
    return false;						\
  }

// Runs a nullary predicate as a test
#define RUN_TEST(tfunc) if (tfunc())			\
    std::cerr << #tfunc << ": ok" << std::endl;		\
  else							\
    std::cerr << #tfunc << ": FAILED" << std::endl;

#endif
