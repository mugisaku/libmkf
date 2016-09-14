#ifndef CMPLR_GLOBALSCOPE_HPP_INCLUDED
#define CMPLR_GLOBALSCOPE_HPP_INCLUDED


#include"cmplr_declaration.hpp"
#include"libpp/pp_string.hpp"
#include"mkf_node.hpp"
#include"../assvm_instruction.hpp"
#include<list>
#include<vector>



struct
GlobalScope
{
  std::list<Declaration>  declaration_list;

  int  local_static_number=0;


  void  print(FILE*  f=stdout) const;

  std::string  compile();

  void  read(const mkf::Node&  src);

};




#endif




