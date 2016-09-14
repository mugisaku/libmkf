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
      else if(nd == "asn"){return Opecode::asn;}
      else if(nd == "aadd"){return Opecode::aadd;}
      else if(nd == "asub"){return Opecode::asub;}
      else if(nd == "amul"){return Opecode::amul;}
      else if(nd == "adiv"){return Opecode::adiv;}
      else if(nd == "arem"){return Opecode::arem;}
      else if(nd == "ashl"){return Opecode::ashl;}
      else if(nd == "ashr"){return Opecode::ashr;}
      else if(nd == "abor"){return Opecode::abor;}
      else if(nd == "aband"){return Opecode::aband;}
      else if(nd == "abxor"){return Opecode::abxor;}
      else if(nd == "bnot"){return Opecode::bnot;}
      else if(nd == "lor"){return Opecode::lor;}
      else if(nd == "land"){return Opecode::land;}
      else if(nd == "lnot"){return Opecode::lnot;}
      else if(nd == "neg"){return Opecode::neg;}
      else if(nd == "ld"){return Opecode::ld;}
      else if(nd == "st"){return Opecode::st;}
      else if(nd == "eq"){return Opecode::eq;}
      else if(nd == "neq"){return Opecode::neq;}
      else if(nd == "lt"){return Opecode::lt;}
      else if(nd == "lteq"){return Opecode::lteq;}
      else if(nd == "gt"){return Opecode::gt;}
      else if(nd == "gteq"){return Opecode::gteq;}
      else if(nd == "hlt"){return Opecode::hlt;}
      else if(nd == "brz"){return Opecode::brz;}
      else if(nd == "brnz"){return Opecode::brnz;}
      else if(nd == "psh0"){return Opecode::psh0;}
      else if(nd == "pshi8"){return Opecode::pshi8;}
      else if(nd == "pshui8"){return Opecode::pshui8;}
      else if(nd == "pshi16"){return Opecode::pshi16;}
      else if(nd == "pshui16"){return Opecode::pshui16;}
      else if(nd == "pshi32"){return Opecode::pshi32;}
      else if(nd == "dup"){return Opecode::dup;}
      else if(nd == "arg"){return Opecode::arg;}
      else if(nd == "pshpc"){return Opecode::pshpc;}
      else if(nd == "pshbp"){return Opecode::pshbp;}
      else if(nd == "pshsp"){return Opecode::pshsp;}
      else if(nd == "updpc"){return Opecode::updpc;}
      else if(nd == "updbp"){return Opecode::updbp;}
      else if(nd == "updsp"){return Opecode::updsp;}
      else if(nd == "pop"){return Opecode::pop;}
      else if(nd == "cal"){return Opecode::cal;}
      else if(nd == "ret"){return Opecode::ret;}
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

      throw operand;
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
      case(Opecode::pshi8):
      case(Opecode::pshui8):
        *p = (i&0xFF);
        break;
      case(Opecode::pshi16):
      case(Opecode::pshui16):
        *p++ = ((i>>8)&0xFF);
        *p   = ((i   )&0xFF);
        break;
      case(Opecode::pshi32):
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
      case(Opecode::pshi8):
      case(Opecode::pshui8):
      case(Opecode::pshi16):
      case(Opecode::pshui16):
      case(Opecode::pshi32):
        fprintf(f," ");
        operand.print(f);
        break;
      default:;
    }
}




}




