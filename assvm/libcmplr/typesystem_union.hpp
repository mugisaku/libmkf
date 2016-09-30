#ifndef TYPESYSTEM_UNION_HPP_INCLUDED
#define TYPESYSTEM_UNION_HPP_INCLUDED


#include<memory>
#include<string>
#include<vector>
#include"typesystem_fundamental.hpp"




namespace typesystem{


struct Element;


struct
UnionMember
{
  std::unique_ptr<Element>  type;

  std::string  name;

  UnionMember(                                      );
  UnionMember(Element&&  type_, std::string&&  name_);

  UnionMember(const UnionMember&   rhs) noexcept;
  UnionMember(      UnionMember&&  rhs) noexcept;

};


struct
Union
{
  std::string  name;

  std::vector<UnionMember>  member_list;

  size_t            size;
  size_t  alignment_size;

  Union();
  Union(std::string&&  name_);

  void  append(UnionMember&&  member);

  void  snprint(char*&  s, size_t&  n) const;

  size_t  get_size() const;
  size_t  get_alignment_size() const;

};


}


#endif




