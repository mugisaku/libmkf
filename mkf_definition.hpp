#ifndef MKF_DEFINITION_HPP_INCLUDED
#define MKF_DEFINITION_HPP_INCLUDED


#include"mkf_element.hpp"
#include"mkf_print.hpp"


namespace mkf{




class
Definition
{
  std::string  identifier;

  ElementList  elements;

  int  solid_flag;
  int   separator;

  void  scan(const char*&  p);

public:
  Definition(const char*  id="");
  Definition(Definition&&  rhs);


  Definition&  operator=(Definition&&  rhs);

  void  clear();

  void  append_element(Element&&  el);

  const ElementList&  get_list() const;

  void  reset(const char*&  p);

  void  change_identifier(const char*  s);

  const std::string&  get_identifier() const;

  void  set_solid_flag();

  bool  test_solid_flag() const;
  bool  test_selective() const;

  void  set_separator(int  c);

  void  print(Printer&  pr) const;

};


}


#endif




