#include"cmplr_declaration.hpp"
#include"cmplr_globalscope.hpp"
#include"cmplr_function.hpp"




void
Declaration::
print_value(FILE*  f) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
        fprintf(f,"var %s",identifier.data());

          if(data.expr)
          {
            fprintf(f," = ");

            data.expr->print(f);
          }
        break;
      case(DeclarationKind::local_static):
        fprintf(f,"static var %s",identifier.data());

          if(data.expr)
          {
            fprintf(f," = ");

            data.expr->print(f);
          }
        break;
      case(DeclarationKind::global):
        fprintf(f,"var %s",identifier.data());

          if(data.expr)
          {
            fprintf(f," = ");

            data.expr->print(f);
          }
        break;
      case(DeclarationKind::parameter):
        fprintf(f,"%s",identifier.data());
        break;
    }
}


void
Declaration::
print_constant(FILE*  f) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        fprintf(f,"const %s = %d",identifier.data(),data.i);
        break;
      case(DeclarationKind::global):
        fprintf(f,"const %s = %d",identifier.data(),data.i);
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
print_array(FILE*  f) const
{
    switch(kind)
    {
      case(DeclarationKind::local_static):
        fprintf(f,"static ");
      case(DeclarationKind::local):
      case(DeclarationKind::global):
        fprintf(f,"%s = {",identifier.data());

          for(auto  v: *data.carr)
          {
            fprintf(f,"%d,",v);
          }


        fprintf(f,"}");
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
print_constant_array(FILE*  f) const
{
    switch(kind)
    {
      case(DeclarationKind::local_static):
        fprintf(f,"static ");
      case(DeclarationKind::local):
      case(DeclarationKind::global):
        fprintf(f,"const %s = {",identifier.data());

          for(auto  v: *data.carr)
          {
            fprintf(f,"%d,",v);
          }


        fprintf(f,"}");
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
print_function(FILE*  f) const
{
    switch(kind)
    {
      case(DeclarationKind::local):
        break;
      case(DeclarationKind::local_static):
        break;
      case(DeclarationKind::global):
        fprintf(f,"function %s",identifier.data());

        data.fn->print(f);
        break;
      case(DeclarationKind::parameter):
        break;
    }
}


void
Declaration::
print(FILE*  f) const
{
    switch(object_kind)
    {
      case(ObjectKind::value):
        print_value(f);
        break;
      case(ObjectKind::constant):
        print_constant(f);
        break;
      case(ObjectKind::function):
        print_function(f);
        break;
      case(ObjectKind::array):
        print_array(f);
        break;
      case(ObjectKind::constant_array):
        print_constant_array(f);
        break;
    }
}




