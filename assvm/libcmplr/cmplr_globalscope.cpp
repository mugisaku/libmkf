#include"cmplr_globalscope.hpp"
#include"cmplr_function.hpp"
#include"cmplr_context.hpp"




void
GlobalScope::
print(FILE*  f) const
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
  prectx.block    = nullptr;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "function_declaration")
        {
          auto  fn = new Function(nd,prectx);

          declaration_list.emplace_back(fn);
        }

      else
        if(nd == "var_declaration")
        {
          declaration_list.emplace_back(Statement::read_var_declaration(nd,prectx));
        }

      else
        if(nd == "const_declaration")
        {
          declaration_list.emplace_back(Statement::read_const_declaration(nd,prectx));
        }


      cur.advance();
    }
}




