#ifndef TYPESYSTEM_ENUM_HPP_INCLUDED
#define TYPESYSTEM_ENUM_HPP_INCLUDED


#include<string>
#include<vector>
#include<vector>
#include"typesystem_fundamental.hpp"




namespace typesystem{


struct
Enumerator
{
  std::string  name;

  bool  value_defined;

  int  value;

  Enumerator(                            ):                         value_defined(false)          {}
  Enumerator(std::string&&  name_        ): name(std::move(name_)), value_defined(false)          {}
  Enumerator(std::string&&  name_, int  v): name(std::move(name_)), value_defined( true), value(v){}

  void  set_value(int  v)
  {
    value = v;

    value_defined = true;
  }

};


struct
Enum
{
  FundamentalKind  base;

  std::string  name;

  std::vector<Enumerator>  enumerator_list;

  Enum(                                        );
  Enum(                    std::string&&  name_);
  Enum(FundamentalKind  k, std::string&&  name_);

  void  append(std::string&&  name_             );
  void  append(std::string&&  name_, int   value);

  void  snprint(char*&  s, size_t&  n) const;

};


}


#endif




