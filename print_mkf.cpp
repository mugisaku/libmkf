#include"mkf_book.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_file.hpp"
#include<cstdio>


using namespace mkf;


int
main(int  argc, char**  argv)
{
    if(argc >= 2)
    {
      Book  book;

      auto  def = load_file(argv[1]);

      book.make(def);

      book.print();

        if(argc >= 3)
        {
          auto  txt = load_file(argv[2]);

          printf("\n\n");


          auto  tree = book.parse(txt);

            if(tree)
            {
              tree->print();
            }
        }


      printf("\n\n");
    }

  else
    {
      printf("使い方:\nprint_mkf 定義ファイルパス 解析対象ファイルパス\n");
    }


  return 0;
}




