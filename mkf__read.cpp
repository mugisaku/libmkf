#include"mkf__read.hpp"
#include<cstdio>
#include<limits>




namespace mkf{




unsigned int
read_decimal_integer(const Node&  src)
{
  unsigned int  i = 0;

  std::string  s;

  src.collect_characters(s);

  auto  p = s.data();

    while(*p)
    {
      auto  c = *p++;

      i *= 10;

        switch(c)
        {
          case('0'): i += 0;break;
          case('1'): i += 1;break;
          case('2'): i += 2;break;
          case('3'): i += 3;break;
          case('4'): i += 4;break;
          case('5'): i += 5;break;
          case('6'): i += 6;break;
          case('7'): i += 7;break;
          case('8'): i += 8;break;
          case('9'): i += 9;break;

          default:
            report;
        }
    }


  return i;
}


unsigned int
read_binary_integer(const Node&  src)
{
  unsigned int  i = 0;

  std::string  s;

  src.collect_characters(s);

  auto  p = s.data();

    while(*p)
    {
      auto  c = *p++;

      i <<= 1;

        switch(c)
        {
          case('0'): i |= 0;break;
          case('1'): i |= 1;break;

          default:
            report;
        }
    }


  return i;
}


unsigned int
read_hex_integer(const Node&  src)
{
  unsigned int  i = 0;

  std::string  s;

  src.collect_characters(s);

  auto  p = s.data();

    while(*p)
    {
      auto  c = *p++;

      i <<= 4;

        switch(c)
        {
          case('0'): i |= 0;break;
          case('1'): i |= 1;break;
          case('2'): i |= 2;break;
          case('3'): i |= 3;break;
          case('4'): i |= 4;break;
          case('5'): i |= 5;break;
          case('6'): i |= 6;break;
          case('7'): i |= 7;break;
          case('8'): i |= 8;break;
          case('9'): i |= 9;break;

          case('a'):
          case('A'): i |= 0xA;break;
          case('b'):
          case('B'): i |= 0xB;break;
          case('c'):
          case('C'): i |= 0xC;break;
          case('d'):
          case('D'): i |= 0xD;break;
          case('e'):
          case('E'): i |= 0xE;break;
          case('f'):
          case('F'): i |= 0xF;break;

          default:
            report;
        }
    }


  return i;
}


}




