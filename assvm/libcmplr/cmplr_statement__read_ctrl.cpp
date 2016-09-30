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
          read_return_statement(nd,prectx);
        }


      cur.advance();
    }
}


namespace{
Block*
read_block(Function*  fn, BlockKind  k, int  n, const mkf::Node&  src, PreContext&  prectx)
{
  expression::Node*  cond = nullptr;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          cond = new expression::Node(nd,prectx);
        }

      else
        if(nd == "block")
        {
          auto&  blk = fn->make_block(k,n,nd,prectx);

          blk.condition.reset(cond);

          return &blk;
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
  auto  fn = prectx.function;

  mkf::Cursor  cur(src);

  auto  brand = new BranchNode;

  brand->index_base = prectx.branchnode_count++;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "conditional_block")
        {
            if(brand->block_list.size())
            {
              auto&  blk = fn->make_block(BlockKind::else_,0,nd,prectx);

              brand->push(blk);
            }

          else
            {
              auto  blk = read_block(fn,BlockKind::if_,0,nd,prectx);

              brand->push(*blk);
            }
        }

      else
        if(nd == "else_block")
        {
          auto  blk = read_block(fn,BlockKind::else_,0,nd,prectx);

          brand->push(*blk);
        }


      cur.advance();
    }


  reset(brand);
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
          int  n = prectx.do_block_count++;

          auto&  blk = prectx.function->make_block(BlockKind::do_,n,nd,prectx);

          reset(&blk);
        }


      cur.advance();
    }
}


void
Statement::
read_return_statement(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  kind = StatementKind::return_;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "value")
        {
          data.val = new Value(nd,prectx);

          kind = StatementKind::return_;
        }


      cur.advance();
    }
}




