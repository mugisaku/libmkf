#ifndef CMPLR_SIGNATURE_HPP_INCLUDED
#define CMPLR_SIGNATURE_HPP_INCLUDED


#include"typesystem_element.hpp"
#include"cmplr_parameter.hpp"
#include<string>


struct
Signature
{
  Type  type;

  std::string  name;

  std::vector<Parameter>  parameter_list;

  Signature();
  Signature(const mkf::Node&  src);


  void  print(FILE*  f=stdout) const;

  void  read(const mkf::Node&  src);

};




#endif




