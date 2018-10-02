constexpr long long factorial(int n)
{
    // C++11 constexpr funct use recursion instead of iteration
    // return n <= 1 ? 1 : (n * factorial(n - 1));

    // C++14 constexpr funct can use variables and loops
    if (n <=1 )
        return 1;

    long long result = 1;
    for (int i = 1; i <= n; ++i)
    {
        result *= i;
    }             

    return result;
}

long long test2()
{
    constexpr auto res = factorial(10);
    return res;
}
