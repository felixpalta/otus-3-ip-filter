#include "lib.hpp"
#include <iostream>
#include <algorithm>

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

int main(int argc, const char *argv[])
{
    if (argc > 1) {
        if ("-v" == std::string(argv[1])) {
            std::cerr << "Version: " << otus::GetVersion() << std::endl;
            return 0;
        }
    }

    try
    {
        IpPool ipPool;
        ReadIpPool(std::cin, ipPool);

//        auto IpAddrReverseLexicalCompare = [](const otus::IpAddr & a, const otus::IpAddr & b) {
//            return  std::get<0>(a) > std::get<0>(b);
//        };
//        std::sort(ipPool.begin(), ipPool.end(), IpAddrReverseLexicalCompare);
        WriteIpPool(std::cout, ipPool);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
