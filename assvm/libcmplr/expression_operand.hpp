#ifndef EXPRESSION_OPERAND_HPP_INCLUDED
#define EXPRESSION_OPERAND_HPP_INCLUDED


#include<string>
#include"cmplr_declaration.hpp"
#include"cmplr_context.hpp"
#include"cmplr_type.hpp"
#include"expression_foldresult.hpp"
#include"mkf_node.hpp"




namespace expression{
struct Node;
}


using NodeList = std::vector<expression::Node>;


struct
ArgumentList
{
  NodeList*  node_list;

  constexpr ArgumentList(NodeList*  ls): node_list(ls){}

};


struct
ExpressionList
{
  NodeList*  node_list;

  constexpr ExpressionList(NodeList*  ls): node_list(ls){}

};


struct Initializer;


namespace expression{


enum class
OperandKind
{
  null,
  integer,
  string,
  identifier,
  expression,
  expression_list,
  argument_list,
  subscript,

};


struct Element;
struct Node;


struct
Identifier
{
  std::string*  s;

  constexpr Identifier(std::string*  s_): s(s_){};

};


struct
Subscript
{
  Node*  nd;

  constexpr Subscript(Node*  nd_): nd(nd_){};

};


struct
Operand
{
  OperandKind  kind;

  union Data{
    unsigned long  i;

    std::string*  s;

    Node*  nd;

    NodeList*  ndls;

  } data;


  Operand();
  Operand(std::string*  s);
  Operand(const Identifier&  id);
  Operand(unsigned long  i);
  Operand(Node*  nd);
  Operand(Initializer&&  init);
  Operand(const ArgumentList&  args);
  Operand(const ExpressionList&  exprs);
  Operand(const Subscript&  subsc);
  Operand(const mkf::Node&  src, PreContext&  prectx);
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
  void  reset(Initializer&&  init);
  void  reset(const ArgumentList&  args);
  void  reset(const ExpressionList&  exprs);
  void  reset(const Subscript&  subsc);

  void  print(FILE*  f=stdout) const;

  FoldResult  fold(FoldContext&  ctx) const;

  Type  compile(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  static unsigned int    read_integer_literal(const mkf::Node&  src);
  static int           read_character_literal(const mkf::Node&  src);
  static std::string      read_string_literal(const mkf::Node&  src);

};


}


#endif




