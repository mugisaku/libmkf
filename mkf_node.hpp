#ifndef MKF_NODE_HPP_INCLUDED
#define MKF_NODE_HPP_INCLUDED


#include"mkf_definition.hpp"
#include"mkf_print.hpp"


namespace mkf{


struct
Node
{
  Node*  parent;

  const char*  defname;

  std::vector<Node*>  children;

  int  depth;
  int  character;

   Node(const char*  defname_="", int  c=0);
   Node(Node&&  rhs);
  ~Node();


  bool  operator==(const char*  name) const;

  void  append(Node*  child);

  Node*  release_unique_child();

  void  collect_characters(std::string&  s) const;

  void  print(FILE*  f=stdout) const;
  void  print(Printer&  pr) const;

};


}


#endif




