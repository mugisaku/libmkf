#include"mkf_element.hpp"
#include"mkf_group.hpp"
#include"mkf_definition.hpp"
#include"mkf_parsecontext.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




namespace mkf{




namespace{


bool
test(const pp::Character*  a, const char*  b, size_t  n)
{
    while(n--)
    {
      auto  byte_number = pp::get_utf8_byte_number(b);

      auto  c = pp::to_char16(b,byte_number);

      b += byte_number;

        if(a++->unicode != c)
        {
          return false;
        }
    }


  return true;
}


size_t
compare_string(const pp::Character*&  p, const std::string&  s, Node&  node)
{
    if(test(p,s.data(),s.size()))
    {
        for(int  i = 0;  i < s.size();  ++i)
        {
          node.append(new Node(s.data(),*p++));
        }


      return s.size();
    }


  return 0;
}


}


bool
Element::
compare(ParseContext&  parser, const pp::Character*&  p, Node&  node) const
{
    switch(kind)
    {
      case(ElementKind::null):
        break;
      case(ElementKind::string):
        return compare_string(p,*get_string(),node);
        break;
      case(ElementKind::identifier):
        return parser.enter(get_string()->data(),p,node);
        break;
      case(ElementKind::group           ): return data.grp->compare(parser,p,node,0                          );break;
      case(ElementKind::option_group    ): return data.grp->compare(parser,p,node,option_flag                );break;
      case(ElementKind::repetition_group): return data.grp->compare(parser,p,node,option_flag|repetition_flag);break;
      default:
        printf("Element clear error");
    }


  return false;
}


}




