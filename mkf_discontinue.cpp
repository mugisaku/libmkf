#include"mkf_discontinue.hpp"
#include"mkf_charptr.hpp"
#include<cstdlib>
#include<cstdio>
#include<cstdarg>




namespace mkf{


void
discontinue(ErrorKind  k, const charptr&  p, const char*  fmt, ...)
{
  (*p).print();

  printf("\n");

  va_list  ap;
  va_start(ap,fmt);

  vprintf(fmt,ap);

  va_end(ap);

  printf("\n");


  throw k;
}


}




