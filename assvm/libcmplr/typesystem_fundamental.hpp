#ifndef TYPESYSTEM_FUNDAMENTAL_HPP_INCLUDED
#define TYPESYSTEM_FUNDAMENTAL_HPP_INCLUDED


#include<cstddef>




namespace typesystem{


enum class
FundamentalKind
{
  void_,

  nullptr_,

  bool_,
  char_,

  int8,
  uint8,
  int16,
  uint16,
  int32,

};


struct
Fundamental
{
  bool  constant;

  FundamentalKind  kind;

  constexpr Fundamental(bool  c, FundamentalKind  k):
  constant(c), kind(k){}

  size_t  get_size() const;


  void  snprint(char*&  s, size_t&  n) const;

};


const char*  get_name(FundamentalKind  k);
size_t       get_size(FundamentalKind  k);


struct I8: public Fundamental
{
  constexpr I8(): Fundamental(false,FundamentalKind::int8){}
};


struct U8: public Fundamental
{
  constexpr U8(): Fundamental(false,FundamentalKind::uint8){}
};


struct I16: public Fundamental
{
  constexpr I16(): Fundamental(false,FundamentalKind::int16){}
};


struct U16: public Fundamental
{
  constexpr U16(): Fundamental(false,FundamentalKind::uint16){}
};


struct I32: public Fundamental
{
  constexpr I32(): Fundamental(false,FundamentalKind::int32){}
};


struct Bool: public Fundamental
{
  constexpr Bool(): Fundamental(false,FundamentalKind::bool_){}
};


struct Char: public Fundamental
{
  constexpr Char(): Fundamental(false,FundamentalKind::char_){}
};


struct Void: public Fundamental
{
  constexpr Void(): Fundamental(false,FundamentalKind::void_){}
};




struct ConstI8: public Fundamental
{
  constexpr ConstI8(): Fundamental(true,FundamentalKind::int8){}
};


struct ConstU8: public Fundamental
{
  constexpr ConstU8(): Fundamental(true,FundamentalKind::uint8){}
};


struct ConstI16: public Fundamental
{
  constexpr ConstI16(): Fundamental(true,FundamentalKind::int16){}
};


struct ConstU16: public Fundamental
{
  constexpr ConstU16(): Fundamental(true,FundamentalKind::uint16){}
};


struct ConstI32: public Fundamental
{
  constexpr ConstI32(): Fundamental(true,FundamentalKind::int32){}
};


struct ConstBool: public Fundamental
{
  constexpr ConstBool(): Fundamental(true,FundamentalKind::bool_){}
};


struct ConstChar: public Fundamental
{
  constexpr ConstChar(): Fundamental(true,FundamentalKind::char_){}
};


struct ConstVoid: public Fundamental
{
  constexpr ConstVoid(): Fundamental(true,FundamentalKind::void_){}
};




struct Nullptr: public Fundamental
{
  constexpr Nullptr(): Fundamental(true,FundamentalKind::nullptr_){}
};




}




#endif




