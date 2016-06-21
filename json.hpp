#ifndef JSON_HPP_INCLUDED
#define JSON_HPP_INCLUDED




#include<cstddef>
#include<cstdio>
#include<string>
#include<utility>
#include<random>
#include<limits>


namespace json{


enum class
ElementKind
{
  null,
  boolean,
  integer,
  fp_number,
  string,
  object,
  array,

};


struct Element;
struct Object;
struct ObjectMember;
struct Array;




struct
Element
{
  ElementKind  kind;

  union{
    bool    b;
    int     i;
    double  f;

    std::string*  str;
    Object*       obj;
    Array*        arr;

  } data;


   Element();
   Element(int             i_);
   Element(bool            b_);
   Element(double          f_);
   Element(Object*       obj_);
   Element(std::string*  str_);
   Element(Array*        arr_);
   Element(Element&&  rhs);
  ~Element();

  Element&  operator=(Element&&  rhs);

  void  clear();

  void  reset(int             i_);
  void  reset(bool            b_);
  void  reset(double          f_);
  void  reset(Object*       obj_);
  void  reset(std::string*  str_);
  void  reset(Array*        arr_);

  void  print(bool  opening=true, int  base_i=0, FILE*  f=stdout) const;


  static Element  create_random_element(int  n=10);
  static Element  create_random_boolean();
  static Element  create_random_object(int  n);
  static Element  create_random_array(int  n);
  static Element  create_random_integer();
  static Element  create_random_fp_number();
  static Element  create_random_string();

};


struct
ObjectMember
{
  std::string  name;

  Element  value;

  ObjectMember(std::string&&  name_, Element&&  value_):
  name(std::move(name_)),
  value(std::move(value_))
  {}

  ObjectMember(ObjectMember&&  rhs):
  name(std::move(rhs.name)),
  value(std::move(rhs.value))
  {}

};


struct
Object
{
  std::vector<ObjectMember>  members;

  Object(){}
  Object(Object&&  rhs): members(std::move(rhs.members)){}

  void  print(bool  opening, int  base_i, FILE*  f) const;

};


struct
Array
{
  std::vector<Element>  elements;

  Array(){}
  Array(Array&&  rhs): elements(std::move(rhs.elements)){}

  void  print(bool  opening, int  base_i, FILE*  f) const;

};




}


#endif




