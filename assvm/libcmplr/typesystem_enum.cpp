#include"typesystem_enum.hpp"
#include"typesystem_element.hpp"




namespace typesystem{


Enum::
Enum():
base(FundamentalKind::int32)
{
}


Enum::
Enum(std::string&&  name_, std::initializer_list<Enumerator>  ls):
base(FundamentalKind::int32),
name(std::move(name_)),
enumerator_list(ls.size())
{
  auto  src =              ls.begin();
  auto  dst = enumerator_list.begin();

  int  v = 0;

    for(int  i = 0;  i < ls.size();  ++i)
    {
      auto&  src_e = *src++;
      auto&  dst_e = *dst++;

      dst_e.name = std::move(src_e.name);

      dst_e.set_value(src_e.value_defined? src_e.value:v);

      v = dst_e.value+1;
    }
}


Enum::
Enum(FundamentalKind  k, std::string&&  name_, std::initializer_list<Enumerator>  ls):
base(k),
name(std::move(name_)),
enumerator_list(ls.size())
{
  auto  src =              ls.begin();
  auto  dst = enumerator_list.begin();

  int  v = 0;

    for(int  i = 0;  i < ls.size();  ++i)
    {
      auto&  src_e = *src++;
      auto&  dst_e = *dst++;

      dst_e.name = std::move(src_e.name);

      dst_e.set_value(src_e.value_defined? src_e.value:v);

      v = dst_e.value+1;
    }
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




