#ifndef ASSVM_ELEMENT_HPP_INCLUDED
#define ASSVM_ELEMENT_HPP_INCLUDED


#include<cstdint>
#include<cstddef>
#include<cstdio>
#include"assvm_binary.hpp"


namespace assvm{


enum class
ElementKind
{
  null,
  instruction,
  data,

};


struct InstructionSource;
struct Data;


struct
ObjectFrame
{
  uint32_t  head_offset;
  uint32_t  tail_offset;

};


struct
Element
{
  ObjectFrame  frame;

  ElementKind  kind;

  union Content{
    InstructionSource*  src;
    Data*               dat;

  } content;


   Element();
   Element(size_t  off, InstructionSource*  src);
   Element(size_t  off, Data*  dat);
   Element(const Element&   rhs)=delete;
   Element(      Element&&  rhs) noexcept;
  ~Element();


  Element&  operator=(Element&&  rhs) noexcept;

  void  clear();

  void  reset(size_t  off, InstructionSource*  src);
  void  reset(size_t  off, Data*  dat);

  void  write(uint8_t*  base) const;

  void  print(FILE*  f=stdout) const;

};


}




#endif




