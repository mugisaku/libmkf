#include"expression_operand.hpp"
#include<cstdlib>




namespace{
unsigned long
read_decimal_literal(const mkf::Node&  base)
{
  std::string  s;

  base.collect_characters(s);

  return std::stoul(s,nullptr,10);
}


unsigned long
read_hex_literal(const mkf::Node&  base)
{
  std::string  s;

  base.collect_characters(s);

  return std::stoul(s,nullptr,16);
}


unsigned long
read_binary_literal(const mkf::Node&  base)
{
  unsigned long  i = 0;

  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "zero_or_one")
        {
          i <<=                                  1;
          i  |= (nd.character.unicode == '1')? 1:0;
        }


      cur.advance();
    }


  return i;
}



}



void
expression::Operand::
read_integer_literal(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == "decimal_literal"){reset(read_decimal_literal(nd));}
      else if(nd == "hex_literal"    ){reset(read_hex_literal(nd));}
      else if(nd == "binary_literal" ){reset(read_binary_literal(nd));}


      cur.advance();
    }
}




