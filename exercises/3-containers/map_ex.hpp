#ifndef CPPEX_MAP_EX_HPP
#define CPPEX_MAP_EX_HPP

#include <map>
#include <iostream>

// A map from a word to its length
using Word2Len = std::map<std::string, int>;

// Add a word as a key and its length as the value to the first argument.
// Returns true when the word is added and false if not.
bool AddWord(Word2Len& wlen_map, std::string const& word);

#endif
