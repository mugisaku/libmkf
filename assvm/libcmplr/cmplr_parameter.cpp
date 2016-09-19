#include"cmplr_parameter.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_context.hpp"




Parameter::
Parameter()
{
}


Parameter::
Parameter(const mkf::Node&  src)
{
  read(src);
}




Type
Parameter::
compile(const Declaration&  decl, Context&  ctx) const
{
  ctx.push("  pshui8 %d;\n",decl.index);
  ctx.push("  arg;\n");
}


void
Parameter::
compile_definition(const Declaration&  decl, Context&  ctx) const
{
}




void
Parameter::
print(FILE*  f) const
{
  type.print(f);

  fprintf(f,"  %s",name.data());
}


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





