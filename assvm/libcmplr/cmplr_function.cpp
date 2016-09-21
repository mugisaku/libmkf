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
      ctx.push("  psh16u %6d;//                            //\n",local_object_size);
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

  fprintf(f,"//parameters\n");

    for(auto&  decl: block->declaration_list)
    {
        if(decl.kind == DeclarationKind::parameter)
        {
          decl.print(f);

          fprintf(f,"(offset %6zu);\n",decl.offset);
        }
    }


  fprintf(f,"\n");

  fprintf(f,"//local_variables\n");

    for(auto&  decl: block->declaration_list)
    {
        if((decl.storage_kind == StorageKind::local) &&
           (decl.kind         == DeclarationKind::variable))
        {
          decl.print(f);

          fprintf(f,"(offset %6zu);\n",decl.offset);
        }
    }


  fprintf(f,"\n");

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

  prectx.do_block_count      = 0;
  prectx.branchnode_count    = 0;

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

          size_t  offset = 0;

          offset += 4;//リターンアドレス
          offset += 4;//スタックアドレス
          offset += 4;//ベースアドレス

          auto  it = prmls.crbegin();

            while(it != prmls.crend())
            {
              auto&  prm = *it++;

              auto&  type = prm.type;

                switch(type.get_object_alignment_size())
                {
              case(0):
              case(1):
                  break;
              case(2):
                  offset +=  1;
                  offset &= ~1;
                  break;
              case(4):
                  offset +=  3;
                  offset &= ~3;
                  break;
                }


              blk->declaration_list.emplace_back(prm,offset);

              offset += type.get_object_size();
            }


          block.reset(blk);
        }


      cur.advance();
    }


  prectx.function = fn;
}




