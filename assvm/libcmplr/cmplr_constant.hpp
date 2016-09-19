#ifndef CMPLR_CONSTANT_HPP_INCLUDED
#define CMPLR_CONSTANT_HPP_INCLUDED


#include<string>
#include"cmplr_type.hpp"
#include<string>
#include<memory>




struct Context;
struct Declaration;


namespace expression{
struct Node;
}


struct
Constant
{
  Type  type;

  std::string  name;

  std::unique_ptr<expression::Node>  initexpr;

  std::unique_ptr<uint8_t[]>  data;

  Constant();
  Constant(Type&&  t, std::string&&  nam, expression::Node*  initexpr_=nullptr);

  Type  compile(const Declaration&  decl, Context&  ctx) const;

  void  compile_definition(const Declaration&  decl, Context&  ctx) const;

  void  print(FILE*  f=stdout) const;

};




#endif




