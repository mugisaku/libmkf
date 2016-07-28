#ifndef MKF_GROUP_HPP_INCLUDED
#define MKF_GROUP_HPP_INCLUDED


#include"mkf_element.hpp"
#include"mkf_list.hpp"


namespace mkf{


class
Group: public List<Element>
{
protected:
  int  separator;

  void  scan(const pp::Character*&  p, int  close);

public:
   Group();
   Group(int  separator_, List<Element>&&  element_list_);
   Group(const pp::Character*&  p, int  close);
   Group(const Group&)=delete;
   Group(Group&&  rhs) noexcept;
  ~Group();


  Group&  operator=(Group&&  rhs);

  bool  test_alternation() const;
  bool  test_exclusion() const;

  void  print(Printer&  pr) const;

  bool  compare_element(ParseContext&  parser, const pp::Character*&  p, Node&  node, const Element&  elm) const;
  bool  compare_with_exclusion(ParseContext&  parser, const pp::Character*&  p, Node&  node) const;
  bool  compare_for_anyone(    ParseContext&  parser, const pp::Character*&  p, Node&  node) const;
  bool  compare_for_all(       ParseContext&  parser, const pp::Character*&  p, Node&  node) const;
  bool  compare(               ParseContext&  parser, const pp::Character*&  p, Node&  node) const;
  bool  compare(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const;

};



}


#endif




