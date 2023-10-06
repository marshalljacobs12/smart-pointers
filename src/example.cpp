#include "example.h"

Dummy::Dummy() {

}

bool Dummy::doSomething() {
    // Do silly things, using some C++17 features to enforce C++17 builds only.
    constexpr int digits[2] = {0, 1};
    auto [zero, one] = digits;
    return zero + one;
}


#ifdef ENABLE_GTEST_IN_LIBRARY
#include "gtest/gtest.h"
TEST(HelloTest4, BasicAssertions3) {
  // Expect two strings not to be equal.
//   EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(8 * 6, 48);
}
#endif
