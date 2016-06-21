#include"mkf_definition.hpp"
#include"mkf_ascii.hpp"
#include"mkf_ctype.hpp"




namespace mkf{




namespace{
int
get_code(int  c)
{
    switch(c)
    {
      case('0' ): c = '\0';break;
      case('n' ): c = '\n';break;
      case('t' ): c = '\t';break;
      case('\\'): c = '\\';break;
      case('\''): c = '\'';break;
      case('\"'): c = '\"';break;
    }


  return c;
}


Element
scan_character(uint32_t  flags, const char*&  p)
{
  int  c = *p++;

    if(c == '\\')
    {
      c = get_code(*p++);
    }


    if(*p != '\'')
    {
      printf("**%2d\n",*p);
      printf("**%s\n",p);
      report;
    }


  ++p;

  return Element(flags,c);
}


Element
scan_identifier(uint32_t  flags, const char*&  p)
{
  std::string  s;

    while(isalnum(*p) || (*p == '_'))
    {
      s.push_back(*p++);
    }


  return Element(flags,Identifier(s.data()));
}


Element
scan_string(uint32_t  flags, const char*&  p)
{
  std::string  s;

    for(;;)
    {
      int  c = *p;

        if(!c)
        {
          report;
          break;
        }

      else
        if(c == '\"')
        {
          ++p;

          break;
        }

      else
        if(c == '\\')
        {
          c = get_code(*++p);
        }


      s.push_back(c);

      ++p;
    }


  return Element(flags,String(s.data()));
}
}




namespace{
uint32_t
read_flags(const char*&  p)
{
  uint32_t  flags = 0;

    for(;;)
    {
           if(*p == '?'){flags |= ElementFlag::omittable;}
      else if(*p == '*'){flags |= ElementFlag::repeat   ;}
      else
        {
          break;
        }


      ++p;
    }


  return flags;
}
}


void
Definition::
scan(const char*&  p)
{
  const char*  last = nullptr;

    for(;;)
    {
      skip_space(p);

      uint32_t  flags = read_flags(p);

      skip_space(p);

      Element  el;

        switch(*p)
        {
          case('\''): el = scan_character(flags,++p);break;
          case('\"'): el =    scan_string(flags,++p);break;
          default:
              if(isalnum(*p) || (*p == '_'))
              {
                el = scan_identifier(flags,p);
              }

            else
              {
                report;
                printf("**%c**\n",*p);
              }
        }


      skip_space(p);

      auto  c = *p++;

      append_element(std::move(el));

        if(!c)
        {
          report;
          break;
        }


        if(c == ';')
        {
          break;
        }


      set_separator(c);

        if(last == p)
        {
          report;
          printf("**loop**%s",p);
          break;
        }


      last = p;
    }
}




}




