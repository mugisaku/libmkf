#include"cmplr_declaration.hpp"
#include"cmplr_context.hpp"




namespace{




void
compile_local_variable(const Declaration&  decl, Context&  ctx)
{
  ctx.push("  pshbp        ;//*********************************//\n");
  ctx.push("  psh16u %6d;//ローカル変数%sのアドレスを読み出し//\n",decl.offset,decl.name.data());
  ctx.push("  sub          ;//*********************************//\n");
}


Value
compile_inconstant(const Declaration&  decl, size_t  offset, Context&  ctx)
{
    switch(decl.storage_kind)
    {
      case(StorageKind::local):
        compile_local_variable(decl,ctx);
        break;
      case(StorageKind::local_static):
        ctx.push("  psh16u _STATIC_%06z;//%s\n",decl.offset,decl.name.data());
        break;
      case(StorageKind::global):
        ctx.push("  psh16u %s;\n",decl.name.data());
        break;
    }
}


}




Value
Declaration::
compile(Context&  ctx) const
{
/*
    switch(storage_kind)
    {
      case(StorageKind::local):
          switch(kind)
          {
        case(ValueKind::single):
            return compile_local_variable(decl,ctx);
            break;
        case(ValueKind::function):
            break;
          }
        break;
      case(StorageKind::local_static):
          switch(kind)
          {
        case(ValueKind::single):
            ctx.push_definition("_STATIC_%06z://%s\n",offset,name.data());
            ctx.push_definition("data i32 {%d};\n",i);
            break;
        case(ValueKind::function):
            break;
          }
        break;
      case(StorageKind::global):
          switch(kind)
          {
        case(ValueKind::single):
            ctx.push_definition("%s:\n",decl.name.data());
            ctx.push_definition("data i32 {%d};\n",i);
            break;
        case(ValueKind::function):
            break;
          }
        break;
    }
*/
}




void
Declaration::
compile_definition(Context&  ctx) const
{
/*
    switch(storage_kind)
    {
      case(StorageKind::local_static):
          switch(kind)
          {
        case(ValueKind::function):
            data.fn->compile_definition(ctx);
            break;
          }
        break;
      case(StorageKind::global):
          switch(kind)
          {
        case(ValueKind::function):
            data.fn->compile_definition(ctx);
            break;
          }
        break;
    }
*/
}




