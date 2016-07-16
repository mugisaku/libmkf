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
reset(charptr&  p)
{
  clear();

  char  buf[256];

  int  n = 0;

  p.skip_space();

    if(sscanf(p," %256[0-9a-zA-Z_] = %n",buf,&n) == 1)
    {
      identifier = buf;

      p += n;

      scan(p,';');
    }

  else
    {
      report;
    }
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
  printf("[%s] = ",identifier.data());

  Group::print(pr);

  pr.putc(';',true);
}


}




