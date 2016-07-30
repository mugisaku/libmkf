#ifndef MKF_NODE_HPP_INCLUDED
#define MKF_NODE_HPP_INCLUDED


#include<string>
#include"libpp/pp.hpp"
#include"mkf_discontinue.hpp"
#include"mkf_cursor.hpp"


namespace mkf{


struct
Node
{
  const char*  defname;

  pp::Character  character;

  NodeList  children;

   Node(const char*  defname_="", pp::Character  character_=pp::Character());
   Node(const Node&)=delete;
   Node(Node&&  rhs) noexcept;
  ~Node();


  bool  operator==(const char*  name) const;

  Node&  operator=(Node&&  rhs);

  Cursor  make_cursor() const;

  void  clear();

  void  append(Node*  child);

  void  collect_characters(pp::String&  s) const;
  void  collect_characters(std::string&  s) const;

  void  print(FILE*  f=stdout) const;
  void  print(Printer&  pr) const;

};


}


#endif




