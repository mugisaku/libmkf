#include"mkf_book.hpp"
#include"mkf_parsecontext.hpp"
#include"assvm_program.hpp"
#include"assvm_context.hpp"
#include<cstdlib>




void
print(std::string&&  s)
{
  mkf::Book  book;

  pp::Stream  def_s;
  pp::Stream  txt_s;

  def_s.reset(pp::FilePath("assvmdef.mid.txt"));
  txt_s.reset(std::move(s));

  pp::String  def_str(def_s);
  pp::String  txt_str(txt_s);

    if(!book.make(def_str))
    {
      report;
      throw;
    }


  mkf::ParseContext  ctx(book);

  auto  root = ctx(txt_str);

    if(root)
    {
//      root->print();
      assvm::Program  prog(*root);

      prog.print();
    }
}


int
main(int  argc, char**  argv)
{
    if(--argc)
    {
      std::string  s;

      ++argv;

        while(argc--)
        {
          auto  f = fopen(*argv++,"rb");

            if(f)
            {
                for(;;)
                {
                  auto  c = fgetc(f);

                    if(feof(f))
                    {
                      break;
                    }


                  s.push_back(c);
                }


              fclose(f);
            }
        }


      print(std::move(s));
    }


  return 0;
}




