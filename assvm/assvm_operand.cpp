#include"assvm_operand.hpp"
#include"assvm_element.hpp"
#include"assvm_operand.hpp"
#include"mkf__read.hpp"
#include<cstdio>
#include<cstdlib>




namespace assvm{


Operand::
Operand()
{
}


Operand::
Operand(const mkf::Node&  src)
{
  read(src);
}




void
Operand::
read(const mkf::Node&  src)
{
  value = 0;

  identifier.clear();

  auto  cur = src.make_cursor();

  bool  minus_flag = false;

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

        if(nd == "integer")
        {
          auto  v = mkf::read_decimal_integer(nd);

          value = minus_flag? -v:v;
        }

      else
        if(nd == "-")
        {
          minus_flag = true;
        }

      else
        if(nd == "identifier")
        {
          nd.collect_characters(identifier);
        }


      cur.advance();
    }
}


void
Operand::
print(FILE*  f) const
{
  fprintf(f,"%d",value);

    if(identifier.size())
    {
      fprintf(f,"/*%s*/",identifier.data());
    }
}




}




