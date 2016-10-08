#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"




Declaration::
Declaration():
storage_kind(StorageKind::null),
offset(0)
{
}


Declaration::
Declaration(const Parameter&  para, size_t  off)
{
  reset(para,off);
}


Declaration::
Declaration(const mkf::Node&  src, PreContext&  prectx):
storage_kind(StorageKind::null),
offset(0)
{
  read(src,prectx);
}




bool
Declaration::
operator==(StorageKind  stkind) const
{
  return storage_kind == stkind;
}




void
Declaration::
reset(Type&&  typ, Literal&&  lit)
{
  type    = std::move(typ);
  literal = std::move(lit);
}


void
Declaration::
reset(Function*  fn)
{
  type = FunctionType();

  literal.reset(fn);

  name = fn->name;
}


void
Declaration::
reset(const Parameter&  para, size_t  off)
{
  storage_kind = StorageKind::parameter;

  offset = off;

  type = Type(para.type);

  name = para.name;
}




Value
Declaration::
make_value() const
{
  return Value();
}


void
Declaration::
print(FILE*  f) const
{
    switch(storage_kind)
    {
  case(StorageKind::local_static):
      fprintf(f,"static ");
  case(StorageKind::local):
  case(StorageKind::global):
      break;
    }


  type.print(f);

  fprintf(f,"  %s = ",name.data());

  literal.print(f);
}




