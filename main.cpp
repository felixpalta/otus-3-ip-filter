#include "lib.hpp"
#include <iostream>
#include <algorithm>
#include <functional>

using IpPool = std::vector<otus::IpAddr>;

void ReadIpPool(std::istream & is, IpPool & ip_pool)
{
    for(std::string line; std::getline(is, line);)
    {
        std::vector<std::string> v = otus::Split(line, '\t');
        ip_pool.emplace_back(otus::IpAddrFromString(v.at(0)));
    }
}

void WriteIpPool(std::ostream & os, const IpPool & ip_pool)
{
    for (const auto & ip : ip_pool) {
        os << ip << std::endl;
    }
}

template <typename Cond>
void WriteIpPoolCondtitional(std::ostream & os, const IpPool & ip_pool, Cond cond)
{
    for (const auto & ip : ip_pool) {
        if (cond(ip))
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
        IpPool ip_pool;
        ReadIpPool(std::cin, ip_pool);

        std::sort(ip_pool.begin(),
                  ip_pool.end(),
                  [](const auto & a, const auto & b){ return otus::IpAddrCompare(otus::SortType::DESCENDING, a, b);}
        );

        auto filter1 = [](const auto & ip) { return std::get<0>(ip) == 1;};
        auto filter2 = [](const auto & ip) { return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;};
        auto filter3 = [](const auto & ip) {
            return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
        };

        WriteIpPool(std::cout, ip_pool);
        WriteIpPoolCondtitional(std::cout, ip_pool, filter1);
        WriteIpPoolCondtitional(std::cout, ip_pool, filter2);
        WriteIpPoolCondtitional(std::cout, ip_pool, filter3);
    }
    catch(const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
