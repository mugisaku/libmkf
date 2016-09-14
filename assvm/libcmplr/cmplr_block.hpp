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

  function,
  do_,
  if_,
  elseif,
  else_,

};


struct
Block
{
  BlockKind  kind;

  std::string  label;

  std::list<Declaration>  declaration_list;
  std::list<Statement>      statement_list;

  int  index;

  std::unique_ptr<expression::Node>  condition;
  std::unique_ptr<Block>            next_block;

  Block(                                                                                                                      );
  Block(BlockKind  k, std::string&&  id, int  i=0                                                                             );
  Block(BlockKind  k, std::string&&  id, const mkf::Node&  src, PreContext&  prectx, int  i=0, expression::Node*  cond=nullptr);

  void  print(FILE*  f=stdout) const;

  void  compile(Context&  ctx);

  void  read(const mkf::Node&  src, PreContext&  prectx);

};


#endif




