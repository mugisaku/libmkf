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
  int  n = 5;

    if(argc == 2)
    {
      n = strtol(argv[1],nullptr,10);
    }


  auto  f = fopen("sample.json","wb");

    if(f)
    {
      auto  elm = json::create_random_object(n);

      elm.print(true,0,f);

      fclose(f);
    }


  return 0;
}




