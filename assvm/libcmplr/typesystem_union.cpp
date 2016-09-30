#include"typesystem_union.hpp"
#include"typesystem_element.hpp"
#include<cstdlib>




namespace typesystem{


UnionMember::
UnionMember()
{
}


UnionMember::
UnionMember(Element&&  type_, std::string&&  name_):
type(new Type(std::move(type_))),
name(std::move(name_))
{
}


UnionMember::
UnionMember(const UnionMember&   rhs) noexcept:
name(rhs.name),
type(rhs.type? new Element(*rhs.type):nullptr)
{
}


UnionMember::
UnionMember(UnionMember&&  rhs) noexcept:
name(std::move(rhs.name)),
type(std::move(rhs.type))
{
}




Union::
Union():
size(0),
alignment_size(0)
{
}


Union::
Union(std::string&&  name_):
size(0),
alignment_size(0),
name(std::move(name_))
{
}




void
Union::
snprint(char*&  s, size_t&  n) const
{
  int  res = snprintf(s,n,"union %s{\n",name.data());

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

      res = snprintf(s,n,"  %s  %s,\n",buf,m.name.data());

      s += res;
      n -= res;
    }


  res = snprintf(s,n,"}\n");

  s += res;
  n -= res;
}


void
Union::
append(UnionMember&&  member)
{
            size = std::max(          size,member.type->get_size()          );
  alignment_size = std::max(alignment_size,member.type->get_alignment_size());

  member_list.emplace_back(std::move(member));
}


size_t
Union::
get_size() const
{
  return 0;
}


size_t
Union::
get_alignment_size() const
{
  return alignment_size;
}


}




