#include"mkf_discontinue.hpp"
#include<cstdlib>
#include<cstdio>
#include<cstdarg>




namespace mkf{


void
discontinue(ErrorKind  k, const pp::Character*  p, const char*  fmt, ...)
{
    if(p && p->unicode)
    {
      p->print(stdout,true);

      printf("\n");
    }


  va_list  ap;
  va_start(ap,fmt);

  vprintf(fmt,ap);

  va_end(ap);

  printf("\n");


  throw k;
}


}




