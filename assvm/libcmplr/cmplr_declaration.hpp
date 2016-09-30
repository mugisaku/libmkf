#ifndef CMPLR_DECLARATION_HPP_INCLUDED
#define CMPLR_DECLARATION_HPP_INCLUDED


#include<string>
#include<vector>
#include"typesystem_element.hpp"
#include"cmplr_value.hpp"




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

};


struct
Declaration
{
  StorageKind  storage_kind;

  size_t  offset;

  std::string  name;

  Value  value;

  Declaration();
  Declaration(const Parameter&  para, size_t  off=0);
  Declaration(const mkf::Node&  src, PreContext&  prectx);


  const Value&  get_value() const;

  const std::string&  get_name() const;

  void  reset(const Parameter&  para, size_t  off=0);
  void  reset(Function*  fn);

  void  print(FILE*  f=stdout) const;

  Type  compile(Context&  ctx) const;
  void  compile_definition(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  void  read_object_declaration(const mkf::Node&  src, PreContext&  prectx);

};




#endif




