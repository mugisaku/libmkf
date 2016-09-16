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
      case(Opecode::pshz): return "pshz";
      case(Opecode::psh8): return "psh8";
      case(Opecode::psh8u): return "psh8u";
      case(Opecode::psh16): return "psh16";
      case(Opecode::psh16u): return "psh16u";
      case(Opecode::psh32): return "psh32";
      case(Opecode::arg): return "arg";
      case(Opecode::pshpc): return "pshpc";
      case(Opecode::pshbp): return "pshbp";
      case(Opecode::pshsp): return "pshsp";
      case(Opecode::updpc): return "updpc";
      case(Opecode::updbp): return "updbp";
      case(Opecode::updsp): return "updsp";
      case(Opecode::pop): return "pop";
      case(Opecode::dup): return "dup";
      case(Opecode::ld8): return "ld8";
      case(Opecode::ld8u): return "ld8u";
      case(Opecode::ld16): return "ld16";
      case(Opecode::ld16u): return "ld16u";
      case(Opecode::ld32): return "ld32";
      case(Opecode::st8): return "st8";
      case(Opecode::st16): return "st16";
      case(Opecode::st32): return "st32";
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
      case(Opecode::psh8):
      case(Opecode::psh8u):
        return 2;
      case(Opecode::psh16):
      case(Opecode::psh16u):
        return 3;
      case(Opecode::psh32):
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
      case(Opecode::psh8):
        printf("  %d",static_cast<int8_t>(*bin++));
        break;
      case(Opecode::psh8u):
        printf("  %d",static_cast<uint8_t>(*bin++));
        break;
      case(Opecode::psh16):
        i   = *bin++<<8;
        i  |= *bin++;

        printf("  %d",static_cast<int16_t>(i));
        break;
      case(Opecode::psh16u):
        i   = *bin++<<8;
        i  |= *bin++;

        printf("  %d",static_cast<uint16_t>(i));
        break;
      case(Opecode::psh32):
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




