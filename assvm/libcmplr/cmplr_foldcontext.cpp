#include"cmplr_foldcontext.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"cmplr_globalscope.hpp"
#include<cstdarg>




FoldContext::
FoldContext(const GlobalScope&  g):
globalscope(g),
function(nullptr)
{
}




const Declaration*
FoldContext::
find_declaration(const std::string&  id) const
{
    {
      auto   it = block_stack.rbegin();
      auto  end = block_stack.rend();

        while(it != end)
        {
          auto  blk = *it++;

            for(auto&  decl: blk->declaration_list)
            {
                if(decl.identifier == id)
                {
                  return &decl;
                }
            }
        }
    }


    if(function)
    {
        for(auto&  decl: function->parameter_list)
        {
            if(decl.identifier == id)
            {
              return &decl;
            }
        }
    }


    for(auto&  decl: globalscope.declaration_list)
    {
        if(decl.identifier == id)
        {
          return &decl;
        }
    }


  return nullptr;
}




