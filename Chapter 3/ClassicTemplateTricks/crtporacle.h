#ifndef CRTPORACLE_H
#define CRTPORACLE_H

#include <iostream>

namespace oracles
{

template<class T>
struct OracleBase
{
 // within base we can use members of derived class T!
 int whatsTheAnswer() const
 {
   return static_cast<const T*>(this)->getAnswer() * 2;
 }
};

struct Oracle1: public OracleBase<Oracle1>
{
 int getAnswer() const { return 22; }
} o1;

struct Oracle2: public OracleBase<Oracle2>
{
 int getAnswer() const { return 21; }
} o2;

// now use the base class
template<typename T>
void answerFrom(const OracleBase<T>& base)
{
 std::cout << "the answer is: " << base.whatsTheAnswer() << '\n';
}

}

#endif // CRTPORACLE_H
