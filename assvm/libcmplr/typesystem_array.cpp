#include"typesystem_array.hpp"
#include"typesystem_element.hpp"




namespace typesystem{


Array::
Array(Element*  e):
element(e),
size_defined(false)
{
}


Array::
Array(Element*  e, int  n):
element(e),
size_defined(true),
number(n)
{
}


Array::
Array(const Array&   rhs) noexcept
{
  size_defined = rhs.size_defined;
  number       = rhs.number;

  element.reset(rhs.element? new Element(*rhs.element):nullptr);
}


Array::
Array(Array&&  rhs) noexcept
{
  size_defined = rhs.size_defined;
  number       = rhs.number;

  element = std::move(rhs.element);
}




void
Array::
snprint(char*&  s, size_t&  n) const
{
    if(!element)
    {
      report;

      throw;
    }

  else
    {
      element->snprint(s,n);
    }


  int  res = 0;

    if(!size_defined)
    {
      res = snprintf(s,n,"[]");
    }

  else
    {
      res = snprintf(s,n,"[%d]",number);
    }


  s += res;
  n -= res;
}


}




