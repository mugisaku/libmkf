#ifndef CMPLR_BLOCK_HPP_INCLUDED
#define CMPLR_BLOCK_HPP_INCLUDED


#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_ctype.hpp"
#include"cmplr_statement.hpp"
#include"cmplr_declaration.hpp"
#include"expression_node.hpp"
#include<list>
#include<memory>




enum class
BlockKind
{
  plain,

  do_,

  if_,
  else_,

};


struct
Block
{
  const Function*  function;

  BlockKind  kind;

  int  index;

  std::list<Declaration>  declaration_list;
  std::list<Statement>      statement_list;

  std::shared_ptr<Literal>  condition;

  Block(                                                                                );
  Block(BlockKind  k                                                                    );
  Block(BlockKind  k, const mkf::Node&  src, PreContext&  prectx, Literal*  cond=nullptr);

  void  print(FILE*  f=stdout) const;

  void  compile_push_do_begin(Context&  ctx) const;
  void  compile_push_do_end(Context&  ctx) const;

  void  compile(Context&  ctx) const;
  void  compile_basic(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

};


#endif




