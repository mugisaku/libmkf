#include"cmplr_type.hpp"
#include"cmplr_context.hpp"
#include<cctype>
#include<cstring>




bool
Type::
is_reinterpretable(const Type&  target) const
{
    switch(target.kind)
    {
      case(TypeKind::pointer):
        return(kind == TypeKind::pointer);
        break;
      case(TypeKind::reference):
        return(kind == TypeKind::pointer);
        break;
    }


  return false;
}




bool
Type::
is_convertable_implicitly(const Type&  target) const
{
    switch(target.kind)
    {
      case(TypeKind::bool_ ):
      case(TypeKind::int8  ):
      case(TypeKind::uint8 ):
      case(TypeKind::int16 ):
      case(TypeKind::uint16):
      case(TypeKind::int32 ):
        return is_convertable_implicitly_to_integer();
        break;
      case(TypeKind::pointer):
        return is_convertable_implicitly_to_pointer(target.kind);
        break;
      case(TypeKind::reference):
        break;
      case(TypeKind::array):
        break;
    }


  return false;
}


bool
Type::
is_convertable_implicitly_to_pointer(TypeKind  target_kind) const
{
    if(kind == TypeKind::array)
    {
      return(referred_type->kind == target_kind);
    }


  return false;
}


bool
Type::
is_convertable_implicitly_to_integer() const
{
    if(kind == TypeKind::reference)
    {
      return referred_type->is_convertable_implicitly_to_integer();
    }


  return((kind == TypeKind::int8  ) ||
         (kind == TypeKind::uint8 ) ||
         (kind == TypeKind::int16 ) ||
         (kind == TypeKind::uint16) ||
         (kind == TypeKind::int32 ));
}


bool
Type::
is_convertable_implicitly_to_boolean() const
{
    if(kind == TypeKind::reference)
    {
      return referred_type->is_convertable_implicitly_to_boolean();
    }


  return((kind == TypeKind::bool_  ) ||
         (kind == TypeKind::pointer) ||
         (kind == TypeKind::int8   ) ||
         (kind == TypeKind::uint8  ) ||
         (kind == TypeKind::int16  ) ||
         (kind == TypeKind::uint16 ) ||
         (kind == TypeKind::int32  ));
}




