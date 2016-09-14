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




namespace{
std::vector<expression::Node>*
read_array(const mkf::Node&  src)
{
  auto  arr = new std::vector<expression::Node>;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          arr->emplace_back(nd);
        }


      cur.advance();
    }


  return arr;
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
          decl.data.expr = new expression::Node(nd);
        }

      else
        if(nd == "array_literal")
        {
          decl.data.arr = read_array(nd);

          decl.object_kind = ObjectKind::array;

            switch(decl.kind)
            {
              case(DeclarationKind::local):
                decl.index = prectx.function->local_object_size;

                prectx.function->local_object_size += decl.get_size();
                break;
              case(DeclarationKind::local_static):
                decl.index = prectx.globalscope.local_static_number++;
                break;
              default:;
            }
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
          auto  expr = new expression::Node(nd);

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

      else
        if(nd == "array_literal")
        {
          auto  carr = new std::vector<int>;

          auto  arr = read_array(nd);

          FoldContext  folctx(prectx.globalscope);

            for(auto&  expr: *arr)
            {
              auto  res = expr.fold(folctx);

                if(!res.folded)
                {
                  delete  arr;
                  delete carr;

                  printf("定数式を畳めませんんでした\n");

                  throw;
                }


              carr->emplace_back(res.value);

                switch(decl.kind)
                {
                  case(DeclarationKind::local):
                    decl.index = prectx.function->local_object_size;

                    prectx.function->local_object_size += decl.get_size();
                    break;
                  case(DeclarationKind::local_static):
                    decl.index = prectx.globalscope.local_static_number++;
                    break;
                  default:;
                }
            }


          delete arr;

          decl.data.carr = carr;

          decl.object_kind = ObjectKind::constant_array;
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




