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
block(nullptr),
do_block_count(0),
branchnode_count(0),
static_object_count(0)
{}




const Declaration*
PreContext::
append(Declaration&&  decl)
{
  Declaration*  ptr;

    if(block)
    {
        if(decl.storage_kind == StorageKind::local_static)
        {
          block->declaration_list.emplace_back(std::move(decl));

          ptr = &block->declaration_list.back();

          ptr->index = static_object_count++;
        }

      else
        {
          block->declaration_list.emplace_back(std::move(decl));

          ptr = &block->declaration_list.back();

          ptr->index = function->local_object_size;

          function->local_object_size += ptr->get_size();
        }
    }

  else
    {
      globalscope.declaration_list.emplace_back(std::move(decl));

      ptr = &globalscope.declaration_list.back();
    }


  return ptr;
}




