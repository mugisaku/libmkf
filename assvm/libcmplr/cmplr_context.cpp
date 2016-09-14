#include"cmplr_context.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"cmplr_globalscope.hpp"
#include<cstdarg>




Context::
Context(GlobalScope&  g):
FoldContext(g),
control_block(nullptr)
{
}




const Block*
Context::
change_control_block(const Block*  blk)
{
  auto  prev = control_block      ;
               control_block = blk;

  return prev;
}


void
Context::
push(const char*  fmt, ...)
{
  char  buf[256];

  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(buf,sizeof(buf),fmt,ap);

  va_end(ap);

  current_content.append(buf);
}


void
Context::
push_definition(const char*  fmt, ...)
{
  char  buf[256];

  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(buf,sizeof(buf),fmt,ap);

  va_end(ap);

  definition_content.append(buf);
}




