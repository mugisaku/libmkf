#include"cmplr_value.hpp"
#include"cmplr_function.hpp"
#include"expression_node.hpp"
#include"cmplr_precontext.hpp"
#include"cmplr_context.hpp"




Value::
Value():
kind(ValueKind::null)
{
}


Value::
Value(Type&&  type_):
kind(ValueKind::null),
type(std::move(type_))
{}



Value::Value( int8_t  i): kind(ValueKind::null){reset(i);}
Value::Value(uint8_t  i): kind(ValueKind::null){reset(i);}
Value::Value( int16_t  i): kind(ValueKind::null){reset(i);}
Value::Value(uint16_t  i): kind(ValueKind::null){reset(i);}
Value::Value( int32_t  i): kind(ValueKind::null){reset(i);}
Value::Value(char16_t                c): kind(ValueKind::null){reset(c);}
Value::Value(nullptr_t             nul): kind(ValueKind::null){reset(nul);}
Value::Value(bool                    b): kind(ValueKind::null){reset(b);}
Value::Value(std::u16string*         s): kind(ValueKind::null){reset(s);}
Value::Value(std::string*           id): kind(ValueKind::null){reset(id);}
Value::Value(expression::Node*      nd): kind(ValueKind::null){reset(nd);}
Value::Value(ValueList*             ls): kind(ValueKind::null){reset(ls);}
Value::Value(Function*              fn): kind(ValueKind::null){reset(fn);}
Value::Value(const ArgumentList&  args): kind(ValueKind::null){reset(args);}
Value::Value(const Subscript&    subsc): kind(ValueKind::null){reset(subsc);}


Value::
Value(const mkf::Node&  src, PreContext&  prectx):
kind(ValueKind::null)
{
  read(src,prectx);
}


Value::
Value(const Value&  rhs) noexcept:
kind(ValueKind::null)
{
  *this = rhs;
}


Value::
Value(Value&&  rhs) noexcept:
kind(ValueKind::null)
{
  *this = std::move(rhs);
}


Value::
~Value()
{
  clear();
}




Value&
Value::
operator=(const Value&   rhs) noexcept
{
  clear();

  kind = rhs.kind;
  type = rhs.type;

    switch(kind)
    {
  case(ValueKind::nullptr_):
      break;
  case(ValueKind::boolean):
      data.b = rhs.data.b;
      break;
  case(ValueKind::string):
      data.s = new std::u16string(*rhs.data.s);
      break;
  case(ValueKind::expression):
      data.nd = new expression::Node(*rhs.data.nd);
      break;
  case(ValueKind::value_list):
  case(ValueKind::argument_list):
      data.ls = new ValueList(*rhs.data.ls);
      break;
  case(ValueKind::identifier):
      data.id = new std::string(*rhs.data.id);
      break;
  case(ValueKind::subscript):
      data.nd = new expression::Node(*rhs.data.nd);
      break;
  case(ValueKind::integer):
      data.i = rhs.data.i;
      break;
  case(ValueKind::character):
      data.c = rhs.data.c;
      break;
  case(ValueKind::function):
      data.fn = new Function(*rhs.data.fn);
      break;
    }


  return *this;
}


Value&
Value::
operator=(Value&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                  ;
         rhs.kind = ValueKind::null;

  type = std::move(rhs.type);

  data = rhs.data;


  return *this;
}




void
Value::
clear()
{
    switch(kind)
    {
  case(ValueKind::identifier):
      delete data.id;
      break;
  case(ValueKind::string):
      delete data.s;
      break;
  case(ValueKind::expression):
      delete data.nd;
      break;
  case(ValueKind::value_list):
  case(ValueKind::argument_list):
      delete data.ls;
      break;
  case(ValueKind::subscript):
      delete data.nd;
      break;
  case(ValueKind::function):
      delete data.fn;
      break;
  case(ValueKind::integer):
  case(ValueKind::character):
      break;
    }


  kind = ValueKind::null;

  type.clear();
}




bool
Value::
dereference()
{
    if(type != TypeKind::reference)
    {
      printf("参照でないオブジェクトから値を取り出そうとしました\n");

      return false;
    }


  type = *type->ptr.referred;

  return true;
}


bool
Value::
change_reference_to_pointer()
{
    if(type != TypeKind::reference)
    {
      printf("参照でないオブジェクトから値を取り出そうとしました\n");

      return false;
    }


  type.change_kind(TypeKind::pointer);

  return true;
}




void
Value::
compile_definition(const Declaration&  decl, Context&  ctx) const
{
    switch(kind)
    {
  case(ValueKind::function):
      data.fn->compile_definition(ctx);
      break;
    }
}




