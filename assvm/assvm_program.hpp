#ifndef ASSVM_PROGRAM_HPP_INCLUDED
#define ASSVM_PROGRAM_HPP_INCLUDED


#include"mkf_node.hpp"
#include"assvm_instruction.hpp"
#include"assvm_block.hpp"
#include"assvm_binary.hpp"
#include<string>
#include<vector>


namespace assvm{


struct
Program
{
  Binary  binary;

  std::vector<Block>  block_list;

  int  main_entry_point;

  Program(const mkf::Node&  src);

  void  print(FILE*  f=stdout) const;

};



}




#endif




