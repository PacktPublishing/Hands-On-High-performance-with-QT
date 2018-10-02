#ifndef EXPRESSIONTEMPL_H
#define EXPRESSIONTEMPL_H

#include <memory>
#include <string>
#include <cassert>
#include <cstring>


namespace exprtempl
{

class String;


// helper template
template <typename L, typename R>
struct GoDownGetCount
{
    static const int result =
            GoDownGetCount<typename L::lhsType, typename L::rhsType>::result + 1;
};

template <>
struct GoDownGetCount<String, const char*>
{
    static const int result = 2; // String && char*
};


// the expression type
template <typename L, typename R>
class StrgSumExpr
{
public:
	explicit StrgSumExpr(const L& lhs, const R rhs)
		: lhs_(lhs)
		, rhs_(rhs)
	{}

	std::size_t size() const
	{
        return strlen(rhs_) + lhs_.size();
	}

	const char* operator[] (std::size_t i) const;

	std::size_t count() const
	{
		return GoDownGetCount<L, R>::result;
	}

	typedef L lhsType;
	typedef R rhsType;

private:
	const L& lhs_;
	const R rhs_;
};


// expression type generator
template <typename L, typename R>
StrgSumExpr<L, R> operator+(const L& lhs, const R& rhs)
{
	return StrgSumExpr<L, R>(lhs, rhs);
}
template <typename L>
StrgSumExpr<L, const char*> operator+(const L& lhs, const char* rhs)
{
	return StrgSumExpr<L, const char*>(lhs, rhs);
}


// expression type user
class String 
	: public std::string
{
public:
  String(const std::string& s) : std::string(s) {}

  template <typename L, typename R>
  String(const StrgSumExpr<L, R>& expression)
  {
	  *this = expression;
  }

  template <typename L, typename R>
  String& operator = (const StrgSumExpr<L, R>& expression)
  {
	auto count = expression.count();
	auto size = expression.size();

    reserve(size);

    for(size_t i = 0; i < count; ++i)
    {
      append(expression[count - 1 - i]);
    }

    return *this;
  }
};


// this impl depends on the String lhs class
//  -- could avoid this by introducing an extra "recursion stopper"
template <typename L, typename R>
const char*
StrgSumExpr<L, R>::operator[] (std::size_t i) const
{
	switch (i)
	{
	case 0:
		return rhs_;
	default:
		return lhs_[i - 1];
	}
}

template <>
const char*
StrgSumExpr<String, const char*>::operator[] (std::size_t i) const
{
	switch (i)
	{
	case 0:
		return rhs_;
	case 1:
		return lhs_.c_str();
	default:
		assert(false && "at the end of the recursive struct");
		return "";
	}
}


}

#endif // EXPRESSIONTEMPL_H


