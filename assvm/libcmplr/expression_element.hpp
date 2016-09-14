#ifndef EXPRESSION_ELEMENT_HPP_INCLUDED
#define EXPRESSION_ELEMENT_HPP_INCLUDED


#include"expression_operand.hpp"
#include"expression_operator.hpp"
#include<cstdint>




namespace expression{


enum class
ElementKind
{
  null,
  operand,
  unary_operator,
  binary_operator,

};


enum class
Associativity
{
  none,
  left_to_right,
  right_to_left,

};


struct
Precedence
{
  int  number;

  constexpr Precedence(int  n=0): number(n){}

};


struct
Element
{
  ElementKind  kind;

  union Data{
   Operator  operator_;

   Operand  operand;

   Data(                        ){}
   Data(Operand&&              o): operand(std::move(o)){}
   Data(const UnaryOperator&   o): operator_(o){}
   Data(const BinaryOperator&  o): operator_(o){}
   ~Data(){}

  } data;


  Element();
  Element(Operand&&  o);
  Element(const UnaryOperator&  o);
  Element(const BinaryOperator&  o);
  Element(const Element&  rhs);
  Element(Element&&  rhs) noexcept;
  ~Element();


  Element&  operator=(const Element&   rhs)         ;
  Element&  operator=(      Element&&  rhs) noexcept;

  operator   ElementKind() const;
  operator Associativity() const;
  operator    Precedence() const;

  void  clear();

  void  print(FILE*  f=stdout, bool  parenthesis=false) const;

};


}


#endif




