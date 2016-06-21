#include"mkf_element.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




constexpr int  ptr_size = sizeof(char*);


namespace mkf{


Element::Element(int  flags_):
kind(ElementKind::null),
flags(flags_)
{
}


Element::
Element(int  flags, int  chr_):
kind(ElementKind::null)
{
  reset(flags,chr_);
}


Element::
Element(int  flags, const String&  str):
kind(ElementKind::null)
{
  reset(flags,str);
}


Element::
Element(int  flags, const Identifier&  id):
kind(ElementKind::null)
{
  reset(flags,id);
}


Element::
Element(Element&&  rhs)
{
  *this = std::move(rhs);
}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(Element&&  rhs)
{
  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

  flags = rhs.flags;

  length = rhs.length;

  ptr = rhs.ptr          ;
        rhs.ptr = nullptr;

  return *this;
}


void
Element::
copy(const char*  s)
{
  length = std::strlen(s);

    if(length >= ptr_size)
    {
      ptr = static_cast<char*>(malloc(length+1));

      std::strcpy(ptr,s);
    }

  else
    {
      char*  dst = buf;

        while(*s)
        {
          *dst++= *s++;
        }


      *dst = 0;
    }
}


void
Element::
reset(int  flags_, int  chr_)
{
  clear();

  kind  = ElementKind::character;
  flags = flags_;

  chr = chr_;
}


void
Element::
reset(int  flags_, const String&  str)
{
  clear();

  kind = ElementKind::string;

  flags = flags_;
  

  copy(str.ptr);
}


void
Element::
reset(int  flags_, const Identifier&  id)
{
  clear();

  kind = ElementKind::identifier;

  flags = flags_;


  copy(id.ptr);
}


void
Element::
clear()
{
    switch(get_kind())
    {
      case(ElementKind::null):
      case(ElementKind::character):
        break;
      case(ElementKind::string):
      case(ElementKind::identifier):
          if(length >= ptr_size)
          {
            free(ptr);
          }
        break;
      default:
        printf("Element clear error");
    }


  kind   = ElementKind::null;
  length = 0;
}


ElementKind  Element::get_kind() const{return kind;}

size_t  Element::get_length() const{return length;}

const char*  Element::get_string() const{return((length >= ptr_size)? ptr:buf);}

int Element::get_character() const{return chr;}

bool  Element::test_omittable() const{return(flags&ElementFlag::omittable);}
bool  Element::test_repeat() const{return(flags&ElementFlag::repeat);}


void
Element::
print(Printer&  pr) const
{
    if(test_omittable())
    {
      pr.putc('?',true);
    }


    if(test_repeat())
    {
      pr.putc('*',true);
    }


    switch(get_kind())
    {
      case(ElementKind::null):
        pr.puts("(null)");
        break;
      case(ElementKind::character):
        pr.printf("\'%c\'",chr);
        break;
      case(ElementKind::string):
        pr.printf("\"%s\"",get_string());
        break;
      case(ElementKind::identifier):
        pr.puts(get_string());
        break;
      default:
        pr.puts("(unknown)");
    }
}


}


