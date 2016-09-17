#ifndef CMPLR_TYPE_HPP_INCLUDED
#define CMPLR_TYPE_HPP_INCLUDED


#include<cstddef>
#include<memory>
#include<cstdio>




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

  pointer,
  array,

  function,

};


struct Type;


struct
TypePointer
{
  Type*  type;

  constexpr TypePointer(Type*  t): type(t){};

};


struct
TypeArray
{
  Type*  type;

  int  element_number;

  constexpr TypeArray(Type*  t, int  n):
  type(t),
  element_number(n){};

};


struct
Type
{
  TypeKind  kind;

  int  element_number;

  std::unique_ptr<Type>  source_type;


  Type(TypeKind  k=TypeKind::null);
  Type(TypePointer  ptr);
  Type(TypeArray    arr);

  size_t  get_size() const;

  int  snprint(char*  s, size_t  n) const;

  std::string  to_string() const;

  void  print(FILE*  f=stdout) const;

};


Type*  make_type(const char*  s);




#endif




