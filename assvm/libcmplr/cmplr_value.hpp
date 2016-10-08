#ifndef CMPLR_VALUE_HPP_INCLUDED
#define CMPLR_VALUE_HPP_INCLUDED


#include"typesystem_element.hpp"




struct Declaration;
struct Function;
struct Literal;


struct
Value
{
  Type  type;

  size_t  base_address;

  size_t  size;

  uint8_t*  data;


  Value();
  Value(const std::u16string&  s);
  Value(Type&&  type_, size_t  size_=0, int  i=0);
  Value(const Declaration*  decl);
  Value(const Function*  fn);
  Value(const Value&   rhs) noexcept;
  Value(      Value&&  rhs) noexcept;
 ~Value();

  Value&  operator=(const Value&   rhs) noexcept;
  Value&  operator=(      Value&&  rhs) noexcept;

  void  clear();

  void  copy(void*  dst, size_t  dst_size) const;

  void  print(FILE*  f=stdout) const;

  template<typename  T>
  const T*
  get(size_t  offset) const
  {
    offset /= sizeof(T);
    offset *= sizeof(T);

    return reinterpret_cast<const T*>(data+offset);
  }

};


Value       VoidValue();
Value       NullptrValue();
Value            CharValue(char16_t  c);
Value       ConstCharValue(char16_t  c);
Value       BoolValue(bool  b);
Value  ConstBoolValue(bool  b);
Value       I8Value(int8_t  i);
Value  ConstI8Value(int8_t  i);
Value       U8Value(uint8_t  i);
Value  ConstU8Value(uint8_t  i);
Value       I16Value(int16_t  i);
Value  ConstI16Value(int16_t  i);
Value       U16Value(uint16_t  i);
Value  ConstU16Value(uint16_t  i);
Value       I32Value(int32_t  i);
Value  ConstI32Value(int32_t  i);




#endif




