#include"assvm_memory.hpp"




namespace assvm{




Memory::
Memory(Callback  cb):
callback(cb)
{
}




uint8_t&
Memory::
get_byte(int  ptr)
{
    if(callback)
    {
      callback(ptr);
    }


  return array[ptr&0xFFFFF];
}


word_t&
Memory::
get_word(int  ptr)
{
    if(callback)
    {
      callback(ptr);
    }


  return reinterpret_cast<word_t&>(array[ptr&0xFFFFC]);
}


void
Memory::
fill(int  v)
{
    for(auto&  e: array)
    {
      e = v;
    }
}


}




