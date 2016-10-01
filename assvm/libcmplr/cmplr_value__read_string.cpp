#include"cmplr_value.hpp"
#include"libpp/pp_utf8chunk.hpp"
#include<cstdlib>




namespace{
char16_t
read_string_element(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == " "                     ){return u' ';}
      else if(nd == "CTYPE_unicode"         ){return nd.character.unicode;}
      else if(nd == "null_character"        ){return u'\0';}
      else if(nd == "newline_character"     ){return u'\n';}
      else if(nd == "backslash_character"   ){return u'\\';}
      else if(nd == "single_quote_character"){return u'\'';}
      else if(nd == "double_quote_character"){return u'\"';}
      else if(nd == "normal_character"      ){return nd.character.unicode;}
      else {return nd.character.unicode;}


      cur.advance();
    }


  return 0;
}
}




char16_t
Value::
read_character_literal(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "string_element")
        {
          return read_string_element(nd);
        }


      cur.advance();
    }


  return 0;
}


std::u16string
Value::
read_string_literal(const mkf::Node&  base)
{
  std::u16string  s;

  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "string_element")
        {
          s.push_back(read_string_element(nd));
        }


      cur.advance();
    }


  return std::move(s);
}




