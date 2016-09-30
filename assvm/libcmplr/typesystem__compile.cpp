#include"typesystem_element.hpp"
#include"cmplr_context.hpp"
#include<cctype>
#include<cstring>




namespace typesystem{


Type
Element::
compile_convert(const Type&  target, Context&  ctx) const
{
/*
    switch(target.kind)
    {
      case(ElementKind::bool_):
        break;
      case(ElementKind::int8  ):
          switch(target.kind)
          {
            case(ElementKind::int8):
            case(ElementKind::uint8):
              break;
            case(ElementKind::int16 ):
            case(ElementKind::uint16):
            case(ElementKind::int32):
              ctx.push("  tr8;\n");
              break;
          }
        break;
      case(ElementKind::uint8 ):
          switch(target.kind)
          {
            case(ElementKind::int8):
            case(ElementKind::uint8):
              break;
            case(ElementKind::int16 ):
            case(ElementKind::uint16):
            case(ElementKind::int32):
              ctx.push("  tr8;\n");
              break;
          }
        break;
      case(ElementKind::int16 ):
          switch(target.kind)
          {
            case(ElementKind::int8):
            case(ElementKind::uint8):
            case(ElementKind::int16 ):
              break;
            case(ElementKind::uint16):
            case(ElementKind::int32):
              ctx.push("  tr16;\n");
              break;
          }
        break;
      case(ElementKind::uint16):
          switch(target.kind)
          {
            case(ElementKind::int8):
            case(ElementKind::uint8):
            case(ElementKind::int16 ):
              break;
            case(ElementKind::uint16):
            case(ElementKind::int32):
              ctx.push("  tr16;\n");
              break;
          }
        break;
      case(ElementKind::int32):
          switch(target.kind)
          {
            case(ElementKind::int8):
            case(ElementKind::uint8):
            case(ElementKind::int16 ):
            case(ElementKind::uint16):
            case(ElementKind::int32):
              break;
          }
        break;
      case(ElementKind::reference):
      case(ElementKind::pointer):
      case(ElementKind::array):
        break;
    }


*/
  return target;
}


Type
Element::
compile_reinterpret(const Type&  target, Context&  ctx) const
{
/*
    switch(target.kind)
    {
      case(ElementKind::int8  ):
        break;
      case(ElementKind::uint8 ):
        break;
      case(ElementKind::int16 ):
        break;
      case(ElementKind::uint16):
        break;
      case(ElementKind::int32 ):
        break;
      case(ElementKind::reference):
      case(ElementKind::pointer):
      case(ElementKind::array):
        break;
    }


*/
  return Type();
}


Type
Element::
compile_dereference(Context&  ctx) const
{
/*
    switch(referred_type->kind)
    {
  case(ElementKind::int8  ):
      ctx.push("  ld8;\n");
      break;
  case(ElementKind::uint8 ):
      ctx.push("  ld8u;\n");
      break;
  case(ElementKind::int16 ):
      ctx.push("  ld16;\n");
      break;
  case(ElementKind::uint16):
      ctx.push("  ld16u;\n");
      break;
  case(ElementKind::int32 ):
      ctx.push("  ld32;\n");
      break;
  default:
      return Type();
    }


*/
  return Type();
}


Type
Element::
compile_assign(Context&  ctx) const
{
/*
    switch(referred_type->kind)
    {
      case(ElementKind::int8  ):
      case(ElementKind::uint8 ):
        ctx.push("  st8;\n");
        break;
      case(ElementKind::int16 ):
      case(ElementKind::uint16):
        ctx.push("  st16;\n");
        break;
      case(ElementKind::int32 ):
        ctx.push("  st32;\n");
        break;
    }


*/
  return Type();
}



}




