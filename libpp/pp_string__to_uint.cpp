#include"pp.hpp"
#include<cstdio>




namespace pp{



namespace{


unsigned int
to_uint_16(const Character*  ptr, const Character**  endptr)
{
  unsigned int  v = 0;

    if(ptr->unicode == '0')
    {
      ++ptr;

        if((ptr->unicode == 'x') ||
           (ptr->unicode == 'X'))
        {
          ++ptr;
        }
    }


    for(;;)
    {
      int  t;

        switch(ptr->unicode)
        {
          case('0'): t = 0;break;
          case('1'): t = 1;break;
          case('2'): t = 2;break;
          case('3'): t = 3;break;
          case('4'): t = 4;break;
          case('5'): t = 5;break;
          case('6'): t = 6;break;
          case('7'): t = 7;break;
          case('8'): t = 8;break;
          case('9'): t = 9;break;
          case('a'):
          case('A'): t = 10;break;
          case('b'):
          case('B'): t = 11;break;
          case('c'):
          case('C'): t = 12;break;
          case('d'):
          case('D'): t = 13;break;
          case('e'):
          case('E'): t = 14;break;
          case('f'):
          case('F'): t = 15;break;
          default:
            if(endptr)
            {
              *endptr = ptr;
            }


          goto END;
        }


      ++ptr;

      v *= 16;
      v +=  t;
    }


END:
  return v;
}


unsigned int
to_uint_10(const Character*  ptr, const Character**  endptr)
{
  unsigned int  v = 0;

    if(ptr->unicode == '0')
    {
      goto FINISH;
    }


    for(;;)
    {
      int  t;

        switch(ptr->unicode)
        {
          case('0'): t = 0;break;
          case('1'): t = 1;break;
          case('2'): t = 2;break;
          case('3'): t = 3;break;
          case('4'): t = 4;break;
          case('5'): t = 5;break;
          case('6'): t = 6;break;
          case('7'): t = 7;break;
          case('8'): t = 8;break;
          case('9'): t = 9;break;
          default:
FINISH:
            if(endptr)
            {
              *endptr = ptr;
            }


          goto END;
        }


      ++ptr;

      v *= 10;
      v +=  t;
    }


END:
  return v;
}


unsigned int
to_uint_2(const Character*  ptr, const Character**  endptr)
{
  unsigned int  v = 0;

    if(ptr->unicode == '0')
    {
      ++ptr;

        if((ptr->unicode == 'b') ||
           (ptr->unicode == 'B'))
        {
          ++ptr;
        }
    }


    for(;;)
    {
        if(ptr->unicode == '0')
        {
          v <<= 1;

          ++ptr;
        }

      else
        if(ptr->unicode == '1')
        {
          v <<= 1;
          v  |= 1;

          ++ptr;
        }

      else
        {
           if(endptr)
           {
             *endptr = ptr;
           }


          break;
        }
    }


  return v;
}



}



unsigned int
to_uint(const Character*  ptr, const Character**  endptr, int  base)
{
    switch(base)
    {
      case( 2): return to_uint_2( ptr,endptr);
      case(16): return to_uint_16(ptr,endptr);
      case(10): return to_uint_10(ptr,endptr);
      default:
        printf("[pp::to_uint] %d進数には対応していません\n",base);
    }


  return 0;
}




}




