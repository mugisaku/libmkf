#ifndef PP_UNICODE_HPP_INCLUDED
#define PP_UNICODE_HPP_INCLUDED


#include<string>


namespace pp{


size_t  get_utf8_byte_number(const char*  s);
size_t  get_unicode_length(const char*  s);

char16_t  to_char16(const char*  s, size_t  byte_number);


}




#endif




