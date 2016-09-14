#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"




void
Declaration::
compile_function_definition(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        data.f->compile_definition(ctx);
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
compile_constant_array_definition(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
compile_array_definition(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
compile_constant_definition(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
compile_value_definition(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
          if(data.expr)
          {
            auto  k = data.expr->compile(ctx);

              if(k == ObjectKind::reference)
              {
                ctx.push("  ld;\n");
              }


            ctx.push("  pshbp;        //\n");
            ctx.push("  pshui8 %6d;//\n",index);
            ctx.push("  sub;          //\n");
            ctx.push("  asn;          //ローカル変数%s\n",identifier.data());
            ctx.push("  pop;\n");
          }
        break;
      case(DeclarationKind::local_static):
        {
          int   i = 0;

            if(data.expr)
            {
              FoldContext  folctx(ctx.globalscope);

              auto  res = data.expr->fold(folctx);

                if(!res.folded)
                {
                  printf("静的変数の初期化は定数式出なければなりません\n");

                  throw;
                }


              i = res.value;
            }


          ctx.push_definition("_STATIC_%04d:\n",index);
          ctx.push_definition("data i32 {%d};\n",i);
        }
        break;
      case(DeclarationKind::global):
        {
          int   i = 0;

            if(data.expr)
            {
              FoldContext  folctx(ctx.globalscope);

              auto  res = data.expr->fold(folctx);

                if(!res.folded)
                {
                  printf("大域変数の初期化は定数式出なければなりません\n");

                  throw;
                }


              i = res.value;
            }


          ctx.push_definition("%s:\n",identifier.data());
          ctx.push_definition("data i32 {%d};\n",i);
        }
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
compile_definition(Context&  ctx) const
{
    switch(object_kind)
    {
      case(ObjectKind::value):
        compile_value_definition(ctx);
        break;
      case(ObjectKind::constant):
        compile_constant_definition(ctx);
        break;
      case(ObjectKind::function):
        compile_function_definition(ctx);
        break;
      case(ObjectKind::array):
        compile_array_definition(ctx);
        break;
      case(ObjectKind::constant_array):
        compile_constant_array_definition(ctx);
        break;
    }
}




