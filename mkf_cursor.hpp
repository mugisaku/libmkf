#ifndef MKF_CURSOR_HPP_INCLUDED
#define MKF_CURSOR_HPP_INCLUDED


#include"mkf_node.hpp"
#include"mkf_print.hpp"


namespace mkf{


class
Cursor
{
  const Node*  node;

  int  child_index;

public:
  Cursor(const Node&  start);


  bool  test_ended() const;

  const Node&  operator*() const;

  bool  advance();

  const Node&  get() const;

};


}


#endif




