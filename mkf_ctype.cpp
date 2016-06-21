#include"mkf_ctype.hpp"
#include"mkf_unicode.hpp"
#include<cstring>
#include<cctype>




namespace mkf{


CType
get_ctype(const char*  name)
{
    if(std::strncmp(name,"CTYPE_",6) == 0)
    {
      name += 6;

           if(std::strcmp(name,"digit")  == 0){return CType::digit;}
      else if(std::strcmp(name,"xdigit") == 0){return CType::xdigit;}
      else if(std::strcmp(name,"lower")  == 0){return CType::lower;}
      else if(std::strcmp(name,"upper")  == 0){return CType::upper;}
      else if(std::strcmp(name,"punct")  == 0){return CType::punct;}
      else if(std::strcmp(name,"space")  == 0){return CType::space;}
      else if(std::strcmp(name,"alpha")  == 0){return CType::alpha;}
      else if(std::strcmp(name,"alnum")  == 0){return CType::alnum;}
      else if(std::strcmp(name,"utf8" )  == 0){return CType::utf8;}
    }


  return CType::null;
}


bool
test_ctype_code(int  c, CType  type)
{
    switch(type)
    {
      case(CType::digit ): return isdigit(c);
      case(CType::xdigit): return isxdigit(c);
      case(CType::lower ): return islower(c);
      case(CType::upper ): return isupper(c);
      case(CType::punct ): return ispunct(c);
      case(CType::space ): return isspace(c);
      case(CType::alpha ): return isalpha(c);
      case(CType::alnum ): return isalnum(c);
      case(CType::utf8  ): return test_utf8code(c);
      default:;
    }


  return false;
}


}


