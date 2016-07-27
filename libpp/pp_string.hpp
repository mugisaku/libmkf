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
String: public std::vector<Character>
{

public:
  String();

  explicit String(Stream&  s);

  std::string  to_stdstring() const;

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


}


#endif




