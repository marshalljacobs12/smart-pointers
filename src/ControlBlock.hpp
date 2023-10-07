#pragma once

#include <atomic>

template <typename T>
class SharedPtr;

class ControlBlock {
    template <typename T>
    friend class SharedPtr;
public:
    ControlBlock() : m_strong_count(1), m_weak_count(0) {}
private:
    std::atomic<unsigned> m_strong_count;
    std::atomic<unsigned> m_weak_count;
};