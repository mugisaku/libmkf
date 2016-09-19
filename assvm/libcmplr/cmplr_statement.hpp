#ifndef CMPLR_STATEMENT_HPP_INCLUDED
#define CMPLR_STATEMENT_HPP_INCLUDED


#include<cstddef>
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_branchnode.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


struct Block;
struct PreContext;


enum class
StatementKind
{
  null,

  halt,
  print,

  block,
  branchnode,
  expression,
  declaration,
  break_,
  continue_,
  label_,
  return_,

};


struct
Print
{
  expression::Node*  expr;

  constexpr Print(expression::Node*  expr_): expr(expr_){}

};


struct
Continue
{
  Continue(){}

};


struct
Break
{
  Break(){}

};


struct
Halt
{
  Halt(){}

};


struct Function;
struct BlockChain;


struct
Statement
{
  StatementKind  kind;

  union{
    void*  ptr;

    int  i;

    const Declaration*    decl;
    const Block*           blk;

    std::string*            id;
    BranchNode*          brand;
    expression::Node*     expr;

  } data;


   Statement();
   Statement(const Block*  blk);
   Statement(const mkf::Node&  src, PreContext&  prectx);
   Statement(const Statement&)=delete;
   Statement(      Statement&&  rhs) noexcept;
  ~Statement();


  Statement&  operator=(Statement&&  rhs);

  operator bool() const;

  void  clear();

  void  reset(expression::Node*  expr);
  void  reset(BranchNode*  brand);
  void  reset(const Block*  blk);
  void  reset(const Declaration*  decl);
  void  reset(const Print&  prn);
  void  reset(const Halt&  hlt);
  void  reset(const Break&     brk);
  void  reset(const Continue&  con);

  void  print(FILE*  f=stdout) const;

  void  compile(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  void  read_print_statement(const mkf::Node&  src, PreContext&  prectx);

  void  read_control_statement( const mkf::Node&  src, PreContext&  prectx);
  void     read_if_statement(   const mkf::Node&  src, PreContext&  prectx);
  void     read_do_statement(   const mkf::Node&  src, PreContext&  prectx);
  void  read_return_statement(  const mkf::Node&  src, PreContext&  prectx);

};




#endif




