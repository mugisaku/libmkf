#include"pp.hpp"
#include<cstdio>




namespace pp{




String::
String()
{
}


String::
String(const char16_t*  s)
{
    while(*s)
    {
      push_back(Character(Position(),0,*s++));
    }
}


String::
String(Stream&  s)
{
  reset(s);
}




std::string
String::
to_stdstring() const
{
  std::string  buf;

    for(auto&  c: *this)
    {
      buf.append(UTF8Chunk(c.unicode).codes);
    }


  return std::move(buf);
}


void
String::
print(FILE*  f, bool  verbose) const
{
    for(auto&  c: *this)
    {
      c.print(f,verbose);

        if(verbose)
        {
          fprintf(f,"\n");
        }
    }
}


void
print(const Character*  s)
{
    while(*s)
    {
      printf("%s",UTF8Chunk(s++->unicode).codes);
    }
}




}




