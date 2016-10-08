#include"cmplr_literal.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_precontext.hpp"




void
Literal::
reset(int8_t  i)
{
  clear();

  kind = LiteralKind::integer;

  data.i = i;
}


void
Literal::
reset(uint8_t  i)
{
  clear();

  kind = LiteralKind::integer;

  data.i = i;
}


void
Literal::
reset(int16_t  i)
{
  clear();

  kind = LiteralKind::integer;

  data.i = i;
}


void
Literal::
reset(uint16_t  i)
{
  clear();

  kind = LiteralKind::integer;

  data.i = i;
}


void
Literal::
reset(int32_t  i)
{
  clear();

  kind = LiteralKind::integer;

  data.i = i;
}


void
Literal::
reset(char16_t  c)
{
  clear();

  kind = LiteralKind::character;

  data.c = c;
}


void
Literal::
reset(std::string*  id)
{
  clear();

  kind = LiteralKind::identifier;

  data.id = id;
}


void
Literal::
reset(nullptr_t  nul)
{
  clear();

  kind = LiteralKind::nullptr_;
}


void
Literal::
reset(bool  b)
{
  clear();

  kind = LiteralKind::boolean;

  data.b = b;
}


void
Literal::
reset(std::u16string*  s)
{
  clear();

  kind = LiteralKind::string;

  data.s = s;
}


void
Literal::
reset(expression::Node*  nd)
{
  clear();

  kind = LiteralKind::expression;

  data.nd = nd;
}


void
Literal::
reset(Array*  arr)
{
  clear();

  kind = LiteralKind::array;

  data.arr = arr;
}


void
Literal::
reset(Function*  fn)
{
  clear();

  kind = LiteralKind::function;

  data.fn = fn;
}


void
Literal::
reset(const ArgumentList&  args)
{
  clear();

  kind = LiteralKind::argument_list;

  data.arr = args.arr;
}


void
Literal::
reset(const Subscript&  subsc)
{
  clear();

  kind = LiteralKind::subscript;

  data.lit = subsc.lit;
}




