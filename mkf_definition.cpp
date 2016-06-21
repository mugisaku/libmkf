#include"mkf_definition.hpp"
#include"mkf_ascii.hpp"
#include"mkf_ctype.hpp"




namespace mkf{




Definition::
Definition(const char*  id):
solid_flag(0),
separator(0),
identifier(id)
{
}


Definition::
Definition(Definition&&  rhs)
{
  *this = std::move(rhs);
}




Definition&
Definition::
operator=(Definition&&  rhs)
{
  identifier = std::move(rhs.identifier);
  elements   = std::move(rhs.elements  );
  solid_flag = rhs.solid_flag;
  separator  = rhs.separator;

  return *this;
}


void
Definition::
reset(const char*&  p)
{
  clear();

  char  buf[256];

  int  n = 0;

  skip_space(p);

    if(std::strncmp(p,"solid ",6) == 0)
    {
      p += 6;

      solid_flag = 1;
    }


    if(sscanf(p," %256[0-9a-zA-Z_] = %n",buf,&n) == 1)
    {
      identifier = buf;

      p += n;

      scan(p);
    }

  else
    {
      report;
    }
}


void
Definition::
clear()
{
  elements.clear();

  solid_flag = 0;
  separator  = 0;
}


void
Definition::
append_element(Element&&  el)
{
  elements.emplace_back(std::move(el));
}


const ElementList&
Definition::
get_list() const
{
  return elements;
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
test_solid_flag() const
{
  return solid_flag;
}


bool
Definition::
test_selective() const
{
  return(separator == '|');
}


void
Definition::
set_solid_flag()
{
  solid_flag = 1;
}


void
Definition::
set_separator(int  c)
{
    if((c != ',') &&
       (c != ';') &&
       (c != ':') &&
       (c != '|'))
    {
      report;
      printf("%c  使えないセパレーターです\n",c);
    }


    if(!separator)
    {
      separator = c;
    }

  else
    if(separator != c)
    {
      report;
      printf("%c = %c  違うセパレーターが混在しています\n",separator,c);
    }
}




void
Definition::
print(Printer&  pr) const
{
  int  sep = (!separator? ':':separator);


  pr.printf("%s[%s] = ",solid_flag? "SOLID":"",identifier.data());

    if(elements.size())
    {
      auto   it = elements.cbegin();
      auto  end = elements.cend();

        for(;;)
        {
          it->print(pr);

            if(++it != end)
            {
              pr.putc(sep,true);
            }

           else
            {
              break;
            }
        }
    }


  pr.putc(';',true);
}


}




