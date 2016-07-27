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
  auto  s = new std::string;

    while(isalnum(p->unicode) || (p->unicode == '_'))
    {
      s->append(pp::UTF8Chunk(p++->unicode).codes);
    }


  return Element(Identifier(s));
}


Element
scan_string(charptr&  p)
{
  auto  s = new std::string;

    for(;;)
    {
      int  c = p->unicode;

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
          ++p;

          c = get_code(p->unicode);
        }


      s->append(pp::UTF8Chunk(c).codes);

      ++p;
    }


  return Element(s);
}


Element
scan_element(charptr&  p)
{
  p.skip_space();

  Element  el;

    switch(p->unicode)
    {
      case('\"'): el = scan_string(++p);break;
      case('[' ): el.reset(    OptionGroup(new Group(++p,']')));break;
      case('{' ): el.reset(RepetitionGroup(new Group(++p,'}')));break;
      case('(' ): el.reset(               (new Group(++p,')')));break;
      default:
          if(isalnum(p->unicode) || (p->unicode == '_'))
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

    if(c.unicode == close)
    {
      separator = 0;

      return;
    }


  separator = c.unicode;

  const pp::Character*  last = nullptr;

    for(;;)
    {
      push(scan_element(p));

      c = *p++;

        if(c.unicode == close)
        {
          break;
        }

      else
        if(!c.unicode)
        {
          discontinue(ErrorKind::null,p,"\';\'で閉じられていません");
        }

      else
        if(c.unicode != separator)
        {
          discontinue(ErrorKind::null,p,"複数のセパレーターが混在しています");
        }


        if(last == &*p)
        {
          discontinue(ErrorKind::null,p,"ループしました");
        }


      last = &*p;
    }
}




}




