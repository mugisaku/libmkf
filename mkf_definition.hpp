#ifndef MKF_DEFINITION_HPP_INCLUDED
#define MKF_DEFINITION_HPP_INCLUDED


#include"mkf_element.hpp"
#include"mkf_group.hpp"
#include"mkf_print.hpp"


namespace mkf{




class
Definition: public Group
{
  std::string  identifier;

  int  noskip_state;

public:
  Definition(const char*  id="");
  Definition(const Definition&)=delete;
  Definition(Definition&&  rhs) noexcept;


  Definition&  operator=(Definition&&  rhs);

  void  clear();

  void  reset(const pp::Character*&  p);

  void  change_identifier(const char*  s);

  const std::string&  get_identifier() const;

  bool  test_noskip_flag() const;

  void  print(Printer&  pr) const;

};


}


#endif




