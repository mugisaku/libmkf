#include"cmplr_block.hpp"
#include"cmplr_function.hpp"
#include<cstdlib>




Block::
Block():
kind(BlockKind::plain)
{
}


Block::
Block(BlockKind  k):
kind(k)
{
}


Block::
Block(BlockKind  k, const mkf::Node&  src, PreContext&  prectx, expression::Node*  cond):
kind(k),
condition(cond)
{
  read(src,prectx);
}




void
Block::
print(FILE*  f) const
{
    switch(kind)
    {
      case(BlockKind::plain):
        break;
      case(BlockKind::do_):
        fprintf(f,"do");
        break;
      case(BlockKind::if_):
        fprintf(f,"if(");

        condition->print(f);

        fprintf(f,")");
        break;
      case(BlockKind::else_):
        fprintf(f,"else");

          if(condition)
          {
            fprintf(f," if(");

            condition->print(f);

            fprintf(f,")");
          }
        break;
    }


  fprintf(f,"{\n");

    for(auto&  stmt: statement_list)
    {
        if(stmt.kind != StatementKind::null)
        {
          stmt.print(f);

          fprintf(f,";\n");
        }
    }


  fprintf(f,"}\n\n\n");
}


void
Block::
compile_push_do_begin(Context&  ctx) const
{
  ctx.push("  pshui16 _FUNC%s_DO%04d_BEGIN;\n",function->identifier.data(),index);
}


void
Block::
compile_push_do_end(Context&  ctx) const
{
  ctx.push("  pshui16 _FUNC%s_DO%04d_END;\n",function->identifier.data(),index);
}


void
Block::
compile(Context&  ctx) const
{
  const Block*  ctrlblk = nullptr;

  ctx.block_stack.emplace_back(this);

    switch(kind)
    {
      case(BlockKind::do_):
        ctx.push("_FUNC%s_DO%04d_BEGIN:\n",function->identifier.data(),index>>16);
        ctrlblk = ctx.change_control_block(this);
        break;
      case(BlockKind::if_):
        ctx.push("_FUNC%s_IF%04dxxxx:\n",function->identifier.data(),index>>16);
        condition->compile(ctx);
        ctx.push("  pshui16 _FUNC%s_IF%08d_END;\n",function->identifier.data(),index);
        ctx.push("  brz;\n");
        break;
      case(BlockKind::else_):
          if(condition)
          {
            condition->compile(ctx);

            ctx.push("  pshui16 _FUNC%s_IF%08d;\n",function->identifier.data(),index);
            ctx.push("  brz;\n");
          }
        break;
    }


  compile_basic(ctx);

    switch(kind)
    {
      case(BlockKind::do_):
        ctx.push("  pshui16  _FUNC%s_DO%04d_BEGIN;\n",function->identifier.data(),index);
        ctx.push("  updpc;\n");
        ctx.push("_FUNC%s_DO%04d_END:\n",function->identifier.data(),index);

        ctx.change_control_block(ctrlblk);
        break;
      case(BlockKind::if_):
      case(BlockKind::else_):
        ctx.push("  pshui16  _FUNC%s_IF%04dxxxx_END;\n",function->identifier.data(),index>>16);
        ctx.push("  updpc;\n");
        ctx.push("_FUNC%s_IF%08d_END:\n",function->identifier.data(),index);
        break;
    }


  ctx.block_stack.pop_back();
}


void
Block::
compile_basic(Context&  ctx) const
{
    for(auto&  stmt: statement_list)
    {
      stmt.compile(ctx);
    }
}


void
Block::
read(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  auto  block = prectx.block       ;
                prectx.block = this;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "statement")
        {
          statement_list.emplace_back(nd,prectx);
        }


      cur.advance();
    }


  prectx.block = block;
}




