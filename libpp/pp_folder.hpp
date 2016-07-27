#ifndef PP_FOLDER_HPP_INCLUDED
#define PP_FOLDER_HPP_INCLUDED


#include<string>
#include"pp_character.hpp"



namespace pp{


struct
Text
{
  std::string       id;
  std::string  content;

  unsigned int  include_count;

};


Index  push_text(std::string&&  id, const std::string&  content);

const Text*  get_text(Index  i);

void  clear_table();


}




#endif




