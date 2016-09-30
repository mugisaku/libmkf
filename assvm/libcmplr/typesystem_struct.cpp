#include"typesystem_struct.hpp"
#include"typesystem_element.hpp"
#include<cstdlib>




namespace typesystem{


StructMember::
StructMember(Element&&  type_, std::string&&  name_):
type(new Type(std::move(type_))),
name(std::move(name_)),
offset(0)
{
}


StructMember::
StructMember(const StructMember&  rhs) noexcept:
name(rhs.name),
type(rhs.type? new Element(*rhs.type):nullptr),
offset(rhs.offset)
{
}


StructMember::
StructMember(StructMember&&  rhs) noexcept:
name(std::move(rhs.name)),
type(std::move(rhs.type)),
offset(rhs.offset)
{
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
  auto  malsz = member.type->get_alignment_size();

  member.offset = size+(size%malsz);

  size = member.offset+member.type->get_size();

  alignment_size = std::max(alignment_size,malsz);

  member_list.emplace_back(std::move(member));
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




