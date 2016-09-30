#ifndef TYPESYSTEM_STRUCT_HPP_INCLUDED
#define TYPESYSTEM_STRUCT_HPP_INCLUDED


#include<memory>
#include<string>
#include<vector>
#include"typesystem_fundamental.hpp"




namespace typesystem{


struct Element;


struct
StructMember
{
  std::unique_ptr<Element>  type;

  std::string  name;

  size_t  offset;

  StructMember(Element&&  type_, std::string&&  name_, size_t  offset_=0);

  StructMember(const StructMember&   rhs) noexcept;
  StructMember(      StructMember&&  rhs) noexcept;

  size_t  get_tail_offset() const;

};


struct
Struct
{
  std::string  name;

  size_t            size;
  size_t  alignment_size;

  std::vector<StructMember>  member_list;

  Struct(                    );
  Struct(std::string&&  name_);

  void  append(StructMember&&  member);

  void  snprint(char*&  s, size_t&  n) const;

  size_t  get_size() const;
  size_t  get_alignment_size() const;

};


}


#endif




