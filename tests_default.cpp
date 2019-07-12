#include <gtest/gtest.h>
#include "lib.hpp"

TEST(DefaultTests,TestVersion) {
    ASSERT_GT(otus::GetVersion(), 0);
}

TEST(DefaultTests, TestSplit) {
    using namespace otus;
    struct TestData
    {
        std::string instr;
        char inchar;
        std::vector<std::string> out;
    };
    const std::vector<TestData> testData = {
        {"", '.', {""}},
        {"11", '.', {"11"}},
        {"..", '.', {"", "", ""}},
        {"11.", '.', {"11", ""}},
        {".11", '.', {"", "11"}},
        {"11.22", '.', {"11", "22"}},
        {"113.162.145.156	111	0", '\t', {"113.162.145.156", "111", "0"}},
        {"157.39.22.224	5	6", '\t', {"157.39.22.224",	"5", "6"}}
    };

    for (const auto & td : testData) {
        ASSERT_EQ(Split(td.instr, td.inchar), td.out);
    }
}

TEST(DefaultTests, TestIpAddrParse) {
    using namespace otus;
    struct TestData
    {
        std::string raw;
        IpAddr parsed;
    };
    const std::vector<TestData> testData = {
        {"0.0.0.0", IpAddr{0, 0, 0, 0}},
        {"113.162.145.156", IpAddr{113, 162, 145, 156}}
    };

    for (const auto & td: testData) {
        ASSERT_EQ(IpAddrFromString(td.raw), td.parsed);
        ASSERT_EQ(IpAddrToString(td.parsed), td.raw);
    }
    ASSERT_THROW(IpAddrFromString(""), std::invalid_argument);
    ASSERT_THROW(IpAddrFromString("113"), std::invalid_argument);
    ASSERT_THROW(IpAddrFromString("113."), std::invalid_argument);
    ASSERT_THROW(IpAddrFromString("113.162.145.156.999"), std::invalid_argument);
    ASSERT_THROW(IpAddrFromString("foo.bar.baz.bak"), std::invalid_argument);
}

TEST(DefaultTests, TestCompareIpAddr) {
    using namespace otus;
    struct TestData
    {
        IpAddr a, b;
        bool compareResult;
    };
    const std::vector<TestData> testData = {
        { IpAddr{0, 0, 0, 0}, IpAddr{0, 0, 0, 0}, true},

        { IpAddr{0, 0, 0, 1}, IpAddr{0, 0, 0, 0}, true},
        { IpAddr{0, 0, 0, 0}, IpAddr{0, 0, 0, 1}, false},

        { IpAddr{250, 173, 235, 246}, IpAddr{222, 173, 235, 246}, true},
        { IpAddr{222, 173, 235, 246}, IpAddr{250, 173, 235, 246}, false},

        { IpAddr{222, 173, 235, 246}, IpAddr{222, 130, 177, 64}, true},
        { IpAddr{222, 130, 177, 64}, IpAddr{222, 173, 235, 246}, false},

        { IpAddr{222, 173, 235, 246}, IpAddr{222, 173, 200, 246}, true},
        { IpAddr{222, 173, 200, 246}, IpAddr{222, 173, 235, 246}, false},

        { IpAddr{68, 46, 218, 208}, IpAddr{46, 251, 197, 23}, true},
        { IpAddr{46, 251, 197, 23}, IpAddr{68, 46, 218, 208}, false},

    };
    for (const auto & td : testData) {
        ASSERT_EQ(td.compareResult, IpAddrCompare(td.a, td.b));
    }
}

