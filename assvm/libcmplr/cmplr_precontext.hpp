#ifndef CMPLR_PRECONTEXT_HPP_INCLUDED
#define CMPLR_PRECONTEXT_HPP_INCLUDED


#include"../assvm_instruction.hpp"
#include"cmplr_foldcontext.hpp"




struct Declaration;


struct
PreContext
{
  GlobalScope&  globalscope;
  Function*        function;
  Block*              block;

  PreContext(GlobalScope&  g);

  const Declaration*  append(Declaration&&  decl);

};


#endif




