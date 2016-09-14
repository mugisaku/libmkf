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

  uint8_t&  get_byte(int  ptr);
  word_t&   get_word(int  ptr);

  void  fill(int  v=0);


};


}




#endif




