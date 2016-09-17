#include"cmplr_type.hpp"
#include<cctype>
#include<cstring>




Type::
Type(TypeKind  k):
kind(k),
element_number(1)
{
}


Type::
Type(TypePointer  ptr):
kind(TypeKind::pointer),
source_type(ptr.type),
element_number(1)
{
}


Type::
Type(TypeArray  arr):
kind(TypeKind::array),
source_type(arr.type),
element_number(arr.element_number)
{
}




size_t
Type::
get_size() const
{
    switch(kind)
    {
      case(TypeKind::int8  ):
      case(TypeKind::uint8 ): return 1;
      case(TypeKind::int16 ):
      case(TypeKind::uint16): return 2;
      case(TypeKind::int32 ):
      case(TypeKind::pointer): return 4;

      case(TypeKind::array):
        return source_type->get_size()*element_number;
    }


  return 0;
}


int
Type::
snprint(char*  s, size_t  n) const
{
    switch(kind)
    {
      case(TypeKind::void_ ): return snprintf(s,n,"void");break;
      case(TypeKind::int8  ): return snprintf(s,n,"int8");break;
      case(TypeKind::uint8 ): return snprintf(s,n,"uint8");break;
      case(TypeKind::int16 ): return snprintf(s,n,"int16");break;
      case(TypeKind::uint16): return snprintf(s,n,"uint16");break;
      case(TypeKind::int32 ): return snprintf(s,n,"int32");break;

      case(TypeKind::array):
      {
        auto  res = source_type->snprint(s,n);

        s += res;
        n -= res;

        return res+snprintf(s,n,"[%d]",element_number);
      } break;
      case(TypeKind::pointer):
        auto  res = source_type->snprint(s,n);

        s += res;
        n -= res;

        return res+snprintf(s,n,"*");
        break;
    }


  return 0;
}


std::string
Type::
to_string() const
{
  char  buf[256];

  snprint(buf,sizeof(buf));

  return std::string(buf);
}


void
Type::
print(FILE*  f) const
{
  char  buf[256];

  snprint(buf,sizeof(buf));

  fprintf(f,"%s",buf);
}




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


Type*
make(int  n, const char*  str)
{
    switch(n)
    {
      case(4):
             if(std::strcmp(str,"void") == 0){return new Type(TypeKind::void_);}
        else if(std::strcmp(str,"int8") == 0){return new Type(TypeKind::int8);}
        break;
      case(5):
             if(std::strcmp(str,"uint8") == 0){return new Type(TypeKind::uint8);}
        else if(std::strcmp(str,"int16") == 0){return new Type(TypeKind::int16);}
        else if(std::strcmp(str,"int32") == 0){return new Type(TypeKind::int32);}
        break;
      case(6):
          if(std::strcmp(str,"uint16") == 0){return new Type(TypeKind::uint16);}
        break;
    }


  return nullptr;
}


}


Type*
make_type(const char*  s)
{
  char  buf[256];

  int  res = scan_typename(s,buf,sizeof(buf));

  Type*  t = make(res,buf);

    for(;;)
    {
      skip_spaces(s);

        if(*s == '*')
        {
          ++s;

          t = new Type(TypePointer(t));
        }

      else
        if(*s == '[')
        {
          ++s;

          auto  n = scan_array_size(s);

          t = new Type(TypeArray(t,n));
        }

      else
        {
          break;
        }
    }


  return t;
}




