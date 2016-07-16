#ifndef JSON_HPP_INCLUDED
#define JSON_HPP_INCLUDED


#include<cstddef>
#include<cstdio>
#include<string>
#include<utility>
#include<random>
#include<limits>
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


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
   Element(const Element&)=delete;
   Element(Element&&  rhs) noexcept;
  ~Element();


  bool  operator==(const Element&  rhs) const;

  Element&  operator=(Element&&  rhs);

  void  clear();

  void  reset(int             i_);
  void  reset(bool            b_);
  void  reset(double          f_);
  void  reset(Object*       obj_);
  void  reset(std::string*  str_);
  void  reset(Array*        arr_);

  void  print(bool  opening=true, int  base_i=0, FILE*  f=stdout) const;

};


struct
ObjectMember
{
  std::string  name;

  Element  value;

  ObjectMember(){}
  ObjectMember(std::string&&  name_, Element&&  value_):
  name(std::move(name_)),
  value(std::move(value_))
  {}

  ObjectMember(ObjectMember&&  rhs):
  name(std::move(rhs.name)),
  value(std::move(rhs.value))
  {}

  bool  operator==(const ObjectMember&  rhs) const
  {
    return((name  == rhs.name ) &&
           (value == rhs.value));
  }

};


struct
Object
{
  std::vector<ObjectMember>  members;

  Object(){}
  Object(Object&&  rhs): members(std::move(rhs.members)){}


  bool  operator==(const Object&  rhs) const
  {
    return(members == rhs.members);
  }

  void  print(bool  opening, int  base_i, FILE*  f) const;

};


struct
Array
{
  std::vector<Element>  elements;

  Array(){}
  Array(Array&&  rhs): elements(std::move(rhs.elements)){}


  bool  operator==(const Array&  rhs) const
  {
    return(elements == rhs.elements);
  }

  void  print(bool  opening, int  base_i, FILE*  f) const;

};






Element        read_json(const mkf::Node&  base);
Element     read_element(const mkf::Node&  base);

Object*              read_object(const mkf::Node&  base);
ObjectMember  read_object_member(const mkf::Node&  base);

Array*            read_array(const mkf::Node&  base);

std::string  read_string(const mkf::Node&  base);


Element  create_random_element(int  n=10);
Element  create_random_boolean();
Element  create_random_object(int  n);
Element  create_random_array(int  n);
Element  create_random_integer();
Element  create_random_fp_number();
Element  create_random_string();




}


#endif




