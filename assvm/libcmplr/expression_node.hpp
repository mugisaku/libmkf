#ifndef EXPRESSION_NODE_HPP_INCLUDED
#define EXPRESSION_NODE_HPP_INCLUDED


#include"expression_operand.hpp"
#include"expression_element.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include<list>


namespace expression{


struct
Node
{
  Element  element;

  Node*   left;
  Node*  right;


  Node();
  Node(const mkf::Node&  src);
  Node(Element&&  el);
  Node(const Element&  el);
  Node(Node&&  rhs) noexcept;
  Node(const Node&  rhs);
  ~Node();

  Node&  operator=(const Node&   rhs)         ;
  Node&  operator=(      Node&&  rhs) noexcept;

  void  clear();


  std::list<Node*>  to_rpn(std::vector<Element>&&  src);

  Node*  create_tree(std::list<Node*>&&  ls);


  void  print(FILE*  f=stdout) const;

  FoldResult  fold(FoldContext&  ctx) const;

  ObjectKind  compile(Context&  ctx) const;

  void  read(const mkf::Node&  src);

};


}




#endif




