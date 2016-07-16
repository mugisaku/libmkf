#ifndef MKF_NODE_HPP_INCLUDED
#define MKF_NODE_HPP_INCLUDED


#include<string>
#include"mkf_list.hpp"
#include"mkf_discontinue.hpp"
#include"mkf_print.hpp"


namespace mkf{


struct Node;


using NodeList = List<Node*>;


struct
Node
{
  const char*  defname;

  int  character;

  NodeList  children;

   Node(const char*  defname_="", int  character_=0);
   Node(const Node&)=delete;
   Node(Node&&  rhs) noexcept;
  ~Node();


  bool  operator==(const char*  name) const;

  Node&  operator=(Node&&  rhs);

  void  clear();

  void  append(Node*  child);

  void  collect_characters(std::string&  s) const;

  void  print(FILE*  f=stdout) const;
  void  print(Printer&  pr) const;

};


using NodeList = List<Node*>;


struct
Result
{
  bool  matched;

  NodeList  node_list;

  Result(bool  b): matched(b){}
  Result(NodeList&  ls): matched(true), node_list(std::move(ls)){}
  Result(Result&&  rhs){*this = std::move(rhs);}
  ~Result(){for(auto  nd: node_list){delete nd;}}


  operator bool() const{return matched;}

  Result&  operator=(Result&&  rhs)
  {
    matched = rhs.matched;

    node_list = std::move(rhs.node_list);

    return *this;
  }


  NodeList  release(){return std::move(node_list);}

};


}


#endif




