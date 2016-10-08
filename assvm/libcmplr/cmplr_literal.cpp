#include"cmplr_literal.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_precontext.hpp"
#include"cmplr_context.hpp"




Literal::
Literal():
kind(LiteralKind::null)
{
}


Literal::Literal( int8_t  i): kind(LiteralKind::null){reset(i);}
Literal::Literal(uint8_t  i): kind(LiteralKind::null){reset(i);}
Literal::Literal( int16_t  i): kind(LiteralKind::null){reset(i);}
Literal::Literal(uint16_t  i): kind(LiteralKind::null){reset(i);}
Literal::Literal( int32_t  i): kind(LiteralKind::null){reset(i);}
Literal::Literal(char16_t                c): kind(LiteralKind::null){reset(c);}
Literal::Literal(nullptr_t             nul): kind(LiteralKind::null){reset(nul);}
Literal::Literal(bool                    b): kind(LiteralKind::null){reset(b);}
Literal::Literal(std::u16string*         s): kind(LiteralKind::null){reset(s);}
Literal::Literal(std::string*           id): kind(LiteralKind::null){reset(id);}
Literal::Literal(expression::Node*      nd): kind(LiteralKind::null){reset(nd);}
Literal::Literal(Array*                arr): kind(LiteralKind::null){reset(arr);}
Literal::Literal(Function*              fn): kind(LiteralKind::null){reset(fn);}
Literal::Literal(const ArgumentList&  args): kind(LiteralKind::null){reset(args);}
Literal::Literal(const Subscript&    subsc): kind(LiteralKind::null){reset(subsc);}


Literal::
Literal(const mkf::Node&  src, PreContext&  prectx):
kind(LiteralKind::null)
{
  read(src,prectx);
}


Literal::
Literal(const Literal&  rhs) noexcept:
kind(LiteralKind::null)
{
  *this = rhs;
}


Literal::
Literal(Literal&&  rhs) noexcept:
kind(LiteralKind::null)
{
  *this = std::move(rhs);
}


Literal::
~Literal()
{
  clear();
}




Literal&
Literal::
operator=(const Literal&   rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(LiteralKind::nullptr_):
      break;
  case(LiteralKind::boolean):
      data.b = rhs.data.b;
      break;
  case(LiteralKind::string):
      data.s = new std::u16string(*rhs.data.s);
      break;
  case(LiteralKind::expression):
      data.nd = new expression::Node(*rhs.data.nd);
      break;
  case(LiteralKind::literal):
  case(LiteralKind::subscript):
      data.lit = new Literal(*rhs.data.lit);
      break;
  case(LiteralKind::array):
  case(LiteralKind::argument_list):
      data.arr = new Array(*rhs.data.arr);
      break;
  case(LiteralKind::identifier):
      data.id = new std::string(*rhs.data.id);
      break;
  case(LiteralKind::integer):
      data.i = rhs.data.i;
      break;
  case(LiteralKind::character):
      data.c = rhs.data.c;
      break;
  case(LiteralKind::function):
      data.fn = new Function(*rhs.data.fn);
      break;
    }


  return *this;
}


Literal&
Literal::
operator=(Literal&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = LiteralKind::null;

  data = rhs.data;


  return *this;
}




void
Literal::
clear()
{
    switch(kind)
    {
  case(LiteralKind::identifier):
      delete data.id;
      break;
  case(LiteralKind::string):
      delete data.s;
      break;
  case(LiteralKind::expression):
      delete data.nd;
      break;
  case(LiteralKind::subscript):
  case(LiteralKind::literal):
      delete data.lit;
      break;
  case(LiteralKind::array):
  case(LiteralKind::argument_list):
      delete data.arr;
      break;
  case(LiteralKind::function):
      delete data.fn;
      break;
  case(LiteralKind::integer):
  case(LiteralKind::character):
      break;
    }


  kind = LiteralKind::null;
}




Value
Literal::
make_value(PreContext&  prectx) const
{
    switch(kind)
    {
  case(LiteralKind::identifier):
      {
        auto  decl = prectx.find_declaration(*data.id);

          if(!decl)
          {
            printf("%sが指すオブジェクトが見つかりません\n",data.id->data());

            throw;
          }


        return decl->make_value();
      }
      break;
  case(LiteralKind::string):
      return Value(*data.s);
      break;
  case(LiteralKind::expression):
      return data.nd->make_value(prectx);
      break;
  case(LiteralKind::array):
    {
      Value  val;

        for(auto&  lit: *data.arr)
        {
        }
    }
     break;
  case(LiteralKind::argument_list):
    {
        for(auto&  lit: *data.arr)
        {
        }
    }
      break;
  case(LiteralKind::subscript):
      break;
  case(LiteralKind::function):
      return Value(data.fn);
      break;
  case(LiteralKind::integer):
      return ConstI32Value(data.i);
      break;
  case(LiteralKind::character):
      return ConstCharValue(data.c);
      break;
    }


  return Value();
}




void
Literal::
compile_definition(const Declaration&  decl, Context&  ctx) const
{
    switch(kind)
    {
  case(LiteralKind::function):
      data.fn->compile_definition(ctx);
      break;
    }
}




