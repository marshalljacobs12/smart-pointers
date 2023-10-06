#pragma once

#include "ControlBlock.hpp"

template <typename T>
class SharedPtr {
public:
    SharedPtr() = delete;
    SharedPtr(T* ptr) : m_data_ptr(ptr), m_control_block(new ControlBlock) {}
private:
    T* m_data_ptr;
    ControlBlock* m_control_block;
};
