#include"mkf_element.hpp"
#include"mkf_group.hpp"
#include"mkf_definition.hpp"
#include"mkf_parsecontext.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




namespace mkf{




namespace{


const pp::Character*
test(const pp::Character*  a, const char*  b, size_t  n)
{
    while(n)
    {
      auto  byte_number = pp::get_utf8_byte_number(b);

      auto  c = pp::to_char16(b,byte_number);

      b += byte_number;
      n -= byte_number;

        if(a->unicode != c)
        {
          return nullptr;
        }


      ++a;
    }


  return a;
}


size_t
compare_string(const pp::Character*&  p, const std::string&  s, bool  id, Node&  node)
{
  auto  res = test(p,s.data(),s.size());

    if(res)
    {
        if(id)
        {
            if(isalnum(res->unicode) ||
               (res->unicode == '_'))
            {
              return 0;
            }
        }


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
compare(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const
{
  flags &= noskip_flag;

    switch(kind)
    {
      case(ElementKind::null):
        break;
      case(ElementKind::string):
        return compare_string(p,*get_string(),false,node);
        break;
      case(ElementKind::identifier):
        return compare_string(p,*get_string(),true,node);
        break;
      case(ElementKind::reference):
        return parser.enter(get_string()->data(),p,node);
        break;
      case(ElementKind::group           ): return data.grp->compare(parser,p,node,flags                            );break;
      case(ElementKind::option_group    ): return data.grp->compare(parser,p,node,flags|option_flag                );break;
      case(ElementKind::repetition_group): return data.grp->compare(parser,p,node,flags|option_flag|repetition_flag);break;
      default:
        printf("Element clear error");
    }


  return false;
}


}




