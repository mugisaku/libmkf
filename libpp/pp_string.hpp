#ifndef PP_STRING_HPP_INCLUDED
#define PP_STRING_HPP_INCLUDED


#include"pp_character.hpp"
#include"pp_stream.hpp"
#include<vector>



namespace pp{


struct
ErrorOnInclude
{
};


struct
ErrorOnIncludeOnce
{
};




class
String: public std::basic_string<Character>
{

public:
  String();
  explicit String(const char16_t*  s);
  explicit String(Stream&  s);


  void  reset(Stream&  s);

  std::string  to_stdstring() const;

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


unsigned int  to_uint(const Character*  ptr, const Character**  endptr, int  base=10);

bool  compare(const Character*  s1, const char16_t*  s2, size_t  length);

void  skip_spaces(const Character*&  p);

void  print(const Character*  s);


}


#endif




