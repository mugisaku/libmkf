#include"cmplr_precontext.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"cmplr_globalscope.hpp"
#include<cstdarg>




PreContext::
PreContext(GlobalScope&  g):
globalscope(g),
function(nullptr),
do_block_count(0),
branchnode_count(0),
static_object_count(0)
{
}




const Declaration*
PreContext::
append_declaration(Declaration&&  decl)
{
  Declaration*  ptr;

    if(block_stack.size())
    {
      auto  block = block_stack.back().pointer;

        if(decl.storage_kind == StorageKind::local_static)
        {
          block->declaration_list.emplace_back(std::move(decl));

          ptr = &block->declaration_list.back();

          ptr->offset = static_object_count++;
        }

      else
        {
          block->declaration_list.emplace_back(std::move(decl));

          ptr = &block->declaration_list.back();

            if(ptr->get_value().kind == ValueKind::single)
            {
              auto&  size = function->local_object_size;

              auto&  type = ptr->get_value().type;

                switch(type.get_alignment_size())
                {
              case(0):
              case(1):
                  break;
              case(2):
                  size +=  1;
                  size &= ~1;
                  break;
              case(4):
                  size +=  3;
                  size &= ~3;
                  break;
                }


              ptr->offset = size                   ;
                            size += type.get_size();
            }
        }
    }

  else
    {
      globalscope.declaration_list.emplace_back(std::move(decl));

      ptr = &globalscope.declaration_list.back();
    }


  return ptr;
}


const Declaration*
PreContext::
find_declaration(const std::string&  id) const
{
    {
      auto   it = block_stack.rbegin();
      auto  end = block_stack.rend();

        while(it != end)
        {
          auto&  blk = *it++;

            for(auto&  decl: blk.const_pointer->declaration_list)
            {
                if(decl.name == id)
                {
                  return &decl;
                }
            }
        }
    }


    for(auto&  decl: globalscope.declaration_list)
    {
        if(decl.name == id)
        {
          return &decl;
        }
    }


  return nullptr;
}




