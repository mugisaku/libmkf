#include"pp_stream.hpp"
#include"pp_unicode.hpp"
#include"pp_folder.hpp"
#include<cstdio>
#include<cstring>




namespace pp{




Stream::
Stream():
pointer(nullptr),
id_index(nullidx)
{
}


Stream::
Stream(std::string&&  source_)
{
  reset(std::move(source_));
}


Stream::
Stream(const FilePath&  path)
{
  reset(path);
}


Stream::
Stream(FILE*  f)
{
  reset(f);
}




void
Stream::
reset(std::string&&  source_)
{
  position.reset();

  source = std::move(source_);

  pointer = source.data();

  change_id_index(push_text(read_id(),source));
}


void
Stream::
reset(const FilePath&  path)
{
  auto  f = fopen(path.s,"rb");

    if(!f)
    {
      printf("%sを開けませんでした\n",path.s);

      throw ErrorOnOpenFile();
    }


    try
    {
      reset(f);
    }


    catch(const ErrorOnReadFile&  e)
    {
      fclose(f);

      printf("ファイル\"%s\"を読み込めませんでした\n",path.s);

      throw;
    }


  fclose(f);
}




void
Stream::
reset(FILE*  f)
{
  std::string  buf;

    for(;;)
    {
      auto  c = fgetc(f);

        if(ferror(f))
        {
          throw ErrorOnReadFile();
        }


        if(feof(f))
        {
          break;
        }


      buf.push_back(c);
    }


  reset(std::move(buf));
}


std::string
Stream::
read_id()
{
  std::string  id;

    if(try_read("#fileid\""))
    {
      auto  base = *this;

        for(;;)
        {
          auto  c = get_char16();

            if(!c)
            {
              printf("\'\"\'で閉じられていません\n");

              throw ErrorOnProcessStream(base);
            }

          else
            if(c == '\n')
            {
              printf("途中で改行されました\n");

              throw ErrorOnProcessStream(*this);
            }

          else
            if(c == '\"')
            {
              break;
            }


          id.push_back(c);
        }
    }


  return std::move(id);
}


Index  Stream::get_id_index() const{return id_index;}
void  Stream::change_id_index(Index  i){id_index = i;}


const Text*
Stream::
get_text() const
{
  return pp::get_text(id_index);
}


bool
Stream::
test() const
{
  return(*pointer);
}


bool
Stream::
test_char(char  c) const
{
  return(*pointer == c);
}


char16_t
Stream::
get_char16()
{
    if(!*pointer)
    {
      return 0;
    }


  auto  byte_number = get_utf8_byte_number(pointer);

  char16_t  c = to_char16(pointer,byte_number);

  pointer += byte_number;

    if(c == '\n')
    {
        if(position.line_number >= 0xFFFF)
        {
          printf("行数が上限を越えましn");

          throw ErrorOnProcessStream(*this);
        }


        position.line_number += 1;
      position.column_number  = 0;
    }

  else
    {
        if(position.column_number >= 0xFFFF)
        {
          printf("桁数が上限を越えましn");

          throw ErrorOnProcessStream(*this);
        }


      position.column_number += 1;
    }


  return c;
}


Position
Stream::
get_position() const
{
  return position;
}


void
Stream::
advance(int  n)
{
    while(n--)
    {
      get_char16();
    }
}


bool
Stream::
try_read(const char*  s)
{
  auto  l = std::strlen(s);

    if(strncmp(pointer,s,l) == 0)
    {
      const char*  end = pointer+l;

        while(pointer != end)
        {
          get_char16();
        }


      return true;
    }


  return false;
}


void
Stream::
print(int  line_length) const
{
  position.print();

  auto  p = pointer-position.column_number;

    for(;;)
    {
      auto  c = *p++;

        if(!c || (c == '\n'))
        {
          printf("\n");

          break;
        }


      printf("%c",c);
    }


    for(int  n = 0;  n < position.column_number;  ++n)
    {
      printf(" ");
    }


    while(line_length--)
    {
      printf("~");
    }
}


}




