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

TEST(UniquePtr, MoveConstructor) {
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptr2(std::move(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*ptr2, 5);
}

TEST(UniquePtr, MoveAssignmentOperator) {
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptr2;
    ptr2 = std::move(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*ptr2, 5);
}

TEST(UniquePtr, Release) {
    UniquePtr<int> ptr(new int(5));
    int* rawPtr = ptr.release();
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*rawPtr, 5);
    delete rawPtr;
}

TEST(UniquePtr, Reset) {
    UniquePtr<int> ptr(new int(5));
    ptr.reset(new int(6));
    EXPECT_EQ(*ptr, 6);

    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtr, Swap) {
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptr2(new int(6));
    ptr.swap(ptr2);
    EXPECT_EQ(*ptr, 6);
    EXPECT_EQ(*ptr2, 5);
}

TEST(UniquePtr, MakeUnique) {
    auto ptr = make_unique<int>(5);
    EXPECT_EQ(*ptr, 5);
}