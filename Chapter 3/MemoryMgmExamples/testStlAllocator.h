#include <cstdlib>
#include <new>
#include <iostream>


template <class T>
struct TestAllocator 
{
  typedef T value_type;
  TestAllocator() = default;
  
  template <class U> constexpr TestAllocator(const TestAllocator<U>&) noexcept {}

  T* allocate(std::size_t n) 
  {
    if(n > std::size_t(-1) / sizeof(T))
        throw std::bad_alloc();
    if(auto p = static_cast<T*>(std::malloc(n*sizeof(T)))) return p;
    std::cout<< "[stl] element created" << std::endl;
    throw std::bad_alloc();
  }
  void deallocate(T* p, std::size_t) noexcept
  {
    std::cout<< "[stl] element created" << std::endl;
    std::free(p);
  }
};

template <class T, class U>
bool operator==(const TestAllocator<T>&, const TestAllocator<U>&) { return true; }

template <class T, class U>
bool operator!=(const TestAllocator<T>&, const TestAllocator<U>&) { return false; }
