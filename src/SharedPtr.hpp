#pragma once
#include <iostream>
#include "ControlBlock.hpp"

template <typename T>
class SharedPtr {
public:
    // default constructor
    SharedPtr() : m_data_ptr(nullptr), m_control_block(nullptr) {};

    // constructor from raw pointer
    SharedPtr(T* ptr) : m_data_ptr(ptr), m_control_block(new ControlBlock) {}

    // get the raw pointer
    T* get() const {
        return m_data_ptr;
    }
    
    // destructor
    ~SharedPtr() {
        if (m_control_block != nullptr) {
            m_control_block->m_strong_count.fetch_sub(1, std::memory_order_relaxed);
            if (m_control_block->m_strong_count == 0) {
                if (m_data_ptr != nullptr) {
                    delete m_data_ptr;
                }
                if (m_control_block->m_weak_count == 0) {
                    delete m_control_block;
                }
            }
        }
    }
    // dereference operator
    T& operator*() const {
        return *m_data_ptr;
    }
    
    // member access operator
    T* operator->() const {
        return m_data_ptr;
    }
    // get the number of SharedPtr instances sharing the ownership of the managed object
    unsigned use_count() const {
        if (m_control_block == nullptr) {
            return 0;
        }
        return m_control_block->m_strong_count;
    }
    // get the number of WeakPtr instances pointing at the current object
    unsigned weak_count() const {
        if (m_control_block == nullptr) {
            return 0;
        }
        return m_control_block->m_weak_count;
    }
    // copy constructor
    SharedPtr(const SharedPtr& other) : m_data_ptr(other.m_data_ptr), m_control_block(other.m_control_block) {
        if (m_control_block != nullptr) {
            m_control_block->m_strong_count.fetch_add(1, std::memory_order_relaxed);
        }
    }
    // copy assignment operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            m_data_ptr = other.m_data_ptr;
            m_control_block = other.m_control_block;
            m_control_block->m_strong_count.fetch_add(1, std::memory_order_relaxed);
        }
        return *this;
    }
    // move constructor
    SharedPtr(SharedPtr&& other) : m_data_ptr(other.m_data_ptr), m_control_block(other.m_control_block) {
        other.m_data_ptr = nullptr;
        other.m_control_block = nullptr;
    }
    
    // move assignment operator
    SharedPtr& operator=(SharedPtr&& other) {
        if (this != &other) {
            m_data_ptr = other.m_data_ptr;
            m_control_block = other.m_control_block;
            other.m_data_ptr = nullptr;
            other.m_control_block = nullptr;
        }
        return *this;
    }

    void reset(T* ptr = nullptr) {
        if (m_control_block != nullptr) {
            m_control_block->m_strong_count.fetch_sub(1, std::memory_order_relaxed);
            if (m_control_block->m_strong_count == 0) {
                delete m_data_ptr;
                if (m_control_block->m_weak_count == 0) {
                    delete m_control_block;
                }
            }
        }
        m_data_ptr = ptr;
        m_control_block = new ControlBlock;
    }

private:
    T* m_data_ptr;
    ControlBlock* m_control_block;
};
