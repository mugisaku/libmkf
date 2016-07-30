#include"mkf_definition.hpp"
#include"mkf_ctype.hpp"




namespace mkf{




Definition::
Definition(const char*  id):
identifier(id),
noskip_state(0)
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

  noskip_state = rhs.noskip_state;

  return *this;
}


void
Definition::
clear()
{
  Group::clear();

  identifier.clear();

  noskip_state = 0;
}


namespace{
bool
test_noskip(const pp::Character*  p)
{
  const char16_t*  s = u"noskip";

    while(*s)
    {
        if(p++->unicode != *s++)
        {
          return false;
        }
    }


  return true;
}
}


void
Definition::
reset(const pp::Character*&  p)
{
  clear();

  pp::skip_spaces(p);

    if(test_noskip(p))
    {
      noskip_state = 1;

      p += 6;

      pp::skip_spaces(p);
    }


    for(;;)
    {
        if(isalnum(p->unicode) || (p->unicode == '_'))
        {
          identifier.append(pp::UTF8Chunk(p->unicode).codes);

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


bool
Definition::
test_noskip_flag() const
{
  return noskip_state;
}


void
Definition::
print(Printer&  pr) const
{
  printf("%s[%s] = ",noskip_state? "noskip ":"",identifier.data());

  Group::print(pr);

  pr.putc(';',true);
}


}




