#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_variable.hpp"
#include"cmplr_constant.hpp"




void
Declaration::
read(const mkf::Node&  src, PreContext&  prectx)
{
  clear();

  mkf::Cursor  cur(src);

  storage_kind = prectx.function? StorageKind::local
                                : StorageKind::global;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "function_declaration")
        {
          reset(new Function(nd,prectx));
        }

      else
        if(nd == "object_declaration")
        {
          read_object_declaration(nd,prectx);
        }


      cur.advance();
    }
}




void
Declaration::
read_object_declaration(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  Type  type;

  std::string  name;

  Initializer  init;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(name);
        }

      else
        if(nd == "type")
        {
          type.read(nd);
        }

      else
        if(nd == "const")
        {
          type.set_constant();
        }

      else
        if(nd == "initializer")
        {
          init.read(nd,prectx);
        }

      else
        if(nd == "static")
        {
          storage_kind = StorageKind::local_static;
        }


      cur.advance();
    }


  reset(new Variable(std::move(type),
                     std::move(name),
                     std::move(init)));
}




