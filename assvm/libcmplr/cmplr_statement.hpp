#ifndef CMPLR_STATEMENT_HPP_INCLUDED
#define CMPLR_STATEMENT_HPP_INCLUDED


#include<cstddef>
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"


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

    const Declaration*    decl;
    std::string*            id;
    Block*                 blk;
    expression::Node*     expr;

  } data;


   Statement();
   Statement(Block*  blk);
   Statement(const mkf::Node&  src, PreContext&  prectx);
   Statement(const Statement&)=delete;
   Statement(      Statement&&  rhs) noexcept;
  ~Statement();


  Statement&  operator=(Statement&&  rhs);

  operator bool() const;

  void  clear();

  void  reset(expression::Node*  expr);
  void  reset(Block*  blk);
  void  reset(const Declaration*  decl);
  void  reset(const Print&  prn);
  void  reset(const Halt&  hlt);
  void  reset(const Break&     brk);
  void  reset(const Continue&  con);

  void  print(FILE*  f=stdout) const;

  void  compile(Context&  ctx);

  void  read(const mkf::Node&  src, PreContext&  prectx);

  void    read_print_statement(const mkf::Node&  src);

  void  read_control_statement( const mkf::Node&  src, PreContext&  prectx);
  void     read_if_statement(   const mkf::Node&  src, PreContext&  prectx);
  void     read_do_statement(   const mkf::Node&  src, PreContext&  prectx);
  void  read_return_statement(  const mkf::Node&  src);


  void  read_declaration(const mkf::Node&  base, PreContext&  prectx);

  static Declaration    read_var_declaration(const mkf::Node&  base, PreContext&  prectx);
  static Declaration  read_const_declaration(const mkf::Node&  base, PreContext&  prectx);

  void       read_enum_declaration(const mkf::Node&  base);

};




#endif




