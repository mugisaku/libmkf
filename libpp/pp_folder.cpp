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
  Index  i;

    if(id.size())
    {
      i = 0;

        for(auto  ptr: table)
        {
            if(ptr->id == id)
            {
              ptr->include_count += 1;

              return i+1;
            }


          ++i;
        }
    }

  else
    {
      i = table.size();
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


const char*
get_line_pointer(Character  c)
{
  auto  text = get_text(c.id_index);

    if(text)
    {
      auto  p = text->content.data();

      int  n = c.position.line_number;

        while(n)
        {
          auto  c = *p++;

            switch(c)
            {
              case('\n'): --n;break;
              case('\0'): return nullptr;
            }
        }


      return p;
    }


  return nullptr;
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


void
print_table()
{
  int  i = 1;

    for(auto  ptr: table)
    {
      printf("%4d %s{\n%s\n}\n\n",i++,ptr->id.data(),ptr->content.data());
    }
}




}




