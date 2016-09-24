#include"cmplr_initializer.hpp"
#include"expression_node.hpp"
#include"expression_operand.hpp"
#include"libpp/pp_utf8chunk.hpp"




Initializer::
Initializer():
kind(InitializerKind::null)
{
}


Initializer::
Initializer(expression::Node*  nd):
kind(InitializerKind::null)
{
  reset(nd);
}


Initializer::
Initializer(NodeList*  ndls):
kind(InitializerKind::null)
{
  reset(ndls);
}


Initializer::
Initializer(std::u16string*  s):
kind(InitializerKind::null)
{
  reset(s);
}


Initializer::
Initializer(const mkf::Node&  src, PreContext&  prectx):
kind(InitializerKind::null)
{
  read(src,prectx);
}


Initializer::
Initializer(const Initializer&   rhs):
kind(InitializerKind::null)
{
  *this = rhs;
}


Initializer::
Initializer(Initializer&&  rhs) noexcept:
kind(InitializerKind::null)
{
  *this = std::move(rhs);
}


Initializer::
~Initializer()
{
  clear();
}




Initializer&
Initializer::
operator=(const Initializer&   rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(InitializerKind::expression):
      data.nd = new expression::Node(*rhs.data.nd);
      break;
  case(InitializerKind::expression_list):
      data.ndls = new NodeList(*rhs.data.ndls);
      break;
  case(InitializerKind::string):
      data.s = new std::u16string(*rhs.data.s);
      break;
    }


  return *this;
}


Initializer&
Initializer::
operator=(Initializer&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                        ;
         rhs.kind = InitializerKind::null;

  data = rhs.data;

  return *this;
}


Initializer::
operator bool() const
{
  return(kind != InitializerKind::null);
}


void
Initializer::
clear()
{
    switch(kind)
    {
  case(InitializerKind::expression):
      delete data.nd;
      break;
  case(InitializerKind::expression_list):
      delete data.ndls;
      break;
  case(InitializerKind::string):
      delete data.s;
      break;
    }


  kind = InitializerKind::null;
}


void
Initializer::
reset(expression::Node*  nd)
{
  clear();

  kind = InitializerKind::expression;

  data.nd = nd;
}


void
Initializer::
reset(NodeList*  ndls)
{
  clear();

  kind = InitializerKind::expression_list;

  data.ndls = ndls;
}


void
Initializer::
reset(std::u16string*  s)
{
  clear();

  kind = InitializerKind::string;

  data.s = s;
}


void
Initializer::
print(FILE*  f) const
{
    switch(kind)
    {
  case(InitializerKind::expression):
      data.nd->print(f);
      break;
  case(InitializerKind::expression_list):
      fprintf(f,"{");

        for(auto&  nd: *data.ndls)
        {
          nd.print(f);

          fprintf(f,",");
        }


      fprintf(f,"}");
      break;
  case(InitializerKind::string):
      fprintf(f,"\"");

        for(auto  c: *data.s)
        {
          fprintf(f,"%s",pp::UTF8Chunk(c).codes);
        }


      fprintf(f,"\"");
      break;
    }
}


void
Initializer::
read(const mkf::Node&  src, PreContext&  prectx)
{
  clear();

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "expression")
        {
          reset(new expression::Node(nd,prectx));
        }

      else
        if(nd == "expression_list")
        {
          reset(new NodeList(expression::Node::read_list(nd,prectx)));
        }

      else
        if(nd == "string_literal")
        {
          reset(new std::u16string(expression::Operand::read_string_literal(nd)));
        }


      cur.advance();
    }
}




