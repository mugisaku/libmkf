#ifndef CMPLR_DECLARATION_HPP_INCLUDED
#define CMPLR_DECLARATION_HPP_INCLUDED


#include<string>
#include<vector>
#include"cmplr_foldcontext.hpp"
#include"cmplr_type.hpp"
#include"cmplr_parameter.hpp"
#include"expression_foldresult.hpp"




struct Context;
struct PreContext;
struct Variable;
struct Constant;
struct Function;


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


enum class
DeclarationKind
{
  null,

  function,
  variable,
  constant,
  parameter,

};


struct
Declaration
{
  StorageKind  storage_kind;

  DeclarationKind  kind;

  size_t  offset;

  union Data{
    const Parameter*  par;

    Function*    fn;
    Variable*   var;
    Constant*   con;

  } data;


  Declaration();
  Declaration(const Parameter&  par, size_t  off);
  Declaration(const mkf::Node&  src, PreContext&  prectx);
  Declaration(const Declaration&   rhs)=delete;
  Declaration(      Declaration&&  rhs) noexcept;
 ~Declaration();


  Declaration&  operator=(Declaration&&  rhs) noexcept;

  void  clear();

  size_t  get_size() const;

  const std::string&  get_name() const;

  void  reset(Type&&  type, std::string&&  name, expression::Node*  initexpr=nullptr);
  void  reset(const Parameter&  par, size_t  off=0);
  void  reset(Function*  fn);

  expression::FoldResult  fold(FoldContext&  ctx) const;

  void  print(FILE*  f=stdout) const;

  Type  compile(Context&  ctx) const;
  void  compile_definition(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  void  read_object_declaration(const mkf::Node&  src, PreContext&  prectx);
  expression::Node*  read_object_initialization(const mkf::Node&  src, PreContext&  prectx);

};




#endif




