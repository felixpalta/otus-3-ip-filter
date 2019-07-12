#include "lib.hpp"
#include <iostream>

using IpPool = std::vector<otus::IpAddr>;

void ReadIpPool(std::istream & is, IpPool & ipPool)
{
    for(std::string line; std::getline(is, line);)
    {
        std::vector<std::string> v = otus::Split(line, '\t');
        ipPool.emplace_back(otus::IpAddrFromString(v.at(0)));
    }
}

void WriteIpPool(std::ostream & os, const IpPool & ipPool)
{
    for (const auto & ip : ipPool) {
        os << ip << std::endl;
    }
}

int main()
{
    try
    {
        IpPool ipPool;
        ReadIpPool(std::cin, ipPool);
        WriteIpPool(std::cout, ipPool);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
