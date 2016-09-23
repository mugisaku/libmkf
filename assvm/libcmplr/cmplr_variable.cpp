#include"cmplr_variable.hpp"
#include"cmplr_context.hpp"
#include"cmplr_declaration.hpp"
#include"expression_node.hpp"




Variable::
Variable()
{
}


Variable::
Variable(Type&&  t, std::string&&  nam, Initializer&&  init):
type(std::move(t)),
name(std::move(nam)),
initializer(std::move(init))
{
}




void
compile_local(const Declaration&  decl, const std::string&  name, Context&  ctx)
{
  ctx.push("  pshbp        ;//*********************************//\n");
  ctx.push("  psh16u %6d;//ローカル変数%sのアドレスを読み出し//\n",decl.offset,name.data());
  ctx.push("  sub          ;//*********************************//\n");
}


Type
Variable::
compile(const Declaration&  decl, Context&  ctx) const
{
    switch(decl.storage_kind)
    {
      case(StorageKind::local):
        compile_local(decl,name,ctx);
        break;
      case(StorageKind::local_static):
        ctx.push("  psh16u _STATIC_%06z;//%s\n",decl.offset,name.data());
        break;
      case(StorageKind::global):
        ctx.push("  psh16u %s;\n",name.data());
        break;
    }


  return type.make_reference();
}


void
Variable::
compile_definition(const Declaration&  decl, Context&  ctx) const
{
    switch(decl.storage_kind)
    {
      case(StorageKind::local):
          if(initializer)
          {
            compile_local(decl,name,ctx);

/*
            auto  t = initializer->compile(ctx);

              if(t == TypeKind::reference)
              {
                t = t.compile_dereference(ctx);
              }


            type.make_reference().compile_assign(ctx);
*/
          }
        break;
/*
      case(StorageKind::local_static):
        {
          int   i = 0;

            if(initexpr)
            {
              FoldContext  folctx(ctx.globalscope);

              auto  res = initexpr->fold(folctx);

                if(!res.folded)
                {
                  printf("静的変数の初期化は定数式出なければなりません\n");

                  throw;
                }


              i = res.value;
            }


          ctx.push_definition("_STATIC_%06z://%s\n",decl.offset,name.data());
          ctx.push_definition("data i32 {%d};\n",i);
        }
        break;
      case(StorageKind::global):
        {
          int   i = 0;

            if(initexpr)
            {
              FoldContext  folctx(ctx.globalscope);

              auto  res = initexpr->fold(folctx);

                if(!res.folded)
                {
                  printf("大域変数の初期化は定数式出なければなりません\n");

                  throw;
                }


              i = res.value;
            }


          ctx.push_definition("%s:\n",name.data());
          ctx.push_definition("data i32 {%d};\n",i);
        }
        break;
*/
    }
}


void
Variable::
print(FILE*  f) const
{
  type.print(f);

  fprintf(f,"  %s",name.data());

    if(initializer)
    {
      fprintf(f," = ");

      initializer.print(f);
    }
}





