#include <gtest/gtest.h>
#include "lib.hpp"

TEST(DefaultTests,TestVersion) {
    ASSERT_GT(otus::GetVersion(), 0);
}

TEST(DefaultTests, TestSplit) {
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
        ASSERT_EQ(otus::Split(td.instr, td.inchar), td.out);
    }
}
