#ifndef COMPILETIMECOMPUTATION_H
#define COMPILETIMECOMPUTATION_H

namespace recursivetempl
{

// recursion step
template <unsigned int Base, unsigned int Exp>
struct Power
{
  static const unsigned long long result = Base * Power<Base, Exp - 1>::result;
};

// base case
template <unsigned int Base>
struct Power<Base, 0>
{
  static const unsigned long long result = 1;
};

// Bailey-Borwein-Plouffe formula for calculating pi
// http://en.wikipedia.org/wiki/Bailey-Borwein-Plouffe_formula
template <unsigned long N>
struct Pi
{
    constexpr static const double value =
    (
        1.0/Power<16, N>::result *
        (
            4.0/(8*N + 1.0) - 2.0/(8*N + 4.0) -
            1.0/(8*N + 5.0) - 1.0/(8*N + 6.0)
        )
    ) + Pi<N-1>::value;
};

template <>
struct Pi<-1>
{
    constexpr static const double value = 0;
};

}

#endif // COMPILETIMECOMPUTATION_H
