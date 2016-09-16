#include"assvm_memory.hpp"




namespace assvm{




Memory::
Memory(Callback  cb):
callback(cb)
{
}




int
Memory::
get8(int  ptr) const
{
    if(callback)
    {
      callback(ptr);
    }


  return static_cast<int8_t>(array[ptr&0xFFFFF]);
}


int
Memory::
get8u(int  ptr) const
{
    if(callback)
    {
      callback(ptr);
    }


  return array[ptr&0xFFFFF];
}


int
Memory::
get16(int  ptr) const
{
    if(callback)
    {
      callback(ptr);
    }


  return reinterpret_cast<const int16_t&>(array[ptr&0xFFFFE]);
}


int
Memory::
get16u(int  ptr) const
{
    if(callback)
    {
      callback(ptr);
    }


  return reinterpret_cast<const uint16_t&>(array[ptr&0xFFFFE]);
}


int
Memory::
get32(int  ptr) const
{
    if(callback)
    {
      callback(ptr);
    }


  return reinterpret_cast<const int32_t&>(array[ptr&0xFFFFC]);
}




void
Memory::
put8(int  ptr, int  val)
{
    if(callback)
    {
      callback(ptr);
    }


  array[ptr&0xFFFFF] = val;
}


void
Memory::
put16(int  ptr, int  val)
{
    if(callback)
    {
      callback(ptr);
    }


  reinterpret_cast<int16_t&>(array[ptr&0xFFFFE]) = val;
}


void
Memory::
put32(int  ptr, int  val)
{
    if(callback)
    {
      callback(ptr);
    }


  reinterpret_cast<int32_t&>(array[ptr&0xFFFFC]) = val;
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




