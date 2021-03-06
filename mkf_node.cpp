#include"mkf_node.hpp"
#include"libpp/pp.hpp"
#include<cstring>




namespace mkf{


Node::
Node(const char*  defname_, pp::Character  character_):
defname(defname_),
character(character_)
{
}


Node::
Node(Node&&  rhs) noexcept
{
  *this = std::move(rhs);
}


Node::
~Node()
{
  clear();
}




bool
Node::
operator==(const char*  name) const
{
  return std::strcmp(defname,name) == 0;
}


Node&
Node::
operator=(Node&&  rhs)
{
  clear();

  defname = rhs.defname;

  character = rhs.character;

  children = std::move(rhs.children);
}


void
Node::
clear()
{
  defname = "";

  character = pp::Character();

    for(auto&  nd: children)
    {
      delete nd;
    }


  children.clear();
}


void
Node::
append(Node*  child)
{
    if(child)
    {
      children.push(child);
    }
}


void
Node::
collect_characters(pp::String&  s) const
{
    if(children.empty())
    {
      s.push_back(character);
    }

  else
    {
        for(auto  child: children)
        {
          child->collect_characters(s);
        }
    }
}


void
Node::
collect_characters(std::string&  s) const
{
    if(children.empty())
    {
      s.append(pp::UTF8Chunk(character.unicode).codes);
    }

  else
    {
        for(auto  child: children)
        {
          child->collect_characters(s);
        }
    }
}


Cursor
Node::
make_cursor() const
{
  return Cursor(*this);
}


void
Node::
print(FILE*  f) const
{
  Printer  pr(0,f);

  print(pr);
}


void
Node::
print(Printer&  pr) const
{
    if(children.empty())
    {
      pr.printf("%s = \'%s\'",defname? defname:"<UNKNOWN>",pp::UTF8Chunk(character.unicode).codes);
    }

  else
    {
      pr.printf("%s{\n",defname);

      ++pr;

        for(auto  child: children)
        {
          child->print(pr);

          pr.putc('\n',true);
        }


      --pr;

      pr.printf("}\n");
    }
}


}



