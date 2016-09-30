#ifndef TYPESYSTEM_POINTER_HPP_INCLUDED
#define TYPESYSTEM_POINTER_HPP_INCLUDED


#include<memory>
#include"typesystem_fundamental.hpp"




namespace typesystem{


struct Element;


struct
Pointer
{
  bool  constant;

  std::unique_ptr<Element>  referred;

  Pointer(Element*  e);
  Pointer(const std::unique_ptr<Element>&  e);
  Pointer(const Pointer&   rhs) noexcept;
  Pointer(      Pointer&&  rhs) noexcept;

  void  snprint(char*&  s, size_t&  n, bool  ref=false) const;

};


}


#endif




