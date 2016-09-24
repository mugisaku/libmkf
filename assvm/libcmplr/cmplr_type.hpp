#ifndef CMPLR_TYPE_HPP_INCLUDED
#define CMPLR_TYPE_HPP_INCLUDED


#include<cstddef>
#include<memory>
#include<cstdio>
#include"mkf_node.hpp"




enum class
TypeKind
{
  null,

  undefined,
  unknown,
  void_,


  nullptr_,
  bool_,
  char_,

  int8,
  uint8,
  int16,
  uint16,
  int32,

  undefined_reference,
  reference,
  undefined_pointer,
  pointer,
  array,

  function,
  signature,

  string_literal,
  array_literal,

  parameter_list,
  argument_list,

};


struct Context;


class
Type
{
  TypeKind  kind;

  bool  constant;

  int  element_number;

  std::unique_ptr<Type>  referred_type;


public:
  Type(TypeKind  k=TypeKind::null, Type*  referred=nullptr, int  n=1);
  Type(const Type&   rhs)         ;
  Type(      Type&&  rhs) noexcept;


  Type&  operator=(const Type&   rhs)         ;
  Type&  operator=(      Type&&  rhs) noexcept;

  bool  operator==(TypeKind  k) const;
  bool  operator!=(TypeKind  k) const;

  bool  operator==(const Type&  rhs) const;

  operator bool() const;

  bool  test_constant() const;

  TypeKind  get_kind() const;

  void    set_constant();
  void  unset_constant();

  const Type*  get_referred_type() const;

  int  get_element_number() const;

  void  change_element_number(int  n);

  void  reset(TypeKind  k=TypeKind::null, Type*  referred=nullptr, int  n=1);

  size_t  get_size() const;
  size_t  get_object_size() const;
  size_t  get_alignment_size() const;
  size_t  get_object_alignment_size() const;

  bool  is_reinterpretable(const Type&  target) const;

  bool  is_convertable_implicitly(const Type&  target) const;
  bool  is_convertable_implicitly_to_pointer(TypeKind  target_kind) const;
  bool  is_convertable_implicitly_to_reference(TypeKind  target_kind) const;
  bool  is_convertable_implicitly_to_integer() const;
  bool  is_convertable_implicitly_to_boolean() const;

  int  snprint(char*  s, size_t  n) const;

  std::string  to_string() const;

  void  print(FILE*  f=stdout) const;

  Type  compile_convert(const Type&  target, Context&  ctx) const;
  Type  compile_reinterpret(const Type&  target, Context&  ctx) const;
  Type  compile_dereference(Context&  ctx) const;
  Type  compile_assign(Context&  ctx) const;

  void  read(const mkf::Node&  src);


  Type*  duplicate() const;

  Type  make_pointer() const;
  Type  make_reference() const;
  Type  make_array(int  n=1) const;

};


Type  make_type(const char*  s);




#endif




