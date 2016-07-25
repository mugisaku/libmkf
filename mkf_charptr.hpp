#ifndef MKF_CHARPTR_HPP_INCLUDED
#define MKF_CHARPTR_HPP_INCLUDED


#include<cstddef>
#include<string>
#include"mkf_ctype.hpp"
#include"mkf_node.hpp"
#include"libminpp/minpp.hpp"


namespace mkf{


class
charptr
{
  const minpp::Character*  p0;
  const minpp::Character*  p1;

public:
  charptr();
  charptr(const minpp::String&  s);


  const minpp::Character&  operator*() const;
  const minpp::Character*  operator->() const;

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




