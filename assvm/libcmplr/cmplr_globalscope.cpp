#include"cmplr_globalscope.hpp"
#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"cmplr_context.hpp"
#include"expression_node.hpp"




void
GlobalScope::
print(FILE*  f)
{
    for(auto&  decl: declaration_list)
    {
      decl.print(f);

      fprintf(f,";\n\n\n");
    }
}


std::string
GlobalScope::
compile()
{
  Context  ctx(*this);

    for(auto&  decl: declaration_list)
    {
      decl.compile_definition(ctx);
    }


  std::string  s = ctx.definition_content;

    for(auto&  ent: ctx.entry_list) 
    {
      s += ent.content.data();
    }


  return std::move(s);
}


void
GlobalScope::
read(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

  PreContext  prectx(*this);

  prectx.function = nullptr;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "declaration")
        {
          declaration_list.emplace_back(nd,prectx);
        }


      cur.advance();
    }
}




