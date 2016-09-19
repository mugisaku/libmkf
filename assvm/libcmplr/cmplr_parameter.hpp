#ifndef CMPLR_PARAMETER_HPP_INCLUDED
#define CMPLR_PARAMETER_HPP_INCLUDED


#include"cmplr_type.hpp"
#include"mkf_node.hpp"
#include<string>
#include<vector>




struct Declaration;
struct Context;


struct
Parameter
{
  Type  type;

  std::string  name;

  Parameter(                     );
  Parameter(const mkf::Node&  src);

  Type  compile(const Declaration&  decl, Context&  ctx) const;

  void  compile_definition(const Declaration&  decl, Context&  ctx) const;

  void  print(FILE*  f=stdout) const;

  void  read(const mkf::Node&  src);

};


using ParameterList = std::vector<Parameter>;


#endif




