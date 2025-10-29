#include <vector>
#include "bits.hpp"
#include "test.hpp"

using namespace morton;

using p32_64 = std::pair<uint32_t, uint64_t>;
const std::vector<p32_64> pdata = {
  {0x00000000U, 0x0000000000000000UL},
  {0x00000001U, 0x0000000000000001UL},
  {0x00000002U, 0x0000000000000004UL},
  {0x00000004U, 0x0000000000000010UL},
  {0x00000008U, 0x0000000000000040UL},
  {0x00000010U, 0x0000000000000100UL},
    
  {0x0000000fU, 0x0000000000000055UL},

  {0xffffffffU, 0x5555555555555555UL},
};


bool test_split() {
  for(auto& item: pdata) {
    auto res = split(item.first);
    // All odd bits must be zero
    // 0xa == 0b1010
    auto mask = 0xaaaaaaaaaaaaaaaaUL;
    if (mask & res) {
      std::cerr << "FAIL! Have a non-zero odd bit in " << res << std::endl;
      return false;
    }

    TEST_ASSERT_EQUAL(item.second, res);
    
  }
  return true;
}


bool test_pack() {
  
  for(auto& item: pdata) {
    auto res = pack(item.second);
    TEST_ASSERT_EQUAL(item.first, res);
  }
  return true;
}


const std::vector<std::tuple<uint32_t, uint32_t, uint64_t>> enc_data = {
  {0, 0, 0},
  {1, 0, 1},
  {0, 1, 2},
  {1, 1, 3},

  {42, 7, 1134},
  {0x45812369U, 0xa7112504U, 0x983b42030c271461UL},
  {0xffffffffU, 0xffffffffU, 0xffffffffffffffffUL}
};

bool test_encode() {
  for (auto& item: enc_data) {
    auto& x = std::get<0>(item);
    auto& y = std::get<1>(item);
    auto& z = std::get<2>(item);

    auto res = encode(x, y);
    TEST_ASSERT_EQUAL(z, res);
    
    uint32_t rx, ry;
    decode(z, rx, ry);

    TEST_ASSERT_EQUAL(x, rx);
    TEST_ASSERT_EQUAL(y, ry);
  }
  return true;
}

bool test_shift() {
  uint64_t start = 0;
  auto res = dec_y(dec_x(inc_y(inc_x(start))));
  TEST_ASSERT_EQUAL(start, res);
  return true;
  
}
int main() {
  RUN_TEST(test_split);
  RUN_TEST(test_pack);
  RUN_TEST(test_encode);
  RUN_TEST(test_shift);
  return 0;
}
