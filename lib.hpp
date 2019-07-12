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

using IpAddr = std::tuple<int, int, int, int>;

// ("113.162.145.156") -> {113, 162, 145, 56}
// Throws std::exception if failed to parse input string
IpAddr IpAddrFromString(const std::string & str);

// {113, 162, 145, 56} -> ("113.162.145.156")
std::string IpAddrToString(const IpAddr & ip);

enum class SortType
{
    ASCENDING,
    DESCENDING
};

bool IpAddrCompare(SortType sortType, const IpAddr & a, const IpAddr & b);

int GetVersion();

} // otus

std::ostream & operator<<(std::ostream & os, const otus::IpAddr & ip);

