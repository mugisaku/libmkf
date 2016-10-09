#ifndef CMPLR_LITERAL_HPP_INCLUDED
#define CMPLR_LITERAL_HPP_INCLUDED


#include"typesystem_element.hpp"
#include"cmplr_constant.hpp"
#include"cmplr_value.hpp"
#include"mkf_node.hpp"
#include<vector>




struct Declaration;
struct Function;
struct PreContext;


namespace expression{
struct Node;
}


struct Literal;

using Array = std::vector<Literal>;


struct
ArgumentList
{
  Array*  arr;

  constexpr ArgumentList(Array*  arr_): arr(arr_){}

};


struct
Subscript
{
  Literal*  lit;

  constexpr Subscript(Literal*  lit_): lit(lit_){};

};


enum class
LiteralKind
{
  null,

  expression,

  array,
  literal,

  nullptr_,
  boolean,
  string,
  character,
  integer,
  identifier,
  argument_list,
  subscript,

  reference,
  function,

};


struct
Literal
{
  LiteralKind  kind;

  union{
    int  i;

    bool  b;

    char16_t  c;

    std::string*    id;
    std::u16string*  s;

    Array*  arr;

    expression::Node*  nd;

    Literal*  lit;

    Function*  fn;

    const Declaration*  decl;

  } data;


  Literal();
  Literal( int8_t  i);
  Literal(uint8_t  i);
  Literal( int16_t  i);
  Literal(uint16_t  i);
  Literal( int32_t  i);
  Literal(char16_t  c);
  Literal(nullptr_t  nul);
  Literal(bool  b);
  Literal(std::u16string*  s);
  Literal(std::string*  id);
  Literal(expression::Node*  nd);
  Literal(Array*  arr);
  Literal(Function*  fn);
  Literal(const ArgumentList&  args);
  Literal(const Subscript&  subsc);
  Literal(const mkf::Node&  src, PreContext&  prectx);
  Literal(const Literal&   rhs) noexcept;
  Literal(      Literal&&  rhs) noexcept;
 ~Literal();

  Literal&  operator=(const Literal&   rhs) noexcept;
  Literal&  operator=(      Literal&&  rhs) noexcept;

  void  clear();

  void  reset( int8_t  i);
  void  reset(uint8_t  i);
  void  reset( int16_t  i);
  void  reset(uint16_t  i);
  void  reset( int32_t  i);
  void  reset(char16_t  c);
  void  reset(nullptr_t  nul);
  void  reset(bool  b);
  void  reset(std::u16string*  s);
  void  reset(std::string*  id);
  void  reset(expression::Node*  nd);
  void  reset(Array*  arr);
  void  reset(Function*  fn);
  void  reset(const ArgumentList&  args);
  void  reset(const Subscript&  subsc);


  void  print(FILE*  f=stdout) const;

  Constant  make_constant(PreContext&  prectx) const;

  Value  make_value(PreContext&  prectx) const;

  Value  compile(Context&  ctx) const;
  void  compile_definition(const Declaration&  decl, Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  static Array  read_list(const mkf::Node&  src, PreContext&  prectx);

  static uint32_t          read_integer_literal(const mkf::Node&  src);
  static char16_t        read_character_literal(const mkf::Node&  src);
  static std::u16string     read_string_literal(const mkf::Node&  src);

};




#endif




