#ifndef CMPLR_INITIALIZER_HPP_INCLUDED
#define CMPLR_INITIALIZER_HPP_INCLUDED


#include"mkf_node.hpp"
#include"expression_node.hpp"




enum class
InitializerKind
{
  null,

  expression,
  expression_list,
  string,

};


struct
Initializer
{
  InitializerKind  kind;

  union Data{
    expression::Node*  nd;
    NodeList*          ndls;
    std::u16string*       s;

  } data;


   Initializer();
   Initializer(expression::Node*  nd);
   Initializer(NodeList*  ndls);
   Initializer(std::u16string*  s);
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
  void  reset(std::u16string*  s);

  void  print(FILE*  f=stdout) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

};




#endif




