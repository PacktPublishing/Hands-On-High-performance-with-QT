#include <iostream>
#include <sstream>
#include <type_traits>
 
constexpr std::uint64_t hashPrime = 0x100000001B3;
constexpr std::uint64_t hashBasis = 0xCBF29CE484222325; 

constexpr std::uint64_t 
    constexprHash(char const* str, std::uint64_t lastValue = hashBasis)
{
    return *str
        ? constexprHash(str + 1, (*str ^ lastValue) * hashPrime)
        : lastValue;
}

constexpr unsigned long long operator "" _hash(char const* p, size_t)
{
    return constexprHash(p);
}

void test(const char* strg)
{
    std::stringstream s;
    s << strg;
    unsigned long long cnt;
    s >> cnt; 

    switch (cnt) 
    {
    case "alpha"_hash:
        std::cout << "1st one" << std::endl;
        break;
    case "beta"_hash:
        std::cout << "2nd one" << std::endl;
        break;
    case "gamma"_hash:
        std::cout << "3rd one" << std::endl;
        break;
    default:
        std::cout << "omega" << std::endl;
    }  
}
