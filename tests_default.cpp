#include <gtest/gtest.h>
#include "lib.hpp"

TEST(DefaultTests,TestVersion) {
    ASSERT_GT(otus::GetVersion(), 0);
}
