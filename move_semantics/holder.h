#pragma once
#include <cstdlib>
#include <algorithm>
#include <iostream>
class Holder
{
public:
    explicit Holder(int size){
        m_data = new int[size];
        m_size = size;
    }

    ~Holder(){
        delete[] m_data;
    }

    Holder& operator=(const Holder & other);

    Holder(const Holder& other);

    Holder(Holder&& other) noexcept;

    Holder& rref_modify(Holder&& obj);

public:
    int* m_data{};
    size_t m_size{};  // zero-initialization
};

Holder& Holder::operator=(const Holder & other){
    if (this == &other)  return *this;
    delete m_data;
    m_data = new int [other.m_size];
    std::copy(
            other.m_data,
            other.m_data + other.m_size,
            m_data);
    m_size = other.m_size;
    std::cout << "operator=" << std::endl;
    return *this;
}

Holder::Holder(const Holder &other) {
    delete[] m_data;
    m_data = new int [other.m_size];
    std::copy(other.m_data,
              other.m_data + other.m_size,
              m_data);
    m_size = other.m_size;
    std::cout << "copy constructor" << std::endl;
}

// move constructor is omited (copy-epsilon)
Holder::Holder(Holder&& other) noexcept{
    delete[] m_data;
    m_data = other.m_data;
    m_size = other.m_size;
    std::cout << "move constructor" << std::endl;
    other.m_data = nullptr; // disable other's ownership
    other.m_size = 0;
}

// using move semantics
Holder &Holder::rref_modify(Holder &&obj) {
    if (&obj == this) return *this;
    delete[] m_data;
    m_data = obj.m_data;
    m_size = obj.m_size;
    obj.m_data = nullptr;
    obj.m_size = 0;
    return *this;
}
