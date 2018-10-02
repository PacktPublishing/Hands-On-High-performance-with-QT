#ifndef CRTPEQUALITY_H
#define CRTPEQUALITY_H

namespace crtpeq
{

template <class Derived>
class Eq {};

template <class Derived>
bool operator == (const Eq<Derived>& lhs, Eq<Derived> const & rhs)
{
  Derived const& d1 = static_cast<Derived const&>(lhs);
  Derived const& d2 = static_cast<Derived const&>(rhs);
  return !(d1 < d2) && !(d2 < d1);
}

struct X: public Eq<X> { int size; };
bool operator < (const X& lhs, const X& rhs)
{
 return lhs.size < rhs.size;
}

}

#endif // CRTPEQUALITY_H
