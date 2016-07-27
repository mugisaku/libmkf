#ifndef PP_CHARACTER_HPP_INCLUDED
#define PP_CHARACTER_HPP_INCLUDED


#include"pp_position.hpp"
#include<string>



namespace pp{


using Index = uint16_t;

constexpr uint16_t  nullidx = 0;


struct
Character
{
  Position  position;

  Index  id_index;

  char16_t  unicode;


  Character(Position  pos=Position(), Index  i=0, char16_t  c=0);

  operator bool() const;

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


}


#endif




