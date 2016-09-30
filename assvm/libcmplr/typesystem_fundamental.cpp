#include"typesystem_fundamental.hpp"
#include<cstdio>




namespace typesystem{


const char*
get_name(FundamentalKind  k)
{
    switch(k)
    {
  case(FundamentalKind::void_ ): return "void";
  case(FundamentalKind::bool_ ): return "bool";
  case(FundamentalKind::int8  ): return "int8";
  case(FundamentalKind::uint8 ): return "uint8";
  case(FundamentalKind::char_ ): return "char";
  case(FundamentalKind::int16 ): return "int16";
  case(FundamentalKind::uint16): return "uint16";
  case(FundamentalKind::int32 ): return "int32";
    }


  return "**error**";
}


size_t
Fundamental::
get_size() const
{
  return typesystem::get_size(kind);
}


size_t
get_size(FundamentalKind  k)
{
    switch(k)
    {
  case(FundamentalKind::void_ ):
      return 0;
  case(FundamentalKind::bool_ ):
  case(FundamentalKind::int8  ):
  case(FundamentalKind::uint8 ):
      return 1;
  case(FundamentalKind::char_ ):
  case(FundamentalKind::int16 ):
  case(FundamentalKind::uint16):
      return 2;
  case(FundamentalKind::int32 ):
      return 4;
    }


  return 0;
}




void
Fundamental::
snprint(char*&  s, size_t&  n) const
{
  int  res = 0;

    switch(kind)
    {
  case(FundamentalKind::void_ ): res = snprintf(s,n,"void");break;
  case(FundamentalKind::bool_ ): res = snprintf(s,n,"bool");break;
  case(FundamentalKind::int8  ): res = snprintf(s,n,"int8");break;
  case(FundamentalKind::uint8 ): res = snprintf(s,n,"uint8");break;
  case(FundamentalKind::char_ ): res = snprintf(s,n,"char");break;
  case(FundamentalKind::int16 ): res = snprintf(s,n,"int16");break;
  case(FundamentalKind::uint16): res = snprintf(s,n,"uint16");break;
  case(FundamentalKind::int32 ): res = snprintf(s,n,"int32");break;
    }


  s += res;
  n -= res;
}


}




