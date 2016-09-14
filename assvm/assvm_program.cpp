#include"assvm_program.hpp"
#include"assvm_block.hpp"
#include<cstdio>




namespace assvm{




Program::
Program(const mkf::Node&  src)
{
  auto  cur = src.make_cursor();

  size_t  offset = 0;

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

        if(nd == "block")
        {
          block_list.emplace_back(offset,nd);

          auto&  blk = block_list.back();

            if(blk.element_list.size())
            {
              auto&  e = blk.element_list.back();

              offset = e.frame.tail_offset;
            }
        }


      cur.advance();
    }


    for(auto&  blk: block_list)
    {
      blk.resolve(block_list);
    }


  binary.resize(offset);

    for(auto&  blk: block_list)
    {
      blk.write(binary.data());
    }


    for(auto&  blk: block_list)
    {
        if(blk.identifier == "main")
        {
          main_entry_point = blk.frame.head_offset;

          return;
        }
    }


  printf("メイン関数が見つかりません\n");

  throw 0;
}


void
Program::
print(FILE*  f) const
{
    for(auto&  blk: block_list)
    {
      blk.print(f);
    
      fprintf(f,"\n");
    }
}


}




