#ifndef ASSVM_MEMORY_HPP_INCLUDED
#define ASSVM_MEMORY_HPP_INCLUDED


#include<cstdint>
#include<cstddef>
#include"assvm_program.hpp"


namespace assvm{


struct
Memory
{
  static constexpr size_t  size = 0x100000;

  using Callback = void  (*)(int  ptr);

  uint8_t  array[size];

  Callback  callback;

  Memory(Callback  cb=nullptr);

  int  get8(  int  ptr) const;
  int  get8u( int  ptr) const;
  int  get16( int  ptr) const;
  int  get16u(int  ptr) const;
  int  get32( int  ptr) const;

  void  put8( int  ptr, int  val);
  void  put16(int  ptr, int  val);
  void  put32(int  ptr, int  val);

  void  fill(int  v=0);


};


}




#endif




