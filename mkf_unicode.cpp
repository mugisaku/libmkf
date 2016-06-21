#include"mkf_unicode.hpp"
#include"mkf_element.hpp"
#include<cstdlib>
#include<cctype>




namespace mkf{


size_t
u16strlen(const char16_t*  str)
{
  size_t  len = 0;

    while(*str++)
    {
      ++len;
    }


  return len;
}


size_t
get_utf8_bytes(int  c)
{
  c &= 0xFF;

       if(!(c>>7)             ){return 1;}
  else if( (c>>1) == 0b1111110){return 6;}
  else if( (c>>2) == 0b111110 ){return 5;}
  else if( (c>>3) == 0b11110  ){return 4;}
  else if( (c>>4) == 0b1110   ){return 3;}
  else if( (c>>5) == 0b110    ){return 2;}
  else if( (c>>6) == 0b10     ){return 1;}


  return 0;
}


size_t
get_utf8_length(const char*  s)
{
  size_t  length = 0;

    while(*s)
    {
      const size_t  bytes = get_utf8_bytes(*s);

        if(!bytes)
        {
          break;
        }


      ++length;

      s += bytes;
    }


  return length;
}


std::u16string
to_u16string(const std::string&  s)
{
  std::u16string  u16s;

  auto  p = s.data();

    while(*p)
    {
      const size_t  bytes = get_utf8_bytes(*p);

        switch(bytes)
        {
          case(1): u16s += ((p[0]             )                                    );break;
          case(2): u16s += ((p[0]&0b11111)<< 6)|((p[1]&0b111111)                   );break;
          case(3): u16s += ((p[0]&0b01111)<<12)|((p[1]&0b111111)<<6)|(p[2]&0b111111);break;
          default:
            report;
            goto END;
        }


      p += bytes;
    }


END:
  return std::move(u16s);
}


std::string
to_string(const std::u16string&  u16s)
{
  std::string  s;

    for(auto  c: u16s)
    {
      push_utf8(s,c);
    }


  return std::move(s);
}




size_t
push_utf8(std::string&  s, char16_t  c)
{
  size_t  bytes = 0;

    if(c <= 0x7F)
    {
      s += c;

      bytes = 1;
    }

  else
    if((c >= 0x0080) &&
       (c <= 0x07FF))
    {
      s += (0b11000000|(c>>6));
      s += (0b10000000|(c&0b111111));

      bytes = 2;
    }

  else
    if((c >= 0x0800) &&
       (c <= 0xFFFF))
    {
      s += (0b11100000|(c>>12));
      s += (0b10000000|((c>>6)&0b111111));
      s += (0b10000000|((c   )&0b111111));

      bytes = 3;
    }


  return bytes;
}


bool
test_utf8code(int  c)
{
  c &= 0xFF;

  return(((c >> 6) == 0b00010) ||
         ((c >> 5) == 0b00110) ||
         ((c >> 4) == 0b01110) ||
         ((c >> 2) == 0b11110));
}


int
get_unicode(const char*  name)
{
  unsigned int  n;

    if(sscanf(name,"UNICODE_%X",&n) == 1)
    {
      return n;
    }


  return -1;
}


}


