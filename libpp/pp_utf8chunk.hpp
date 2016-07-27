#ifndef PP_UTF8CHUNK_HPP_INCLUDED
#define PP_UTF8CHUNK_HPP_INCLUDED


#include<string>


namespace pp{


struct
UTF8Chunk
{
  char  codes[4];

  UTF8Chunk(char16_t  c=0);
  UTF8Chunk(const char*  s);

  UTF8Chunk&  operator=(char16_t  c);
  UTF8Chunk&  operator=(const char*  s);

};


}




#endif




