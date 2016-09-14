#include"assvm_data.hpp"
#include"assvm_element.hpp"
#include"assvm_block.hpp"
#include"mkf__read.hpp"
#include<cstdio>
#include<cstdlib>




namespace assvm{


namespace{
int
read_array_size(const mkf::Node&  src)
{
  int  i = 0;

  auto  cur = src.make_cursor();

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

        if(nd == "integer")
        {
          i = mkf::read_decimal_integer(nd);
        }


      cur.advance();
    }


  return i;
}


void
read_array(std::vector<Operand>&  buf, const mkf::Node&  src)
{
  int  i = 0;

  auto  cur = src.make_cursor();

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

        if(nd == "operand")
        {
            if(i < buf.size())
            {
              buf[i].read(nd);
            }

          else
            {
              buf.emplace_back(nd);
            }


          ++i;
        }


      cur.advance();
    }
}
}


Data::
Data(const mkf::Node&  src):
kind(DataKind::i8)
{
  auto  cur = src.make_cursor();

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

        if(nd == "array_size")
        {
          operand_list.resize(read_array_size(nd));
        }

      else
        if(nd == "array")
        {
          read_array(operand_list,nd);
        }

      else
        if(nd == "i8")
        {
          kind = DataKind::i8;
        }

      else
        if(nd == "i16")
        {
          kind = DataKind::i16;
        }

      else
        if(nd == "i32")
        {
          kind = DataKind::i32;
        }


      cur.advance();
    }
}


void
Data::
resolve(std::vector<Block>&  ls)
{
    for(auto&  op: operand_list)
    {
        if(op.identifier.size())
        {
          bool  flag = false;

            for(auto&  blk: ls)
            {
                if(blk.identifier == op.identifier)
                {
                  op.value = blk.frame.head_offset;

                  flag = true;

                  break;
                }
            }


            if(!flag)
            {
              printf("識別子%sが見つかりません",op.identifier.data());

              throw op;
            }
        }
    }
}


void
Data::
write(uint8_t*  base, size_t  offset) const
{
  auto  p = base+offset;

  auto  p16 = reinterpret_cast<uint16_t*>(p);
  auto  p32 = reinterpret_cast<uint32_t*>(p);

    switch(kind)
    {
      case(DataKind::i8):
          for(auto&  op: operand_list)
          {
            *p = (op.value);
          }
        break;
      case(DataKind::i16):
          if(offset&1)
          {
            printf("2バイト境界ではありません\n");

            throw;
          }


          for(auto&  op: operand_list)
          {
            *p16++ = op.value;
          }
        break;
      case(DataKind::i32):
          if(offset&3)
          {
            printf("4バイト境界ではありません\n");

            throw;
          }


          for(auto&  op: operand_list)
          {
            *p32++ = op.value;
          }
        break;
    }
}


void
Data::
fix(ObjectFrame&  of) const
{
  size_t  size = operand_list.size();

    switch(kind)
    {
      case(DataKind::i8):
        break;
      case(DataKind::i16):
        of.head_offset += 1;
        of.head_offset &= 0xFFFFFFFE;
        size *= 2;
        break;
      case(DataKind::i32):
        of.head_offset += 3;
        of.head_offset &= 0xFFFFFFFC;
        size *= 4;
        break;
    }


  of.tail_offset = of.head_offset+size;
}


void
Data::
print(FILE*  f) const
{
  fprintf(f,"data %s{",(kind == DataKind::i8)?   "i8":
                       (kind == DataKind::i16)? "i16":
                                                "i32");

    for(auto&  op: operand_list)
    {
      op.print(f);

      fprintf(f,",");
    }


  fprintf(f,"}");
}




}




