#include"cmplr_block.hpp"
#include<cstdlib>




Block::
Block():
kind(BlockKind::plain)
{
}


Block::
Block(BlockKind  k, std::string&&  id, int  i):
kind(k),
condition(nullptr),
index(i),
label(std::move(id))
{
}


Block::
Block(BlockKind  k, std::string&&  id, const mkf::Node&  src, PreContext&  prectx, int  i, expression::Node*  cond):
kind(k),
condition(cond),
index(i),
label(std::move(id))
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
      case(BlockKind::elseif):
        fprintf(f,"else if(");

        condition->print(f);

        fprintf(f,")");
        break;
      case(BlockKind::else_):
        fprintf(f,"else");
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

    if(next_block)
    {
      next_block->print(f);
    }
}


void
Block::
compile(Context&  ctx)
{
  const Block*  ctrlblk = nullptr;

    switch(kind)
    {
      case(BlockKind ::do_):
        ctx.push("%s_BEGIN:\n",label.data());
        ctrlblk = ctx.change_control_block(this);
        break;
      case(BlockKind ::if_):
        ctx.push("%s_%04d_BEGIN:\n",label.data(),index);
        condition->compile(ctx);
        ctx.push("  pshui16 %s_%04d_BEGIN;\n",label.data(),index+1);
        ctx.push("  brz;\n",label.data());
        break;
      case(BlockKind ::elseif):
        ctx.push("%s_%04d_BEGIN:\n",label.data(),index);
        condition->compile(ctx);
        ctx.push("  pshui16 %s_%04d_BEGIN;\n",label.data(),index+1);
        ctx.push("  brz;\n",label.data());
        break;
      case(BlockKind ::else_):
        ctx.push("%s_%04d_BEGIN:\n",label.data(),index);
        break;
    }


    for(auto&  stmt: statement_list)
    {
      stmt.compile(ctx);
    }


    switch(kind)
    {
      case(BlockKind ::do_):
        ctx.push("  pshui16  %s_BEGIN;\n",label.data());
        ctx.push("  updpc;\n");
        break;
      case(BlockKind ::if_):
      case(BlockKind ::elseif):
        ctx.push("  pshui16  %s_END;\n",label.data());
        ctx.push("  updpc;\n");
        break;
      case(BlockKind ::else_):
        break;
    }


    switch(kind)
    {
      case(BlockKind ::do_):
        ctx.change_control_block(ctrlblk);
        break;
    }


    if(next_block)
    {
      next_block->compile(ctx);
    }

  else
    {
      ctx.push("%s_END:\n",label.data());
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




