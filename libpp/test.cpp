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

  else
    {
      String  s(u"12343210");

      const Character*  endptr = nullptr;

      auto  v = to_uint(s.data(),&endptr,16);

        if(endptr && *endptr)
        {
          printf("end point = ");

          print(endptr);

          printf("\n");
        }


      printf("0x%X\n",v);
      printf("%u\n",v);

      printf("0b");

        while(v)
        {
          printf("%c",(v&0x80000000)? '1':'0');

          v <<= 1;
        }


      printf("\n");
    }


  return 0;
}




