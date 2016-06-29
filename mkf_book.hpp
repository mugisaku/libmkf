#ifndef MKF_BOOK_HPP_INCLUDED
#define MKF_BOOK_HPP_INCLUDED


#include"mkf_definition.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"


namespace mkf{


using DefinitionList = std::list<Definition>;


class
Book
{
  Definition  main_definition;

  DefinitionList  sub_definitions;


  Definition  read_definition(const Node&  base);

  void  read_entry(Definition&  def, const Node&  base);

  Element  read_element(uint32_t  flags, const Node&  base);

  uint32_t  read_mark(const Node&  base);

  std::string  read_string_literal(const Node&  base);
  int  read_string_element(const Node&  base);
  int  read_character_literal(const Node&  base);


public:
  const Definition&          get_main_definition() const;
  const DefinitionList&  get_sub_definition_list() const;

  void  change_main_definition(Definition&&  def);

  void  append_sub_definition(Definition&&  def);

  bool  make(const std::string&  s);
  bool  make(const Node&  src);


  void  clear();

  const Definition*  find(const std::string&  id) const;

  void  print(FILE*  f=stdout) const;
  void  print(Printer&  pr) const;

};


}


#endif




