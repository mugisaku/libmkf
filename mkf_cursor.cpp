#include"mkf_cursor.hpp"




namespace mkf{


Cursor::
Cursor(const Node&  start):
iter(start.children.begin())
{}




bool
Cursor::
test_ended() const
{
  return !static_cast<bool>(iter);
}


const Node&
Cursor::
operator*() const
{
  return **iter;
}


bool
Cursor::
advance()
{
    if(iter)
    {
      ++iter;
    }


  return !static_cast<bool>(iter);
}


const Node&
Cursor::
get() const
{
  return **iter;
}




}



