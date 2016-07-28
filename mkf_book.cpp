#include"mkf_book.hpp"
#include"mkf_cursor.hpp"
#include<cstdlib>




namespace mkf{




const DefinitionList&
Book::
get_definition_list() const
{
  return definitions;
}


void
Book::
append_definition(Definition&&  def)
{
  definitions.emplace_back(std::move(def));
}


bool
Book::
make(const pp::String&  s)
{
  auto  p = s.data();

    try
    {
        while(p->unicode)
        {
          const pp::Character*  last = &*p;

          definitions.emplace_back();

          definitions.back().reset(p);

          pp::skip_spaces(p);

            if(&*p == last)
            {
              discontinue(ErrorKind::null,p,"");
            }
        }
    }


    catch(ErrorKind  k)
    {
      return false;
    }


  return true;
}


void
Book::
clear()
{
  definitions.clear();
}


const Definition*
Book::
find(const std::string&  id) const
{
    for(auto&  def: definitions)
    {
        if(def.get_identifier() == id)
        {
          return &def;
        }
    }


  return nullptr;
}


void
Book::
print(FILE*  f) const
{
  Printer  pr(0,f);

  print(pr);
}


void
Book::
print(Printer&  pr) const
{
  pr.printf("book has %4d definitions.\n",definitions.size());

  pr.printf("--------\n");

    for(auto&  def: definitions)
    {
      def.print(pr);

      pr.putc('\n',true);
    }


  pr.printf("--------\n");
}




}



