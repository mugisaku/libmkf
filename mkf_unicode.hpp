#ifndef MKF_UNICODE_HPP_INCLUDED
#define MKF_UNICODE_HPP_INCLUDED


#include<string>


namespace mkf{


size_t  u16strlen(const char16_t*  str);

size_t  get_utf8_bytes(int  c);

size_t  get_utf8_length(const char*  s);

std::u16string  to_u16string(const std::string&  s);

std::string  to_string(const std::u16string&  u16s);

size_t  push_utf8(std::string&  s, char16_t  c);

bool  test_utf8code(int  c);

int  get_unicode(const char*  name);


}


#endif




