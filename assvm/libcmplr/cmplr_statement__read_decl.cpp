#include"cmplr_statement.hpp"
#include"cmplr_block.hpp"
#include"cmplr_function.hpp"
#include"cmplr_globalscope.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"




void
Statement::
read_declaration(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "var_declaration")
        {
          auto  decl = prectx.append(read_var_declaration(nd,prectx));

          reset(decl);
        }

      else
        if(nd == "const_declaration")
        {
          auto  decl = prectx.append(read_const_declaration(nd,prectx));

          reset(decl);
        }

      else
        if(nd == "function_declaration")
        {
//          read_function_declaration(nd);
        }

      else
        if(nd == "enum_declaration")
        {
          read_enum_declaration(nd);
        }


      cur.advance();
    }
}




Declaration
Statement::
read_var_declaration(const mkf::Node&  src, PreContext&  prectx)
{
  Declaration  decl;

  mkf::Cursor  cur(src);

  decl.kind = prectx.function? DeclarationKind::local
                             : DeclarationKind::global;

  decl.object_kind = ObjectKind::value;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(decl.identifier);
        }

      else
        if(nd == "expression")
        {
          decl.data.expr = new expression::Node(nd,prectx);
        }

      else
        if(nd == "static")
        {
          decl.kind = DeclarationKind::local_static;
        }


      cur.advance();
    }


  return std::move(decl);
}




Declaration
Statement::
read_const_declaration(const mkf::Node&  src, PreContext&  prectx)
{
  Declaration  decl;

  mkf::Cursor  cur(src);

  decl.kind = prectx.function? DeclarationKind::local_static
                             : DeclarationKind::global;

  decl.object_kind = ObjectKind::constant;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(decl.identifier);
        }

      else
        if(nd == "expression")
        {
          auto  expr = new expression::Node(nd,prectx);

          FoldContext  folctx(prectx.globalscope);

          auto  res = expr->fold(folctx);

          delete expr;

            if(!res.folded)
            {
              printf("定数式を畳めませんんでした\n");

              throw;
            }


          decl.data.i = res.value;
        }


      cur.advance();
    }


  return std::move(decl);
}




namespace{


void
read_enumerator(const mkf::Node&  base, int  v)
{
  mkf::Cursor  cur(base);

  std::string  id;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(id);
        }

      else
        if(nd == "expression")
        {
          auto  tree = new expression::Node;

//          tree->read(nd);
        }


      cur.advance();
    }
}
}


void
Statement::
read_enum_declaration(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

  int  v = 0;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "enumerator")
        {
//          v = parent->append_enumerator(read_enumerator(nd,v));
        }


      cur.advance();
    }
}




