//
// Created by nylon on 05.08.2023.
//

#ifndef ARRAY_H
#define ARRAY_H
#include <cstdint>
#include <cassert>

template <typename T>
struct array {
public:
    array(): size(0) {
        data = nullptr;
    }
    array(uint32_t n) {
        size = n;
        data = new T[size];
    }

    ~array() {
        dealloc();
    }

    array(const array<T>& a) {
        size = a.size;
        data = new T[size];
        for (uint32_t i = 0; i < size; ++i)
            data[i] = a.data[i];
    }

    array(const T* start, const T* stop) {
        size = std::distance(start, stop);
        while (start != stop) {
            pb(*start), start++;
        }
    }

    array(T* arr, uint32_t size) {
        this->size = size;
        data = new T[size];
        for (uint32_t i = 0; i < size; ++i)
            data[i] = arr[i];
    }


    T& operator[](const uint32_t& i) const {
        return get(i);
    }
    array<T>& operator=(const array<T>& a) {
        dealloc();
        size = a.size;
        data = new T[size];
        for (uint32_t i = 0; i < size; ++i)
            data[i] = a.data[i];
        return *this;
    }

    void resize(const uint32_t size) {
        T* tmp = new T[size];
        for (uint32_t i = 0; i < size; ++i)
            tmp[i] = i < this->size ? data[i] : 0;
        if (this->size) delete[] data;
        this->data = tmp;
        this->size = size;
    }

    T* getPointer() const {
        return data;
    }

    void pb(const T& d) {
        resize(size+1);
        data[size-1] = d;
    }

    T& get(const uint32_t& i) const {
        assert(i < size && "Index out of range");
        return data[i];
    }

    void pf(const T& d) {
        resize(size+1);
        for (uint32_t i = size-1; i > 0; --i)
            data[i] = data[i-1];
        data[0] = d;
    }

    void pop() {
        assert(size > 0 && "Pop from empty array");
        T* newArr = new T[size-1];
        for (uint32_t i = 0; i < size-1; ++i)
            newArr[i] = data[i];
        delete[] data;
        data = newArr;
        this->size--;
    }

    uint32_t getSize() const { return size; }
    void dealloc() { if (this->size) delete[] data; }
private:
    T* data;
    uint32_t size;
};


#endif //ARRAY_H
