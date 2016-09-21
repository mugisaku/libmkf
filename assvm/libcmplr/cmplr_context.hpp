#ifndef CMPLR_CONTEXT_HPP_INCLUDED
#define CMPLR_CONTEXT_HPP_INCLUDED


#include"../assvm_instruction.hpp"
#include"cmplr_foldcontext.hpp"
#include"cmplr_precontext.hpp"




struct
Entry
{
  const Function*  function;

  std::string  content;

};


struct
Context: public FoldContext
{
  std::string  current_content;

  std::vector<Entry>  entry_list;

  std::string  definition_content;

  const Block*  control_block;

  Context(GlobalScope&  g);
  

  const Block*  change_control_block(const Block*  blk);

  void  push(const char*  fmt, ...);
  void  push_definition(const char*  fmt, ...);

  void  push_psh(int  v, const char*  fmt="", ...);
  void  push_definition_psh(int  v, const char*  fmt="", ...);

};


#endif




