#include"cmplr_parameter.hpp"




void
Parameter::
read(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "type")
        {
          type.read(nd);
        }

      else
        if(nd == "identifier")
        {
          nd.collect_characters(name);
        }


      cur.advance();
    }
}



void
Parameter::
print(FILE*  f) const
{
  type.print(f);

  fprintf(f,"  %s",name.data());
}





