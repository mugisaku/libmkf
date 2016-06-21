#include"mkf_book.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_file.hpp"
#include<cstdio>


using namespace mkf;


int
main(int  argc, char**  argv)
{
  Book  book;

  auto  a = tmpfile();
  auto  b = tmpfile();


  auto  def = load_file("mkffmt.def.txt");

  book.make(def);

  book.print();

  printf("\n\n");


  auto  tree = book.parse(def);

    if(tree)
    {
      tree->print();
      tree->print(a);


      printf("\n\n\n\n構文木からブックを作成します\n");

      Book  second_book;

      second_book.make(*tree);

      second_book.print();

      printf("\n\n\n\nブックを使って新しい構文木を作成します\n");

      auto  second_tree = second_book.parse(def);

        if(second_tree)
        {
          second_tree->print();
          second_tree->print(b);


          rewind(a);
          rewind(b);

          printf("%s\n",compare_file(a,b)? "OK":"NG");
        }
    }


  return 0;
}




