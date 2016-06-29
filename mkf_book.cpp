#include"mkf_book.hpp"
#include"mkf_cursor.hpp"
#include<cstdlib>




namespace mkf{




const Definition&          Book::get_main_definition() const{return main_definition;}
const DefinitionList&  Book::get_sub_definition_list() const{return sub_definitions;}


void
Book::
change_main_definition(Definition&&  def)
{
  main_definition = std::move(def);
}


void
Book::
append_sub_definition(Definition&&  def)
{
  sub_definitions.emplace_back(std::move(def));
}


bool
Book::
make(const std::string&  s)
{
  charptr  p(s);

  bool  lost_first = false;

    try
    {
        while(p)
        {
          const char*  last = p;

            if(lost_first)
            {
              sub_definitions.emplace_back();

              sub_definitions.back().reset(p);
            }

          else
            {
              main_definition.reset(p);

              lost_first = true;
            }


          p.skip_space();

            if(p.get_raw_pointer() == last)
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
  sub_definitions.clear();
}


const Definition*
Book::
find(const std::string&  id) const
{
    for(auto&  def: sub_definitions)
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
  pr.puts("book has a main definition.\n");

  main_definition.print(pr);

  pr.putc('\n',true);

  pr.printf("book has %4d sub definitions.\n",sub_definitions.size());

  pr.printf("--------\n");

    for(auto&  def: sub_definitions)
    {
      def.print(pr);

      pr.putc('\n',true);
    }


  pr.printf("--------\n");
}




}



