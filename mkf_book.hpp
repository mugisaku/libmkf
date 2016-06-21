#ifndef MKF_BOOK_HPP_INCLUDED
#define MKF_BOOK_HPP_INCLUDED


#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_ascii.hpp"
#include"mkf_ctype.hpp"


namespace mkf{


using DefinitionList = std::list<Definition>;


struct Block;


struct
CompareContext
{
  const char*&       p0;
  const char*  const p1;

  Node*  nd;

  CompareContext(const char*&  p0_, const char*  p1_, Node*  nd_=nullptr):
  p0(p0_),
  p1(p1_),
  nd(nd_){}

};


class
Book
{
  Definition  main_definition;

  DefinitionList  sub_definitions;


  bool  compare_definition_reference(CompareContext&  ctx, const Definition&  def) const;

  bool  compare_for_any(CompareContext&  ctx, const Definition&  def) const;
  bool  compare_for_all(CompareContext&  ctx, const Definition&  def) const;

  bool  compare0(CompareContext&  ctx, const Element&  elm, bool solid_flag) const;
  bool  compare1(CompareContext&  ctx, const Element&  elm) const;

  bool  compare(CompareContext&  ctx, const Definition&  def) const;


  Definition  read_definition(const Node&  base);

  void  read_entry(Definition&  def, const Node&  base);

  Element  read_element(uint32_t  flags, const Node&  base);

  uint32_t  read_mark(const Node&  base);

  std::string  read_string_literal(const Node&  base);
  int  read_string_element(const Node&  base);
  int  read_character_literal(const Node&  base);


public:


  void  change_main_definition(Definition&&  def);

  void  append_sub_definition(Definition&&  def);

  void  make(const std::string&  s);
  void  make(const Node&  src);


  void  clear();

  const Definition*  find(const std::string&  id) const;

  Node*  parse(const std::string&  s) const;

  void  print(FILE*  f=stdout) const;
  void  print(Printer&  pr) const;

};


}


#endif




