#include"assvm_instruction.hpp"
#include<cstdio>
#include<limits>




namespace assvm{




const char*
get_string(Opecode  op)
{
    switch(op)
    {
      case(Opecode::nop): return "nop";
      case(Opecode::add): return "add";
      case(Opecode::sub): return "sub";
      case(Opecode::mul): return "mul";
      case(Opecode::div): return "div";
      case(Opecode::rem): return "rem";
      case(Opecode::shl): return "shl";
      case(Opecode::shr): return "shr";
      case(Opecode::bor): return "bor";
      case(Opecode::band): return "band";
      case(Opecode::bxor): return "bxor";
      case(Opecode::asn): return "asn";
      case(Opecode::aadd): return "aadd";
      case(Opecode::asub): return "asub";
      case(Opecode::amul): return "amul";
      case(Opecode::adiv): return "adiv";
      case(Opecode::arem): return "arem";
      case(Opecode::ashl): return "ashl";
      case(Opecode::ashr): return "ashr";
      case(Opecode::abor): return "abor";
      case(Opecode::aband): return "aband";
      case(Opecode::abxor): return "abxor";
      case(Opecode::lor): return "lor";
      case(Opecode::land): return "land";
      case(Opecode::eq): return "eq";
      case(Opecode::neq): return "neq";
      case(Opecode::lt): return "lt";
      case(Opecode::lteq): return "lteq";
      case(Opecode::gt): return "gt";
      case(Opecode::gteq): return "gteq";
      case(Opecode::bnot): return "bnot";
      case(Opecode::lnot): return "lnot";
      case(Opecode::neg): return "neg";
      case(Opecode::hlt): return "hlt";
      case(Opecode::brz): return "brz";
      case(Opecode::brnz): return "brnz";
      case(Opecode::psh0): return "psh0";
      case(Opecode::pshi8): return "pshi8";
      case(Opecode::pshui8): return "pshui8";
      case(Opecode::pshi16): return "pshi16";
      case(Opecode::pshui16): return "pshui16";
      case(Opecode::pshi32): return "pshi32";
      case(Opecode::arg): return "arg";
      case(Opecode::pshpc): return "pshpc";
      case(Opecode::pshbp): return "pshbp";
      case(Opecode::pshsp): return "pshsp";
      case(Opecode::updpc): return "updpc";
      case(Opecode::updbp): return "updbp";
      case(Opecode::updsp): return "updsp";
      case(Opecode::pop): return "pop";
      case(Opecode::dup): return "dup";
      case(Opecode::ld): return "ld";
      case(Opecode::st): return "st";
      case(Opecode::cal): return "cal";
      case(Opecode::ret): return "ret";
      case(Opecode::prn): return "prn";
    }


  return "**unknown**";
}




int
get_byte_number(Opecode  op)
{
    switch(op)
    {
      case(Opecode::pshi8):
      case(Opecode::pshui8):
        return 2;
      case(Opecode::pshi16):
      case(Opecode::pshui16):
        return 3;
      case(Opecode::pshi32):
        return 5;
      default:;
    }


  return 1;
}




const uint8_t*
print(const uint8_t*  bin)
{
  auto  op = static_cast<Opecode>(*bin++);

  printf("%s",get_string(op));

  int  i;

    switch(op)
    {
      case(Opecode::pshi8):
        printf("  %d",static_cast<int8_t>(*bin++));
        break;
      case(Opecode::pshui8):
        printf("  %d",static_cast<uint8_t>(*bin++));
        break;
      case(Opecode::pshi16):
        i   = *bin++<<8;
        i  |= *bin++;

        printf("  %d",static_cast<int16_t>(i));
        break;
      case(Opecode::pshui16):
        i   = *bin++<<8;
        i  |= *bin++;

        printf("  %d",static_cast<uint16_t>(i));
        break;
      case(Opecode::pshi32):
        i  = *bin++<<24;
        i |= *bin++<<16;
        i |= *bin++<< 8;
        i |= *bin++    ;

        printf("  %d",static_cast<int32_t>(i));
        break;
      default:;
    }


  return bin;
}


}




