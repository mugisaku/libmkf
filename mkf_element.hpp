#ifndef MKF_ELEMENT_HPP_INCLUDED
#define MKF_ELEMENT_HPP_INCLUDED


#include<cstdint>
#include<cstddef>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<string>
#include<vector>
#include<list>
#include<initializer_list>


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace mkf{


enum class
ElementKind: uint8_t
{
  null,
  character,
  string,
  identifier,

};


namespace ElementFlag
{
constexpr int  omittable = 1;
constexpr int     repeat = 2;
}


struct Element;
struct Book;
struct Definition;
struct Printer;


inline
void
skip_space(const char*&  p)
{
    while(isspace(*p))
    {
      ++p;
    }
}


struct
String
{
  const char*  ptr;

  constexpr String(const char*  p): ptr(p){}

};


struct
Identifier
{
  const char*  ptr;

  constexpr Identifier(const char*  p): ptr(p){}

};


class
Element
{
  ElementKind  kind;

  uint8_t  flags;

  uint16_t  length;

  union{
    char  chr;

    char*  ptr;

    char  buf[4];
  };


  void  copy(const char*  s);

public:
  Element(int  flags_=0);
  Element(int  flags_, int  chr_);
  Element(int  flags_, const String&     str);
  Element(int  flags_, const Identifier&  id);
  Element(Element&&  rhs);
 ~Element();


  Element&  operator=(Element&&  rhs);

  void  reset(int  flags_, int  chr_);
  void  reset(int  flags_, const String&  str);
  void  reset(int  flags_, const Identifier&  id);

  void  clear();

  ElementKind  get_kind() const;

  size_t  get_length() const;

  const char*  get_string() const;
  int       get_character() const;

  bool  test_omittable() const;
  bool  test_repeat() const;

  void  print(Printer&  pr) const;

};


using ElementList = std::list<Element>;


}


#endif




