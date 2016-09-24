#include"expression_operand.hpp"
#include"expression_element.hpp"
#include"expression_node.hpp"
#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_initializer.hpp"
#include"libpp/pp_utf8chunk.hpp"
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
Operand(std::string*  id):
kind(OperandKind::null)
{
  reset(id);
}


Operand::
Operand(std::u16string*  s):
kind(OperandKind::null)
{
  reset(s);
}


Operand::
Operand(uint32_t  i):
kind(OperandKind::null)
{
  reset(i);
}


Operand::
Operand(char16_t  c):
kind(OperandKind::null)
{
  reset(c);
}


Operand::
Operand(Node*  nd):
kind(OperandKind::null)
{
  reset(nd);
}


Operand::
Operand(Initializer&&  init):
kind(OperandKind::null)
{
  reset(std::move(init));
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
        data.s = new std::u16string(*rhs.data.s);
        break;
      case(OperandKind::identifier):
        data.id = new std::string(*rhs.data.id);
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
      case(OperandKind::character):
        data.c = rhs.data.c;
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

  data = rhs.data;

  return *this;
}


void
Operand::
clear()
{
    switch(kind)
    {
      case(OperandKind::identifier):
        delete data.id;
        break;
      case(OperandKind::string):
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
      case(OperandKind::character):
        break;
    }


  kind = OperandKind::null;
}


void
Operand::
reset(uint32_t  i)
{
  clear();

  kind = OperandKind::integer;

  data.i = i;
}


void
Operand::
reset(char16_t  c)
{
  clear();

  kind = OperandKind::character;

  data.c = c;
}


void
Operand::
reset(std::u16string*  s)
{
  clear();

  kind = OperandKind::string;

  data.s = s;
}


void
Operand::
reset(std::string*  id)
{
  clear();

  kind = OperandKind::identifier;

  data.id = id;
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
reset(Initializer&&  init)
{
  clear();

    switch(init.kind)
    {
  case(InitializerKind::expression):
      init.kind = InitializerKind::null;

      kind = OperandKind::expression;

      data.nd = init.data.nd;
      break;
  case(InitializerKind::expression_list):
      init.kind = InitializerKind::null;

      kind = OperandKind::expression_list;

      data.ndls = init.data.ndls;
      break;
  case(InitializerKind::string):
      init.kind = InitializerKind::null;

      kind = OperandKind::string;

      data.s = init.data.s;
      break;
    }
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
          auto  decl = ctx.find_declaration(*data.id);

            if(!decl)
            {
              printf("関数%s内において、識別子%sが指すオブジェクトが見つかりません\n",
                     ctx.function->signature.name.data(),data.id->data());

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


Type
Operand::
compile(Context&  ctx) const
{
    switch(kind)
    {
  case(OperandKind::string):
      return Type(TypeKind::pointer);
      break;
  case(OperandKind::identifier):
    {
      auto  decl = ctx.find_declaration(*data.id);

        if(!decl)
        {
          printf("関数%s内において、識別子%sが指すオブジェクトが見つかりません\n",
                 ctx.function->signature.name.data(),data.id->data());

          throw;
        }


      return decl->compile(ctx);
    } break;
  case(OperandKind::expression):
      return data.nd->compile(ctx);
      break;
  case(OperandKind::subscript):
      break;
  case(OperandKind::argument_list):
    {
        if(data.ndls->size())
        {
          ctx.push("  //************//\n");
          ctx.push("  //引数積み始め//\n");
          ctx.push("  //************//\n");

            for(auto  it = data.ndls->crbegin();  it != data.ndls->crend();  ++it)
            {
              auto  t = it->compile(ctx);

                if(t == TypeKind::reference)
                {
                  t = t.compile_dereference(ctx);
                }
            }


          ctx.push("  //**************//\n");
          ctx.push("  //引数積み終わり//\n");
          ctx.push("  //**************//\n");
        }


      return Type(TypeKind::argument_list,nullptr,data.ndls->size());
    } break;
  case(OperandKind::character):
           if(data.i <= 0x00FF){ctx.push("  psh8u   %d;//即値\n",data.i);}
      else if(data.i <= 0xFFFF){ctx.push("  psh16u  %d;//即値\n",data.i);}
      else                     {ctx.push("  psh32   %d;//即値\n",data.i);}

      return Type(TypeKind::char_);
      break;
  case(OperandKind::integer):
           if(data.i <= 0x00FF){ctx.push("  psh8u   %d;//即値\n",data.i);}
      else if(data.i <= 0xFFFF){ctx.push("  psh16u  %d;//即値\n",data.i);}
      else                     {ctx.push("  psh32   %d;//即値\n",data.i);}

      return Type(TypeKind::int32);
      break;
    }


  return Type();
}


void
Operand::
print(FILE*  f) const
{
    switch(kind)
    {
  case(OperandKind::character):
      fprintf(f,"\'%s\'",pp::UTF8Chunk(data.c).codes);
      break;
  case(OperandKind::string):
      fprintf(f,"\"");

        for(auto  c: *data.s)
        {
          fprintf(f,"%s",pp::UTF8Chunk(c).codes);
        }


      fprintf(f,"\"");
      break;
  case(OperandKind::identifier):
      fprintf(f,"%s",data.id->data());
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
    {
      fprintf(f,"<");

      auto   it = data.ndls->cbegin();
      auto  end = data.ndls->cend();

        if(it != end)
        {
          it++->print(f);

            while(it != end)
            {
              fprintf(f,",");

              it++->print(f);
            }
        }

      fprintf(f,">");
    } break;
  case(OperandKind::integer):
      fprintf(f,"%u",data.i);
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

          reset(s);
        }

      else
        if(nd == "integer_literal")
        {
          reset(read_integer_literal(nd));
        }

      else
        if(nd == "string_literal")
        {
          reset(new std::u16string(read_string_literal(nd)));
        }

      else
        if(nd == "character_literal")
        {
          reset(read_character_literal(nd));
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
          reset(UINT32_C(0));
        }

      else
        if(nd == "false")
        {
          reset(UINT32_C(0));
        }


      cur.advance();
    }
}




}




