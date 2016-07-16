#include"json.hpp"




namespace json{




Element::Element(                  ): kind(ElementKind::null){}
Element::Element(int             i_): kind(ElementKind::null){reset(i_);}
Element::Element(bool            b_): kind(ElementKind::null){reset(b_);}
Element::Element(double          f_): kind(ElementKind::null){reset(f_);}
Element::Element(Object*       obj_): kind(ElementKind::null){reset(obj_);}
Element::Element(std::string*  str_): kind(ElementKind::null){reset(str_);}
Element::Element(Array*        arr_): kind(ElementKind::null){reset(arr_);}
Element::Element(Element&&  rhs) noexcept: kind(ElementKind::null){*this = std::move(rhs);}
Element::~Element(){clear();}




Element&
Element::
operator=(Element&&  rhs)
{
  clear();

  data = rhs.data;

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

  return *this;
}


bool
Element::
operator==(const Element&  rhs) const
{
    if(kind == rhs.kind)
    {
        switch(kind)
        {
          case(ElementKind::null):
            return true;
          case(ElementKind::integer):
            return(data.i == rhs.data.i);
          case(ElementKind::boolean):
            return(data.b == rhs.data.b);
          case(ElementKind::fp_number):
            return true;
//            return(data.f == rhs.data.f);
          case(ElementKind::object):
            return(*data.obj == *rhs.data.obj);
          case(ElementKind::string):
            return(*data.str == *rhs.data.str);
          case(ElementKind::array):
            return(*data.arr == *rhs.data.arr);
          default:
            report;
        }
    }


  return false;
}


void
Element::
clear()
{
    switch(kind)
    {
      case(ElementKind::null):
      case(ElementKind::integer):
      case(ElementKind::boolean):
      case(ElementKind::fp_number):
        break;
      case(ElementKind::object):
        delete data.obj;
        break;
      case(ElementKind::string):
        delete data.str;
        break;
      case(ElementKind::array):
       delete data.arr;
        break;
    }


  kind = ElementKind::null;
}


void  Element::reset(int             i_){  clear();    data.i =   i_;  kind = ElementKind::integer  ;}
void  Element::reset(bool            b_){  clear();    data.b =   b_;  kind = ElementKind::boolean  ;}
void  Element::reset(double          f_){  clear();    data.f =   f_;  kind = ElementKind::fp_number;}
void  Element::reset(Object*       obj_){  clear();  data.obj = obj_;  kind = ElementKind::object   ;}
void  Element::reset(std::string*  str_){  clear();  data.str = str_;  kind = ElementKind::string   ;}
void  Element::reset(Array*        arr_){  clear();  data.arr = arr_;  kind = ElementKind::array    ;}


namespace{
void
fputi(int  i, FILE*  f)
{
    while(i--)
    {
      fputc(' ',f);
    }
}
}


void
Element::
print(bool  opening, int  base_i, FILE*  f) const
{
    switch(kind)
    {
      case(ElementKind::null):
        fprintf(f,"null");
        break;
      case(ElementKind::integer):
        fprintf(f,"%d",data.i);
        break;
      case(ElementKind::boolean):
        fprintf(f,"%s",data.b? "true":"false");
        break;
      case(ElementKind::fp_number):
        fprintf(f,"%g",data.f);
        break;
      case(ElementKind::string):
        fprintf(f,"\"%s\"",data.str->data());
        break;
      case(ElementKind::object):
        data.obj->print(opening,base_i,f);
        break;
      case(ElementKind::array):
        data.arr->print(opening,base_i,f);
        break;
    }
}




constexpr int  inc = 4;


void
Object::
print(bool  opening, int  base_i, FILE*  f) const
{
    if(opening)
    {
      fputi(base_i,f);

      fprintf(f,"{\n");
    }


    if(members.size())
    {
      auto   it = members.cbegin();
      auto  end = members.cend();

        for(;;)
        {
          fputi(base_i+inc,f);

          fprintf(f,"\"%s\":",it->name.data());

               if(it->value.kind == ElementKind::object){fprintf(f,"{\n");}
          else if(it->value.kind == ElementKind::array ){fprintf(f,"[\n");}


          it->value.print(false,base_i+inc,f);

          ++it;

            if(it == end)
            {
              break;
            }


          fprintf(f,",\n");
        }
    }


  fprintf(f,"\n");

  fputi(base_i,f);

  fprintf(f,"}");
}


void
Array::
print(bool  opening, int  base_i, FILE*  f) const
{
    if(opening)
    {
      fputi(base_i,f);

      fprintf(f,"[\n");
    }


    if(elements.size())
    {
      auto   it = elements.cbegin();
      auto  end = elements.cend();

        for(;;)
        {
          fputi(base_i+inc,f);

               if(it->kind == ElementKind::object){fprintf(f,"{\n");}
          else if(it->kind == ElementKind::array ){fprintf(f,"[\n");}

          it->print(false,base_i+inc,f);

          ++it;

            if(it == end)
            {
              break;
            }


          fprintf(f,",\n");
        }
    }


  fprintf(f,"\n");

  fputi(base_i,f);

  fprintf(f,"]");
}


}

