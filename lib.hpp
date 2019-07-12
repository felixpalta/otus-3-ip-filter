#pragma once
#include <string>
#include <vector>

namespace otus {

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> Split(const std::string &str, char d);

int GetVersion();

} // otus
