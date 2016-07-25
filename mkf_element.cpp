#include"mkf_element.hpp"
#include"mkf_group.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




namespace mkf{


Element::Element():
kind(ElementKind::null)
{
}


Element::
Element(std::string*  s):
kind(ElementKind::null)
{
  reset(s);
}


Element::
Element(const Identifier&  id):
kind(ElementKind::null)
{
  reset(id);
}


Element::
Element(Group*  grp):
kind(ElementKind::null)
{
  reset(grp);
}


Element::
Element(const OptionGroup&  grp):
kind(ElementKind::null)
{
  reset(grp);
}


Element::
Element(const RepetitionGroup&  grp):
kind(ElementKind::null)
{
  reset(grp);
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
operator=(Element&&  rhs)
{
  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

  data = rhs.data;

  return *this;
}


void
Element::
reset(std::string*  s)
{
  clear();

  kind = ElementKind::string;

  data.str = s;
}


void
Element::
reset(const Identifier&  id)
{
  clear();

  kind = ElementKind::identifier;

  data.str = id.s;
}


void
Element::
reset(Group*  grp)
{
  clear();

  kind = ElementKind::group;

  data.grp = grp;
}


void
Element::
reset(const OptionGroup&  grp)
{
  clear();

  kind = ElementKind::option_group;

  data.grp = grp.ptr;
}


void
Element::
reset(const RepetitionGroup&  grp)
{
  clear();

  kind = ElementKind::repetition_group;

  data.grp = grp.ptr;
}


void
Element::
clear()
{
    switch(get_kind())
    {
      case(ElementKind::null):
        break;
      case(ElementKind::string):
      case(ElementKind::identifier):
        delete data.str;
        break;
      case(ElementKind::group):
      case(ElementKind::option_group):
      case(ElementKind::repetition_group):
        delete data.grp;
        break;
      default:
        printf("Element clear error");
    }


  kind = ElementKind::null;
}


ElementKind  Element::get_kind() const{return kind;}

const std::string*  Element::get_string() const{return data.str;}

Group*  Element::get_group() const{return data.grp;}


void
Element::
print(Printer&  pr) const
{
    switch(get_kind())
    {
      case(ElementKind::null):
        pr.puts("(null)");
        break;
      case(ElementKind::string):
        pr.printf("\"%s\"",get_string()->data());
        break;
      case(ElementKind::identifier):
        pr.puts(get_string()->data());
        break;
      case(ElementKind::group):
        pr.puts("(");
        data.grp->print(pr);
        pr.puts(")");
        break;
      case(ElementKind::repetition_group):
        pr.putc('{');
        data.grp->print(pr);
        pr.putc('}');
        break;
      case(ElementKind::option_group):
        pr.putc('[');
        data.grp->print(pr);
        pr.putc(']');
        break;
      default:
        pr.puts("(unknown)");
    }
}


}


