#ifndef EXPRESSION_OPERAND_HPP_INCLUDED
#define EXPRESSION_OPERAND_HPP_INCLUDED


#include<string>
#include"cmplr_declaration.hpp"
#include"cmplr_context.hpp"
#include"expression_foldresult.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"




namespace expression{
struct Node;
}


using ArgumentList = std::vector<expression::Node>;


namespace expression{


enum class
OperandKind
{
  null,
  integer,
  string,
  identifier,
  expression,
  argument_list,
  subscript,

};


struct Element;
struct Node;


struct
Identifier
{
  std::string*  s;

  Identifier(std::string*  s_): s(s_){};

};


struct
Subscript
{
  Node*  nd;

  Subscript(Node*  nd_): nd(nd_){};

};


struct
Operand
{
  OperandKind  kind;

  union Data{
    unsigned long  i;

    std::string*  s;

    Node*  nd;

    ArgumentList*  args;

  } data;


  Operand();
  Operand(std::string*  s);
  Operand(const Identifier&  id);
  Operand(unsigned long  i);
  Operand(Node*  nd);
  Operand(ArgumentList*  args);
  Operand(const Subscript&  subsc);
  Operand(const mkf::Node&  src);
  Operand(const Operand&  rhs);
  Operand(Operand&&  rhs) noexcept;
  ~Operand();


  Operand&  operator=(const Operand&   rhs);
  Operand&  operator=(      Operand&&  rhs) noexcept;

  void  clear();

  void  reset(unsigned long  i);
  void  reset(std::string*  s);
  void  reset(const Identifier&  id);
  void  reset(Node*  nd);
  void  reset(ArgumentList*  args);
  void  reset(const Subscript&  subsc);

  void  print(FILE*  f=stdout) const;

  FoldResult  fold(FoldContext&  ctx) const;

  ObjectKind  compile(Context&  ctx) const;

  void  read(const mkf::Node&  src);
  void  read_integer_literal(const mkf::Node&  src);
  void  read_character_literal(const mkf::Node&  src);

};


}


#endif




