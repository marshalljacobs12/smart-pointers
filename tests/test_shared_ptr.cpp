#include <gtest/gtest.h>
#include "SharedPtr.hpp"

TEST(SharedPtr, DefaultConstructor) {
    SharedPtr<int> ptr1;
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(ptr1.use_count(), 0);
    ASSERT_EQ(ptr1.weak_count(), 0);
}
TEST(SharedPtr, Constructor) {
    SharedPtr<int> ptr1(new int(5));
    ASSERT_NE(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr1, 5);
    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr1.weak_count(), 0);
}

TEST(SharedPtr, CopyConstructor) {
    SharedPtr<int> ptr1(new int(5));
    SharedPtr<int> ptr2(ptr1);
    ASSERT_EQ(ptr1.get(), ptr2.get());
    ASSERT_EQ(*ptr1, *ptr2);
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr1.weak_count(), 0);
    ASSERT_EQ(ptr2.use_count(), 2);
    ASSERT_EQ(ptr2.weak_count(), 0);
}

TEST(SharedPtr, CopyAssignmentOperator) {
    SharedPtr<int> ptr1(new int(5));
    SharedPtr<int> ptr2;
    ptr2 = ptr1;
    ASSERT_EQ(ptr1.get(), ptr2.get());
    ASSERT_EQ(*ptr1, *ptr2);
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr1.weak_count(), 0);
    ASSERT_EQ(ptr2.use_count(), 2);
    ASSERT_EQ(ptr2.weak_count(), 0);
}

TEST(SharedPtr, MoveConstructor) {
    SharedPtr<int> ptr1(new int(5));
    ASSERT_NE(ptr1.get(), nullptr);

    auto* underlying = ptr1.get();
    SharedPtr<int> ptr2(std::move(ptr1));
    ASSERT_EQ(ptr1.get(), nullptr);
    // ASSERT_EQ(ptr1.use_count(), 0);
    // ASSERT_EQ(ptr1.weak_count(), 0);
    ASSERT_EQ(ptr2.get(), underlying);
    ASSERT_EQ(*ptr2, 5);
    ASSERT_EQ(ptr2.use_count(), 1);
    ASSERT_EQ(ptr2.weak_count(), 0);
}

TEST(SharedPtr, MoveAssignmentOperator) {
    SharedPtr<int> ptr1(new int(5));
    ASSERT_NE(ptr1.get(), nullptr);

    auto* underlying = ptr1.get();
    SharedPtr<int> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT_EQ(ptr1.get(), nullptr);
    // ASSERT_EQ(ptr1.use_count(), 0);
    // ASSERT_EQ(ptr1.weak_count(), 0);
    ASSERT_EQ(ptr2.get(), underlying);
    ASSERT_EQ(*ptr2, 5);
    ASSERT_EQ(ptr2.use_count(), 1);
    ASSERT_EQ(ptr2.weak_count(), 0);
}

TEST(SharedPtr, Reset) {
    SharedPtr<int> ptr1(new int(5));
    ASSERT_NE(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr1, 5);
    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr1.weak_count(), 0);

    ptr1.reset(new int(42));
    ASSERT_NE(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr1, 42);
    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr1.weak_count(), 0);

    ptr1.reset();
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr1.weak_count(), 0);
}