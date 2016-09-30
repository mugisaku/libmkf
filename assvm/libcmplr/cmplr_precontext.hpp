#ifndef CMPLR_PRECONTEXT_HPP_INCLUDED
#define CMPLR_PRECONTEXT_HPP_INCLUDED


#include<string>
#include<vector>




struct Declaration;
struct Function;
struct GlobalScope;
struct Block;


struct
PreContext
{
  union BlockFolder{
          Block*        pointer;
    const Block*  const_pointer;

    BlockFolder(      Block*  ptr):       pointer(ptr){};
    BlockFolder(const Block*  ptr): const_pointer(ptr){};
  };


  GlobalScope&  globalscope;

  union{
          Function*        function;
    const Function*  const_function;
  };

  std::vector<BlockFolder>  block_stack;

  unsigned int       do_block_count;
  unsigned int     branchnode_count;
  unsigned int  static_object_count;

  PreContext(GlobalScope&  g);

  const Declaration*  append_declaration(Declaration&&  decl);
  const Declaration*  find_declaration(const std::string&  id) const;

};


#endif




