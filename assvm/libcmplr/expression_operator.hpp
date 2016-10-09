#ifndef EXPRESSION_OPERATOR_HPP_INCLUDED
#define EXPRESSION_OPERATOR_HPP_INCLUDED


#include<cstring>
#include"cmplr_constant.hpp"
#include"cmplr_value.hpp"
#include"typesystem_element.hpp"




struct PreContext;
struct Context;


namespace expression{


struct Node;


struct
Operator
{
  char  codes[4];


  Operator(const char*  s);


constexpr Operator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
codes{c0,c1,c2,c3}
{}


constexpr operator uint32_t() const
{
  return((codes[0]<<24)|
         (codes[1]<<16)|
         (codes[2]<< 8)|
         (codes[3]    ));
}

};


struct
UnaryOperator: Operator
{
constexpr UnaryOperator(const Operator&  src):
Operator(src)
{}

constexpr UnaryOperator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
Operator(c0,c1,c2,c3)
{}

UnaryOperator(const char*  s): Operator(s){}
};


struct
BinaryOperator: Operator
{
constexpr BinaryOperator(const Operator&  src):
Operator(src)
{}


constexpr BinaryOperator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
Operator(c0,c1,c2,c3)
{}


BinaryOperator(const char*  s): Operator(s){}
};




Type  compile(const Node&  l                , const UnaryOperator&   op, Context&  ctx);
Type  compile(const Node&  l, const Node&  r, const BinaryOperator&  op, Context&  ctx);

Value  make_value(const Node&  l                , const UnaryOperator&   op, PreContext&  prectx);
Value  make_value(const Node&  l, const Node&  r, const BinaryOperator&  op, PreContext&  prectx);

Constant  make_constant(const Node&  l                , const UnaryOperator&   op, PreContext&  prectx);
Constant  make_constant(const Node&  l, const Node&  r, const BinaryOperator&  op, PreContext&  prectx);


}


#endif




