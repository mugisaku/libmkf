#include"mkf_book.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_parsecontext.hpp"
#include<cstdio>


using namespace mkf;


int
main(int  argc, char**  argv)
{
  Book  book;

    if(argc >= 2)
    {
      pp::Stream  s;

      s.reset(pp::FilePath(argv[1]));

      pp::String  def(s);

        if(!book.make(def))
        {
          return -1;
        }


      book.print();

      printf("\n\n");

        if(argc >= 3)
        {
          s.reset(pp::FilePath(argv[2]));

          pp::String  txt(s);

          ParseContext  ctx(book);

          auto  tree = ctx(txt);

            if(tree)
            {
              tree->print();
            }


          printf("\n\n");
        }
    }

  else
    {
      printf("使い方:\nprint_mkf 定義ファイルパス 解析対象ファイルパス\n");
    }


  return 0;
}




