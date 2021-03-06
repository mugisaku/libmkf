#include"typesystem_struct.hpp"
#include"typesystem_element.hpp"
#include<cstdlib>




namespace typesystem{


StructMember::
StructMember(Element&&  type_, std::string&&  name_, size_t  offset_):
type(new Type(std::move(type_))),
name(std::move(name_)),
offset(offset_)
{
  offset += (offset%type->get_alignment_size());
}


StructMember::
StructMember(const StructMember&  rhs) noexcept:
name(rhs.name),
type(rhs.type? new Element(*rhs.type):nullptr),
offset(rhs.offset)
{
  offset += (offset%type->get_alignment_size());
}


StructMember::
StructMember(StructMember&&  rhs) noexcept:
name(std::move(rhs.name)),
type(std::move(rhs.type)),
offset(rhs.offset)
{
  offset += (offset%type->get_alignment_size());
}




size_t
StructMember::
get_tail_offset() const
{
  return offset+type->get_size();
}




Struct::
Struct():
size(0),
alignment_size(0)
{
}


Struct::
Struct(std::string&&  name_):
size(0),
alignment_size(0),
name(std::move(name_))
{
}




void
Struct::
append(StructMember&&  member)
{
  alignment_size = std::max(alignment_size,member.type->get_alignment_size());

  member.offset = (member_list.size()? member_list.back().get_tail_offset():0);

  member_list.emplace_back(std::move(member));


  auto  tail_offset = member_list.back().get_tail_offset();

  size = (tail_offset+(alignment_size-1))/alignment_size*alignment_size;
}


void
Struct::
snprint(char*&  s, size_t&  n) const
{
  int  res = snprintf(s,n,"struct %s{\n",name.data());

  s += res;
  n -= res;

  res = snprintf(s,n,"          size = %8zd\nalignment_size = %8zd\n",size,alignment_size);

  s += res;
  n -= res;

    for(auto&  m: member_list)
    {
      char  buf[256];

      auto  ss = buf;
      auto  nn = sizeof(buf);

      m.type->snprint(ss,nn);

      res = snprintf(s,n,"  %s  %s(offset = %8zd),\n",buf,m.name.data(),m.offset);

      s += res;
      n -= res;
    }


  res = snprintf(s,n,"}\n");

  s += res;
  n -= res;
}


size_t
Struct::
get_size() const
{
  return size;
}


size_t
Struct::
get_alignment_size() const
{
  return alignment_size;
}


}




