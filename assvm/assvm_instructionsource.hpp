#ifndef ASSVM_INSTRUCTIONSOURCE_HPP_INCLUDED
#define ASSVM_INSTRUCTIONSOURCE_HPP_INCLUDED


#include<string>
#include<cstddef>
#include<cstdio>
#include"mkf_node.hpp"
#include"assvm_instruction.hpp"
#include"assvm_operand.hpp"
#include"assvm_binary.hpp"


namespace assvm{


struct ObjectFrame;
struct Block;


struct
InstructionSource
{
  Opecode  opecode;
  Operand  operand;

  InstructionSource(const mkf::Node&  src);

  void  resolve(std::vector<Block>&  ls);

  void  write(uint8_t*  base, size_t  offset) const;

  void  fix(ObjectFrame&  of) const;

  void  print(FILE*  f=stdout) const;

};


}




#endif




