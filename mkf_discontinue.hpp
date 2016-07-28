#ifndef MKF_DISCONTINUE_HPP_INCLUDED
#define MKF_DISCONTINUE_HPP_INCLUDED


#include"libpp/pp.hpp"


namespace mkf{


class charptr;


enum class
ErrorKind
{
  null,
};


[[noreturn]] void  discontinue(ErrorKind  k, const pp::Character*  p, const char*  fmt, ...);


}


#endif




