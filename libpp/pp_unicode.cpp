#include"pp_unicode.hpp"
#include<cstdio>




namespace pp{




size_t
get_utf8_byte_number(const char*  s)
{
  const int  c = *(const unsigned char*)s;

       if(!(c>>7)             ){return 1;}
/*
  else if( (c>>1) == 0b1111110){return 6;}
  else if( (c>>2) == 0b111110 ){return 5;}
  else if( (c>>3) == 0b11110  ){return 4;}
*/
  else if( (c>>4) == 0b1110   ){return 3;}
  else if( (c>>5) == 0b110    ){return 2;}
  else if( (c>>6) == 0b10     ){return 1;}


  return 0;
}


size_t
get_unicode_length(const char*  s)
{
  size_t  length = 0;

    for(;;)
    {
      const size_t  byte_number = get_utf8_byte_number(s);

        if(!byte_number)
        {
          break;
        }


      ++length;

      s += byte_number;
    }


  return length;
}


char16_t
to_char16(const char*  s, size_t  byte_number)
{
    switch(byte_number)
    {
      case(1): return ((s[0]             )                                    );break;
      case(2): return ((s[0]&0b11111)<< 6)|((s[1]&0b111111)                   );break;
      case(3): return ((s[0]&0b01111)<<12)|((s[1]&0b111111)<<6)|(s[2]&0b111111);break;
    }


  return 0;
}


}