Value
Literal::
compile(Context&  ctx) const
{
    switch(kind)
    {
/*
      case(LiteralKind::constant):
        ctx.push("  pshi32 %d;//constexpr\n",value.cdata.i);

        return value;
        break;
*/
      case(LiteralKind::function):
        return data.fn->compile(ctx);
        break;
//      case(LiteralKind::parameter):
//        ctx.push("  pshbp        ;//*************************//\n");
//        ctx.push_psh(offset,"//実引数%sのアドレス読み出し//\n",name.data());
//        ctx.push("  add          ;//*************************//\n");

//        return type.make_reference();
        break;
  case(LiteralKind::identifier):
    {
      auto  decl = ctx.find_declaration(*data.id);

        if(!decl)
        {
          printf("関数%s内において、識別子%sが指すオブジェクトが見つかりません\n",
                 ctx.function->name.data(),data.id->data());

          throw;
        }


      return decl->compile(ctx);
    } break;
  case(LiteralKind::expression):
      return data.nd->compile(ctx);
      break;
  case(LiteralKind::array):
      break;
  case(LiteralKind::subscript):
      break;
  case(LiteralKind::argument_list):
    {
        if(data.arr->size())
        {
          ctx.push("  //************//\n");
          ctx.push("  //引数積み始め//\n");
          ctx.push("  //************//\n");

            for(auto  it = data.arr->crbegin();  it != data.arr->crend();  ++it)
            {
              auto  v = it->compile(ctx);

                if(v.type == TypeKind::reference)
                {
//                  t = t.compile_dereference(ctx);
                }
            }


          ctx.push("  //**************//\n");
          ctx.push("  //引数積み終わり//\n");
          ctx.push("  //**************//\n");
        }


//      return Literal(TypeKind::argument_list);
    } break;
  case(LiteralKind::character):
           if(data.i <= 0x00FF){ctx.push("  psh8u   %d;//即値\n",data.i);}
      else if(data.i <= 0xFFFF){ctx.push("  psh16u  %d;//即値\n",data.i);}
      else                     {ctx.push("  psh32   %d;//即値\n",data.i);}

      return ConstCharValue(data.i);
      break;
  case(LiteralKind::integer):
           if(data.i <= 0x00FF){ctx.push("  psh8u   %d;//即値\n",data.i);}
      else if(data.i <= 0xFFFF){ctx.push("  psh16u  %d;//即値\n",data.i);}
      else                     {ctx.push("  psh32   %d;//即値\n",data.i);}

      return ConstI32Value(data.i);
      break;
    }


  return Value();
}




void
Literal::
print(FILE*  f) const
{
    switch(kind)
    {
  case(LiteralKind::character):
      fprintf(f,"\'%s\'",pp::UTF8Chunk(data.c).codes);
      break;
  case(LiteralKind::expression):
      data.nd->print(f);
      break;
  case(LiteralKind::identifier):
      fprintf(f,"%s",data.id->data());
      break;
  case(LiteralKind::string):
      fprintf(f,"\"");

        for(auto  c: *data.s)
        {
          fprintf(f,"%s",pp::UTF8Chunk(c).codes);
        }


      fprintf(f,"\"");
      break;
  case(LiteralKind::subscript):
      fprintf(f,"[");
      data.lit->print(f);
      fprintf(f,"]");
      break;
  case(LiteralKind::argument_list):
    {
      fprintf(f,"<");

      auto   it = data.arr->cbegin();
      auto  end = data.arr->cend();

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
  case(LiteralKind::integer):
      fprintf(f,"%d",data.i);
      break;
  case(LiteralKind::nullptr_):
      fprintf(f,"nullptr");
      break;
  case(LiteralKind::boolean):
      fprintf(f,"%s",data.b? "true":"false");
      break;
  case(LiteralKind::literal):
      data.lit->print(f);
      break;
  case(LiteralKind::array):
      fprintf(f,"{");

        for(auto&  e: *data.arr)
        {
          e.print(f);

          fprintf(f,",");
        }


      fprintf(f,"}");
      break;
  case(LiteralKind::function):
      data.fn->print(f);
      break;
    }
}




namespace{
Subscript
read_subscript(const mkf::Node&  src, PreContext&  prectx)
{
  Literal*  lit = nullptr;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "literal_object")
        {
          lit = new Literal(nd,prectx);
        }

      else
        if(nd == "expression")
        {
          lit = new Literal(new expression::Node(nd,prectx));
        }


      cur.advance();
    }


  return Subscript(lit);
}
}


void
Literal::
read(const mkf::Node&  src, PreContext&  prectx)
{
  clear();

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
          reset(static_cast<int>(read_integer_literal(nd)));
        }

      else
        if(nd == "character_literal")
        {
          reset(read_character_literal(nd));
        }

      else
        if(nd == "expression")
        {
          reset(new expression::Node(nd,prectx));
        }

        if(nd == "string_literal")
        {
          reset(new std::u16string(read_string_literal(nd)));
        }

      else
        if(nd == "nullptr")
        {
          reset(nullptr);
        }

      else
        if(nd == "true")
        {
          reset(true);
        }

      else
        if(nd == "false")
        {
          reset(false);
        }

      else
        if(nd == "array_literal")
        {
          reset(new Array(read_list(nd,prectx)));
        }

      else
        if(nd == "argument_list")
        {
          auto  arr = new Array(read_list(nd,prectx));


          reset(ArgumentList(arr));
        }

      else
        if(nd == "subscript")
        {
          reset(read_subscript(nd,prectx));
        }


      cur.advance();
    }
}


Array
Literal::
read_list(const mkf::Node&  src, PreContext&  prectx)
{
  Array  ls;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "literal_object")
        {
          ls.emplace_back(nd,prectx);
        }

      else
        if(nd == "expression")
        {
          ls.emplace_back(new expression::Node(nd,prectx));
        }


      cur.advance();
    }


  return std::move(ls);
}




