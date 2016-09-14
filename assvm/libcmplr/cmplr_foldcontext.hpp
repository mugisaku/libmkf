#ifndef CMPLR_FOLDCONTEXT_HPP_INCLUDED
#define CMPLR_FOLDCONTEXT_HPP_INCLUDED


#include<string>
#include<vector>
#include"../assvm_instruction.hpp"




struct GlobalScope;
struct Function;
struct Block;
struct Declaration;


struct
FoldContext
{
  GlobalScope&  globalscope;

  Function*  function;

  std::vector<Block*>  block_stack;

  FoldContext(GlobalScope&  g);

  void  operator()();

  Declaration*  find_declaration(const std::string&  id);

};


#endif




