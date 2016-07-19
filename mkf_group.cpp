#include"mkf_group.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




namespace mkf{




Group::
Group()
{
}


Group::
Group(int  separator_, List<Element>&&  element_list_):
List<Element>(std::move(element_list_)),
separator(separator_)
{
}


Group::
Group(charptr&  p, int  close)
{
  scan(p,close);
}


Group::
Group(Group&&  rhs) noexcept
{
  *this = std::move(rhs);
}


Group::
~Group()
{
  clear();
}




Group&
Group::
operator=(Group&&  rhs)
{
  static_cast<List<Element>&>(*this) = std::move(rhs);

  separator = rhs.separator;
}


bool
Group::
test_alternation() const
{
  return(separator == '|');
}


bool
Group::
test_exclusion() const
{
  return(separator == '-');
}


void
Group::
print(Printer&  pr) const
{
    if(!empty())
    {
      auto  it = begin();

      it->print(pr);

      ++it;

        while(it != end())
        {
          pr.putc(separator);

          it->print(pr);

          ++it;
        }
    }
}




}




