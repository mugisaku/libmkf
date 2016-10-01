#include"cmplr_statement.hpp"
#include"cmplr_block.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_context.hpp"




Statement::
Statement():
kind(StatementKind::null)
{
}


Statement::
Statement(const Block*  blk):
kind(StatementKind::null)
{
  reset(blk);
}


Statement::
Statement(const mkf::Node&  src, PreContext&  prectx):
kind(StatementKind::null)
{
  read(src,prectx);
}


Statement::
Statement(const Statement&  rhs):
kind(StatementKind::null)
{
  *this = rhs;
}


Statement::
Statement(Statement&&  rhs) noexcept:
kind(StatementKind::null)
{
  *this = std::move(rhs);
}


Statement::
~Statement()
{
  clear();
}




Statement&
Statement::
operator=(const Statement&  rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(StatementKind::null):
  case(StatementKind::halt):
  case(StatementKind::break_):
  case(StatementKind::continue_):
  case(StatementKind::declaration):
  case(StatementKind::block):
    data = rhs.data;
    break;
  case(StatementKind::branchnode):
    data.brand = new BranchNode(*rhs.data.brand);
    break;
  case(StatementKind::return_):
  case(StatementKind::print):
      data.val = new Value(*rhs.data.val);
      break;
  case(StatementKind::expression):
      data.expr = new expression::Node(*rhs.data.expr);
      break;
  default:
      report;
    }


  return *this;
}


Statement&
Statement::
operator=(Statement&&  rhs)
{
  clear();

  kind = rhs.kind                      ;
         rhs.kind = StatementKind::null;

  data = rhs.data;

  return *this;
}


Statement::
operator bool() const
{
  return(kind != StatementKind::null);
}


void
Statement::
clear()
{
    switch(kind)
    {
      case(StatementKind::null):
      case(StatementKind::halt):
      case(StatementKind::break_):
      case(StatementKind::continue_):
      case(StatementKind::declaration):
      case(StatementKind::block):
        break;
      case(StatementKind::branchnode):
        delete data.brand;
        break;
      case(StatementKind::return_):
      case(StatementKind::print):
        delete data.val;
        break;
      case(StatementKind::expression):
        delete data.expr;
        break;
      default:
        report;
    }


  data.ptr = nullptr;

  kind = StatementKind::null;
}


void
Statement::
reset(expression::Node*  expr)
{
  clear();

  kind = StatementKind::expression;

  data.expr = expr;
}


void
Statement::
reset(Return  ret)
{
  clear();

  kind = StatementKind::return_;

  data.val = ret.v;
}


void
Statement::
reset(BranchNode*  brand)
{
  clear();

  kind = StatementKind::branchnode;

  data.brand = brand;
}


void
Statement::
reset(const Block*  blk)
{
  clear();

  kind = StatementKind::block;

  data.blk = blk;
}


void
Statement::
reset(const Declaration*  decl)
{
  clear();

  kind = StatementKind::declaration;

  data.decl = decl;
}


void
Statement::
reset(const Break&  brk)
{
  clear();

  kind = StatementKind::break_;
}


void
Statement::
reset(const Continue&  con)
{
  clear();

  kind = StatementKind::continue_;
}


void
Statement::
reset(const Print&  prn)
{
  clear();

  kind = StatementKind::print;

  data.val = prn.v;
}


void
Statement::
reset(const Halt&  halt)
{
  clear();

  kind = StatementKind::halt;
}


void
Statement::
compile(Context&  ctx) const
{
    switch(kind)
    {
      case(StatementKind::null):
        break;
      case(StatementKind::block):
        data.blk->compile(ctx);
        break;
      case(StatementKind::branchnode):
        data.brand->compile(ctx);
        break;
      case(StatementKind::declaration):
        data.decl->compile_definition(ctx);
        break;
      case(StatementKind::print):
/*
          if(data.expr)
          {
            auto  t = data.expr->compile(ctx);

              if(t == TypeKind::reference)
              {
                t.compile_dereference(ctx);
              }
          }


        ctx.push("  prn;\n");

          if(data.expr)
          {
            ctx.push("  pop;\n");
          }
*/
        break;
      case(StatementKind::halt):
        ctx.push("  hlt;\n");
        break;
      case(StatementKind::break_):
          if(ctx.control_block)
          {
            ctx.control_block->compile_push_do_end(ctx);
            ctx.push("  updpc;//break\n");
          }

        else
          {
            printf("breakするブロックがありません\n");

            throw;
          }
        break;
      case(StatementKind::continue_):
          if(ctx.control_block)
          {
            ctx.control_block->compile_push_do_begin(ctx);
            ctx.push("  updpc;//continue\n");
          }

        else
          {
            printf("continueするブロックがありません\n");

            throw;
          }
        break;
        break;
      case(StatementKind::return_):
/*
          if(data.expr)
          {
            auto  t = data.expr->compile(ctx);

              if(t == TypeKind::reference)
              {
                t.compile_dereference(ctx);
              }


            ctx.push("  ret;\n");
          }
*/
        break;
      case(StatementKind::expression):
        data.expr->compile(ctx);

        ctx.push("  pop;\n");
        break;
      default:;
    }
}


void
Statement::
print(FILE*  f) const
{
    switch(kind)
    {
      case(StatementKind::null):
        fprintf(f,"(null)");
        break;
      case(StatementKind::block):
        data.blk->print(f);
        break;
      case(StatementKind::branchnode):
        data.brand->print(f);
        break;
      case(StatementKind::declaration):
        data.decl->print(f);
        break;
      case(StatementKind::halt):
        fprintf(f,"halt");
        break;
      case(StatementKind::print):
        fprintf(f,"print ");

          if(data.val)
          {
            data.val->print(f);
          }
        break;
      case(StatementKind::break_):
        fprintf(f,"break");
        break;
      case(StatementKind::continue_):
        fprintf(f,"continue");
        break;
      case(StatementKind::return_):
        fprintf(f,"return ");

          if(data.val)
          {
            data.val->print(f);
          }
        break;
      case(StatementKind::expression):
        data.expr->print(f);
        break;
      default:
        report;
    }
}




