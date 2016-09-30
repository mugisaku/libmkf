#include"typesystem_element.hpp"





namespace typesystem{


bool  Element::is_void()      const{return(is_fundamental() && (data.fdm.kind == FundamentalKind::void_));}
bool  Element::is_function()  const{return(kind == TypeKind::function);}
bool  Element::is_nullptr()   const{return(is_fundamental() && (data.fdm.kind == FundamentalKind::nullptr_));}
bool  Element::is_pointer()   const{return(kind == TypeKind::pointer);}
bool  Element::is_array()     const{return(kind == TypeKind::array);}
bool  Element::is_reference() const{return(kind == TypeKind::reference);}
bool  Element::is_enum()      const{return(kind == TypeKind::enum_);}
bool  Element::is_struct()    const{return(kind == TypeKind::struct_);}
bool  Element::is_union()     const{return(kind == TypeKind::union_);}


bool
Element::
is_integer() const
{
  return(is_fundamental() &&
         ((data.fdm.kind == FundamentalKind::char_ ) ||
          (data.fdm.kind == FundamentalKind::bool_ ) ||
          (data.fdm.kind == FundamentalKind::int8  ) ||
          (data.fdm.kind == FundamentalKind::uint8 ) ||
          (data.fdm.kind == FundamentalKind::int16 ) ||
          (data.fdm.kind == FundamentalKind::uint16) ||
          (data.fdm.kind == FundamentalKind::int32 )));
}


bool  Element::is_arithmetic() const{return is_integer();}
bool  Element::is_fundamental() const{return (kind == TypeKind::fundamental);}
bool  Element::is_object() const{return(is_enum()||is_struct()||is_union()||is_array()||is_scalar());}
bool  Element::is_scalar() const{return(is_arithmetic()||is_enum()||is_pointer()||is_nullptr());}
bool  Element::is_compound() const{return(is_array()||is_function()||is_pointer()||is_reference()||is_struct()||is_union()||is_enum());}


bool
Element::
is_literal() const
{
  return(is_scalar()||
           is_void()||
         (is_reference() && data.ptr.referred->is_literal())|
         (is_array()     && data.arr.element->is_literal()));
}


bool
Element::
is_signed() const
{
  return(is_fundamental() &&
         ((data.fdm.kind == FundamentalKind::int8  ) ||
          (data.fdm.kind == FundamentalKind::int16 ) ||
          (data.fdm.kind == FundamentalKind::int32 )));
}


bool
Element::
is_unsigned() const
{
  return(is_fundamental() &&
         ((data.fdm.kind == FundamentalKind::char_ ) ||
          (data.fdm.kind == FundamentalKind::bool_ ) ||
          (data.fdm.kind == FundamentalKind::uint8 ) ||
          (data.fdm.kind == FundamentalKind::uint16)));
}




}




