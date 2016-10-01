#include"cmplr_value.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_precontext.hpp"




void
Value::
reset(int8_t  i)
{
  clear();

  kind = ValueKind::integer;

  type = ConstI8Type();

  data.i = i;
}


void
Value::
reset(uint8_t  i)
{
  clear();

  kind = ValueKind::integer;

  type = ConstU8Type();

  data.i = i;
}


void
Value::
reset(int16_t  i)
{
  clear();

  kind = ValueKind::integer;

  type = ConstI16Type();

  data.i = i;
}


void
Value::
reset(uint16_t  i)
{
  clear();

  kind = ValueKind::integer;

  type = ConstU16Type();

  data.i = i;
}


void
Value::
reset(int32_t  i)
{
  clear();

  kind = ValueKind::integer;

  type = ConstI32Type();

  data.i = i;
}


void
Value::
reset(char16_t  c)
{
  clear();

  kind = ValueKind::character;

  type = ConstCharType();

  data.c = c;
}


void
Value::
reset(std::string*  id)
{
  clear();

  kind = ValueKind::identifier;

  data.id = id;
}


void
Value::
reset(nullptr_t  nul)
{
  clear();

  type = NullptrType();

  kind = ValueKind::nullptr_;
}


void
Value::
reset(bool  b)
{
  clear();

  kind = ValueKind::boolean;

  type = ConstBoolType();

  data.b = b;
}


void
Value::
reset(std::u16string*  s)
{
  clear();

  kind = ValueKind::string;

  data.s = s;
}


void
Value::
reset(expression::Node*  nd)
{
  clear();

  kind = ValueKind::expression;

  data.nd = nd;
}


void
Value::
reset(ValueList*  ls)
{
  clear();

  kind = ValueKind::value_list;

  data.ls = ls;
}


void
Value::
reset(Function*  fn)
{
  clear();

  type = Type(fn);

  kind = ValueKind::function;

  data.fn = fn;
}


void
Value::
reset(const ArgumentList&  args)
{
  clear();

  kind = ValueKind::argument_list;

  data.ls = args.value_list;
}


void
Value::
reset(const Subscript&  subsc)
{
  clear();

  kind = ValueKind::subscript;

  data.nd = subsc.nd;
}




