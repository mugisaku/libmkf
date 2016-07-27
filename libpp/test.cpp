#include"pp.hpp"




using namespace pp;


int
main(int  argc, char**  argv)
{
    if(argc == 2)
    {
        try
        {
          Stream  s;

          s.reset(FilePath(argv[1]));

          String  str(s);

          str.print(stdout);

          printf("\n");
        }


        catch(...)
        {
          return -1;
        }
    }


  return 0;
}




