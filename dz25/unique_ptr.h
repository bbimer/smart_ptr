#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    explicit UniquePtr(T* p = nullptr);
    ~UniquePtr();

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(UniquePtr&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T* release();
    void reset(T* p = nullptr);
};

template <typename T>
UniquePtr<T>::UniquePtr(T* p) : ptr(p) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete ptr;
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
    return *ptr;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
    return ptr;
}

template <typename T>
T* UniquePtr<T>::get() const {
    return ptr;
}

template <typename T>
T* UniquePtr<T>::release() {
    T* temp = ptr;
    ptr = nullptr;
    return temp;
}

template <typename T>
void UniquePtr<T>::reset(T* p) {
    delete ptr;
    ptr = p;
}

struct Test {
    Test() { std::cout << "Test created\n"; }
    ~Test() { std::cout << "Test destroyed\n"; }
    void sayHello() { std::cout << "Hello from Test!\n"; }
};

#endif // UNIQUE_PTR_H
