#include "ControlBlock.hpp"
#include "SharedPtr.hpp"
// Forward declaration of SharedPtr
// template <typename T>
// class SharedPtr;

// Custom WeakPtr class
template <typename T>
class WeakPtr {
public:
    WeakPtr() = delete;

    // Constructor from SharedPtr
    WeakPtr(const SharedPtr<T>& shared)) {
        std::cout << "Weak Ptr constructor" << std::endl;
    }

private:
    T* m_data_ptr;
    ControlBlock* m_control_block;
};
