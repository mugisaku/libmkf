#ifndef ASSVM_OPERAND_HPP_INCLUDED
#define ASSVM_OPERAND_HPP_INCLUDED


#include<string>
#include<cstddef>
#include<cstdio>
#include"mkf_node.hpp"


namespace assvm{


struct
Operand
{
  int  value;

  std::string  identifier;


  Operand();
  Operand(const mkf::Node&  src);

  void  read(const mkf::Node&  src);

  void  print(FILE*  f=stdout) const;

};


}




#endif




