#ifndef MKF_CHARPTR_HPP_INCLUDED
#define MKF_CHARPTR_HPP_INCLUDED


#include<cstddef>
#include<string>
#include"mkf_ctype.hpp"
#include"mkf_node.hpp"


namespace mkf{


class
charptr
{
  const char*        p0;
  const char*  const p1;

  int  column_number;
  int    line_number;

public:
  charptr(const char*  p0_=nullptr, const char*  p1_=nullptr);
  charptr(const std::string&  s);


  const char&  operator*() const;

  operator bool() const;
  operator const char*() const;

  bool  operator==(const charptr&  rhs) const;
  bool  operator!=(const charptr&  rhs) const;
  bool  operator< (const charptr&  rhs) const;

  charptr&  operator=(const charptr&  rhs);

  charptr&  operator+=(int  n);

  charptr&  operator++(   );
  charptr   operator++(int);

  void  skip_space();

  const char*  get_raw_pointer() const;

  int  get_column_number() const;
  int    get_line_number() const;

  size_t  compare_ctype(CType  type, Node&  node);
  size_t  compare_string(const char*  string, size_t  length, Node&  node);

  void  print() const;

};


}


#endif




