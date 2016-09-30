#ifndef CMPLR_FUNCTION_HPP_INCLUDED
#define CMPLR_FUNCTION_HPP_INCLUDED


#include"cmplr_parameter.hpp"
#include"cmplr_statement.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_block.hpp"
#include<memory>




struct Statement;
struct Block;
struct GlobalScope;
struct PreContext;


//////////////////////////
//スタックフレームの構造//
//////////////////////////
//**リターンアドレス**//
//**ベースアドレス**//
//**最初の実引数**//
//**||||||||||||**//
//**最後の実引数**//
//**一時変数...**//
//**|||||||||||**//
//**一時変数...**//
//**局所変数...**//
//**|||||||||||**//
//**局所変数...**//
/////////////////////////


struct
Function
{
  std::string  name;

  Type  type;

  std::vector<Parameter>  parameter_list;

  std::list<Block>  block_list;

  size_t  local_object_size;

  std::shared_ptr<Block>  block;

  Function();


  Block&  make_block(BlockKind  k, int  count, const mkf::Node&  src, PreContext&  prectx);

  void  print(FILE*  f=stdout) const;

  Type  compile(Context&  ctx) const;
  void  compile_definition(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

};




#endif




