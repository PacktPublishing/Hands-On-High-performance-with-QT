#include <cstring>
#include <complex>
#include <cstdio>


// undefined behaviour in loop
int main()
{
  std::complex<int> delta;
  std::complex<int> mc[4]= {0};

  for (int di=0; di < 4; di++, delta = mc[di])
  {
    //std::cout << di << std::endl;
    printf("%i\n", di);
  }
}


// dead store elimination
bool AskForUserPassd(const char* passwd, size_t pwdSize);

void GetData(char* RemoteAddr)
{
  char passwd[64];
  if (AskForUserPassd(passwd, sizeof(passwd)))
  {
     // get data from remote ..
  }
  // erase the passwd form cache!
  memset(passwd, 0, sizeof(passwd));
}


