#include"mkf_file.hpp"




void
save_file(const char*  path, const std::string&  s)
{
  auto  f = fopen(path,"wb");

    if(f)
    {
        for(auto  c: s)
        {
          fputc(c,f);
        }


      fclose(f);
    }
}


std::string
load_file(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
      auto  s = to_string(f);

      fclose(f);

      return std::move(s);
    }


  return std::string();
}


std::string
to_string(FILE*  f)
{
  std::string  s;

    for(;;)
    {
      const int  c = fgetc(f);

        if(feof(f) || ferror(f))
        {
          break;
        }


      s.push_back(c);
    }


  return std::move(s);
}


bool
compare_file(FILE*  a, FILE*  b)
{
    for(;;)
    {
      int  ac = fgetc(a);
      int  bc = fgetc(b);

        if(feof(a) && !feof(b))
        {
          break;
        }


        if(!feof(a) && feof(b))
        {
          break;
        }


        if(feof(a) && feof(b))
        {
          return true;
        }


        if(ac != bc)
        {
          break;
        }
    }


  return false;
}




