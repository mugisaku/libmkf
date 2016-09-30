#ifndef TYPESYSTEM_ARRAY_HPP_INCLUDED
#define TYPESYSTEM_ARRAY_HPP_INCLUDED


#include<memory>
#include"typesystem_fundamental.hpp"




namespace typesystem{


struct Element;


struct
Array
{
  std::unique_ptr<Element>  element;

  bool  size_defined;

  int  number;

  Array(Element*  e        );
  Array(Element*  e, int  n);
  Array(const Array&   rhs) noexcept;
  Array(      Array&&  rhs) noexcept;

  void  snprint(char*&  s, size_t&  n) const;

};


}


#endif




