#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"




Declaration::
Declaration():
storage_kind(StorageKind::null),
offset(0)
{
}


Declaration::
Declaration(const Parameter&  para, size_t  off):
storage_kind(StorageKind::null)
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




bool  Declaration::operator==(StorageKind  stkind) const{return storage_kind == stkind;}


const Value&
Declaration::
get_value() const
{
  return value;
}


void
Declaration::
reset(Function*  fn)
{
  storage_kind = StorageKind::global;

  value.~Value();

  new(&value) Value(fn);

  name = fn->name;
}


void
Declaration::
reset(const Parameter&  para, size_t  off)
{
  storage_kind = StorageKind::local;

  value.clear();

  value.kind = ValueKind::parameter;

  offset = off;

  value.type = para.type;
  name       = para.name;
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


  fprintf(f,"  %s = ",name.data());

  value.print(f);
}




