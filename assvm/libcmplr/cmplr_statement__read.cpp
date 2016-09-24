#include"cmplr_statement.hpp"
#include"cmplr_block.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_initializer.hpp"




void
Statement::
read(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "declaration")
        {
          reset(prectx.append(Declaration(nd,prectx)));
        }

      else
        if(nd == "control_statement")
        {
          read_control_statement(nd,prectx);
        }

      else
        if(nd == "print_statement")
        {
          read_print_statement(nd,prectx);
        }

      else
        if(nd == "halt")
        {
          reset(Halt());
        }

      else
        if(nd == "block")
        {
          auto&  blk = prectx.function->make_block(BlockKind::plain,0,nd,prectx);

          reset(&blk);
        }

      else
        if(nd == "expression")
        {
          reset(new expression::Node(nd,prectx));
        }


      cur.advance();
    }
}


void
Statement::
read_print_statement(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  Initializer*  init = nullptr;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "initializer")
        {
          init = new Initializer(nd,prectx);
        }


      cur.advance();
    }


  reset(Print(init));
}




