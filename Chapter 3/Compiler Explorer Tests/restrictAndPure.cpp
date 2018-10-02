#include <vector>
 
void addThroughPointers(int* ptr1, int* ptr2, int* ptrValue)
{
  *ptr1 += *ptrValue;
  *ptr2 += *ptrValue;
}
 
// gcc __ restrict or __restrict__
// msvc __restrict
void addThroughPointers2(int* __restrict ptr1, int* __restrict ptr2, int* __restrict ptrValue)
{
  *ptr1 += *ptrValue;
  *ptr2 += *ptrValue;
}

int mutatingFunc(int value);
// gcc, bot not msvc!!!
int mutatingFunc2(int value) __attribute__((pure));
 
int sum(const std::vector<int>& v)
{
  int sum = 0;
  for(std::size_t i = 0; i < v.size(); ++i)
  {
    sum += mutatingFunc(v[i]);
    //sum += mutatingFunc2(v[i]);
  }
  return sum;
}