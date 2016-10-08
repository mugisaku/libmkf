#ifndef TYPESYSTEM_ELEMENT_HPP_INCLUDED
#define TYPESYSTEM_ELEMENT_HPP_INCLUDED


#include<cstddef>
#include<memory>
#include<cstdio>
#include"typesystem_fundamental.hpp"
#include"typesystem_array.hpp"
#include"typesystem_pointer.hpp"
#include"typesystem_struct.hpp"
#include"typesystem_union.hpp"
#include"typesystem_enum.hpp"
#include"mkf_node.hpp"




struct Context;
struct Function;


namespace typesystem{


enum class
ElementKind
{
  null,

  undefined,

  fundamental,

  reference,
  pointer,
  array,

  enum_,
  union_,
  struct_,

  function,

  parameter_list,
  argument_list,

};


class
Element
{
  ElementKind  kind;

  union Data{
    Fundamental  fdm;
    Array        arr;
    Pointer      ptr;
    Struct       str;
    Union        uni;
    Enum         enu;

     Data(){};
    ~Data(){};

  } data;

public:
  Element(ElementKind  k=ElementKind::null);
  Element(bool  c, FundamentalKind  k);
  Element(Array&&      arr);
  Element(Pointer&&    ptr, bool  ref=false);
  Element(Struct&&  str);
  Element(Union&&  uni);
  Element(Enum&&  enu);
  Element(const Element&   rhs)         ;
  Element(      Element&&  rhs) noexcept;
 ~Element(                    );


  Element&  operator=(const Element&   rhs)         ;
  Element&  operator=(      Element&&  rhs) noexcept;

  bool  operator==(ElementKind  k) const;
  bool  operator!=(ElementKind  k) const;

  bool  operator==(const Element&  rhs) const;

  operator bool() const;

  void  clear();

  const Data*  operator->() const;

  ElementKind  get_kind() const;

  void  change_kind(ElementKind  k);

  size_t  get_size() const;
  size_t  get_alignment_size() const;


  bool  is_void() const;
  bool  is_function() const;
  bool  is_nullptr() const;
  bool  is_pointer() const;
  bool  is_array() const;
  bool  is_reference() const;
  bool  is_integer() const;
  bool  is_enum() const;
  bool  is_union() const;
  bool  is_struct() const;

  bool  is_object() const;
  bool  is_scalar() const;
  bool  is_arithmetic() const;
  bool  is_fundamental() const;
  bool  is_compound() const;
  bool  is_literal() const;
  bool  is_signed() const;
  bool  is_unsigned() const;


  void  snprint(char*&  s, size_t&  n) const;

  std::string  to_string() const;

  void  print(FILE*  f=stdout) const;

  Element  compile_convert(const Element&  target, Context&  ctx) const;
  Element  compile_reinterpret(const Element&  target, Context&  ctx) const;
  Element  compile_dereference(Context&  ctx) const;
  Element  compile_assign(Context&  ctx) const;

  void  read(const mkf::Node&  src);

  Element*  duplicate() const;

  Element  make_pointer() const;
  Element  make_reference() const;
  Element  make_array(int  n=1) const;

};


Element  make_type(const char*  s);


}


using Type     = typesystem::Element    ;
using TypeKind = typesystem::ElementKind;


Type  I8Type();
Type  U8Type();
Type  I16Type();
Type  U16Type();
Type  I32Type();
Type  BoolType();
Type  CharType();
Type  VoidType();
Type  ConstI8Type();
Type  ConstU8Type();
Type  ConstI16Type();
Type  ConstU16Type();
Type  ConstI32Type();
Type  ConstBoolType();
Type  ConstCharType();
Type  ConstVoidType();
Type  NullptrType();
Type  StructType();
Type  UnionType();
Type  EnumType();
Type  FunctionType();




#endif




