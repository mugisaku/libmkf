#include"expression_operand.hpp"
#include<cstdlib>




namespace{
unsigned int
read_decimal_literal(const mkf::Node&  base)
{
  std::string  s;

  base.collect_characters(s);

  return std::stoul(s,nullptr,10);
}


unsigned int
read_hex_literal(const mkf::Node&  base)
{
  std::string  s;

  base.collect_characters(s);

  return std::stoul(s,nullptr,16);
}


unsigned int
read_binary_literal(const mkf::Node&  base)
{
  unsigned int  i = 0;

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



unsigned int
expression::Operand::
read_integer_literal(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == "decimal_literal"){return read_decimal_literal(nd);}
      else if(nd == "hex_literal"    ){return read_hex_literal(nd);}
      else if(nd == "binary_literal" ){return read_binary_literal(nd);}


      cur.advance();
    }


  return 0;
}




