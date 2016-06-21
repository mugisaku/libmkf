#include"mkf_cursor.hpp"




namespace mkf{


Cursor::
Cursor(const Node&  start):
node(&start),
child_index(0){}




bool
Cursor::
test_ended() const
{
  return child_index >= node->children.size();
}


const Node&
Cursor::
operator*() const
{
  return *node;
}


bool
Cursor::
advance()
{
  const auto&  n = node->children.size();

    if(child_index < n)
    {
      ++child_index;
    }


  return(child_index < n);
}


const Node&
Cursor::
get() const
{
  return *node->children[child_index];
}




}



