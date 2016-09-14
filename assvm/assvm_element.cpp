#include"assvm_element.hpp"
#include"assvm_instructionsource.hpp"
#include"assvm_data.hpp"
#include<cstdio>
#include<cstdlib>




namespace assvm{


Element::
Element():
kind(ElementKind::null)
{
}


Element::
Element(size_t  off, InstructionSource*  src):
kind(ElementKind::null)
{
  reset(off,src);
}


Element::
Element(size_t  off, Data*  dat):
kind(ElementKind::null)
{
  reset(off,dat);
}


Element::
Element(Element&&  rhs) noexcept:
kind(ElementKind::null)
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
operator=(Element&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

  frame = rhs.frame;

  content = rhs.content;

  return *this;
}




void
Element::
clear()
{
    switch(kind)
    {
      case(ElementKind::instruction):
        delete content.src;
        break;
      case(ElementKind::data):
        delete content.dat;
        break;
      default:;
    }


  kind = ElementKind::null;
}




void
Element::
reset(size_t  off, InstructionSource*  src)
{
  clear();

  frame.head_offset = off;

  src->fix(frame);

  kind = ElementKind::instruction;

  content.src = src;
}


void
Element::
reset(size_t  off, Data*  dat)
{
  clear();

  frame.head_offset = off;

  dat->fix(frame);

  kind = ElementKind::data;

  content.dat = dat;
}


void
Element::
write(uint8_t*  base) const
{
    switch(kind)
    {
      case(ElementKind::instruction):
        content.src->write(base,frame.head_offset);
        break;
      case(ElementKind::data):
        content.dat->write(base,frame.head_offset);
        break;
      default:;
    }
}


void
Element::
print(FILE*  f) const
{
  fprintf(f,"/*[%8zd]*/  ",frame.head_offset);

    switch(kind)
    {
      case(ElementKind::instruction):
        content.src->print(f);
        break;
      case(ElementKind::data):
        content.dat->print(f);
        break;
      default:;
    }
}




}




