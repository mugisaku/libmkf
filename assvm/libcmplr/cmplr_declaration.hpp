#ifndef CMPLR_DECLARATION_HPP_INCLUDED
#define CMPLR_DECLARATION_HPP_INCLUDED


#include<string>
#include<vector>
#include"cmplr_foldcontext.hpp"
#include"expression_foldresult.hpp"




struct Context;


namespace expression{
struct Node;
}


enum class
ObjectKind
{
  null,

  undefined,

  value,
  constant,
  array,
  constant_array,
  function,

  reference,
  argument_list,

};


enum class
DeclarationKind
{
  global,
  local,
  local_static,
  parameter,

};


struct
Declaration
{
  DeclarationKind  kind;

  std::string  identifier;

  int  index;

  ObjectKind  object_kind;

  union Data{
    void*  ptr;

    int  i;

    const Function*  fn;

    expression::Node*  expr;

    std::vector<expression::Node>*   arr;
    std::vector<int>*               carr;

  } data;


  Declaration();
  Declaration(DeclarationKind  k, std::string&&  id, expression::Node*  expr=nullptr);
  Declaration(const Function*  fn);
  Declaration(const Declaration&  rhs)=delete;
  Declaration(Declaration&&  rhs) noexcept;
  ~Declaration();


  Declaration&  operator=(Declaration&&  rhs) noexcept;

  size_t  get_size() const;

  void  clear();

  void  reset(const Function*  fn);

  expression::FoldResult  fold(FoldContext&  ctx) const;

  void  print(FILE*  f=stdout) const;
  void  print_value(FILE*  f=stdout) const;
  void  print_constant(FILE*  f=stdout) const;
  void  print_array(FILE*  f=stdout) const;
  void  print_constant_array(FILE*  f=stdout) const;
  void  print_function(FILE*  f=stdout) const;

  ObjectKind  compile(Context&  ctx) const;
  ObjectKind  compile_function(Context&  ctx) const;
  ObjectKind  compile_value(Context&  ctx) const;
  ObjectKind  compile_constant(Context&  ctx) const;
  ObjectKind  compile_array(Context&  ctx) const;
  ObjectKind  compile_constant_array(Context&  ctx) const;

  void  compile_definition(Context&  ctx) const;
  void  compile_value_definition(Context&  ctx) const;
  void  compile_constant_definition(Context&  ctx) const;
  void  compile_array_definition(Context&  ctx) const;
  void  compile_constant_array_definition(Context&  ctx) const;
  void  compile_function_definition(Context&  ctx) const;

};




#endif




