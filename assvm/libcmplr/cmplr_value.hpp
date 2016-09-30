#ifndef CMPLR_VALUE_HPP_INCLUDED
#define CMPLR_VALUE_HPP_INCLUDED


#include"typesystem_element.hpp"
#include"mkf_node.hpp"
#include<vector>




struct Declaration;
struct Function;
struct PreContext;


namespace expression{
struct Node;
}


struct Value;

using ValueList = std::vector<Value>;


enum class
ValueKind
{
  null,

  single,
  array,

  reference,
  parameter,
  function,

};


struct
Value
{
  ValueKind  kind;

  Type  type;

  union{
    expression::Node*  nd;

    ValueList*  ls;

    Function*  fn;

    const Value*  v;

  } data;


  Value();
  Value(Function*  fn);
  Value(const Declaration&  decl);
  Value(Type&&  t, int  i);
  Value(Type&&  t, ValueList*  ls);
  Value(const mkf::Node&  src, PreContext&  prectx);
  Value(const Value&   rhs) noexcept;
  Value(      Value&&  rhs) noexcept;
 ~Value();

  Value&  operator=(const Value&   rhs) noexcept;
  Value&  operator=(      Value&&  rhs) noexcept;


  void  clear();

  bool  dereference();

  bool  change_reference_to_pointer();

  void  print(FILE*  f=stdout) const;

  Value  compile(Context&  ctx) const;
  void  compile_definition(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  static ValueList  read_list(const mkf::Node&  src, PreContext&  prectx);

};




#endif




