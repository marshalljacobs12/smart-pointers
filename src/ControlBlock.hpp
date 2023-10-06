#pragma once

template <typename T>
class SharedPtr;

class ControlBlock {
    template <typename T>
    friend class SharedPtr;
    friend class WeakPtr;
public:
    ControlBlock() : m_strong_count(1), m_weak_count(0) {}
private:
    unsigned m_strong_count;
    unsigned m_weak_count;
};