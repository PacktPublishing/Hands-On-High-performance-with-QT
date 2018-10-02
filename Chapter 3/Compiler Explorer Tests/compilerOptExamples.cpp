#include <vector>
#include <memory>
#include <cstdint>

// summation
int sum() {
    int a[] = {1, 2, 3, 4, 5, 6};
    //std::vector<int> a{1, 2, 3, 4, 5, 6};
    //auto a = new std::vector<int>{1, 2, 3, 4, 5, 6};
    int sum = 0;
    for(auto x : a)
    {
        sum += x;
    }
    return sum;
}

unsigned int sumSeriesTo(unsigned int x)
{
    unsigned int sum = 0;
    for(size_t i = 0; i < x; ++i)
    {
        sum += i;
    }
    return sum;
}

unsigned int callSumSeries()
{
    return sumSeriesTo(20);
}

unsigned int callSumSeries(unsigned int x)
{
    return sumSeriesTo(x);
}

// heap elision
int valueInPointer()
{
    auto val = new int(44);
    return *val;
}

int valueInSmartPointers()
{
    auto val1 = std::make_unique<int>(22);
    auto val2 = std::make_unique<int>(22);
    return *val1 + *val2;
}

// modulo
int modulo(unsigned int a)
{
    auto y = a % 32;
    return y;
}

// branch elision
int ternaryArg(unsigned int a, unsigned int b, unsigned int c)
{
    a +=  b ? 0 : c;
    //assert(((b-1) & c) == (b ? 0 : c));
    return a;
}

int ternaryConst(int a)
{
    auto x = a < 0 ? 1234 : 5678;
    return x;
}

// multiplication
int multiply2(unsigned int x)
{
    auto a = 2 * x;
    return a;
}

int multiply3(unsigned int x)
{
    auto a = 3 * x;
    return a;
}

int multiply4(unsigned int x)
{
    auto a = 4 * x;
    return a;
}

int multiply7(unsigned int x)
{
    auto a = 7 * x;
    return a;
}

int multiply8(unsigned int x)
{
    auto a = 8 * x;
    return a;
}

int multiply32(unsigned int x)
{
    auto a = 32 * x;
    return a;
}

// division
int divide2(unsigned int x)
{
    auto a = x / 2;
    return a;
}

int divide3(unsigned int x)
{
    auto a = x / 3;
    return a;
}

int divide4(unsigned int x)
{
    auto a = x / 4;
    return a;
}

// popcount
unsigned int countBits(unsigned int x)
{
  unsigned int count = 0;
  while (x)
  {
    ++count;
    x &= (x - 1);
  }
  return count;
}

// goodie: scalar replacement of aggregates
struct S
{
    std::uint8_t a;
    std::uint8_t b;
    std::uint8_t c;
    std::uint8_t d;
};

void takeInts(std::uint8_t,  std::uint8_t, std::uint8_t, std::uint8_t);
void takeStruct(S);

void callWithInts()
{
    takeInts(1, 2, 3, 4);
}

void callWithStruct()
{
    takeStruct(S{1, 2, 3, 4});
}


