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


struct
ArgumentList
{
  ValueList*  value_list;

  constexpr ArgumentList(ValueList*  ls): value_list(ls){}

};


struct
Subscript
{
  expression::Node*  nd;

  constexpr Subscript(expression::Node*  nd_): nd(nd_){};

};


enum class
ValueKind
{
  null,

  expression,

  value_list,

  nullptr_,
  boolean,
  string,
  character,
  integer,
  identifier,
  argument_list,
  subscript,

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
    int  i;

    bool  b;

    char16_t  c;

    std::string*    id;
    std::u16string*  s;

    ValueList*  ls;

    expression::Node*  nd;

    Function*  fn;

    const Declaration*  decl;

  } data;


  Value();
  Value(Type&&  type_);
  Value( int8_t  i);
  Value(uint8_t  i);
  Value( int16_t  i);
  Value(uint16_t  i);
  Value( int32_t  i);
  Value(char16_t  c);
  Value(nullptr_t  nul);
  Value(bool  b);
  Value(std::u16string*  s);
  Value(std::string*  id);
  Value(expression::Node*  nd);
  Value(ValueList*  vals);
  Value(const ArgumentList&  args);
  Value(const Subscript&  subsc);
  Value(const mkf::Node&  src, PreContext&  prectx);
  Value(const Value&   rhs) noexcept;
  Value(      Value&&  rhs) noexcept;
 ~Value();

  Value&  operator=(const Value&   rhs) noexcept;
  Value&  operator=(      Value&&  rhs) noexcept;

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
  void  reset(ValueList*  vals);
  void  reset(const ArgumentList&  args);
  void  reset(const Subscript&  subsc);


  bool  dereference();

  bool  change_reference_to_pointer();

  void  print(FILE*  f=stdout) const;

  Value  compile(Context&  ctx) const;
  void  compile_definition(const Declaration&  decl, Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  static ValueList  read_list(const mkf::Node&  src, PreContext&  prectx);

  static uint32_t          read_integer_literal(const mkf::Node&  src);
  static char16_t        read_character_literal(const mkf::Node&  src);
  static std::u16string     read_string_literal(const mkf::Node&  src);

};


Value       VoidValue();
Value       NullptrValue();
Value            CharValue(           );
Value       ConstCharValue(char16_t  c);
Value       BoolValue(       );
Value  ConstBoolValue(bool  b);
Value       I8Value(         );
Value  ConstI8Value(int8_t  i);
Value       U8Value(         );
Value  ConstU8Value(uint8_t  i);
Value       I16Value(         );
Value  ConstI16Value(int16_t  i);
Value       U16Value(           );
Value  ConstU16Value(uint16_t  i);
Value       I32Value(          );
Value  ConstI32Value(int32_t  i);




#endif




