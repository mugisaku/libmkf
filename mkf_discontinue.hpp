#ifndef MKF_DISCONTINUE_HPP_INCLUDED
#define MKF_DISCONTINUE_HPP_INCLUDED


namespace mkf{


class charptr;


enum class
ErrorKind
{
  null,
};


[[noreturn]] void  discontinue(ErrorKind  k, const charptr&  p, const char*  fmt, ...);


}


#endif




