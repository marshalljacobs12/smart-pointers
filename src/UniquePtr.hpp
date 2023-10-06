template <typename T>
class UniquePtr {
public:
    // Constructor
    UniquePtr(T* ptr = nullptr) : m_ptr(ptr) {}

    // Destructor
    ~UniquePtr() {
        if (m_ptr != nullptr) {
            delete m_ptr;
        }
    }

    // Copy constructor (deleted)
    UniquePtr(const UniquePtr& other) = delete;

    // Move constructor
    UniquePtr(UniquePtr&& other) {
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }

    // Copy assignment operator (deleted)
    UniquePtr& operator=(const UniquePtr& other) = delete;

    // Move assignment operator
    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    // Dereference operator
    T& operator*() const {
        return *m_ptr;
    }

    // Arrow operator
    T* operator->() const {
        return m_ptr;
    }

    // Get the raw pointer
    T* get() const {
        return m_ptr;
    }

    // Release the ownership of the pointer
    T* release() {
        T* ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }

    // Reset the pointer
    void reset(T* ptr = nullptr) {
        delete m_ptr;
        m_ptr = ptr;
    }

private:
    T* m_ptr;
};

// Custom make_unique function for UniquePtr
template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
