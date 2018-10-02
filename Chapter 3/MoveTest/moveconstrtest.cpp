#include "moveconstrtest.h"

#include <iostream>
#include <utility>


T::T(const std::string& s)
    : s_(s)
{
    std::cout << "constructed" << std::endl;
}


T::T(T&& other)
    : s_(std::move(other.s_))
{
    std::cout << "moved" << std::endl;
}


T::T(const T& other)
    : s_(other.s_)
{
    std::cout << "copied" << std::endl;
}


const std::string& T::s() const
{
    return s_;
}


// test it

void func1(const T& obj)
{
    std::cout << "func1 - const ref: " << obj.s() << std::endl;
	T copy(obj);
}

void func2(T obj)
{
	std::cout << "func2 - value: " << obj.s() << std::endl;
    T copy = std::move(obj);
}

