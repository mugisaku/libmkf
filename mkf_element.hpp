#ifndef MKF_ELEMENT_HPP_INCLUDED
#define MKF_ELEMENT_HPP_INCLUDED


#include<cstdint>
#include<cstddef>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<string>
#include<vector>
#include<list>
#include<initializer_list>
#include"mkf_node.hpp"
#include"mkf_charptr.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace mkf{


enum class
ElementKind: uint16_t
{
  null,
  string,
  identifier,
  group,
  option_group,
  repetition_group,

};


struct Element;
struct Group;
struct Book;
struct Definition;
struct ParseContext;
struct Printer;


struct
Identifier
{
  const char*  ptr;

  constexpr explicit Identifier(const char*  p): ptr(p){}

};


struct
OptionGroup
{
  Group*  ptr;

  constexpr explicit OptionGroup(Group*  p): ptr(p){}

};


struct
RepetitionGroup
{
  Group*  ptr;

  constexpr explicit RepetitionGroup(Group*  p): ptr(p){}

};


constexpr int      option_flag = 1;
constexpr int  repetition_flag = 2;


class
Element
{
  static constexpr auto  ptr_size = sizeof(char*);

  ElementKind  kind;

  uint16_t  length;

  union{
    char*  ptr;

    char  buf[ptr_size];

    Group*  grp;

  } data;


  void  copy(const char*  s);

public:
  Element();
  Element(const char*       str);
  Element(const Identifier&  id);
  Element(Group*  grp);
  Element(const OptionGroup&      grp);
  Element(const RepetitionGroup&  grp);
  Element(Element&&  rhs);
 ~Element();


  Element&  operator=(Element&&  rhs);

  void  reset(const char*  str);
  void  reset(const Identifier&  id);
  void  reset(Group*  grp);
  void  reset(const OptionGroup&      grp);
  void  reset(const RepetitionGroup&  grp);

  void  clear();

  ElementKind  get_kind() const;

  size_t  get_length() const;

  const char*  get_string() const;
  Group*       get_group() const;

  void  print(Printer&  pr) const;

  bool  compare(ParseContext&  parser, charptr&  p, Node&  node) const;

};


using ElementList = List<Element>;


}


#endif




