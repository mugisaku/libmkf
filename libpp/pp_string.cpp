#include"pp.hpp"
#include<cstdio>
#include<cctype>




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


bool
compare(const Character*  s1, const char16_t*  s2, size_t  length)
{
    while(length--)
    {
        if(s1->unicode != *s2)
        {
          return false;
        }


      ++s1;
      ++s2;
    }


  return true;
}


void
skip_spaces(const Character*&  p)
{
    while(isspace(p->unicode))
    {
      ++p;
    }
}


void
print(const Character*  s)
{
    while(s->unicode)
    {
      printf("%s",UTF8Chunk(s++->unicode).codes);
    }
}




}




