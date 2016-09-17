#include"expression_operand.hpp"
#include"expression_element.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include<cstring>
#include<string>
#include<vector>
#include<new>




namespace expression{




Operand::
Operand():
kind(OperandKind::null)
{
}


Operand::
Operand(std::string*  s):
kind(OperandKind::null)
{
  reset(s);
}


Operand::
Operand(const Identifier&  id):
kind(OperandKind::null)
{
  reset(id);
}


Operand::
Operand(unsigned long  i):
kind(OperandKind::null)
{
  reset(i);
}


Operand::
Operand(Node*  nd):
kind(OperandKind::null)
{
  reset(nd);
}


Operand::
Operand(const ArgumentList&  args):
kind(OperandKind::null)
{
  reset(args);
}


Operand::
Operand(const Subscript&  subsc):
kind(OperandKind::null)
{
  reset(subsc);
}


Operand::
Operand(const mkf::Node&  src, PreContext&  prectx):
kind(OperandKind::null)
{
  read(src,prectx);
}


Operand::
Operand(const Operand&  rhs):
kind(OperandKind::null)
{
  *this = rhs;
}


Operand::
Operand(Operand&&  rhs) noexcept:
kind(OperandKind::null)
{
  *this = std::move(rhs);
}


Operand::
~Operand()
{
  clear();
}




Operand&
Operand::
operator=(const Operand&  rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
      case(OperandKind::string):
      case(OperandKind::identifier):
        data.s = new std::string(*rhs.data.s);
        break;
      case(OperandKind::argument_list):
        data.ndls = new NodeList(*rhs.data.ndls);
        break;
      case(OperandKind::expression):
      case(OperandKind::subscript):
        data.nd = new Node(*rhs.data.nd);
        break;
      case(OperandKind::integer):
        data.i = rhs.data.i;
        break;
    }


  return *this;
}


Operand&
Operand::
operator=(Operand&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = OperandKind::null;

    switch(kind)
    {
      case(OperandKind::string):
      case(OperandKind::identifier):
        data.s = rhs.data.s;
        break;
      case(OperandKind::argument_list):
        data.ndls = rhs.data.ndls;
        break;
      case(OperandKind::expression):
      case(OperandKind::subscript):
        data.nd = rhs.data.nd;
        break;
      case(OperandKind::integer):
        data.i = rhs.data.i;
        break;
    }


  return *this;
}


void
Operand::
clear()
{
    switch(kind)
    {
      case(OperandKind::string):
      case(OperandKind::identifier):
        delete data.s;
        break;
      case(OperandKind::argument_list):
        delete data.ndls;
        break;
      case(OperandKind::expression):
      case(OperandKind::subscript):
        delete data.nd;
        break;
      case(OperandKind::integer):
        break;
    }


  kind = OperandKind::null;
}


void
Operand::
reset(unsigned long  i)
{
  clear();

  kind = OperandKind::integer;

  data.i = i;
}


void
Operand::
reset(std::string*  s)
{
  clear();

  kind = OperandKind::string;

  data.s = s;
}


void
Operand::
reset(const Identifier&  id)
{
  clear();

  kind = OperandKind::identifier;

  data.s = id.s;
}


void
Operand::
reset(Node*  nd)
{
  clear();

  kind = OperandKind::expression;

  data.nd = nd;
}


void
Operand::
reset(const ArgumentList&  args)
{
  clear();

  kind = OperandKind::argument_list;

  data.ndls = args.node_list;
}


void
Operand::
reset(const Subscript&  subsc)
{
  clear();

  kind = OperandKind::subscript;

  data.nd = subsc.nd;
}




FoldResult
Operand::
fold(FoldContext&  ctx) const
{
    switch(kind)
    {
      case(OperandKind::string):
        break;
      case(OperandKind::identifier):
        {
          auto  decl = ctx.find_declaration(*data.s);

            if(!decl)
            {
              printf("関数%s内において、識別子%sが指すオブジェクトが見つかりません\n",
                     ctx.function->identifier.data(),data.s->data());

              throw;
            }


          return decl->fold(ctx);
        }
        break;
      case(OperandKind::expression):
        return data.nd->fold(ctx);
        break;
      case(OperandKind::subscript):
        break;
      case(OperandKind::argument_list):
        break;
      case(OperandKind::integer):
        return FoldResult(data.i);
        break;
    }


  return FoldResult();
}


ObjectKind
Operand::
compile(Context&  ctx) const
{
    switch(kind)
    {
      case(OperandKind::string):
        return ObjectKind::value;
        break;
      case(OperandKind::identifier):
        {
          auto  decl = ctx.find_declaration(*data.s);

            if(!decl)
            {
              printf("関数%s内において、識別子%sが指すオブジェクトが見つかりません\n",
                     ctx.function->identifier.data(),data.s->data());

              throw;
            }


          return decl->compile(ctx);
        }
        break;
      case(OperandKind::expression):
        return data.nd->compile(ctx);
        break;
      case(OperandKind::subscript):
        break;
      case(OperandKind::argument_list):
          for(auto  it = data.ndls->crbegin();  it != data.ndls->crend();  ++it)
          {
            auto  k = it->compile(ctx);

              if(k == ObjectKind::reference)
              {
                ctx.push("  ld;\n");
              }
          }


        ctx.push("  pshi8 %d;//引数個数\n",data.ndls->size());

        return ObjectKind::argument_list;
        break;
      case(OperandKind::integer):
        ctx.push("  pshi16  %d;//int\n",data.i);
        return ObjectKind::value;
        break;
    }


  return ObjectKind::null;
}


void
Operand::
print(FILE*  f) const
{
    switch(kind)
    {
      case(OperandKind::string):
        fprintf(f,"\"%s\"",data.s->data());
        break;
      case(OperandKind::identifier):
        fprintf(f,"%s",data.s->data());
        break;
      case(OperandKind::expression):
        data.nd->print(f);
        break;
      case(OperandKind::subscript):
        fprintf(f,"[");
        data.nd->print(f);
        fprintf(f,"]");
        break;
      case(OperandKind::argument_list):
        fprintf(f,"(");

          for(auto&  arg: *data.ndls)
          {
            arg.print(f);

            fprintf(f,",");
          }
        fprintf(f,")");
        break;
      case(OperandKind::integer):
        fprintf(f,"%lu",data.i);
        break;
    }
}


void
Operand::
read(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          auto  s = new std::string;

          nd.collect_characters(*s);

          reset(Identifier(s));
        }

      else
        if(nd == "integer_literal")
        {
          read_integer_literal(nd);
        }

      else
        if(nd == "string_literal")
        {
          auto  s = new std::string;

          nd.collect_characters(*s);

          reset(s);
        }

      else
        if(nd == "array_literal")
        {
//          reset(Array(new NodeList(Node::read_list(nd,prectx))));
        }

      else
        if(nd == "character_literal")
        {
          read_character_literal(nd);
        }

      else
        if(nd == "expression")
        {
          auto  expr = new Node(nd,prectx);

          reset(expr);
        }

      else
        if(nd == "null")
        {
          clear();
        }

      else
        if(nd == "true")
        {
          reset(1UL);
        }

      else
        if(nd == "false")
        {
          reset(0UL);
        }


      cur.advance();
    }
}




}




