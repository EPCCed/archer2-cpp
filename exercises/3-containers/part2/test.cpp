// Catch2 is a unit testing library
// Here we let it create a main() function for us
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "map_ex.hpp"
#include <sstream>

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
