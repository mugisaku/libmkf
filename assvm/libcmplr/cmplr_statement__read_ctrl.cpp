#include"cmplr_statement.hpp"
#include"cmplr_block.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"




void
Statement::
read_control_statement(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "if_statement")
        {
          read_if_statement(nd,prectx);
        }

      else
        if(nd == "do_statement")
        {
          read_do_statement(nd,prectx);
        }

      else
        if(nd == "break_statement")
        {
          reset(Break());
        }

      else
        if(nd == "continue_statement")
        {
          reset(Continue());
        }

      else
        if(nd == "return_statement")
        {
          read_return_statement(nd);
        }


      cur.advance();
    }
}


namespace{
Block*
read_block(const char*  base, BlockKind  k, int  n, const mkf::Node&  src, PreContext&  prectx)
{
  expression::Node*  cond = nullptr;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          cond = new expression::Node;

          cond->read(nd);
        }

      else
        if(nd == "block")
        {
          return new Block(k,std::string(base),nd,prectx,n,cond);
        }


      cur.advance();
    }


  return nullptr;
}
}


void
Statement::
read_if_statement(const mkf::Node&  src, PreContext&  prectx)
{
  char  buf[80];

  auto  fn = prectx.function;

  snprintf(buf,sizeof(buf),"_FUNC_%s_IF%04d",fn->identifier.data(),fn->if_node_count++);

  int  block_count = 0;

  bool  else_flag = false;

  Block*  last = nullptr;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "conditional_block")
        {
            if(last)
            {
              auto  blk = read_block(buf,BlockKind::elseif,block_count++,nd,prectx);

              last->next_block.reset(blk);

              last = blk;
            }

          else
            {
              last = read_block(buf,BlockKind::if_,block_count++,nd,prectx);

              reset(last);
            }
        }

      else
        if(nd == "else_block")
        {
          auto  blk = read_block(buf,BlockKind::else_,block_count,nd,prectx);

          last->next_block.reset(blk);

          last = blk;

          else_flag = true;
        }


      cur.advance();
    }


    if(!else_flag)
    {
      last->next_block.reset(new Block(BlockKind::else_,std::string(buf),block_count));
    }
}


void
Statement::
read_do_statement(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "block")
        {
          char  buf[32];

          auto  fn = prectx.function;

          snprintf(buf,sizeof(buf),"_FUNC_%s_DO%04d",fn->identifier.data(),fn->do_block_count++);

          auto  blk = new Block(BlockKind::do_,std::string(buf),nd,prectx);

          reset(blk);
        }


      cur.advance();
    }
}


void
Statement::
read_return_statement(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

  kind = StatementKind::return_;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          data.expr = new expression::Node;

          data.expr->read(nd);

          kind = StatementKind::return_;
        }


      cur.advance();
    }
}




