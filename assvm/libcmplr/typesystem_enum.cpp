#include"typesystem_enum.hpp"
#include"typesystem_element.hpp"




namespace typesystem{


Enum::
Enum():
base(FundamentalKind::int32)
{
}


Enum::
Enum(std::string&&  name_):
base(FundamentalKind::int32),
name(std::move(name_))
{
}


Enum::
Enum(FundamentalKind  k, std::string&&  name_):
base(k),
name(std::move(name_))
{
}




void
Enum::
append(std::string&&  name_)
{
    if(enumerator_list.size())
    {
      int  v = enumerator_list.back().value+1;

      enumerator_list.emplace_back(std::move(name_),v);
    }

  else
    {
      enumerator_list.emplace_back(std::move(name_),0);
    }
}


void
Enum::
append(std::string&&  name_, int   value)
{
  enumerator_list.emplace_back(std::move(name_),value);
}


void
Enum::
snprint(char*&  s, size_t&  n) const
{
  int  res = snprintf(s,n,"enum %s: %s{\n",name.data(),get_name(base));

  s += res;
  n -= res;

    for(auto&  e: enumerator_list)
    {
      res = snprintf(s,n,"  %s = %d,\n",e.name.data(),e.value);

      s += res;
      n -= res;
    }


  res = snprintf(s,n,"}\n");

  s += res;
  n -= res;
}


}




