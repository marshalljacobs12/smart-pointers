#pragma once

#include <atomic>

#include "SharedPtr.hpp"
#include "ControlBlock.hpp"


template<typename T>
class WeakPtr {
public:
    // default constructor
    WeakPtr() noexcept : m_shared_ptr(nullptr), m_control_block(nullptr) {}

    // copy constructor
    WeakPtr(const WeakPtr& other) : m_shared_ptr(other.m_shared_ptr), m_control_block(other.m_control_block) {
        if (m_control_block) {
            m_control_block->m_weak_count.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // move constructor
    WeakPtr(WeakPtr&& other) : m_shared_ptr(other.m_shared_ptr), m_control_block(other.m_control_block) {
        other.m_shared_ptr = nullptr;
        other.m_control_block = nullptr;
    }

    // constructor from SharedPtr
    WeakPtr(const SharedPtr<T>& ptr) : m_control_block(ptr.m_control_block) {
        m_shared_ptr = &(const_cast<SharedPtr<T>&>(ptr));
        if (m_control_block) {
            m_control_block->m_weak_count.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // copy assignment
    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            m_shared_ptr = other.m_shared_ptr;
            m_control_block = other.m_control_block;
            if (m_control_block) {
                m_control_block->m_weak_count.fetch_add(1, std::memory_order_relaxed);
            }
        }
        return *this;
    }

    // move assignment operator
    WeakPtr& operator=(WeakPtr&& other) {
        if (this != &other) {
            m_shared_ptr = other.m_shared_ptr;
            m_control_block = other.m_control_block;
            other.m_shared_ptr = nullptr;
            other.m_control_block = nullptr;
        }
        return *this;
    }

    // destructor
    ~WeakPtr() {
        if (m_control_block) {
            m_control_block->m_weak_count.fetch_sub(1, std::memory_order_relaxed);
        }
    }

    // get strong count
    unsigned use_count() const {
        if (m_control_block) {
            return m_control_block->m_strong_count.load(std::memory_order_relaxed);
        }
        return 0;
    }

    // get weak count
    unsigned weak_count() const {
        if (m_control_block) {
            return m_control_block->m_weak_count.load(std::memory_order_relaxed);
        }
        return 0;
    }

    // lock method
    SharedPtr<T> lock() const {
        if (!m_control_block || m_control_block->m_strong_count.load(std::memory_order_relaxed) == 0) {
            return SharedPtr<T>();
        }
        SharedPtr<T> new_shared_ptr;
        new_shared_ptr.m_data_ptr = m_shared_ptr->get();
        new_shared_ptr.m_control_block = m_control_block;
        m_control_block->m_strong_count.fetch_add(1, std::memory_order_relaxed);
        return new_shared_ptr;
    }

    // expired method
    bool expired() {
        bool is_expired = m_shared_ptr->m_control_block == nullptr || m_shared_ptr->m_control_block->m_strong_count.load(std::memory_order_relaxed) == 0;
        if (is_expired) {
            m_control_block = nullptr;
            m_shared_ptr = nullptr;
        }
        return is_expired;
    }

    // swap method
    void swap(WeakPtr& other) {
        std::swap(m_shared_ptr, other.m_shared_ptr);
        std::swap(m_control_block, other.m_control_block);
    }

private:
    SharedPtr<T>* m_shared_ptr;
    ControlBlock* m_control_block;
};

// For default constructor
template <typename T>
WeakPtr<T> make_weak() {
    return WeakPtr<T>();
}

template <typename T, typename U>
WeakPtr<T> make_weak(U param) {
    if (std::is_convertible<U, SharedPtr<T>>::value) {
        return WeakPtr<T>(param);
    }
    return WeakPtr<T>(std::forward<U>(param));
}
