#include"cmplr_type.hpp"
#include"cmplr_context.hpp"
#include<cctype>
#include<cstring>




Type::
Type(TypeKind  k, bool  c)
{
  reset(k,c);
}


Type::
Type(TypePointer&&  ptr, bool  c)
{
  reset(std::move(ptr),c);
}


Type::
Type(TypeReference&&  ref, bool  c)
{
  reset(std::move(ref),c);
}


Type::
Type(TypeArray&&  arr, bool  c)
{
  reset(std::move(arr),c);
}


Type::
Type(const Type&  rhs)
{
  *this = rhs;
}


Type::
Type(Type&&  rhs) noexcept
{
  *this = std::move(rhs);
}




Type&
Type::
operator=(const Type&  rhs)
{
  kind = rhs.kind;

  constant = rhs.constant;

  element_number = rhs.element_number;

  source_type.reset(rhs.source_type? new Type(*rhs.source_type):nullptr);

  return *this;
}


Type&
Type::
operator=(Type&&  rhs) noexcept
{
  kind = rhs.kind                 ;
         rhs.kind = TypeKind::null;

  constant = rhs.constant;

  element_number = rhs.element_number;

  source_type = std::move(rhs.source_type);

  return *this;
}


bool  Type::operator==(TypeKind  k) const{return(kind == k);}
bool  Type::operator!=(TypeKind  k) const{return(kind != k);}


void
Type::
reset(TypeKind  k, bool  c)
{
  kind = k;

  constant = c;

  element_number = 1;

  source_type.reset();
}


void
Type::
reset(TypePointer&&  ptr, bool  c)
{
  kind = TypeKind::pointer;

  constant = c;

  element_number = 1;

  source_type.reset(new Type(std::move(ptr.type)));
}


void
Type::
reset(TypeReference&&  ref, bool  c)
{
  kind = TypeKind::reference;

  constant = c;

  element_number = 1;

  source_type.reset(new Type(std::move(ref.type)));

if(!source_type)
{
report;
}
}


void
Type::
reset(TypeArray&&  arr, bool  c)
{
  kind = TypeKind::array;

  constant = c;

  element_number = arr.element_number;

  source_type.reset(new Type(std::move(arr.type)));
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

      case(TypeKind::reference):
        return source_type->get_size();

      case(TypeKind::array):
        return source_type->get_size()*element_number;
    }


  return 0;
}




Type
Type::
compile_dereference(Context&  ctx) const
{
    switch(kind)
    {
      case(TypeKind::int8  ):
        ctx.push("  ld8;\n");
        break;
      case(TypeKind::uint8 ):
        ctx.push("  ld8u;\n");
        break;
      case(TypeKind::int16 ):
        ctx.push("  ld16;\n");
        break;
      case(TypeKind::uint16):
        ctx.push("  ld16u;\n");
        break;
      case(TypeKind::int32 ):
      case(TypeKind::pointer):
      case(TypeKind::array):
        ctx.push("  ld32;\n");
        break;
    }


  return *this;
}


Type
Type::
compile_assign(Context&  ctx) const
{
    switch(kind)
    {
      case(TypeKind::int8  ):
      case(TypeKind::uint8 ):
        ctx.push("  st8;\n");
        break;
      case(TypeKind::int16 ):
      case(TypeKind::uint16):
        ctx.push("  st16;\n");
        break;
      case(TypeKind::int32 ):
        ctx.push("  st32;\n");
        break;
    }


  return Type(TypeKind::int32);
}




int
Type::
snprint(char*  s, size_t  n) const
{
  int  a = 0;

    if(constant)
    {
      a = snprintf(s,n,"const");

      s += a;
      n -= a;
    }


    switch(kind)
    {
      case(TypeKind::void_ ): return a+snprintf(s,n,"void");break;
      case(TypeKind::int8  ): return a+snprintf(s,n,"int8");break;
      case(TypeKind::uint8 ): return a+snprintf(s,n,"uint8");break;
      case(TypeKind::int16 ): return a+snprintf(s,n,"int16");break;
      case(TypeKind::uint16): return a+snprintf(s,n,"uint16");break;
      case(TypeKind::int32 ): return a+snprintf(s,n,"int32");break;

      case(TypeKind::array):
        {
            if(!source_type)
            {
              report;
            }


          auto  res = source_type->snprint(s,n);

          s += res;
          n -= res;

          return a+res+snprintf(s,n,"[%d]",element_number);
        }
        break;
      case(TypeKind::pointer):
        {
            if(!source_type)
            {
              report;
            }


          auto  res = source_type->snprint(s,n);

          s += res;
          n -= res;

          return a+res+snprintf(s,n,"*");
        }
        break;
      case(TypeKind::reference):
        {
            if(!source_type)
            {
              report;
            }


          auto  res = source_type->snprint(s,n);

          s += res;
          n -= res;

          return a+res+snprintf(s,n,"&");
        }
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


void
Type::
read(const mkf::Node&  src)
{
  source_type.reset();

  std::string  s;

  src.collect_characters(s);


  *this = make_type(s.data());
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




