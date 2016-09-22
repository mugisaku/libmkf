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
  ctx.push("  pshbp        ;//*************************//\n");
  ctx.push_psh(decl.offset,"//実引数%sのアドレス読み出し//\n",name.data());
  ctx.push("  sub          ;//*************************//\n");

  return type.make_reference();
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





