#ifndef CMPLR_VARIABLE_HPP_INCLUDED
#define CMPLR_VARIABLE_HPP_INCLUDED


#include<string>
#include"cmplr_type.hpp"
#include"cmplr_initializer.hpp"




struct Context;
struct Declaration;


namespace expression{
struct Node;
}


struct
Variable
{
  Type  type;

  std::string  name;

  Initializer  initializer;


  Variable();
  Variable(Type&&  t, std::string&&  nam, Initializer&&  init=Initializer());

  Type  compile(const Declaration&  decl, Context&  ctx) const;

  void  compile_definition(const Declaration&  decl, Context&  ctx) const;

  void  print(FILE*  f=stdout) const;

};




#endif




