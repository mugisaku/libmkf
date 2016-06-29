#include"mkf_definition.hpp"
#include"mkf_ctype.hpp"
#include"mkf_tmp_string.hpp"




namespace mkf{




namespace{
int
get_code(int  c)
{
    switch(c)
    {
      case('0' ): c = '\0';break;
      case('n' ): c = '\n';break;
      case('t' ): c = '\t';break;
      case('r' ): c = '\r';break;
      case('f' ): c = '\f';break;
      case('b' ): c = '\b';break;
      case('\\'): c = '\\';break;
      case('\''): c = '\'';break;
      case('\"'): c = '\"';break;
    }


  return c;
}


Element
scan_identifier(charptr&  p)
{
  tmp_string<>  s;

    while(isalnum(*p) || (*p == '_'))
    {
      s.push(*p++);
    }


  return Element(Identifier(s.data()));
}


Element
scan_string(charptr&  p)
{
  tmp_string<>  s;

    for(;;)
    {
      int  c = *p;

        if(!c)
        {
          discontinue(ErrorKind::null,p,"文字列が閉じられていません");

          break;
        }

      else
        if(c == '\"')
        {
          ++p;

          break;
        }

      else
        if(c == '\\')
        {
          c = get_code(*++p);
        }


      s.push(c);

      ++p;
    }


  return Element(s.data());
}


Element
scan_element(charptr&  p)
{
  p.skip_space();

  Element  el;

    switch(*p)
    {
      case('\"'): el = scan_string(++p);break;
      case('[' ): el.reset(    OptionGroup(new Group(++p,']')));break;
      case('{' ): el.reset(RepetitionGroup(new Group(++p,'}')));break;
      case('(' ): el.reset(               (new Group(++p,')')));break;
      default:
          if(isalnum(*p) || (*p == '_'))
          {
            el = scan_identifier(p);
          }

        else
          {
            discontinue(ErrorKind::null,p,"identifierに使えない文字です");
          }
    }


  p.skip_space();

  return std::move(el);
}


}




void
Group::
scan(charptr&  p, int  close)
{
  push(scan_element(p));

  auto  c = *p++;

    if(c == close)
    {
      separator = 0;

      return;
    }


  separator = c;

  const char*  last = nullptr;

    for(;;)
    {
      push(scan_element(p));

      c = *p++;

        if(c == close)
        {
          break;
        }

      else
        if(!c)
        {
          discontinue(ErrorKind::null,p,"\';\'で閉じられていません");
        }

      else
        if(c != separator)
        {
          discontinue(ErrorKind::null,p,"複数のセパレーターが混在しています");
        }


        if(last == p)
        {
          discontinue(ErrorKind::null,p,"ループしました");
        }


      last = p;
    }
}




}




