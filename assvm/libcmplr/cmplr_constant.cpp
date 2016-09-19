#include"cmplr_constant.hpp"
#include"cmplr_context.hpp"
#include"cmplr_declaration.hpp"
#include"expression_node.hpp"




Constant::
Constant()
{
}


Constant::
Constant(Type&&  t, std::string&&  nam, expression::Node*  initexpr_):
type(std::move(t)),
name(std::move(nam)),
initexpr(initexpr_)
{
}




Type
Constant::
compile(const Declaration&  decl, Context&  ctx) const
{
  ctx.push("  pshi32 %d;//constexpr\n",5);

  return type;
}


void
Constant::
compile_definition(const Declaration&  decl, Context&  ctx) const
{
    switch(decl.storage_kind)
    {
      case(StorageKind::local):
        break;
      case(StorageKind::local_static):
        break;
      case(StorageKind::global):
        break;
    }
}


void
Constant::
print(FILE*  f) const
{
  type.print(f);

  fprintf(f,"  %s",name.data());

    if(initexpr)
    {
      fprintf(f," = ");

      initexpr->print(f);
    }
}





