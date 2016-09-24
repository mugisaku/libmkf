#ifndef CMPLR_INITIALIZER_HPP_INCLUDED
#define CMPLR_INITIALIZER_HPP_INCLUDED


#include"mkf_node.hpp"
#include"cmplr_type.hpp"
#include"expression_node.hpp"




struct Context;


enum class
InitializerKind
{
  null,

  expression,
  initializer_list,

};


struct
Initializer
{
  InitializerKind  kind;

  union Data{
    expression::Node*  nd;
    NodeList*          ndls;

  } data;


   Initializer();
   Initializer(expression::Node*  nd);
   Initializer(NodeList*  ndls);
   Initializer(const mkf::Node&  src, PreContext&  prectx);
   Initializer(const Initializer&   rhs);
   Initializer(      Initializer&&  rhs) noexcept;
  ~Initializer();


  operator  bool() const;

  Initializer&  operator=(const Initializer&   rhs);
  Initializer&  operator=(      Initializer&&  rhs) noexcept;

  void  clear();

  void  reset(expression::Node*  nd);
  void  reset(NodeList*  ndls);

  Type  compile(Context&  ctx) const;

  void  print(FILE*  f=stdout) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

};




#endif




