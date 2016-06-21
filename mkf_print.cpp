#include"mkf_print.hpp"
#include<cstdlib>
#include<cstdio>
#include<cstdarg>




namespace mkf{




Printer::
Printer(int  depth_, FILE*  f_, std::string*  s_):
depth(depth_),
f(f_),
s(s_)
{
}




void
Printer::
set(FILE*  f_)
{
  f = f_;
}


void
Printer::
set(std::string*  s_)
{
  s = s_;
}


void
Printer::
close()
{
    if(f)
    {
      fclose(f)         ;
             f = nullptr;
    }
}


void  Printer::operator++(){++depth;}
void  Printer::operator--(){--depth;}


void
Printer::
indent()
{
  int  i = depth;

    while(i--)
    {
        if(f){fprintf(f,"  ");}
        if(s){s->append("  ");}
    }
}


void
Printer::
printf(const char*  fmt, ...)
{
  char  buf[256];

  indent();

  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(buf,sizeof(buf),fmt,ap);

  va_end(ap);


    if(f){fprintf(f,"%s",buf);}
    if(s){s->append(buf);}
}


void
Printer::
putc(int  c, bool  natural)
{
    if(natural)
    {
        if(f){fputc(c,f);}
        if(s){s->push_back(c);}

      return;
    }


  char  buf[2] = {0};

  const char*  str = nullptr;

    switch(c)
    {
      case(0   ): str = "(null)";break;
      case(' ' ): str = "(space)";break;
      case('\n'): str = "(newline)";break;
      case('\t'): str = "(tab)";break;
      default:
        buf[0] = c;
        str = buf;
    }


    if(f){fprintf(f,"%s",str);}
    if(s){s->append(str);}
}


void
Printer::
puts(const char*  s)
{
  indent();

    while(*s)
    {
      putc(*s++,true);
    }
}




}




