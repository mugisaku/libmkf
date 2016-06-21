#ifndef MKF_PRINT_HPP_INCLUDED
#define MKF_PRINT_HPP_INCLUDED


#include<cstdio>
#include<string>


namespace mkf{


class
Printer
{
  int  depth;

  FILE*  f;

  std::string*  s;

public:
  Printer(int  depth_=0, FILE*  f_=stdout, std::string*  s_=nullptr);


  void  set(FILE*  f_);
  void  set(std::string*  s_);

  void  close();

  void  operator++();
  void  operator--();

  void  indent();

  void  printf(const char*  fmt, ...);

  void  putc(int  c, bool  natural=false);
  void  puts(const char*  s);
  
};


}




#endif




