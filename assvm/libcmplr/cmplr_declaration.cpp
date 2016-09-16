#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"




Declaration::
Declaration():
index(0),
kind(DeclarationKind::global),
object_kind(ObjectKind::null)
{
  data.ptr = nullptr;
}


Declaration::
Declaration(DeclarationKind  k, std::string&&  id, expression::Node*  expr):
identifier(std::move(id)),
index(0),
kind(k),
object_kind(expr? ObjectKind::value:ObjectKind::null)
{
  data.expr = expr;
}


Declaration::
Declaration(const Function*  fn):
index(0),
kind(DeclarationKind::global),
object_kind(ObjectKind::null)
{
  data.ptr = nullptr;

  reset(fn);
}


Declaration::
Declaration(Declaration&&  rhs) noexcept:
kind(DeclarationKind::global),
object_kind(ObjectKind::null)
{
  data.ptr = nullptr;

  *this = std::move(rhs);
}


Declaration::
~Declaration()
{
  clear();
}




Declaration&
Declaration::
operator=(Declaration&&  rhs) noexcept
{
  clear();

  identifier = std::move(rhs.identifier);

  index = rhs.index;

  kind = rhs.kind;

  object_kind = rhs.object_kind                   ;
                rhs.object_kind = ObjectKind::null;

  data = rhs.data;

  return *this;
}


size_t
Declaration::
get_size() const
{
    switch(object_kind)
    {
      case(ObjectKind::function):
      case(ObjectKind::value):
      case(ObjectKind::constant):
      case(ObjectKind::reference):
        return assvm::word_size;
        break;
      case(ObjectKind::array):
        return assvm::word_size*data.arr->size();
        break;
      case(ObjectKind::constant_array):
        return assvm::word_size*data.carr->size();
        break;
    }


  return 0;
}


void
Declaration::
clear()
{
  identifier.clear();

    switch(object_kind)
    {
      case(ObjectKind::function):
      case(ObjectKind::reference):
      case(ObjectKind::constant):
        break;
      case(ObjectKind::value):
        delete data.expr;
        break;
      case(ObjectKind::array):
        delete data.arr;
        break;
      case(ObjectKind::constant_array):
        delete data.carr;
        break;
    }


  data.ptr = nullptr;

  object_kind = ObjectKind::null;
}


void
Declaration::
reset(const Function*  fn)
{
  clear();

  identifier = fn->identifier;

  kind = DeclarationKind::global;

  object_kind = ObjectKind::function;

  data.fn = fn;
}


expression::FoldResult
Declaration::
fold(FoldContext&  ctx) const
{
    if(object_kind == ObjectKind::constant)
    {
      return expression::FoldResult(data.i);
    }


  return expression::FoldResult();
}





