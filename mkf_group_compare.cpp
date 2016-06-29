#include"mkf_group.hpp"
#include"mkf_parsecontext.hpp"
#include"mkf_print.hpp"
#include<cstdlib>




namespace mkf{




bool
Group::
compare_element(ParseContext&  parser, charptr&  p, Node&  node, const Element&  elm) const
{
  auto  start = p;

    if(!elm.compare(parser,p,node))
    {
      p = start;

      p.skip_space();

//        if(p)
        {
            if(!elm.compare(parser,p,node))
            {
              parser.push_error(p);

              p = start;

              return false;
            }
        }
    }


  return true;
}


bool
Group::
compare_for_anyone(ParseContext&  parser, charptr&  p, Node&  node) const
{
    for(auto&  elm: *this)
    {
        if(!p)
        {
          return false;
        }


        if(compare_element(parser,p,node,elm))
        {
          return true;
        }
    }


  return false;
}


bool
Group::
compare_for_all(ParseContext&  parser, charptr&  p, Node&  node) const
{
    for(auto&  elm: *this)
    {
        if(!p)
        {
          return false;
        }


        if(!compare_element(parser,p,node,elm))
        {
          return false;
        }
    }


  return true;
}


bool
Group::
compare(ParseContext&  parser, charptr&  p, Node&  node) const
{
    if(test_alternation()){return compare_for_anyone(parser,p,node);}
  else                    {return compare_for_all(   parser,p,node);}


  return false;
}


bool
Group::
compare(ParseContext&  parser, charptr&  p, Node&  node, int  flags) const
{
    if(!compare(parser,p,node))
    {
      return(flags&option_flag);
    }

  else
    {
        if(flags&repetition_flag)
        {
            for(;;)
            {
                if(!compare(parser,p,node))
                {
                  break;
                }
            }

        }
    }


  return true;
}




}




