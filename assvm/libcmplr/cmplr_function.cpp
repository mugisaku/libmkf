#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"expression_operand.hpp"




Function::
Function():
local_object_size(0)
{
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
  ctx.push("  //******************//\n");
  ctx.push("  //関数の呼び出し始め//\n");
  ctx.push("  //******************//\n");

  ctx.push("  psh16u %s;\n",name.data());
  ctx.push("  cal      ;\n");
  ctx.push("  pshsp    ;\n");
  ctx.push("  psh8u %3d;\n",4*parameter_list.size());
  ctx.push("  add      ;\n");
  ctx.push("  updsp    ;\n");
  ctx.push("  pshtm    ;\n");

  ctx.push("  //********************//\n");
  ctx.push("  //関数の呼び出し終わり//\n");
  ctx.push("  //********************//\n");


//  return Type(TypeKind::function,signature.type.duplicate());
  return Type();
}


void
Function::
compile_definition(Context&  ctx) const
{
  auto  f = ctx.const_function       ;
            ctx.const_function = this;

  ctx.block_stack.clear();

  ctx.push("%s:\n",name.data());

    if(local_object_size)
    {
      ctx.push("  pshsp        ;//****************************//\n");
      ctx.push("  psh16u %6d;//                            //\n",local_object_size);
      ctx.push("  sub          ;//ローカルオブジェクト領域確保//\n");
      ctx.push("  updsp        ;//****************************//\n");
    }


  block->compile(ctx);

  ctx.push("  ret;\n");

  ctx.entry_list.emplace_back(Entry{this,std::move(ctx.current_content)});

  ctx.current_content.clear();


  ctx.const_function = f;
}


void
Function::
print(FILE*  f) const
{
  fprintf(f,"function  %s: ",name.data());

  type.print(f);

  fprintf(f,"(");

    if(parameter_list.size())
    {
      auto  it = parameter_list.cbegin();

        for(;;)
        {
          auto&  p = *it++;

          p.print(f);

            if(it == parameter_list.cend())
            {
              break;
            }


          fprintf(f,",");
        }
    }


  fprintf(f,")\n");

  fprintf(f,"//parameters\n");

    for(auto&  decl: block->declaration_list)
    {
        if(decl.get_value().kind == ValueKind::parameter)
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
           (decl.get_value().kind != ValueKind::parameter))
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

        if(nd == "type")
        {
          type.read(nd);
        }

      else
        if(nd == "identifier")
        {
          nd.collect_characters(name);
        }

      else
        if(nd == "parameter")
        {
          parameter_list.emplace_back(nd);
        }

      else
        if(nd == "block")
        {
          auto  blk = new Block(BlockKind::plain,nd,prectx);

          blk->function = this;

          auto&  prmls = parameter_list;

          size_t  offset = 0;

          offset += 4;//
          offset += 4;//リターンアドレス
          offset += 4;//ベースアドレス

          auto  it = prmls.crbegin();

            while(it != prmls.crend())
            {
              auto&  prm = *it++;

              blk->declaration_list.emplace_back(prm,offset);

              offset += 4;
            }


          block.reset(blk);
        }


      cur.advance();
    }


  local_object_size +=  3;
  local_object_size &= ~3;

  prectx.function = fn;
}




