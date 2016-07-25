#include"mkf_ctype.hpp"
#include"mkf_unicode.hpp"
#include"mkf_node.hpp"
#include<cstring>
#include<cctype>




namespace mkf{


const char*
get_ctype_name(CType  type)
{
    switch(type)
    {
      case(CType::print ): return "print";
      case(CType::graph ): return "graph";
      case(CType::blank ): return "blank";
      case(CType::digit ): return "digit";
      case(CType::xdigit): return "xdigit";
      case(CType::lower ): return "lower";
      case(CType::upper ): return "upper";
      case(CType::punct ): return "punct";
      case(CType::space ): return "space";
      case(CType::alpha ): return "alpha";
      case(CType::alnum ): return "alnum";
      case(CType::unicode): return "unicode";
      default:;
    }


  return "unknown";
}


CType
get_ctype(const char*  name)
{
    if(std::strncmp(name,"CTYPE_",6) == 0)
    {
      name += 6;

           if(std::strcmp(name,"digit"  ) == 0){return CType::digit;}
      else if(std::strcmp(name,"graph"  ) == 0){return CType::graph;}
      else if(std::strcmp(name,"print"  ) == 0){return CType::print;}
      else if(std::strcmp(name,"blank"  ) == 0){return CType::blank;}
      else if(std::strcmp(name,"xdigit" ) == 0){return CType::xdigit;}
      else if(std::strcmp(name,"lower"  ) == 0){return CType::lower;}
      else if(std::strcmp(name,"upper"  ) == 0){return CType::upper;}
      else if(std::strcmp(name,"punct"  ) == 0){return CType::punct;}
      else if(std::strcmp(name,"space"  ) == 0){return CType::space;}
      else if(std::strcmp(name,"alpha"  ) == 0){return CType::alpha;}
      else if(std::strcmp(name,"alnum"  ) == 0){return CType::alnum;}
      else if(std::strcmp(name,"unicode") == 0){return CType::unicode;}
    }


  return CType::null;
}


bool
test_ctype_code(char16_t  c, CType  type)
{
    switch(type)
    {
      case(CType::print ): return isprint(c);
      case(CType::graph ): return isgraph(c);
      case(CType::blank ): return isblank(c);
      case(CType::digit ): return isdigit(c);
      case(CType::xdigit): return isxdigit(c);
      case(CType::lower ): return islower(c);
      case(CType::upper ): return isupper(c);
      case(CType::punct ): return ispunct(c);
      case(CType::space ): return isspace(c);
      case(CType::alpha ): return isalpha(c);
      case(CType::alnum ): return isalnum(c);
      case(CType::unicode): return !isascii(c);
      default:;
    }


  return false;
}




}


