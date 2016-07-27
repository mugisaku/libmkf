#include"pp.hpp"
#include<cstdio>




namespace pp{


namespace{
std::string
read_std_string_until(Stream&  s, char  c)
{
  std::string  buf;

  auto  base = s;

    for(;;)
    {
      auto  cc = s.get_char16();

        if(!cc)
        {
          printf("\'%c\'で閉じられていません\n",c);

          throw ErrorOnProcessStream(base);
        }

      else
        if(cc == '\n')
        {
          printf("文字列の途中で改行されました\n");

          throw ErrorOnProcessStream(base);
        }

      else
        if(cc == '\\')
        {
          buf.push_back(cc);
          buf.push_back(s.get_char16());
        }

      else
        if(cc == c)
        {
          break;
        }

      else
        {
          buf.push_back(cc);
        }
    }


  return std::move(buf);
}


void
read_character_until(String&  str, Stream&  s, char  c)
{
  auto  base = s;

  auto  id_index = s.get_id_index();

    for(;;)
    {
      auto  pos = s.get_position();

      auto  cc = s.get_char16();

        if(!cc)
        {
          printf("\'%c\'で閉じられていません\n",c);

          throw ErrorOnProcessStream(base);
        }

      else
        if(cc == '\\')
        {
          str.emplace_back(pos,id_index,cc);

          pos = s.get_position();

          cc = s.get_char16();

          str.emplace_back(pos,id_index,cc);
        }

      else
        if(cc == '\n')
        {
          printf("文字列の途中で改行されました\n");

          throw ErrorOnProcessStream(base);
        }

      else
        if(cc == c)
        {
          break;
        }

      else
        {
          str.emplace_back(pos,id_index,cc);
        }
    }
}


bool
try_read_range(String&  str, Stream&  s, char  c)
{
    if(!s.test_char(c))
    {
      return false;
    }


  auto  id_index = s.get_id_index();

  str.emplace_back(s.get_position(),id_index,c);

  s.advance();

  read_character_until(str,s,c);

  str.emplace_back(s.get_position(),id_index,c);

  return true;
}


void  include(String&  dst, Stream&  s, Index  parent_id_index, bool  once);


bool
try_read_include(String&  str, Stream&  s)
{
    if(!s.try_read("#include\""))
    {
      return false;
    }


  std::string  buf = read_std_string_until(s,'\"');

  Stream  subs(FilePath(buf.data()));

  include(str,subs,s.get_id_index(),false);

  return true;
}


bool
try_read_include_once(String&  str, Stream&  s)
{
    if(!s.try_read("#include_once\""))
    {
      return false;
    }


  std::string  buf = read_std_string_until(s,'\"');

  Stream  subs(FilePath(buf.data()));

    try
    {
      include(str,subs,s.get_id_index(),true);
    }


    catch(const ErrorOnIncludeOnce&  e)
    {
      printf("include_onceしようとしたファイル\"%s\"にIDがありません\n",buf.data());


      auto  text = s.get_text();

        if(text)
        {
          printf("%s\n",text->id.data());
        }


      s.print();

      printf("\n");

      throw;
    }


  return true;
}


bool
try_read_line_comment(Stream&  s)
{
    if(!s.try_read("//"))
    {
      return false;
    }


    for(;;)
    {
      auto  c = s.get_char16();

        if((c == '\0') ||
           (c == '\n'))
        {
          break;
        }
    }


  return true;
}


bool
try_read_range_comment(Stream&  s)
{
  auto  base = s;

    if(!s.try_read("/*"))
    {
      return false;
    }


    while(!s.try_read("*/"))
    {
        if(!s.test())
        {
          printf("コメントが閉じられていません\n");

          throw ErrorOnProcessStream(base);
        }


      s.advance();
    }


  return true;
}


void
include(String&  dst, Stream&  s, Index  parent_id_index, bool  once)
{
  const Stream  tmps = s;

    if((s.get_id_index() != nullidx) &&
       ( parent_id_index != nullidx))
    {
        if(s.get_id_index() == parent_id_index)
        {
          printf("再帰読み込みが発生しました\n");

          throw ErrorOnInclude();
        }
    }


    if(once)
    {
        if(s.get_id_index() == nullidx)
        {
          throw ErrorOnIncludeOnce();
        }


      auto  text = s.get_text();

        if(text)
        {
            if(text->include_count)
            {
              return;
            }
        }
    }


    try
    {
        for(;;)
        {
               if(try_read_range(       dst,s,'\"')){}
          else if(try_read_range(       dst,s,'\'')){}
          else if(try_read_include(     dst,s)){}
          else if(try_read_include_once(dst,s)){}
          else if(try_read_range_comment(   s)){}
          else if(try_read_line_comment(    s)){}
          else
            {
              auto  pos = s.get_position();
              auto    c = s.get_char16();

                if(!c)
                {
                  break;
                }


              dst.emplace_back(pos,s.get_id_index(),c);
            }
        }
    }


    catch(ErrorOnProcessStream&  e)
    {
        if(!e.printed)
        {
          auto  text = e.stream.get_text();

            if(text)
            {
              printf("%s\n",text->id.data());
            }


          e.stream.print();

          printf("\n");

          e.printed = 1;
        }


      throw;
    }


    catch(const ErrorOnInclude&  e)
    {
      auto  text = s.get_text();

        if(text)
        {
          printf("%s\n",text->id.data());
        }


      tmps.print();

      printf("\n");

      throw;
    }
}
}




String::
String()
{
}


String::
String(Stream&  s)
{
  include(*this,s,nullidx,false);
}


std::string
String::
to_stdstring() const
{
  std::string  buf;

    for(auto&  c: *this)
    {
      buf.append(UTF8Chunk(c.unicode).codes);
    }


  return std::move(buf);
}


void
String::
print(FILE*  f, bool  verbose) const
{
    for(auto&  c: *this)
    {
      c.print(f,verbose);

        if(verbose)
        {
          fprintf(f,"\n");
        }
    }
}


}




