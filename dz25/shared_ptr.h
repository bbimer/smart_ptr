#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* ref_count;

public:
    explicit SharedPtr(T* p = nullptr);
    ~SharedPtr();

    SharedPtr(const SharedPtr& other);
    SharedPtr& operator=(const SharedPtr& other);

    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get() const;
    size_t use_count() const;
    void reset(T* p = nullptr);
};

template <typename T>
SharedPtr<T>::SharedPtr(T* p) : ptr(p), ref_count(new size_t(1)) {}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (--(*ref_count) == 0) {
        delete ptr;
        delete ref_count;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
    ++(*ref_count);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
    if (this != &other) {
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
        ptr = other.ptr;
        ref_count = other.ref_count;
        ++(*ref_count);
    }
    return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
    other.ptr = nullptr;
    other.ref_count = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }
    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*() const {
    return *ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const {
    return ptr;
}

template <typename T>
T* SharedPtr<T>::get() const {
    return ptr;
}

template <typename T>
size_t SharedPtr<T>::use_count() const {
    return ptr ? *ref_count : 0;
}

template <typename T>
void SharedPtr<T>::reset(T* p) {
    if (--(*ref_count) == 0) {
        delete ptr;
        delete ref_count;
    }
    ptr = p;
    ref_count = new size_t(1);
}

#endif // SHARED_PTR_H