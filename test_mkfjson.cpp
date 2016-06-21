#include"mkf_book.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_file.hpp"
#include"json.hpp"
#include<cstdio>


using namespace mkf;


int
main(int  argc, char**  argv)
{
  Book  book;

  auto  def = load_file("json.def.txt");

  book.make(def);

  constexpr int  n = 256;

  int  count = 0;

    for(int  i = 0;  i < n;  ++i)
    {
      auto  j = json::Element::create_random_object(8);

      auto  f = tmpfile();

      printf("[%4d/%4d] ",i,n);

        if(f)
        {
          j.print(true,0,f);

          rewind(f);

          auto  s = to_string(f);

          fclose(f);


          auto  tree = book.parse(s);

            if(tree)
            {
              ++count;

              printf("OK\n");

              continue;
            }
        }


      printf("NG\n");
    }


  printf("%4d/%4d passed.\n",count,n);

  return 0;
}




