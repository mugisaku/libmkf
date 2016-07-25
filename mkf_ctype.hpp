#ifndef MKF_CTYPE_HPP_INCLUDED
#define MKF_CTYPE_HPP_INCLUDED


#include"libminpp/minpp.hpp"


namespace mkf{


enum class
CType
{
  null,
  print,
  graph,
  blank,
  digit,
  xdigit,
  lower,
  upper,
  punct,
  space,
  alpha,
  alnum,
  unicode,

};


const char*  get_ctype_name(CType  type);

CType  get_ctype(const char*  name);

bool  test_ctype_code(char16_t  c, CType  type);


}


#endif




