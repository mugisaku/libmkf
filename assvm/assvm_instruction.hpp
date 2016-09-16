#ifndef ASSVM_INSTRUCTION_HPP_INCLUDED
#define ASSVM_INSTRUCTION_HPP_INCLUDED


#include<cstdint>
#include<cstddef>
#include"mkf_node.hpp"


namespace assvm{


enum class
Opecode
{
  nop,

  hlt,

  neg,
  lnot,
  bnot,

  add,
  sub,
  mul,
  div,
  rem,
  shl,
  shr,
  bor,
  band,
  bxor,

  eq,
  neq,
  lt,
  lteq,
  gt,
  gteq,

  lor,
  land,

  pshz,
  psh8,
  psh8u,
  psh16,
  psh16u,
  psh32,

  arg,

  pshpc,
  pshbp,
  pshsp,

  pop,
  dup,

  updpc,
  updbp,
  updsp,

  ld8,
  ld8u,
  ld16,
  ld16u,
  ld32,
  st8,
  st16,
  st32,

  brz,
  brnz,

  cal,
  ret,

  prn,

};


using word_t = int32_t;

constexpr size_t  word_size = sizeof(word_t);




const char*  get_string(Opecode  op);

int  get_byte_number(Opecode  op);

const uint8_t*  print(const uint8_t*  bin);


}




#endif




