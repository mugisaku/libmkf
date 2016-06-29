#ifndef MKF_TMP_STRING_HPP_INCLUDED
#define MKF_TMP_STRING_HPP_INCLUDED


#include<cstddef>


namespace mkf{


template<size_t  SZ=256>
class
tmp_string
{
  size_t  length;

  char  buffer[SZ];

public:
  tmp_string(){clear();}

  virtual ~tmp_string(){}


  int  size() const
  {
    return length;
  }


  bool  empty() const{return !length;}

  void  clear()
  {
    length = 0;

    buffer[0] = 0;
  }


  const char&  push(char  c)
  {
    buffer[length++] = c;
    buffer[length  ] = 0;

    return buffer[length-1];
  }


  const char&  front() const{return buffer[       0];}
  const char&   back() const{return buffer[length-1];}

  const char*  data() const{return buffer;}

  const char*  begin() const{return buffer       ;}
  const char*    end() const{return buffer+length;}

};


}


#endif