Value
Value::
compile(Context&  ctx) const
{
    switch(kind)
    {
/*
      case(ValueKind::constant):
        ctx.push("  pshi32 %d;//constexpr\n",value.cdata.i);

        return value;
        break;
*/
      case(ValueKind::function):
        return data.fn->compile(ctx);
        break;
      case(ValueKind::parameter):
//        ctx.push("  pshbp        ;//*************************//\n");
//        ctx.push_psh(offset,"//実引数%sのアドレス読み出し//\n",name.data());
//        ctx.push("  add          ;//*************************//\n");

//        return type.make_reference();
        break;
  case(ValueKind::identifier):
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
  case(ValueKind::expression):
      return data.nd->compile(ctx);
      break;
  case(ValueKind::value_list):
      break;
  case(ValueKind::subscript):
      break;
  case(ValueKind::argument_list):
    {
        if(data.ls->size())
        {
          ctx.push("  //************//\n");
          ctx.push("  //引数積み始め//\n");
          ctx.push("  //************//\n");

            for(auto  it = data.ls->crbegin();  it != data.ls->crend();  ++it)
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


//      return Value(TypeKind::argument_list);
    } break;
  case(ValueKind::character):
           if(data.i <= 0x00FF){ctx.push("  psh8u   %d;//即値\n",data.i);}
      else if(data.i <= 0xFFFF){ctx.push("  psh16u  %d;//即値\n",data.i);}
      else                     {ctx.push("  psh32   %d;//即値\n",data.i);}

      return ConstCharValue(data.i);
      break;
  case(ValueKind::integer):
           if(data.i <= 0x00FF){ctx.push("  psh8u   %d;//即値\n",data.i);}
      else if(data.i <= 0xFFFF){ctx.push("  psh16u  %d;//即値\n",data.i);}
      else                     {ctx.push("  psh32   %d;//即値\n",data.i);}

      return ConstI32Value(data.i);
      break;
    }


  return Value();
}




void
Value::
print(FILE*  f) const
{
    switch(kind)
    {
  case(ValueKind::character):
      fprintf(f,"\'%s\'",pp::UTF8Chunk(data.c).codes);
      break;
  case(ValueKind::expression):
      data.nd->print(f);
      break;
  case(ValueKind::identifier):
      fprintf(f,"%s",data.id->data());
      break;
  case(ValueKind::string):
      fprintf(f,"\"");

        for(auto  c: *data.s)
        {
          fprintf(f,"%s",pp::UTF8Chunk(c).codes);
        }


      fprintf(f,"\"");
      break;
  case(ValueKind::subscript):
      fprintf(f,"[");
      data.nd->print(f);
      fprintf(f,"]");
      break;
  case(ValueKind::argument_list):
    {
      fprintf(f,"<");

      auto   it = data.ls->cbegin();
      auto  end = data.ls->cend();

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
  case(ValueKind::integer):
      fprintf(f,"%d",data.i);
      break;
  case(ValueKind::nullptr_):
      fprintf(f,"nullptr");
      break;
  case(ValueKind::boolean):
      fprintf(f,"%s",data.b? "true":"false");
      break;
  case(ValueKind::value_list):
      fprintf(f,"{");

        for(auto&  v: *data.ls)
        {
          v.print(f);

          fprintf(f,",");
        }


      fprintf(f,"}");
      break;
  case(ValueKind::function):
      data.fn->print(f);
      break;
    }
}




void
Value::
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

        if(nd == "value_list")
        {
          reset(new ValueList(read_list(nd,prectx)));
        }


      cur.advance();
    }
}


ValueList
Value::
read_list(const mkf::Node&  src, PreContext&  prectx)
{
  ValueList  ls;

  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "value")
        {
          ls.emplace_back(nd,prectx);
        }


      cur.advance();
    }


  return std::move(ls);
}




Value       VoidValue(){return Value(VoidType());}
Value       NullptrValue(){return Value(NullptrType());}
Value            CharValue(           ){return Value(CharType());}
Value       ConstCharValue(char16_t  c){return Value(c);}
Value       BoolValue(       ){return Value(BoolType());}
Value  ConstBoolValue(bool  b){return Value(b);}
Value       I8Value(         ){return Value(I8Type());}
Value  ConstI8Value(int8_t  i){return Value(i);}
Value       U8Value(         ){return Value(U8Type());}
Value  ConstU8Value(uint8_t  i){return Value(i);}
Value       I16Value(         ){return Value(I16Type());}
Value  ConstI16Value(int16_t  i){return Value(i);}
Value       U16Value(           ){return Value(U16Type());}
Value  ConstU16Value(uint16_t  i){return Value(i);}
Value       I32Value(          ){return Value(I32Type());}
Value  ConstI32Value(int32_t  i){return Value(i);}





