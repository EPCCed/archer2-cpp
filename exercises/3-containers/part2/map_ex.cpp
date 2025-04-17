#include "map_ex.hpp"

// std::map documentation:
// https://en.cppreference.com/w/cpp/container/map
bool AddWord(Word2Len& wlen_map, std::string const& word) {
  auto iter = wlen_map.find(word);
  if (iter == wlen_map.end()) {
    wlen_map[word] = word.size();
    return true;
  } else {
    return false;
  }
}
