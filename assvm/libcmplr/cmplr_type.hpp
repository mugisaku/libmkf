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

  int8,
  uint8,
  int16,
  uint16,
  int32,

  reference,
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
struct TypePointer;
struct TypeReference;
struct TypeArray;


struct
Type
{
  TypeKind  kind;

  bool  constant;

  int  element_number;

  std::unique_ptr<Type>  source_type;


  Type(TypeKind  k=TypeKind::null, bool  c=false);
  Type(TypePointer&&    ptr, bool  c=false);
  Type(TypeReference&&  ref, bool  c=false);
  Type(TypeArray&&      arr, bool  c=false);
  Type(const Type&   rhs)         ;
  Type(      Type&&  rhs) noexcept;


  Type&  operator=(const Type&   rhs)         ;
  Type&  operator=(      Type&&  rhs) noexcept;

  bool  operator==(TypeKind  k) const;
  bool  operator!=(TypeKind  k) const;

  void  reset(TypeKind  k=TypeKind::null, bool  c=false);
  void  reset(TypePointer&&    ptr, bool  c=false);
  void  reset(TypeReference&&  ref, bool  c=false);
  void  reset(TypeArray&&      arr, bool  c=false);

  size_t  get_size() const;

  int  snprint(char*  s, size_t  n) const;

  std::string  to_string() const;

  void  print(FILE*  f=stdout) const;

  Type  compile_dereference(Context&  ctx) const;
  Type  compile_assign(Context&  ctx) const;

  void  read(const mkf::Node&  src);

};


struct
TypePointer
{
  Type  type;

  TypePointer(TypeKind  k=TypeKind::null, bool   c=false): type(k,c){};
  TypePointer(const Type&   t): type(t){};
  TypePointer(      Type&&  t): type(std::move(t)){};

};


struct
TypeReference
{
  Type  type;

  TypeReference(TypeKind  k=TypeKind::null, bool   c=false): type(k,c){};
  TypeReference(const Type&   t): type(t){};
  TypeReference(      Type&&  t): type(std::move(t)){};

};


struct
TypeArray
{
  Type  type;

  int  element_number;

  TypeArray(TypeKind  k, int  n, bool   c=false): type(k,c), element_number(n){};
  TypeArray(const Type&   t, int  n): type(t), element_number(n){};
  TypeArray(      Type&&  t, int  n): type(std::move(t)), element_number(n){};

};


Type  make_type(const char*  s);




#endif




