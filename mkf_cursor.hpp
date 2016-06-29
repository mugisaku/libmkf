#ifndef MKF_CURSOR_HPP_INCLUDED
#define MKF_CURSOR_HPP_INCLUDED


#include"mkf_node.hpp"
#include"mkf_print.hpp"


namespace mkf{


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




