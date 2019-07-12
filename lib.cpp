#include "lib.hpp"
#include "version.hpp"
#include <sstream>

namespace otus {

namespace impl  {

std::string StringForwarder(std::string && s) {
    return std::move(s);
}

template <typename T>
std::vector<T> Split(const std::string & str, char d, T typeConverter(std::string &&) = StringForwarder)
{
    std::vector<T> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(typeConverter(str.substr(start, stop - start)));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(typeConverter(str.substr(start)));

    return r;
}

} // namespace impl

std::vector<std::string> Split(const std::string & str, char d)
{
    return impl::Split<std::string>(str, d);
}

IpAddr IpAddrFromString(const std::string & str)
{
    std::vector<int> spl = impl::Split<int>(str, '.', [](auto && s) {return std::stoi(s); });
    if (spl.size() != 4)
        throw std::invalid_argument("Failed to parse IpAddr from string");
    return std::tie(spl.at(0), spl.at(1), spl.at(2), spl.at(3));
}

std::string IpAddrToString(const IpAddr & ip)
{
    std::ostringstream oss;
    oss << ip;
    return oss.str();
}

int GetVersion() {
    return PROJECT_VERSION_PATCH;
}

bool IpAddrCompare(const IpAddr & a, const IpAddr & b)
{
    return a >= b;
}

} // otus

std::ostream & operator<<(std::ostream & os, const otus::IpAddr & ip)
{
    os << std::get<0>(ip) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip);
    return os;
}
