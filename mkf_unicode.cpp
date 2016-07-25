#include"mkf_unicode.hpp"
#include"mkf_element.hpp"
#include<cstdlib>
#include<cctype>




namespace mkf{


int
get_unicode(const char*  name)
{
  unsigned int  n;

    if(sscanf(name,"UNICODE_%X",&n) == 1)
    {
      return n;
    }


  return -1;
}


}


