#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_variable.hpp"
#include"cmplr_constant.hpp"




Declaration::
Declaration():
storage_kind(StorageKind::null),
kind(DeclarationKind::null),
index(0)
{
}


Declaration::
Declaration(const Parameter&  par, int  i):
storage_kind(StorageKind::null),
kind(DeclarationKind::null)
{
  reset(par,i);
}


Declaration::
Declaration(const mkf::Node&  src, PreContext&  prectx):
kind(DeclarationKind::null)
{
  read(src,prectx);
}


Declaration::
Declaration(Declaration&&  rhs) noexcept:
kind(DeclarationKind::null)
{
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

  storage_kind = rhs.storage_kind;

  kind = rhs.kind                        ;
         rhs.kind = DeclarationKind::null;

  data = rhs.data;

  index = rhs.index;


  return *this;
}


void
Declaration::
clear()
{
    switch(kind)
    {
      case(DeclarationKind::function):
        delete data.fn;
        break;
      case(DeclarationKind::variable):
        delete data.var;
        break;
      case(DeclarationKind::constant):
        delete data.con;
        break;
      case(DeclarationKind::parameter):
        break;
    }


  kind = DeclarationKind::null;
}




size_t
Declaration::
get_size() const
{
    switch(kind)
    {
      case(DeclarationKind::function):
        return data.fn->signature.type.get_size();
        break;
      case(DeclarationKind::variable):
        return data.var->type.get_size();
        break;
      case(DeclarationKind::constant):
        return data.con->type.get_size();
        break;
      case(DeclarationKind::parameter):
        return data.par->type.get_size();
        break;
    }


  return 0;
}


const std::string&
Declaration::
get_name() const
{
    switch(kind)
    {
      case(DeclarationKind::function):
        return data.fn->signature.name;
        break;
      case(DeclarationKind::variable):
        return data.var->name;
        break;
      case(DeclarationKind::constant):
        return data.con->name;
        break;
      case(DeclarationKind::parameter):
        return data.par->name;
        break;
    }


  report;

  printf("データがありません\n");

  throw;
}


void
Declaration::
reset(Type&&  type, std::string&&  name, expression::Node*  initexpr)
{
  clear();

    if(type.constant)
    {
      kind = DeclarationKind::constant;

      data.con = new Constant(std::move(type),std::move(name),initexpr);
    }

  else
    {
      kind = DeclarationKind::variable;

      data.var = new Variable(std::move(type),std::move(name),initexpr);
    }
}


void
Declaration::
reset(Function*  fn)
{
  clear();

  storage_kind = StorageKind::global;

  kind = DeclarationKind::function;

  data.fn = fn;
}


void
Declaration::
reset(const Parameter&  par, int  i)
{
  clear();

  storage_kind = StorageKind::local;

  kind = DeclarationKind::parameter;

  data.par = &par;
}


expression::FoldResult
Declaration::
fold(FoldContext&  ctx) const
{
/*
    if(object_kind == ObjectKind::constant)
    {
      return expression::FoldResult(data.i);
    }
*/


  return expression::FoldResult();
}




Type
Declaration::
compile(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::function):
        return data.fn->compile(ctx);
        break;
      case(DeclarationKind::variable):
        return data.var->compile(*this,ctx);
        break;
      case(DeclarationKind::constant):
        return data.con->compile(*this,ctx);
        break;
      case(DeclarationKind::parameter):
        return data.par->compile(*this,ctx);
        break;
     }


  return Type();
}


void
Declaration::
compile_definition(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::function):
        data.fn->compile_definition(ctx);
        break;
      case(DeclarationKind::variable):
        data.var->compile_definition(*this,ctx);
        break;
      case(DeclarationKind::constant):
        data.con->compile_definition(*this,ctx);
        break;
      case(DeclarationKind::parameter):
        data.par->compile_definition(*this,ctx);
        break;
    }
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


    switch(kind)
    {
      case(DeclarationKind::function):
        data.fn->print(f);
        break;
      case(DeclarationKind::variable):
        data.var->print(f);
        break;
      case(DeclarationKind::constant):
        data.con->print(f);
        break;
      case(DeclarationKind::parameter):
        data.par->print(f);
        break;
    }
}




