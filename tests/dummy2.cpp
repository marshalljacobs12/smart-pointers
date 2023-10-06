#include "gtest/gtest.h"
#include "example.h"

// Tests that don't naturally fit in the headers/.cpp files directly
// can be placed in a tests/*.cpp file. Integration tests are a good example.

// Demonstrate some basic assertions.
TEST(HelloTest2, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(5 * 6, 30);
}
