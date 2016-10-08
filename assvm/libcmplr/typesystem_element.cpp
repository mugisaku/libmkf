#include"typesystem_element.hpp"
#include<new>




namespace typesystem{


Element::
Element(ElementKind  k):
kind(k)
{
}


Element::
Element(bool  c, FundamentalKind  k):
kind(ElementKind::fundamental)
{
  data.fdm.constant = c;
  data.fdm.kind     = k;
}


Element::
Element(Array&&  arr):
kind(ElementKind::array)
{
  new(&data) Array(std::move(arr));
}


Element::
Element(Pointer&&  ptr, bool  ref):
kind(ref? ElementKind::reference:ElementKind::pointer)
{
  new(&data) Pointer(std::move(ptr));
}


Element::
Element(Struct&&  str):
kind(ElementKind::struct_)
{
  new(&data) Struct(std::move(str));
}


Element::
Element(Union&&  uni):
kind(ElementKind::union_)
{
  new(&data) Union(std::move(uni));
}


Element::
Element(Enum&&  enu):
kind(ElementKind::enum_)
{
  new(&data) Enum(std::move(enu));
}


Element::
Element(const Element&  rhs):
kind(ElementKind::null)
{
  *this = rhs;
}


Element::
Element(Element&&  rhs) noexcept:
kind(ElementKind::null)
{
  *this = std::move(rhs);
}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(const Element&  rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(ElementKind::fundamental):
      data.fdm = rhs.data.fdm;
      break;
  case(ElementKind::array):
      new(&data) Array(rhs.data.arr);
      break;
  case(ElementKind::pointer):
  case(ElementKind::reference):
      new(&data) Pointer(rhs.data.ptr);
      break;
  case(ElementKind::struct_):
      new(&data) Struct(rhs.data.str);
      break;
  case(ElementKind::union_):
      new(&data) Union(rhs.data.uni);
      break;
  case(ElementKind::enum_):
      new(&data) Enum(rhs.data.enu);
      break;
    }


  return *this;
}


Element&
Element::
operator=(Element&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

    switch(kind)
    {
  case(ElementKind::fundamental):
      data.fdm = std::move(rhs.data.fdm);
      break;
  case(ElementKind::array):
      new(&data) Array(std::move(rhs.data.arr));
      break;
  case(ElementKind::pointer):
  case(ElementKind::reference):
      new(&data) Pointer(std::move(rhs.data.ptr));
      break;
  case(ElementKind::struct_):
      new(&data) Struct(std::move(rhs.data.str));
      break;
  case(ElementKind::union_):
      new(&data) Union(std::move(rhs.data.uni));
      break;
  case(ElementKind::enum_):
      new(&data) Enum(std::move(rhs.data.enu));
      break;
    }


  return *this;
}


bool
Element::
operator==(const Element&  rhs) const
{
  return(to_string() == rhs.to_string());
}




bool  Element::operator==(ElementKind  k) const{return(kind == k);}
bool  Element::operator!=(ElementKind  k) const{return(kind != k);}


Element::
operator bool() const
{
  return(kind == ElementKind::null);
}




void
Element::
clear()
{
    switch(kind)
    {
  case(ElementKind::function):
  case(ElementKind::fundamental):
//      data.fdm;
      break;
  case(ElementKind::array):
      data.arr.~Array();
      break;
  case(ElementKind::pointer):
  case(ElementKind::reference):
      data.ptr.~Pointer();
      break;
  case(ElementKind::struct_):
      data.str.~Struct();
      break;
  case(ElementKind::union_):
      data.uni.~Union();
      break;
  case(ElementKind::enum_):
      data.enu.~Enum();
      break;
    }


  kind = ElementKind::null;
}


ElementKind
Element::
get_kind() const
{
  return kind;
}


void
Element::
change_kind(ElementKind  k)
{
  kind = k;
}


const Element::Data*
Element::
operator->() const
{
  return &data;
}


Element*
Element::
duplicate() const
{
  return new Element(*this);
}


