#include <iostream>

template <char... String> struct Interned
{
  static constexpr char const value[sizeof...(String) + 1]{String...};
};

template <char... String> constexpr char const Interned<String...>::value[];

#if 1
// c++ 11 workaround
template<int N>
constexpr char chr(char const(&s)[N], int i) {
  return i < N ? s[i] : '\0';
}

#define intern_(s) Interned<chr(s,0),chr(s,1),chr(s,2),chr(s,3),chr(s,4),chr(s,5),chr(s,6)>::value

#else
// c++14 only
template<typename CharT, CharT ...String> constexpr const char *operator""_intern() {
  static_assert(std::is_same<CharT, char>(), "can only intern narrow strings");
  return (Interned<String...>::value);
}
#endif

int main()
{
#if 1
   // c++ 11
   std::cout <<  intern_("foo") << std::endl;
   std::cout <<  intern_("bar") << std::endl;
   std::cout <<  intern_("foo") << std::endl;

   std::cout <<  (intern_("foo") == intern_("foo")) << std::endl;
   std::cout <<  (intern_("foo") == intern_("bar")) << std::endl;
#else
   // c++ 14
   std::cout <<  "bar"_intern << std::endl;
   std::cout <<  "foo"_intern << std::endl;
   std::cout <<  "BOOO!"_intern << std::endl;

   std::cout <<  ("foo"_intern == "foo"_intern) << std::endl;
   std::cout <<  ("foo"_intern == "bar"_intern) << std::endl;

#endif
}
