#ifndef CMPLR_FUNCTION_HPP_INCLUDED
#define CMPLR_FUNCTION_HPP_INCLUDED


#include"cmplr_statement.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_signature.hpp"
#include"cmplr_block.hpp"
#include<memory>




struct Statement;
struct Block;
struct GlobalScope;
struct PreContext;


struct
Function
{
  Signature  signature;

  std::list<Block>  block_list;

  size_t  local_object_size;

  std::unique_ptr<Block>  block;

  Function();
  Function(const mkf::Node&  src, PreContext&  prectx);


  Block&  make_block(BlockKind  k, int  count, const mkf::Node&  src, PreContext&  prectx);

  void  print(FILE*  f=stdout) const;

  Type  compile(Context&  ctx) const;
  void  compile_definition(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

};




#endif




