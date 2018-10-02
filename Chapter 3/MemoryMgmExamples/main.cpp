#include "testStlAllocator.h"
#include "testOverrideMemoryMgr.h"

#include <vector>


int main()
{
    // class memory mgr.
    auto olafur = new Person("Olafur", 44);
    delete olafur;

    // STL allocator
    std::vector<int, TestAllocator<int>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.emplace_back(3);
}
