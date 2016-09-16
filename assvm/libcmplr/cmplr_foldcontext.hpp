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
  const GlobalScope&  globalscope;

  const Function*  function;

  std::vector<const Block*>  block_stack;

  FoldContext(const GlobalScope&  g);

  const Declaration*  find_declaration(const std::string&  id) const;

};


#endif




