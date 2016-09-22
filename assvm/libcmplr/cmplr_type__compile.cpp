#include"cmplr_type.hpp"
#include"cmplr_context.hpp"
#include<cctype>
#include<cstring>




Type
Type::
compile_convert(const Type&  target, Context&  ctx) const
{
    switch(target.kind)
    {
      case(TypeKind::bool_):
        break;
      case(TypeKind::int8  ):
          switch(target.kind)
          {
            case(TypeKind::int8):
            case(TypeKind::uint8):
              break;
            case(TypeKind::int16 ):
            case(TypeKind::uint16):
            case(TypeKind::int32):
              ctx.push("  tr8;\n");
              break;
          }
        break;
      case(TypeKind::uint8 ):
          switch(target.kind)
          {
            case(TypeKind::int8):
            case(TypeKind::uint8):
              break;
            case(TypeKind::int16 ):
            case(TypeKind::uint16):
            case(TypeKind::int32):
              ctx.push("  tr8;\n");
              break;
          }
        break;
      case(TypeKind::int16 ):
          switch(target.kind)
          {
            case(TypeKind::int8):
            case(TypeKind::uint8):
            case(TypeKind::int16 ):
              break;
            case(TypeKind::uint16):
            case(TypeKind::int32):
              ctx.push("  tr16;\n");
              break;
          }
        break;
      case(TypeKind::uint16):
          switch(target.kind)
          {
            case(TypeKind::int8):
            case(TypeKind::uint8):
            case(TypeKind::int16 ):
              break;
            case(TypeKind::uint16):
            case(TypeKind::int32):
              ctx.push("  tr16;\n");
              break;
          }
        break;
      case(TypeKind::int32):
          switch(target.kind)
          {
            case(TypeKind::int8):
            case(TypeKind::uint8):
            case(TypeKind::int16 ):
            case(TypeKind::uint16):
            case(TypeKind::int32):
              break;
          }
        break;
      case(TypeKind::reference):
      case(TypeKind::pointer):
      case(TypeKind::array):
        break;
    }


  return target;
}


Type
Type::
compile_reinterpret(const Type&  target, Context&  ctx) const
{
    switch(target.kind)
    {
      case(TypeKind::int8  ):
        break;
      case(TypeKind::uint8 ):
        break;
      case(TypeKind::int16 ):
        break;
      case(TypeKind::uint16):
        break;
      case(TypeKind::int32 ):
        break;
      case(TypeKind::reference):
      case(TypeKind::pointer):
      case(TypeKind::array):
        break;
    }


  return Type();
}


Type
Type::
compile_dereference(Context&  ctx) const
{
    switch(referred_type->kind)
    {
  case(TypeKind::int8  ):
      ctx.push("  ld8;\n");
      break;
  case(TypeKind::uint8 ):
      ctx.push("  ld8u;\n");
      break;
  case(TypeKind::int16 ):
      ctx.push("  ld16;\n");
      break;
  case(TypeKind::uint16):
      ctx.push("  ld16u;\n");
      break;
  case(TypeKind::int32 ):
      ctx.push("  ld32;\n");
      break;
  default:
      return Type();
    }


  return Type(*referred_type);
}


Type
Type::
compile_assign(Context&  ctx) const
{
    switch(kind)
    {
      case(TypeKind::int8  ):
      case(TypeKind::uint8 ):
        ctx.push("  st8;\n");
        break;
      case(TypeKind::int16 ):
      case(TypeKind::uint16):
        ctx.push("  st16;\n");
        break;
      case(TypeKind::int32 ):
        ctx.push("  st32;\n");
        break;
    }


  return Type(TypeKind::int32);
}