size_t
Element::
get_size() const
{
    switch(kind)
    {
  case(ElementKind::fundamental):
      return data.fdm.get_size();
      break;
  case(ElementKind::array):
      return data.arr.element->get_size()*data.arr.number;
      break;
  case(ElementKind::pointer):
  case(ElementKind::reference):
      return 4;
      break;
  case(ElementKind::enum_):
      return typesystem::get_size(data.enu.base);
      break;
  case(ElementKind::struct_):
      return data.str.get_size();
      break;
  case(ElementKind::union_):
      return data.uni.get_size();
      break;
    }


  return 0;
}


size_t
Element::
get_alignment_size() const
{
    switch(kind)
    {
  case(ElementKind::fundamental):
      return data.fdm.get_size();
      break;
  case(ElementKind::array):
      return data.arr.element->get_alignment_size();
      break;
  case(ElementKind::pointer):
  case(ElementKind::reference):
      return 4;
      break;
  case(ElementKind::enum_):
      return typesystem::get_size(data.enu.base);
      break;
  case(ElementKind::struct_):
      return data.str.get_alignment_size();
      break;
  case(ElementKind::union_):
      return data.uni.get_alignment_size();
      break;
    }


  return 0;
}




void
Element::
snprint(char*&  s, size_t&  n) const
{
  *s = 0;

    switch(kind)
    {
  case(ElementKind::fundamental):
      data.fdm.snprint(s,n);
      break;
  case(ElementKind::argument_list):
  case(ElementKind::array):
      data.arr.snprint(s,n);
      break;
  case(ElementKind::pointer):
      data.ptr.snprint(s,n);
      break;
  case(ElementKind::reference):
      data.ptr.snprint(s,n,true);
      break;
  case(ElementKind::enum_):
      data.enu.snprint(s,n);
      break;
  case(ElementKind::struct_):
      data.str.snprint(s,n);
      break;
  case(ElementKind::union_):
      data.uni.snprint(s,n);
      break;
  case(ElementKind::function):
    {
      int  res = snprintf(s,n,"function");

      s += res;
      n -= res;
    }
      break;
    }
}


std::string
Element::
to_string() const
{
  char  buf[1024];

  auto  s = buf;
  auto  n = sizeof(buf);

  snprint(s,n);

  return std::string(buf);
}


void
Element::
print(FILE*  f) const
{
  char  buf[1024];

  auto  s = buf;
  auto  n = sizeof(buf);

  snprint(s,n);

  fprintf(f,"%s",buf);
}


void
Element::
read(const mkf::Node&  src)
{
  clear();


  std::string  s;

  src.collect_characters(s);


  *this = make_type(s.data());
}




}




Type  I8Type(){return Type(false,typesystem::FundamentalKind::int8);}
Type  U8Type(){return Type(false,typesystem::FundamentalKind::uint8);}
Type  I16Type(){return Type(false,typesystem::FundamentalKind::int16);}
Type  U16Type(){return Type(false,typesystem::FundamentalKind::uint16);}
Type  I32Type(){return Type(false,typesystem::FundamentalKind::int32);}
Type  BoolType(){return Type(false,typesystem::FundamentalKind::bool_);}
Type  CharType(){return Type(false,typesystem::FundamentalKind::char_);}
Type  VoidType(){return Type(false,typesystem::FundamentalKind::void_);}
Type  ConstI8Type(){return Type(true,typesystem::FundamentalKind::int8);}
Type  ConstU8Type(){return Type(true,typesystem::FundamentalKind::uint8);}
Type  ConstI16Type(){return Type(true,typesystem::FundamentalKind::int16);}
Type  ConstU16Type(){return Type(true,typesystem::FundamentalKind::uint16);}
Type  ConstI32Type(){return Type(true,typesystem::FundamentalKind::int32);}
Type  ConstBoolType(){return Type(true,typesystem::FundamentalKind::bool_);}
Type  ConstCharType(){return Type(true,typesystem::FundamentalKind::char_);}
Type  ConstVoidType(){return Type(true,typesystem::FundamentalKind::void_);}
Type  NullptrType(){return Type(true,typesystem::FundamentalKind::nullptr_);}
Type  StructType(){return Type(typesystem::Struct());}
Type  UnionType(){return Type(typesystem::Union());}
Type  EnumType(){return Type(typesystem::Enum());}
Type  FunctionType(){return Type(typesystem::ElementKind::function);}





