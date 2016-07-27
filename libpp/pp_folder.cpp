#include"pp_folder.hpp"
#include<vector>




namespace pp{


namespace{


std::vector<Text*>
table;


}


Index
push_text(std::string&&  id, const std::string&  content)
{
  Index  i = 0;

    for(auto  ptr: table)
    {
        if(ptr->id == id)
        {
          ptr->include_count += 1;

          return i+1;
        }


      ++i;
    }


  auto  txt = new Text;

  txt->id            = std::move(id);
  txt->content       = content;
  txt->include_count = 0;

  table.emplace_back(txt);

  return i+1;
}


const Text*
get_text(Index  i)
{
    if(!i)
    {
      return nullptr;
    }


  return table[i-1];
}


void
clear_table()
{
    for(auto  ptr: table)
    {
      delete ptr;
    }


  table.clear();
}


}




