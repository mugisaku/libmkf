#ifndef CMPLR_DECLARATION_HPP_INCLUDED
#define CMPLR_DECLARATION_HPP_INCLUDED


#include<string>
#include<vector>
#include"typesystem_element.hpp"
#include"cmplr_literal.hpp"




struct Context;
struct PreContext;
struct Function;
struct Parameter;


namespace expression{
struct Node;
}


enum class
StorageKind
{
  null,

  global,
  local,
  local_static,
  alias,
  parameter,

};


struct
Declaration
{
  StorageKind  storage_kind;

  size_t  offset;

  std::string  name;

  Type  type;

  Literal  literal;


  Declaration();
  Declaration(const Parameter&  para, size_t  off=0);
  Declaration(const mkf::Node&  src, PreContext&  prectx);


  bool  operator==(StorageKind  stkind) const;

  const std::string&  get_name() const;

  void  reset(Type&&  typ, Literal&&  lit);
  void  reset(const Parameter&  para, size_t  off=0);
  void  reset(Function*  fn);

  void  print(FILE*  f=stdout) const;

  Value  make_value() const;

  Value  compile(Context&  ctx) const;
  void   compile_definition(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  void  read_object_declaration(const mkf::Node&  src, PreContext&  prectx);

};




#endif




