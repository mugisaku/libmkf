#include"expression_operand.hpp"
#include<cstdlib>




namespace{
int
read_string_element(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == " "                     ){return ' ';}
      else if(nd == "null_character"        ){return 0;}
      else if(nd == "newline_character"     ){return '\n';}
      else if(nd == "backslash_character"   ){return '\\';}
      else if(nd == "single_quote_character"){return '\'';}
      else if(nd == "double_quote_character"){return '\"';}
      else if(nd == "normal_character"      ){return nd.character.unicode;}


      cur.advance();
    }


  return 0;
}
}




int
expression::Operand::
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


std::string
expression::Operand::
read_string_literal(const mkf::Node&  base)
{
  std::string  s;

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




