#include"assvm_instructionsource.hpp"
#include"assvm_element.hpp"
#include"assvm_block.hpp"
#include"mkf__read.hpp"
#include<cstdio>
#include<cstdlib>




namespace assvm{


namespace{
Opecode
read_opecode(const mkf::Node&  src)
{
  auto  cur = src.make_cursor();

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

           if(nd == "nop"){return Opecode::nop;}
      else if(nd == "add"){return Opecode::add;}
      else if(nd == "sub"){return Opecode::sub;}
      else if(nd == "mul"){return Opecode::mul;}
      else if(nd == "div"){return Opecode::div;}
      else if(nd == "rem"){return Opecode::rem;}
      else if(nd == "shl"){return Opecode::shl;}
      else if(nd == "shr"){return Opecode::shr;}
      else if(nd == "bor"){return Opecode::bor;}
      else if(nd == "band"){return Opecode::band;}
      else if(nd == "bxor"){return Opecode::bxor;}
      else if(nd == "bnot"){return Opecode::bnot;}
      else if(nd == "bnot"){return Opecode::bnot;}
      else if(nd == "lor"){return Opecode::lor;}
      else if(nd == "land"){return Opecode::land;}
      else if(nd == "lnot"){return Opecode::lnot;}
      else if(nd == "neg"){return Opecode::neg;}
      else if(nd == "ld8"){return Opecode::ld8;}
      else if(nd == "ld8u"){return Opecode::ld8u;}
      else if(nd == "ld16"){return Opecode::ld16;}
      else if(nd == "ld16u"){return Opecode::ld16u;}
      else if(nd == "ld32"){return Opecode::ld32;}
      else if(nd == "st8"){return Opecode::st8;}
      else if(nd == "st16"){return Opecode::st16;}
      else if(nd == "st32"){return Opecode::st32;}
      else if(nd == "sx8"){return Opecode::sx8;}
      else if(nd == "sx16"){return Opecode::sx16;}
      else if(nd == "tr8"){return Opecode::tr8;}
      else if(nd == "tr16"){return Opecode::tr16;}
      else if(nd == "eq"){return Opecode::eq;}
      else if(nd == "neq"){return Opecode::neq;}
      else if(nd == "lt"){return Opecode::lt;}
      else if(nd == "lteq"){return Opecode::lteq;}
      else if(nd == "gt"){return Opecode::gt;}
      else if(nd == "gteq"){return Opecode::gteq;}
      else if(nd == "hlt"){return Opecode::hlt;}
      else if(nd == "brz"){return Opecode::brz;}
      else if(nd == "brnz"){return Opecode::brnz;}
      else if(nd == "pshz"){return Opecode::pshz;}
      else if(nd == "psh8"){return Opecode::psh8;}
      else if(nd == "psh8u"){return Opecode::psh8u;}
      else if(nd == "psh16"){return Opecode::psh16;}
      else if(nd == "psh16u"){return Opecode::psh16u;}
      else if(nd == "psh32"){return Opecode::psh32;}
      else if(nd == "dup"){return Opecode::dup;}
      else if(nd == "pop"){return Opecode::pop;}
      else if(nd == "pshpc"){return Opecode::pshpc;}
      else if(nd == "pshbp"){return Opecode::pshbp;}
      else if(nd == "pshsp"){return Opecode::pshsp;}
      else if(nd == "pshtm"){return Opecode::pshtm;}
      else if(nd == "updpc"){return Opecode::updpc;}
      else if(nd == "updbp"){return Opecode::updbp;}
      else if(nd == "updsp"){return Opecode::updsp;}
      else if(nd == "updtm"){return Opecode::updtm;}
      else if(nd == "prn"){return Opecode::prn;}
      else {report;throw;}


      cur.advance();
    }


  return Opecode::nop;
}


}


InstructionSource::
InstructionSource(const mkf::Node&  src):
opecode(Opecode::nop)
{
  auto  cur = src.make_cursor();

    while(!cur.test_ended())
    {
      auto&  nd = *cur;

        if(nd == "opecode")
        {
          opecode = read_opecode(nd);
        }

      else
        if(nd == "operand")
        {
          operand.read(nd);
        }


      cur.advance();
    }
}


void
InstructionSource::
resolve(std::vector<Block>&  ls)
{
    if(operand.identifier.size())
    {
        for(auto&  blk: ls)
        {
            if(blk.identifier == operand.identifier)
            {
              operand.value = blk.frame.head_offset;

              return;
            }
        }


      printf("識別子%sが見つかりません\n",operand.identifier.data());

//      throw operand;
    }
}


void
InstructionSource::
write(uint8_t*  base, size_t  offset) const
{
  auto  p = base+offset;

  *p++ = static_cast<uint8_t>(opecode);

  unsigned int  const i = operand.value;

    switch(opecode)
    {
      case(Opecode::psh8):
      case(Opecode::psh8u):
        *p = (i&0xFF);
        break;
      case(Opecode::psh16):
      case(Opecode::psh16u):
        *p++ = ((i>>8)&0xFF);
        *p   = ((i   )&0xFF);
        break;
      case(Opecode::psh32):
        *p++ = ((i>>24)&0xFF);
        *p++ = ((i>>16)&0xFF);
        *p++ = ((i>> 8)&0xFF);
        *p   = ((i    )&0xFF);
        break;
      default:;
    }
}


void
InstructionSource::
fix(ObjectFrame&  of) const
{
  of.tail_offset = of.head_offset+get_byte_number(opecode);
}


void
InstructionSource::
print(FILE*  f) const
{
  fprintf(f,"%s",get_string(opecode));

    switch(opecode)
    {
      case(Opecode::psh8):
      case(Opecode::psh8u):
      case(Opecode::psh16):
      case(Opecode::psh16u):
      case(Opecode::psh32):
        fprintf(f," ");
        operand.print(f);
        break;
      default:;
    }
}




}




