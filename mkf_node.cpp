#include"mkf_node.hpp"




namespace mkf{


Node::
Node(const char*  defname_, int  c):
parent(nullptr),
depth(0),
defname(defname_),
character(c)
{
}


Node::
Node(Node&&  rhs):
parent(rhs.parent),
depth(rhs.depth),
defname(rhs.defname),
character(rhs.character),
children(std::move(rhs.children))
{
}


Node::
~Node()
{
    for(auto&  nd: children)
    {
      delete nd;
    }
}




bool
Node::
operator==(const char*  name) const
{
  return(std::strcmp(defname,name) == 0);
}


void
Node::
append(Node*  child)
{
    if(child)
    {
      child->depth = depth+1;

      child->parent = this;

      children.emplace_back(child);
    }
}


Node*
Node::
release_unique_child()
{
  Node*  child = nullptr;

    if(children.size() == 1)
    {
      child = children.front();

      children.clear();
    }


  return child;
}


void
Node::
collect_characters(std::string&  s) const
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
      pr.printf("%s = \'%c\'",defname,character);
    }

  else
    if((children.size() == 1) && children.front()->children.empty())
    {
      pr.printf("%s = \'%c\'",defname,children.front()->character);
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



