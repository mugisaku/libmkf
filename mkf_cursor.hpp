#ifndef MKF_CURSOR_HPP_INCLUDED
#define MKF_CURSOR_HPP_INCLUDED


#include"mkf_print.hpp"
#include"mkf_list.hpp"


namespace mkf{


struct Node;


using NodeList = List<Node*>;


class
Cursor
{
  NodeList::Iterator  iter;

public:
  Cursor(const Node&  start);


  bool  test_ended() const;

  const Node&  operator*() const;

  bool  advance();

  const Node&  get() const;

};


}


#endif




