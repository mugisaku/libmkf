#ifndef MKF_CHARPTR_HPP_INCLUDED
#define MKF_CHARPTR_HPP_INCLUDED


#include<cstddef>
#include<string>
#include"mkf_ctype.hpp"
#include"mkf_node.hpp"
#include"libpp/pp.hpp"


namespace mkf{


class
charptr
{
  const pp::Character*  p0;
  const pp::Character*  p1;

public:
  charptr();
  charptr(const pp::String&  s);


  const pp::Character&  operator*() const;
  const pp::Character*  operator->() const;

  operator bool() const;

  bool  operator==(const charptr&  rhs) const;
  bool  operator!=(const charptr&  rhs) const;
  bool  operator< (const charptr&  rhs) const;

  charptr&  operator=(const charptr&  rhs);
  charptr&  operator+=(int  n);

  charptr&  operator++(   );
  charptr   operator++(int);

  void  skip_space();

  bool  test(const std::string&  s) const;

  size_t  compare_ctype(CType  type, Node&  node);
  size_t  compare_string(const std::string&  s, Node&  node);

};


}


#endif




