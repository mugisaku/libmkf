#include"assvm_block.hpp"
#include"assvm_program.hpp"
#include"assvm_instructionsource.hpp"
#include"assvm_data.hpp"
#include<cstdio>
#include<cstdlib>




namespace assvm{


Block::
Block(size_t  offset, const mkf::Node&  src)
{
  frame.head_offset = offset;


  Element*  last = nullptr;

  auto  cur = src.make_cursor();

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

        if(nd == "identifier")
        {
          nd.collect_characters(identifier);
        }

      else
        if(nd == "instruction")
        {
          element_list.emplace_back(offset,new InstructionSource(nd));

          last = &element_list.back();
        }

      else
        if(nd == "data")
        {
          element_list.emplace_back(offset,new Data(nd));

          last = &element_list.back();
        }


        if(last)
        {
          offset = last->frame.tail_offset;
        }


      cur.advance();
    }


    if(element_list.size())
    {
      frame.head_offset = element_list.front().frame.head_offset;
    }


  frame.tail_offset = offset;
}




void
Block::
resolve(std::vector<Block>&  ls)
{
    for(auto&  e: element_list)
    {
        if(e.kind == ElementKind::instruction)
        {
          e.content.src->resolve(ls);
        }

      else
        if(e.kind == ElementKind::data)
        {
          e.content.dat->resolve(ls);
        }
    }
}


void
Block::
write(uint8_t*  base) const
{
    for(auto&  e: element_list)
    {
      e.write(base);
    }
}


void
Block::
print(FILE*  f) const
{
  fprintf(f,"%s:\n",identifier.data());

    for(auto&  e: element_list)
    {
      e.print(f);

      fprintf(f,";\n");
    }
}




}




