#include "gtest/gtest.h"
#include "UniquePtr.hpp"

TEST(UniquePtr, EmptyConstructor) {
    UniquePtr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtr, Constructor) {
    UniquePtr<int> ptr(new int(5));
    EXPECT_EQ(*ptr, 5);
}

// move constructor
TEST(UniquePtr, MoveConstructor) {
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptr2(std::move(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*ptr2, 5);
}

// move assignment operator
TEST(UniquePtr, MoveAssignmentOperator) {
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptr2;
    ptr2 = std::move(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*ptr2, 5);
}

// release
TEST(UniquePtr, Release) {
    UniquePtr<int> ptr(new int(5));
    int* rawPtr = ptr.release();
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*rawPtr, 5);
    delete rawPtr;
}

// reset
TEST(UniquePtr, Reset) {
    UniquePtr<int> ptr(new int(5));
    ptr.reset(new int(6));
    EXPECT_EQ(*ptr, 6);

    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}