#ifndef CMPLR_GLOBALSCOPE_HPP_INCLUDED
#define CMPLR_GLOBALSCOPE_HPP_INCLUDED


#include"cmplr_declaration.hpp"
#include"libpp/pp_string.hpp"
#include"mkf_node.hpp"
#include<list>



struct
GlobalScope
{
  std::list<Declaration>  declaration_list;


  void  print(FILE*  f=stdout);

  std::string  compile();

  void  read(const mkf::Node&  src);

};




#endif




