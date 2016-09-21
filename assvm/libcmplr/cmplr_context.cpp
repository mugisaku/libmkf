#include"cmplr_context.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_block.hpp"
#include"cmplr_globalscope.hpp"
#include<cstdlib>
#include<cstdarg>
#include<limits>




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




namespace{
void
append_psh(std::string&  buf, int  v)
{
  const char*  fmt = "  pshz;";

    if(v < 0)
    {
      const char*  dfmt = (v <= std::numeric_limits<int8_t>::min() )? "  psh8 %6d;":
                          (v <= std::numeric_limits<int16_t>::min())? "  psh16 %6d;":
                                                                      "  psh32 %6d;";
    }

  else
    if(v > 0)
    {
      const char*  dfmt = (v <= std::numeric_limits<uint8_t>::max() )? "  psh8u %6d;":
                          (v <= std::numeric_limits<uint16_t>::max())? "  psh16u %6d;":
                                                                       "  psh32 %6d;";
    }


  char  s[256];

  snprintf(s,sizeof(s),fmt,v);

  buf.append(s);

  buf.push_back('\n');
}
}


void
Context::
push_psh(int  v, const char*  fmt, ...)
{
  append_psh(current_content,v);


  char  buf[256];

  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(buf,sizeof(buf),fmt,ap);

  va_end(ap);

  current_content.append(buf);
}


void
Context::
push_definition_psh(int  v, const char*  fmt, ...)
{
  append_psh(definition_content,v);


  char  buf[256];

  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(buf,sizeof(buf),fmt,ap);

  va_end(ap);

  definition_content.append(buf);
}




