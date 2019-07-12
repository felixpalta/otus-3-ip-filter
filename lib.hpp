#pragma once
#include <string>
#include <vector>
#include <tuple>

namespace otus {

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> Split(const std::string & str, char d);

using IpAddr = std::tuple<std::string, std::string, std::string, std::string>;

// ("113.162.145.156") -> {"113", "162", "145", "56"}
// Throws std::out_of_range if failed to parse input string
IpAddr IpAddrFromString(const std::string & str);

// {"113", "162", "145", "56"} -> ("113.162.145.156")
std::string IpAddrToString(const IpAddr & ip);
int GetVersion();

} // otus

std::ostream & operator<<(std::ostream & os, const otus::IpAddr & ip);

