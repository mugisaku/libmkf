#ifndef MKF_CTYPE_HPP_INCLUDED
#define MKF_CTYPE_HPP_INCLUDED




namespace mkf{


enum class
CType
{
  null,
  digit,
  xdigit,
  lower,
  upper,
  punct,
  space,
  alpha,
  alnum,
  utf8,

};


const char*  get_ctype_name(CType  type);

CType  get_ctype(const char*  name);

bool  test_ctype_code(int  c, CType  type);


}


#endif




