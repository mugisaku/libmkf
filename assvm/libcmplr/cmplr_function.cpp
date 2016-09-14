#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"expression_operand.hpp"




Function::
Function():
local_object_size(0),
nolabel_block_count(0),
do_block_count(0),
switch_block_count(0),
if_node_count(0)
{
}


Function::
Function(const mkf::Node&  src, PreContext&  prectx):
local_object_size(0),
nolabel_block_count(0),
do_block_count(0),
switch_block_count(0),
if_node_count(0)
{
  read_declaration(src,prectx);
}




void
Function::
compile_definition(Context&  ctx)
{
  auto  f = ctx.function       ;
            ctx.function = this;

  ctx.block_stack.clear();

  ctx.push("%s:\n",identifier.data());

    if(local_object_size)
    {
      ctx.push("  pshsp;        //////\n");
      ctx.push("  pshui8 %6d;//\n",local_object_size);
      ctx.push("  sub;          //ローカルオブジェクト領域確保\n");
      ctx.push("  updsp;        //////\n");
    }


  statement.compile(ctx);

  ctx.entry_list.emplace_back(Entry{this,std::move(ctx.current_content)});

  ctx.current_content.clear();

  ctx.function = f;
}


void
Function::
print(FILE*  f) const
{
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

  statement.print(f);

  fprintf(f,"\n");
}




void
Function::
read_declaration(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(identifier);
        }

      else
        if(nd == "function_definition")
        {
          read_definition(nd,prectx);
        }


      cur.advance();
    }
}


void
Function::
read_definition(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  auto  fn = prectx.function       ;
             prectx.function = this;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "parameter")
        {
          read_parameter(nd);
        }

      else
        if(nd == "block")
        {
          int  local_object_count = parameter_list.size()-1;

            for(auto  it  = parameter_list.rbegin();
                      it != parameter_list.rend()  ;
                                               ++it)
            {
              it->index = local_object_count--;
            }


          statement = Statement(new Block(BlockKind::function,std::string(identifier),nd,prectx));
        }


      cur.advance();
    }


  prectx.function = fn;
}


void
Function::
read_parameter(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          std::string  s;

          nd.collect_characters(s);

          parameter_list.emplace_back(DeclarationKind::parameter,std::move(s));

          parameter_list.back().object_kind = ObjectKind::value;
        }


      cur.advance();
    }
}





