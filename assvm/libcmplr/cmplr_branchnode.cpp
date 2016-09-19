#include"cmplr_branchnode.hpp"
#include"cmplr_block.hpp"
#include"cmplr_function.hpp"
#include"cmplr_context.hpp"
#include<cstdlib>




void
BranchNode::
push(Block&  blk)
{
  blk.index = ((index_base<<16)|block_list.size());

  block_list.emplace_back(&blk);
}


void
BranchNode::
print(FILE*  f) const
{
    for(auto  blk: block_list)
    {
      blk->print(f);
    }
}


void
BranchNode::
compile(Context&  ctx) const
{
    for(auto  blk: block_list)
    {
      blk->compile(ctx);
    }


  auto  first = block_list[0];

  auto  name = first->function->signature.name.data();

  ctx.push("_FUNC%s_IF%04dxxxx_END:\n",name,first->index>>16);
}




