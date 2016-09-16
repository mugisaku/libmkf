#include"cmplr_statement.hpp"
#include"cmplr_block.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"




void
Statement::
read(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "declaration_statement")
        {
          read_declaration(nd,prectx);
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
          auto  expr = new expression::Node(nd,prectx);

          reset(expr);
        }


      cur.advance();
    }
}


void
Statement::
read_print_statement(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  expression::Node*  expr = nullptr;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          expr = new expression::Node(nd,prectx);
        }


      cur.advance();
    }


  reset(Print(expr));
}




