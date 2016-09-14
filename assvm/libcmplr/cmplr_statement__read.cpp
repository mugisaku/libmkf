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
          read_print_statement(nd);
        }

      else
        if(nd == "halt")
        {
          reset(Halt());
        }

      else
        if(nd == "block")
        {
          char  buf[256];

          auto  fn = prectx.function;

          snprintf(buf,sizeof(buf),"FN_%s_%04d",fn->identifier.data(),fn->nolabel_block_count++);

          reset(new Block(BlockKind::plain,std::string(buf),nd,prectx));
        }

      else
        if(nd == "expression")
        {
          auto  expr = new expression::Node;

          expr->read(nd);

          reset(expr);
        }


      cur.advance();
    }
}


void
Statement::
read_print_statement(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

  expression::Node*  expr = nullptr;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          expr = new expression::Node;

          expr->read(nd);
        }


      cur.advance();
    }


  reset(Print(expr));
}




