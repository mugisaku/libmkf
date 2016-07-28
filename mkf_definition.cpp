#include"mkf_definition.hpp"
#include"mkf_ctype.hpp"




namespace mkf{




Definition::
Definition(const char*  id):
identifier(id)
{
}


Definition::
Definition(Definition&&  rhs) noexcept
{
  *this = std::move(rhs);
}




Definition&
Definition::
operator=(Definition&&  rhs)
{
  static_cast<Group&>(*this) = std::move(rhs);

  identifier = std::move(rhs.identifier);

  return *this;
}


void
Definition::
clear()
{
  Group::clear();

  identifier.clear();
}


void
Definition::
reset(const pp::Character*&  p)
{
  clear();

  pp::skip_spaces(p);

    for(;;)
    {
      auto  c = p->unicode;

        if(isalnum(c) || (c == '_'))
        {
          identifier.push_back(c);

          ++p;
        }

      else
        {
          break;
        }
    }


  pp::skip_spaces(p);

    if(p->unicode == '=')
    {
      ++p;
    }


  pp::skip_spaces(p);

  scan(p,';');
}


void
Definition::
change_identifier(const char*  s)
{
  identifier = s;
}


const std::string&
Definition::
get_identifier() const
{
  return identifier;
}




void
Definition::
print(Printer&  pr) const
{
  printf("[");

    for(auto  c: identifier)
    {
      printf("%c",c);
    }


  printf("] = ");

  Group::print(pr);

  pr.putc(';',true);
}


}




