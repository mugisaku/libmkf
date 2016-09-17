#include"cmplr_declaration.hpp"
#include"cmplr_globalscope.hpp"
#include"cmplr_function.hpp"




ObjectKind
Declaration::
compile_function(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::parameter):
        break;
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        ctx.push("  pshui16 %s;\n",identifier.data());
        return ObjectKind::function;
        break;
    }
}


ObjectKind
Declaration::
compile_array(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::parameter):
        break;
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        break;
    }
}


ObjectKind
Declaration::
compile_constant_array(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::parameter):
        break;
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        break;
    }
}


/*
ObjectKind
Declaration::
compile_value(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::parameter):
        ctx.push("  pshui8 %d;\n",index);
        ctx.push("  arg;\n");
        return ObjectKind::reference;
        break;
      case(DeclarationKind::local):
        ctx.push("  pshbp;        //\n");
        ctx.push("  pshui8 %6d;//\n",index);
        ctx.push("  sub;          //\n");
        return ObjectKind::reference;
        break;
      case(DeclarationKind::local_static):
        ctx.push("  pshui16 _STATIC_%04d;//%s\n",index,identifier.data());
        return ObjectKind::reference;
        break;
      case(DeclarationKind::global):
        ctx.push("  pshui16 %s;\n",identifier.data());
        return ObjectKind::reference;
        break;
    }
}
*/


ObjectKind
Declaration::
compile_constant(Context&  ctx) const
{
    switch(kind)
    {
      case(DeclarationKind::parameter):
        break;
      case(DeclarationKind::local):
        ctx.push("  pshi32 %6d;\n",data.i);
        return ObjectKind::constant;
        break;
      case(DeclarationKind::local_static):
        ctx.push("  pshi32 %d;//constexpr\n",data.i);
        return ObjectKind::constant;
        break;
      case(DeclarationKind::global):
        ctx.push("  pshi32 %d;//constexpr\n",data.i);
        return ObjectKind::constant;
        break;
    }
}




ObjectKind
Declaration::
compile(Context&  ctx) const
{
    switch(object_kind)
    {
      case(ObjectKind::value):
//        return compile_value(ctx);
        break;
      case(ObjectKind::constant):
        return compile_constant(ctx);
        break;
      case(ObjectKind::function):
        return compile_function(ctx);
        break;
      case(ObjectKind::array):
        return compile_array(ctx);
        break;
      case(ObjectKind::constant_array):
        return compile_constant_array(ctx);
        break;
    }


  return ObjectKind::null;
}




