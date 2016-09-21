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


//////////////////////////
//スタックフレームの構造//
//////////////////////////
//**リターンアドレス**//
//**関数呼び出し時のスタックアドレス**//
//**関数呼び出し時のベースアドレス**//
//**最初の実引数**//
//**||||||||||||**//
//**最後の実引数**//
//**呼び出す関数のアドレス**//関数から戻ると、ここに返り値が置かれる
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




