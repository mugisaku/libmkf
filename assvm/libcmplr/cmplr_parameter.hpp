#ifndef CMPLR_PARAMETER_HPP_INCLUDED
#define CMPLR_PARAMETER_HPP_INCLUDED


#include"typesystem_element.hpp"
#include<string>


struct
Parameter
{
  Type  type;

  std::string  name;

  Parameter(const mkf::Node&  src){read(src);}

  void  read(const mkf::Node&  src);

  void  print(FILE*  f=stdout) const;

};




#endif




