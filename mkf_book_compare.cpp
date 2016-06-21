#include"mkf_book.hpp"




namespace mkf{


namespace{


bool
compare_ctype(CompareContext&  ctx, CType  type, const char*  defname)
{
    if(test_ctype_code(*ctx.p0,type))
    {
      int  c = *ctx.p0++;

        if(ctx.nd)
        {
          ctx.nd->append(new Node(defname,c));
        }


      return true;
    }


  return false;
}


bool
compare_ascii(CompareContext&  ctx, int  c, const char*  defname)
{
    if(c == *ctx.p0)
    {
      ++ctx.p0;

        if(ctx.nd)
        {
          ctx.nd->append(new Node(defname,c));
        }


      return true;
    }


  return false;
}


}


bool
Book::
compare_definition_reference(CompareContext&  ctx, const Definition&  def) const
{
  auto  p = ctx.p0;

    if(!*p)
    {
      return false;
    }


  CompareContext  subctx(p,ctx.p1,new Node(def.get_identifier().data()));

    if(compare(subctx,def))
    {
      ctx.p0 = p;

      ctx.nd->append(subctx.nd);


      return true;
    }


  delete subctx.nd;

  return false;
}


bool
Book::
compare0(CompareContext&  ctx, const Element&  elm, bool  solid_flag) const
{
  auto  base = ctx.p0;

    if(!solid_flag)
    {
      skip_space(ctx.p0);
    }


  auto  res = compare1(ctx,elm);

    if(!res)
    {
      ctx.p0 = base;
    }

  else
    if(!solid_flag)
    {
      skip_space(ctx.p0);
    }


  return res;
}


bool
Book::
compare1(CompareContext&  ctx, const Element&  elm) const
{
    switch(elm.get_kind())
    {
      case(ElementKind::null):
        report;
        break;
      case(ElementKind::character):
          if(elm.get_character() == *ctx.p0)
          {
            int  c = *ctx.p0++;

              if(ctx.nd)
              {
                ctx.nd->append(new Node("<CHARACTER>",c));
              }


            return true;
          }
        break;
      case(ElementKind::string):
          if(std::strncmp(elm.get_string(),ctx.p0,elm.get_length()) == 0)
          {
            int  c = *ctx.p0                    ;
                      ctx.p0 += elm.get_length();

              if(ctx.nd)
              {
                ctx.nd->append(new Node("<STRING>",' '));
              }


            return true;
          }
        break;
      case(ElementKind::identifier):
        {
          auto  defname = elm.get_string();

          auto  ctype = get_ctype(defname);

            if(ctype != CType::null)
            {
              return compare_ctype(ctx,ctype,defname);
            }


          auto  c = find_ascii_code(defname);

            if(c)
            {
              return compare_ascii(ctx,c,defname);
            }


          auto  def = find(elm.get_string());

            if(def)
            {
              return compare_definition_reference(ctx,*def);
            }

          else
            {
              report;
              printf("definition [%s] is not found.\n",defname);
              printf("%s.\n",ctx.p0);
            }
        }
        break;
      default:
        report;
    }


  return false;
}


bool
Book::
compare(CompareContext&  ctx, const Definition&  def) const
{
    if(def.test_selective())
    {
      return compare_for_any(ctx,def);
    }


  return compare_for_all(ctx,def);
}




bool
Book::
compare_for_any(CompareContext&  ctx, const Definition&  def) const
{
    for(auto&  elm: def.get_list())
    {
        if(!*ctx.p0 || (ctx.p0 >= ctx.p1))
        {
          return false;
        }


        if(compare0(ctx,elm,def.test_solid_flag()))
        {
            if(elm.test_repeat())
            {
                for(;;)
                {
                    if(!compare0(ctx,elm,def.test_solid_flag()))
                    {
                      break;
                    }
                }
            }


          return true;
        }
    }


  return false;
}


bool
Book::
compare_for_all(CompareContext&  ctx, const Definition&  def) const
{
    for(auto&  elm: def.get_list())
    {
        if(!*ctx.p0 || (ctx.p0 >= ctx.p1))
        {
          return true;
        }


        if(!compare0(ctx,elm,def.test_solid_flag()))
        {
            if(elm.test_omittable())
            {
              continue;
            }


          return false;
        }


          if(elm.test_repeat())
          {
              for(;;)
              {
                  if(!compare0(ctx,elm,def.test_solid_flag()))
                  {
                    break;
                  }
              }
          }
    }


  return true;
}



}




