#include"cmplr_value.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_precontext.hpp"




Value::
Value():
kind(ValueKind::null)
{
}


Value::
Value(Function*  fn):
kind(ValueKind::function),
type(fn)
{
  data.fn = fn;
}


Value::
Value(const Declaration&  decl):
kind(ValueKind::reference),
type(decl.get_value().type)
{
  data.v = &decl.get_value();
}


Value::
Value(const mkf::Node&  src, PreContext&  prectx):
kind(ValueKind::null)
{
  read(src,prectx);
}


Value::
Value(const Value&  rhs) noexcept:
kind(ValueKind::null)
{
  *this = rhs;
}


Value::
Value(Value&&  rhs) noexcept:
kind(ValueKind::null)
{
  *this = std::move(rhs);
}


Value::
Value(Type&&  t, int  i):
kind(ValueKind::single),
type(std::move(t))
{
}


Value::
Value(Type&&  t, ValueList*  ls):
kind(ValueKind::array),
type(std::move(t))
{
  data.ls = ls;
}


Value::
~Value()
{
  clear();
}




Value&
Value::
operator=(const Value&   rhs) noexcept
{
  clear();

  kind = rhs.kind;
  type = rhs.type;

    switch(kind)
    {
  case(ValueKind::single):
      data.nd = new expression::Node(*rhs.data.nd);
      break;
  case(ValueKind::array):
      data.ls = new ValueList(*rhs.data.ls);
      break;
  case(ValueKind::function):
      data.fn = new Function(*rhs.data.fn);
      break;
  case(ValueKind::reference):
      data.v = rhs.data.v;
      break;
    }


  return *this;
}


Value&
Value::
operator=(Value&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                  ;
         rhs.kind = ValueKind::null;

  type = std::move(rhs.type);

  data = rhs.data;


  return *this;
}




void
Value::
clear()
{
    switch(kind)
    {
  case(ValueKind::single):
      delete data.nd;
      break;
  case(ValueKind::array):
      delete data.ls;
      break;
  case(ValueKind::function):
      delete data.fn;
      break;
    }


  kind = ValueKind::null;

  type.clear();
}


bool
Value::
dereference()
{
    if(type != TypeKind::reference)
    {
      printf("参照でないオブジェクトから値を取り出そうとしました\n");

      return false;
    }


  type = *type->ptr.referred;

  return true;
}


bool
Value::
change_reference_to_pointer()
{
    if(type != TypeKind::reference)
    {
      printf("参照でないオブジェクトから値を取り出そうとしました\n");

      return false;
    }


  type.change_kind(TypeKind::pointer);

  return true;
}




Value
Value::
compile(Context&  ctx) const
{
}




void
Value::
print(FILE*  f) const
{
    switch(kind)
    {
  case(ValueKind::single):
      data.nd->print(f);
      break;
  case(ValueKind::array):
      fprintf(f,"{");

        for(auto&  v: *data.ls)
        {
          v.print(f);

          fprintf(f,",");
        }


      fprintf(f,"}");
      break;
  case(ValueKind::function):
      data.fn->print(f);
      break;
    }
}




void
Value::
read(const mkf::Node&  src, PreContext&  prectx)
{
  clear();

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          kind = ValueKind::single;

          data.nd = new expression::Node(nd,prectx);
        }

      else
        if(nd == "value_list")
        {
          kind = ValueKind::array;

          data.ls = new ValueList(read_list(nd,prectx));
        }


      cur.advance();
    }
}


ValueList
Value::
read_list(const mkf::Node&  src, PreContext&  prectx)
{
  ValueList  ls;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "value")
        {
          ls.emplace_back(nd,prectx);
        }


      cur.advance();
    }


  return std::move(ls);
}




