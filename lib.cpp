#include "lib.hpp"
#include "version.hpp"

namespace otus {

int GetVersion() {
    return PROJECT_VERSION_PATCH;
}

std::vector<std::string> Split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

IpAddr IpAddrFromString(const std::string & str)
{
    IpAddr retval;
    std::vector<std::string> spl = Split(str, '.');
    return std::tie(spl.at(0), spl.at(1), spl.at(2), spl.at(3));
}

std::string IpAddrToString(const IpAddr & ip)
{
    return std::get<0>(ip)
            + "." + std::get<1>(ip)
            + "." + std::get<2>(ip)
            + "." + std::get<3>(ip) ;
}

} // otus

std::ostream & operator<<(std::ostream & os, const otus::IpAddr & ip)
{
    os << otus::IpAddrToString(ip);
    return os;
}
