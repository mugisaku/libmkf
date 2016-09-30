#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"




Declaration::
Declaration():
storage_kind(StorageKind::null),
offset(0)
{
}


Declaration::
Declaration(const Parameter&  para, size_t  off):
storage_kind(StorageKind::null)
{
  reset(para,off);
}


Declaration::
Declaration(const mkf::Node&  src, PreContext&  prectx):
storage_kind(StorageKind::null),
offset(0)
{
  read(src,prectx);
}




const Value&
Declaration::
get_value() const
{
  return value;
}


void
Declaration::
reset(Function*  fn)
{
  storage_kind = StorageKind::global;

  value.~Value();

  new(&value) Value(fn);

  name = fn->name;
}


void
Declaration::
reset(const Parameter&  para, size_t  off)
{
  storage_kind = StorageKind::local;

  value.clear();

  value.kind = ValueKind::parameter;

  offset = off;

  value.type = para.type;
  name       = para.name;
}




namespace{
void
compile_local(const Declaration&  decl, Context&  ctx)
{
  ctx.push("  pshbp        ;//*********************************//\n");
  ctx.push("  psh16u %6d;//ローカル変数%sのアドレスを読み出し//\n",decl.offset,decl.name.data());
  ctx.push("  sub          ;//*********************************//\n");
}


Type
compile_inconstant(const Declaration&  decl, Context&  ctx)
{
    switch(decl.storage_kind)
    {
      case(StorageKind::local):
        compile_local(decl,ctx);
        break;
      case(StorageKind::local_static):
        ctx.push("  psh16u _STATIC_%06z;//%s\n",decl.offset,decl.name.data());
        break;
      case(StorageKind::global):
        ctx.push("  psh16u %s;\n",decl.name.data());
        break;
    }


  return decl.get_value().type.make_reference();
}


void
compile_inconstant_definition(const Declaration&  decl, Context&  ctx)
{
    switch(decl.storage_kind)
    {
      case(StorageKind::local):
/*
          if(initializer)
          {
            compile_local(decl,name,ctx);

            auto  t = initializer.compile(ctx);

              if(t == TypeKind::reference)
              {
                t = t.compile_dereference(ctx);
              }


            type.make_reference().compile_assign(ctx);
          }
*/
        break;
      case(StorageKind::local_static):
        ctx.push_definition("_STATIC_%06z://%s\n",decl.offset,decl.name.data());
//        ctx.push_definition("data i32 {%d};\n",i);
        break;
      case(StorageKind::global):
        ctx.push_definition("%s:\n",decl.name.data());
//        ctx.push_definition("data i32 {%d};\n",i);
        break;
    }
}


}


Type
Declaration::
compile(Context&  ctx) const
{
    switch(value.kind)
    {
      case(ValueKind::single):
        return compile_inconstant(*this,ctx);
        break;
      case(ValueKind::array):
        break;
//      case(ValueKind::constant):
//        ctx.push("  pshi32 %d;//constexpr\n",value.cdata.i);

        return value.type;
        break;
      case(ValueKind::function):
        return value.data.fn->compile(ctx);
        break;
      case(ValueKind::parameter):
        ctx.push("  pshbp        ;//*************************//\n");
        ctx.push_psh(offset,"//実引数%sのアドレス読み出し//\n",name.data());
        ctx.push("  add          ;//*************************//\n");

        return value.type.make_reference();
        break;
     }


  return Type();
}


void
Declaration::
compile_definition(Context&  ctx) const
{
  value.compile_definition(ctx);
}




void
Declaration::
print(FILE*  f) const
{
    switch(storage_kind)
    {
  case(StorageKind::local_static):
      fprintf(f,"static ");
  case(StorageKind::local):
  case(StorageKind::global):
      break;
    }


  fprintf(f,"  %s = ",name.data());

  value.print(f);
}




