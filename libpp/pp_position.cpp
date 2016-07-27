#include"pp_position.hpp"
#include<cstdio>




namespace pp{




Position::
Position(uint16_t  ln, uint16_t  cn):
line_number(ln),
column_number(cn)
{
}




void
Position::
reset(uint16_t  ln, uint16_t  cn)
{
    line_number = ln;
  column_number = cn;
}


void
Position::
print(FILE*  f) const
{
  fprintf(f,"行:%4d\n"
            "列:%4d\n",line_number+1,column_number+1);
}


}




