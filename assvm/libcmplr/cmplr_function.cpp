#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"expression_operand.hpp"




Function::
Function():
local_object_size(0)
{
}


Function::
Function(const mkf::Node&  src, PreContext&  prectx):
local_object_size(0)
{
  read(src,prectx);
}




Block&
Function::
make_block(BlockKind  k, int  count, const mkf::Node&  src, PreContext&  prectx)
{
  block_list.emplace_back(k,src,prectx);

  auto&  blk = block_list.back();

  blk.function = this;

  blk.index = count;

  return blk;
}


Type
Function::
compile(Context&  ctx) const
{
  ctx.push("  pshui16 %s;\n",signature.name.data());

  return Type(TypeKind::function);
}


void
Function::
compile_definition(Context&  ctx) const
{
  auto  f = ctx.function       ;
            ctx.function = this;

  ctx.block_stack.clear();

  ctx.push("%s:\n",signature.name.data());

    if(local_object_size)
    {
      ctx.push("  pshsp       ;//****************************//\n");
      ctx.push("  psh8u %6d;//                            //\n",local_object_size);
      ctx.push("  sub         ;//ローカルオブジェクト領域確保//\n");
      ctx.push("  updsp       ;//****************************//\n");
    }


  block->compile(ctx);

  ctx.entry_list.emplace_back(Entry{this,std::move(ctx.current_content)});

  ctx.current_content.clear();

  ctx.function = f;
}


void
Function::
print(FILE*  f) const
{
  signature.print(f);

  block->print(f);

  fprintf(f,"\n");
}




void
Function::
read(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  auto  fn = prectx.function       ;
             prectx.function = this;

  prectx.do_block_count   = 0;
  prectx.branchnode_count = 0;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "signature")
        {
          signature.read(nd);
        }

      else
        if(nd == "block")
        {
          auto  blk = new Block(BlockKind::plain,nd,prectx);

          blk->function = this;

          auto&  prmls = signature.parameter_list;

          int  local_object_count = prmls.size()-1;

            for(auto  it  = prmls.crbegin();
                      it != prmls.crend()  ;
                                      ++it)
            {
              auto&  prm = *it++;

              blk->declaration_list.emplace_back(prm,local_object_count--);
            }


          block.reset(blk);
        }


      cur.advance();
    }


  prectx.function = fn;
}




