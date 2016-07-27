#ifndef PP_POSITION_HPP_INCLUDED
#define PP_POSITION_HPP_INCLUDED


#include<cstdint>
#include<cstdio>


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pp{


struct
Position
{
  uint16_t    line_number;
  uint16_t  column_number;

  Position(uint16_t  ln=0, uint16_t  cn=0);

  void  reset(uint16_t  ln=0, uint16_t  cn=0);

  void  print(FILE*  f=stdout) const;

};


}


#endif




