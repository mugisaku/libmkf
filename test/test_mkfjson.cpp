#include"mkf_book.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_parsecontext.hpp"
#include"json.hpp"
#include<cstdio>


using namespace mkf;


Node*
get_tree(const Book&  book, int  n, bool  check=false)
{
  auto  j = json::create_random_object(n);

  auto  f = tmpfile();

    if(f)
    {
      j.print(true,0,f);

      rewind(f);

      pp::Stream  s(f);

      pp::String  txt(s);

      fclose(f);


      ParseContext  ctx(book);

      auto  tree = ctx(txt);

        if(tree)
        {
            if(check)
            {
              printf("check\n");

//              tree->print();
//              printf("\n");

              mkf::Cursor  cur(*tree);

                while(!cur.test_ended())
                {
                  auto&  nd = cur.get();

                    if(nd == "json")
                    {
                      auto  e = json::read_json(nd);

                      bool  res = (e == j);
j.print();
e.print();
                      printf("checktest: %s\n",res? "OK":"NG");


                      break;
                    }


                  cur.advance();
                }
            }
        }


      return ctx.release_root();
    }


  return nullptr;
}




int
main(int  argc, char**  argv)
{
  Book  book;

  pp::Stream  s;

  s.reset(pp::FilePath("json.def.txt"));


  pp::String  def(s);

  book.make(def);

//  book.print();

  constexpr int  n = 6;

  int  count = 0;

    for(int  i = 0;  i < n;  ++i)
    {
      auto  tree = get_tree(book,6,false);

        if(tree)
        {
          ++count;

          printf("OK\n");

          delete tree;

          continue;
        }


      printf("NG\n");
    }


  printf("%4d/%4d passed.\n",count,n);

  delete get_tree(book,4,true);

  return 0;
}




