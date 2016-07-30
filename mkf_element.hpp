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
#include"libpp/pp.hpp"


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
  std::string*  s;

  constexpr explicit Identifier(std::string*  s_): s(s_){}

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
constexpr int      noskip_flag = 4;


class
Element
{
  ElementKind  kind;

  pp::Position  position;

  pp::Index  id_index;

  union{
    std::string*  str;
    Group*        grp;

  } data;


public:
  Element();
  Element(std::string*  s);
  Element(const Identifier&  id);
  Element(Group*  grp);
  Element(const OptionGroup&      grp);
  Element(const RepetitionGroup&  grp);
  Element(const Element&)=delete;
  Element(Element&&  rhs) noexcept;
 ~Element();


  Element&  operator=(Element&&  rhs);

  void  reset(std::string*  s);
  void  reset(const Identifier&  id);
  void  reset(Group*  grp);
  void  reset(const OptionGroup&      grp);
  void  reset(const RepetitionGroup&  grp);

  void  clear();

  ElementKind  get_kind() const;

  const std::string*  get_string() const;
  Group*              get_group() const;

  void  print(Printer&  pr) const;

  bool  compare(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const;

};


using ElementList = List<Element>;


}


#endif




