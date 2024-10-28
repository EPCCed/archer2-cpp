// Catch2 is a unit testing library
// Here we let it create a main() function for us
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "vector_ex.hpp"
#include "map_ex.hpp"
#include <sstream>

// type alias
using IV = std::vector<int>;

IV IntRange(int n) {
  auto ans = IV(n);
  for (int i = 0; i < n; ++i)
    ans[i] = i;
  return ans;
}

TEST_CASE("Vector Even") {
  IV const empty;
  REQUIRE(empty == GetEven(empty));

  auto const zero = IntRange(1);
  // Test the testing code!
  REQUIRE(zero.size() == 1);
  REQUIRE(zero[0] == 0);

  REQUIRE(zero == GetEven(zero));

  auto const zero_one = IntRange(2);
  // Test the testing code!
  REQUIRE(zero_one.size() == 2);
  REQUIRE(zero_one[0] == 0);
  REQUIRE(zero_one[1] == 1);

  REQUIRE(zero == GetEven(zero_one));

  // edited toddler random numbers
  auto const random = IV{8, 127356, 1, 29, 4376, 263478, 1537};
  auto const random_even = IV{ 8, 127356, 4376, 263478};
  REQUIRE(GetEven(random) == random_even);
}

std::string STR(IV const& v) {
  std::stringstream ss;
  PrintVectorOfInt(ss, v);
  return ss.str();
}

TEST_CASE("Vector Print") {
  REQUIRE(STR(IV{}) == "[ ]");
  REQUIRE(STR(IntRange(1)) == "[ 0]");
  REQUIRE(STR(IntRange(2)) == "[ 0, 1]");
  // edited toddler random numbers
  REQUIRE(STR(IV{8, 127356, 1, 29, 4376, 263478, 1537}) == "[ 8, 127356, 1, 29, 4376, 263478, 1537]");
}

using Word2Len = std::map<std::string, int>;

TEST_CASE("Map adding") {
  Word2Len wlens;

  SECTION( "Adding a word works") {
    bool did_insert = AddWord(wlens, "test");
    REQUIRE(did_insert);
    REQUIRE(wlens.size() == 1);
    REQUIRE(wlens.find("test") != wlens.end());

    // Second time must return false
    bool did_insert_second_time = AddWord(wlens, "test");
    REQUIRE(!did_insert_second_time);
    REQUIRE(wlens.size() == 1);
    REQUIRE(wlens.find("test") != wlens.end());
  }

}
