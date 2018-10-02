#ifndef T_H
#define T_H

#include <string>

class T
{
public:
    T(const std::string& s);
    T(T&& other);
    T(const T& other);
    const std::string& s() const;

private:
    std::string s_;
};

void func1(const T& obj);
void func2(T obj);

#endif // T_H
