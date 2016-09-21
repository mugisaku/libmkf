#include"cmplr_type.hpp"
#include"cmplr_context.hpp"
#include<cctype>
#include<cstring>




namespace{
void
skip_spaces(const char*&  p)
{
    while(isspace(*p))
    {
      ++p;
    }
}


int
scan_typename(const char*&  src, char*  dst, int  bufn)
{
  skip_spaces(src);

    if(bufn > 1)
    {
      int  res = 0;

      int  c = *src;

        if(isalpha(c) || (c == '_'))
        {
          *dst++ = c;

           ++src;
          --bufn;
           ++res;

            for(;;)
            {
                if(bufn == 1)
                {
                  break;
                }


              c = *src;

                if(!isalnum(c) && (c != '_'))
                {
                  break;
                }


              *dst++ = c;

               ++src;
              --bufn;
               ++res;
            }


          *dst = 0;

          return res;
        }
    }


  return 0;
}


int
scan_array_size(const char*&  src)
{
  int  i = 0;

  skip_spaces(src);

    for(;;)
    {
      int  c = *src;

        if(isdigit(c))
        {
          i *= 10;

          i += c-'0';

          ++src;
        }

      else
        {
          skip_spaces(src);

            if(*src == ']')
            {
              ++src;

              break;
            }


          throw;
        }
    }


  return i;
}


Type
make(int  n, const char*  str)
{
    switch(n)
    {
      case(3):
        if(std::strcmp(str,"int") == 0){return Type(TypeKind::int32);}
        break;
      case(4):
             if(std::strcmp(str,"void") == 0){return Type(TypeKind::void_);}
        else if(std::strcmp(str,"int8") == 0){return Type(TypeKind::int8);}
        break;
      case(5):
             if(std::strcmp(str,"uint8") == 0){return Type(TypeKind::uint8);}
        else if(std::strcmp(str,"int16") == 0){return Type(TypeKind::int16);}
        else if(std::strcmp(str,"int32") == 0){return Type(TypeKind::int32);}
        break;
      case(6):
          if(std::strcmp(str,"uint16") == 0){return Type(TypeKind::uint16);}
        break;
    }


  return Type();
}


}


Type
make_type(const char*  s)
{
  char  buf[256];

  int  res = scan_typename(s,buf,sizeof(buf));

  Type  t = make(res,buf);

    for(;;)
    {
      skip_spaces(s);

        if(*s == '*')
        {
          ++s;

          t.reset(TypePointer(std::move(t)));
        }

      else
        if(*s == '&')
        {
          ++s;

          t.reset(TypeReference(std::move(t)));
        }

      else
        if(*s == '[')
        {
          ++s;

          auto  n = scan_array_size(s);

          t.reset(TypeArray(std::move(t),n));
        }

      else
        {
          break;
        }
    }


  return std::move(t);
}




