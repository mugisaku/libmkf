#include"mkf_element.hpp"
#include"mkf_group.hpp"
#include"mkf_definition.hpp"
#include"mkf_unicode.hpp"
#include"mkf_ctype.hpp"
#include"mkf_parsecontext.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




namespace mkf{




bool
Element::
compare(ParseContext&  parser, charptr&  p, Node&  node) const
{
    switch(kind)
    {
      case(ElementKind::null):
        break;
      case(ElementKind::string):
        return p.compare_string(*get_string(),node);
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




