#include"mkf_group.hpp"
#include"mkf_parsecontext.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




namespace mkf{




bool
Group::
compare_element(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags, const Element&  elm) const
{
  auto  start = p;

    if(!elm.compare(parser,p,node,flags))
    {
      p = start;

        if(!(flags&noskip_flag))
        {
          pp::skip_spaces(p);

            if(p->unicode)
            {
                if(!elm.compare(parser,p,node,flags))
                {
                  parser.push_error(p);

                  p = start;
                }

              else
                {
                  return true;
                }
            }
        }


      return false;
    }


  return true;
}


namespace{
bool
compare_exclusion(Group::Iterator  it,
                  Group::Iterator  end,
                  ParseContext&  parser,
                  const pp::Character*  start_p,
                  const pp::Character*    end_p,
                  const pp::Character*&       p,
                  Node&  parent, Node&  node, int  flags)
{
  Node  tmpnode;

    while(++it != end)
    {
      p = start_p;

        if(it->compare(parser,p,tmpnode,flags))
        {
          parser.push_error(start_p);

          p = start_p;

          return false;
        }
    }


  p = end_p;

  

  parent.append(node.children.front());

  node.children.front() = nullptr;

  return true;
}
}


bool
Group::
compare_with_exclusion(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const
{
  auto  it = begin();
  auto   e =   end();

  auto  start_p = p;

  Node  tmpnode;

    if(it->compare(parser,p,tmpnode,flags))
    {
      auto  end_p = p;

      return compare_exclusion(it,e,parser,start_p,end_p,p,node,tmpnode,flags);
    }

  else
    if(!(flags&noskip_flag))
    {
      p = start_p;

      pp::skip_spaces(p);

      start_p = p;

        if(it->compare(parser,p,tmpnode,flags))
        {
          auto  end_p = p;

          return compare_exclusion(it,e,parser,start_p,end_p,p,node,tmpnode,flags);
        }
    }


  return false;
}


bool
Group::
compare_for_anyone(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const
{
    for(auto&  elm: *this)
    {
        if(compare_element(parser,p,node,flags,elm))
        {
          return true;
        }
    }


  return false;
}


bool
Group::
compare_for_all(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const
{
    for(auto&  elm: *this)
    {
        if(!compare_element(parser,p,node,flags,elm))
        {
          return false;
        }
    }


  return true;
}


bool
Group::
subcompare(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const
{
    if(test_alternation()){return compare_for_anyone(    parser,p,node,flags);}
    if(test_exclusion()  ){return compare_with_exclusion(parser,p,node,flags);}
  else                    {return compare_for_all(       parser,p,node,flags);}


  return false;
}


bool
Group::
compare(ParseContext&  parser, const pp::Character*&  p, Node&  node, int  flags) const
{
    if(!subcompare(parser,p,node,flags))
    {
      return(flags&option_flag);
    }

  else
    {
        if(flags&repetition_flag)
        {
            for(;;)
            {
                if(!subcompare(parser,p,node,flags))
                {
                  break;
                }
            }
        }
    }


  return true;
}




}




