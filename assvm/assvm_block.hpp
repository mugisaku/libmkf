#ifndef ASSVM_BLOCK_HPP_INCLUDED
#define ASSVM_BLOCK_HPP_INCLUDED


#include<string>
#include<vector>
#include<cstddef>
#include<cstdio>
#include"assvm_element.hpp"
#include"mkf_node.hpp"


namespace assvm{


struct
Block
{
  std::string  identifier;

  ObjectFrame  frame;

  std::vector<Element>  element_list;

  Block(size_t  offset, const mkf::Node&  src);

  void  resolve(std::vector<Block>&  ls);

  void  write(uint8_t*  base) const;

  void  print(FILE*  f=stdout) const;

};


}




#endif




