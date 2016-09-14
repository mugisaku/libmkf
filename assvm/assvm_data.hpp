#ifndef ASSVM_DATA_HPP_INCLUDED
#define ASSVM_DATA_HPP_INCLUDED


#include<vector>
#include<cstdio>
#include"mkf_node.hpp"
#include"assvm_binary.hpp"
#include"assvm_operand.hpp"


namespace assvm{


struct ObjectFrame;
struct Block;


enum class
DataKind
{
  i8,
  i16,
  i32,

};


struct
Data
{
  DataKind  kind;

  std::vector<Operand>  operand_list;

  Data(const mkf::Node&  src);

  void  resolve(std::vector<Block>&  ls);

  void  write(uint8_t*  base, size_t  offset) const;

  void  fix(ObjectFrame&  of) const;

  void  print(FILE*  f=stdout) const;

};


}




#endif




