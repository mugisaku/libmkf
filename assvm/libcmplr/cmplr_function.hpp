#ifndef CMPLR_FUNCTION_HPP_INCLUDED
#define CMPLR_FUNCTION_HPP_INCLUDED


#include"cmplr_statement.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_block.hpp"
#include<memory>




using ParameterList = std::vector<Declaration>;


struct Statement;
struct Block;
struct GlobalScope;
struct PreContext;


struct
Function
{
  std::string  identifier;

  std::list<Block>  block_list;

  ParameterList  parameter_list;

  size_t  local_object_size;

  std::unique_ptr<Block>  block;

   Function();
   Function(const mkf::Node&  src, PreContext&  prectx);


  Block&  make_block(BlockKind  k, int  count, const mkf::Node&  src, PreContext&  prectx);

  void  print(FILE*  f=stdout) const;

  void  compile_definition(Context&  ctx) const;

  void  read_declaration(const mkf::Node&  src, PreContext&  prectx);
  void   read_definition(const mkf::Node&  src, PreContext&  prectx);
  void    read_parameter(const mkf::Node&  src);

};




#endif




