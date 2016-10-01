#include"libcmplr/typesystem_element.hpp"
#include<cstdlib>




using namespace typesystem;


int
main(int  argc, char**  argv)
{
  --argc;
  ++argv;

  printf("\n\n");

    while(argc--)
    {
      auto  t = make_type(*argv++);

      t.print();

      printf(" size = %d\n",t.get_size());
    }


  char  buf[1024];

  auto  s = buf;
  auto  n = sizeof(buf);

  Struct  u("test_struct");

  u.append({I8Type(),"t3"});
  u.append({I32Type(),"t1"});
  u.append({I32Type(),"t1"});
  u.append({I8Type(),"t3"});
  u.append({CharType(),"t3"});
  u.append({I8Type(),"t3"});
  u.append({CharType(),"t3"});
  u.append({I8Type(),"t3"});
  u.append({I8Type(),"t3"});
  u.append({I8Type(),"t3"});
  u.append({I8Type(),"t3"});
  u.append({I8Type(),"t3"});

  u.snprint(s,n);

  printf("%s\n",buf);

  return 0;
}




