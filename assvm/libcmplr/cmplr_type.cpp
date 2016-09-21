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

  referred_type.reset(rhs.referred_type? new Type(*rhs.referred_type):nullptr);

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

  referred_type = std::move(rhs.referred_type);

  return *this;
}


bool
Type::
operator==(const Type&  rhs) const
{
  return(to_string() == rhs.to_string());
}




bool  Type::operator==(TypeKind  k) const{return(kind == k);}
bool  Type::operator!=(TypeKind  k) const{return(kind != k);}


Type::
operator bool() const
{
  return(kind == TypeKind::null);
}




void
Type::
reset(TypeKind  k, bool  c)
{
  kind = k;

  constant = c;

  element_number = 1;

  referred_type.reset();
}


void
Type::
reset(TypePointer&&  ptr, bool  c)
{
  kind = TypeKind::pointer;

  constant = c;

  element_number = 1;

  referred_type.reset(new Type(std::move(ptr.type)));
}


void
Type::
reset(TypeReference&&  ref, bool  c)
{
  kind = TypeKind::reference;

  constant = c;

  element_number = 1;

  referred_type.reset(new Type(std::move(ref.type)));
}


void
Type::
reset(TypeArray&&  arr, bool  c)
{
  kind = TypeKind::array;

  constant = c;

  element_number = arr.element_number;

  referred_type.reset(new Type(std::move(arr.type)));
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
        return referred_type->get_size();
      case(TypeKind::array):
        return referred_type->get_size()*element_number;
    }


  return 0;
}


size_t
Type::
get_object_size() const
{
    if(kind == TypeKind::reference)
    {
      return 4;
    }


  return get_size();
}




size_t
Type::
get_alignment_size() const
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
      case(TypeKind::array):
        return referred_type->get_alignment_size();
    }


  return 0;
}


size_t
Type::
get_object_alignment_size() const
{
    if(kind == TypeKind::reference)
    {
      return 4;
    }


  return get_alignment_size();
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
            if(!referred_type)
            {
              report;
            }


          auto  res = referred_type->snprint(s,n);

          s += res;
          n -= res;

          return a+res+snprintf(s,n,"[%d]",element_number);
        }
        break;
      case(TypeKind::pointer):
        {
            if(!referred_type)
            {
              report;
            }


          auto  res = referred_type->snprint(s,n);

          s += res;
          n -= res;

          return a+res+snprintf(s,n,"*");
        }
        break;
      case(TypeKind::reference):
        {
            if(!referred_type)
            {
              report;
            }


          auto  res = referred_type->snprint(s,n);

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
  referred_type.reset();

  std::string  s;

  src.collect_characters(s);


  *this = make_type(s.data());
}




