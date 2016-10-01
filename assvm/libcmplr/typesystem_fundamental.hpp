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


}




#endif




