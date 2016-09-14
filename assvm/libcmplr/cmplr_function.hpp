#ifndef CMPLR_FUNCTION_HPP_INCLUDED
#define CMPLR_FUNCTION_HPP_INCLUDED


#include"cmplr_statement.hpp"
#include"cmplr_declaration.hpp"




using ParameterList = std::vector<Declaration>;


struct Statement;
struct GlobalScope;
struct PreContext;


struct
Function
{
  std::string  identifier;

  ParameterList  parameter_list;

  size_t  local_object_size;

  unsigned int  nolabel_block_count;
  unsigned int       do_block_count;
  unsigned int   switch_block_count;
  unsigned int        if_node_count;


  Statement  statement;

   Function();
   Function(const mkf::Node&  src, PreContext&  prectx);


  void  print(FILE*  f=stdout) const;

  void  compile_definition(Context&  ctx);

  void  read_declaration(const mkf::Node&  src, PreContext&  prectx);
  void   read_definition(const mkf::Node&  src, PreContext&  prectx);
  void    read_parameter(const mkf::Node&  src);

};




#endif




