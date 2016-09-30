#include"typesystem_pointer.hpp"
#include"typesystem_element.hpp"




namespace typesystem{


Pointer::Pointer(Element*  e): referred(e){}
Pointer::Pointer(const std::unique_ptr<Element>&  e): referred(e? new Element(*e):nullptr){}
Pointer::Pointer(const Pointer&   rhs) noexcept: referred(rhs.referred? new Element(*rhs.referred):nullptr){}
Pointer::Pointer(      Pointer&&  rhs) noexcept: referred(std::move(rhs.referred)){}




void
Pointer::
snprint(char*&  s, size_t&  n, bool  ref) const
{
    if(referred)
    {
      referred->snprint(s,n);

      auto  res = snprintf(s,n,ref? "&":"*");

      s += res;
      n -= res;
    }

  else
    {
      report;
      throw;
    }
}


}




