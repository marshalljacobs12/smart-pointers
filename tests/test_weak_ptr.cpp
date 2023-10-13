#include "gtest/gtest.h"
#include "SharedPtr.hpp"
#include "WeakPtr.hpp"

TEST(WeakPtr, DefaultConstructor) {
    WeakPtr<int> ptr;
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.weak_count(), 0);
}

TEST(WeakPtr, CopyConstructor) {
    WeakPtr<int> ptr;
    WeakPtr<int> ptr2(ptr);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.weak_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr2.weak_count(), 0);

    auto shared_ptr = make_shared<int>(5);
    WeakPtr<int> ptr3(shared_ptr);
    WeakPtr<int> ptr4(ptr3);
    EXPECT_EQ(ptr3.use_count(), 1);
    EXPECT_EQ(ptr3.weak_count(), 2);
    EXPECT_EQ(ptr4.use_count(), 1);
    EXPECT_EQ(ptr4.weak_count(), 2);
}

TEST(WeakPtr, MoveConstructor) {
    auto shared_ptr = make_shared<int>(5);
    WeakPtr<int> ptr(shared_ptr);
    WeakPtr<int> ptr2(std::move(ptr));
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.weak_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.weak_count(), 1);
}

TEST(WeakPtr, ConstructorFromSharedPtr) {
    auto shared_ptr = make_shared<int>(5);
    WeakPtr<int> ptr(shared_ptr);
    EXPECT_EQ(shared_ptr.use_count(), 1);
    EXPECT_EQ(shared_ptr.weak_count(), 1);
    EXPECT_EQ(ptr.use_count(), 1);
    EXPECT_EQ(ptr.weak_count(), 1);
}

TEST(WeakPtr, CopyAssignmentOperator) {
    auto shared_ptr = make_shared<int>(5);
    WeakPtr<int> ptr(shared_ptr);
    WeakPtr<int> ptr2;
    ptr2 = ptr;
    EXPECT_EQ(ptr.use_count(), 1);
    EXPECT_EQ(ptr.weak_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.weak_count(), 2);
}

TEST(WeakPtr, MoveAssignmentOperator) {
    auto shared_ptr = make_shared<int>(5);
    WeakPtr<int> ptr(shared_ptr);
    WeakPtr<int> ptr2;
    ptr2 = std::move(ptr);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.weak_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.weak_count(), 1);
}

TEST(WeakPtr, Lock) {
    // empty SharedPtr returned
    WeakPtr<int> empty_ptr;
    auto empty_shared_ptr = empty_ptr.lock();
    EXPECT_EQ(empty_ptr.use_count(), 0);
    EXPECT_EQ(empty_ptr.weak_count(), 0);
    EXPECT_EQ(empty_shared_ptr.use_count(), 0);
    EXPECT_EQ(empty_shared_ptr.weak_count(), 0);
    EXPECT_EQ(empty_shared_ptr.get(), nullptr);

    // non-empty SharedPtr returned
    auto shared_ptr = make_shared<int>(5);
    WeakPtr<int> ptr(shared_ptr);
    auto shared_ptr2 = ptr.lock();
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_EQ(ptr.weak_count(), 1);
    EXPECT_EQ(shared_ptr.use_count(), 2);
    EXPECT_EQ(shared_ptr.weak_count(), 1);
    EXPECT_EQ(shared_ptr2.use_count(), 2);
    EXPECT_EQ(shared_ptr2.weak_count(), 1);
}

TEST(WeakPtr, Expired) {
    auto shared_ptr_1 = make_shared<int>(5);
    WeakPtr<int> ptr_1(shared_ptr_1);
    EXPECT_FALSE(ptr_1.expired());
    shared_ptr_1.reset();
    EXPECT_TRUE(ptr_1.expired());

    auto shared_ptr_2 = make_shared<int>(10);
    WeakPtr<int> ptr_2(shared_ptr_2);
    EXPECT_FALSE(ptr_2.expired());
    shared_ptr_2 = shared_ptr_1;
    EXPECT_TRUE(ptr_2.expired());
}

TEST(WeakPtr, Swap) {
    auto shared_ptr_1 = make_shared<int>(5);
    auto shared_ptr_2 = make_shared<int>(10);
    WeakPtr<int> ptr_1(shared_ptr_1);
    WeakPtr<int> ptr_2(shared_ptr_2);
    WeakPtr<int> ptr_3(ptr_2);
    EXPECT_EQ(ptr_1.use_count(), 1);
    EXPECT_EQ(ptr_1.weak_count(), 1);
    EXPECT_EQ(ptr_2.use_count(), 1);
    EXPECT_EQ(ptr_2.weak_count(), 2);
    ptr_1.swap(ptr_2);
    EXPECT_EQ(ptr_1.use_count(), 1);
    EXPECT_EQ(ptr_1.weak_count(), 2);
    EXPECT_EQ(ptr_2.use_count(), 1);
    EXPECT_EQ(ptr_2.weak_count(), 1);
}

TEST(WeakPtr, MakeWeak) {
    // test default constructor
    auto ptr_1 = make_weak<int>();
    EXPECT_EQ(ptr_1.use_count(), 0);
    EXPECT_EQ(ptr_1.weak_count(), 0);

    // test constructoer from shared_ptr
    auto shared_ptr_1 = make_shared<int>(5);
    auto ptr_2 = make_weak<int>(shared_ptr_1);
    EXPECT_EQ(ptr_2.use_count(), 1);
    EXPECT_EQ(ptr_2.weak_count(), 1);

    // test copy constructor
    auto ptr_3 = make_weak<int>(ptr_2);
    EXPECT_EQ(ptr_3.use_count(), 1);
    EXPECT_EQ(ptr_3.weak_count(), 2);
 
    // test move constructor
    auto ptr_4 = make_weak<int>(std::move(ptr_3));
    EXPECT_EQ(ptr_4.use_count(), 1);
    EXPECT_EQ(ptr_4.weak_count(), 2);
    EXPECT_EQ(ptr_3.use_count(), 0);
    EXPECT_EQ(ptr_3.weak_count(), 0);
}