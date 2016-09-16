#ifndef CMPLR_BRANCHNODE_HPP_INCLUDED
#define CMPLR_BRANCHNODE_HPP_INCLUDED


#include"mkf_node.hpp"
#include<vector>
#include<cstdio>




struct Block;
struct Context;


struct
BranchNode
{
  int  index_base;

  std::vector<const Block*>  block_list;

  void  push(Block&  blk);

  void  print(FILE*  f=stdout) const;

  void  compile(Context&  ctx) const;

};


#endif




