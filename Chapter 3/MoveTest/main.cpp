#include "moveconstrtest.h"


int main()
{
    // move constr test:
    T test("object");
    func1(test);
    func1(T("temporary"));

    func2(test);
    func2(T("temporary"));

    return 0;
}
