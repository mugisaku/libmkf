#include"mkf_book.hpp"
#include"mkf_parsecontext.hpp"
#include"libcmplr/cmplr_globalscope.hpp"
#include"libcmplr/cmplr_function.hpp"
#include"libcmplr/cmplr_block.hpp"
#include"assvm_program.hpp"
#include"assvm_context.hpp"
#include<cstdlib>


using namespace assvm;


GlobalScope
get_global(const char*  txt_path, FILE*  f)
{
  mkf::Book  book;

  pp::Stream  def_s;
  pp::Stream  txt_s;

  def_s.reset(pp::FilePath("assvmdef.hi.txt"));
  txt_s.reset(pp::FilePath(txt_path));

  pp::String  def_str(def_s);
  pp::String  txt_str(txt_s);

    if(!book.make(def_str))
    {
      report;
      throw;
    }


//  book.print();

  GlobalScope  g;

  mkf::ParseContext  ctx(book);

  auto  root = ctx(txt_str);

    if(!root)
    {
      report;

      throw;
    }


  root->print(f);

  auto  cur = root->make_cursor();

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "global_scope")
        {
          g.read(nd);
        }


      cur.advance();
    }


  return std::move(g);
}


void
execute(std::string&&  s, bool  disp, const FileSet*  fs)
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


//  book.print();

  mkf::ParseContext  ctx(book);

  auto  root = ctx(txt_str);

    if(root)
    {
//      root->print(f);

      assvm::Program  prog(*root);

      auto  mem = new assvm::Memory;

      assvm::Context  ctx(prog,*mem,fs);

      ctx.set_flag(assvm::Context::enable_halt_flag);

        if(disp)
        {
          ctx.set_flag(assvm::Context::display_flag);
        }


        while(!ctx.test_flag(assvm::Context::halted_flag))
        {
          ctx.step();
        }
    }
}


int
main(int  argc, char**  argv)
{
  FileSet  fs;

  fs.out = fopen("__assvm_out.txt","wb");
  fs.err = stdout;
//  fs.err = fopen("__assvm_err.txt","wb");

    if(--argc)
    {
      std::string  s;

      bool  disp_flag = false;

      ++argv;

        while(argc--)
        {
          const char*  opt = *argv++;

            if(*opt == '-')
            {
              disp_flag = true;
            }

          else
            {
              auto  f = fopen("__tree.txt","wb");

              auto  g = get_global(opt,f);

              g.print(fs.out);

              s = g.compile();

              fclose(f);
            }
        }


        for(auto  c: s)
        {
          fputc(c,fs.out);
        }


      fflush(fs.out);

      execute(std::move(s),disp_flag,&fs);
    }


  fs.close_all();

  return 0;
}




