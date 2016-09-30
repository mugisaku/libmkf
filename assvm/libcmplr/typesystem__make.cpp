#include"typesystem_element.hpp"
#include<cctype>
#include<cstring>




namespace typesystem{


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
        if(std::strcmp(str,"int") == 0){return Type(I32());}
        break;
      case(4):
             if(std::strcmp(str,"void") == 0){return Type(Void());}
        else if(std::strcmp(str,"int8") == 0){return Type(I8());}
        else if(std::strcmp(str,"char") == 0){return Type(Char());}
        else if(std::strcmp(str,"bool") == 0){return Type(Bool());}
        else if(std::strcmp(str,"enum") == 0){return Type(Enum());}
        break;
      case(5):
             if(std::strcmp(str,"uint8") == 0){return Type(U8());}
        else if(std::strcmp(str,"int16") == 0){return Type(I16());}
        else if(std::strcmp(str,"int32") == 0){return Type(I32());}
        else if(std::strcmp(str,"union") == 0){return Type(Union());}
        break;
      case(6):
             if(std::strcmp(str,"uint16") == 0){return Type(U16());}
        else if(std::strcmp(str,"struct") == 0){return Type(Struct());}
        break;
      case(7):
          if(std::strcmp(str,"nullptr") == 0){return Type(Nullptr());}
        break;
    }


  return Type();
}


}




Type
Element::
make_pointer() const
{
  return Type(Pointer(duplicate()));
}


Type
Element::
make_reference() const
{
  return Type(Pointer(duplicate()),true);
}


Type
Element::
make_array(int  n) const
{
  return Type(Array(duplicate(),n));
}




Type
make_type(const char*  s)
{
  char  buf[256];

  int  res = scan_typename(s,buf,sizeof(buf));

  auto  t = make(res,buf);

    for(;;)
    {
      skip_spaces(s);

        if(*s == '*')
        {
          ++s;

          t = t.make_pointer();
        }

      else
        if(*s == '&')
        {
          ++s;

          t = t.make_reference();
        }

      else
        if(*s == '[')
        {
          ++s;

          t = t.make_array(scan_array_size(s));
        }

      else
        {
          break;
        }
    }


  return std::move(t);
}



}




