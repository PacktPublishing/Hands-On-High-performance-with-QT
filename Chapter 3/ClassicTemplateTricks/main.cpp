#include <crtporacle.h>
#include <crtpequality.h>
#include <expressiontempl.h>
#include <recursivetempl.h>

#include <limits>
#include <iostream>


int main()
{
    // oracles
    oracles::answerFrom(oracles::o1);
    oracles::answerFrom(oracles::o2);

    // CRTP equality
    crtpeq::X a, b ,c;
    a.size = 100;
    b.size = 100;
    c.size = 200;

    std::cout << "a == b: " << (a == b ? "yes" : "no") << std::endl;
    std::cout << "a == c: " << (a == c ? "yes" : "no")  << std::endl;

    // expression templates
    exprtempl::String s = exprtempl::String("Hello") + " y'all" + "," + " how" + " are " + "you" + "?";
    std::cout << "string: " << s << std::endl;
    auto exprObj = exprtempl::String("AA") + " cc" + "cc";
    std::cout << "expr: count=" << exprObj.count() << ", size=" << exprObj.size() << std::endl;

    // pi calculation
    std::cout.precision(std::numeric_limits<double>::digits10);
    std::cout << "pi approximation 3 digits : " << recursivetempl::Pi<3>::value << std::endl;
    std::cout << "pi approximation 10 digits: " << recursivetempl::Pi<10>::value << std::endl;

    return 0;
}
