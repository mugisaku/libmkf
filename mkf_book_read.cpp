#include"mkf_book.hpp"
#include"mkf_cursor.hpp"
#include<cstdlib>




namespace mkf{


bool
Book::
make(const Node&  src)
{
  Cursor  cur(src);

  sub_definitions.clear();

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "definition")
        {
          sub_definitions.emplace_back(read_definition(nd));
        }


      cur.advance();
    }


    if(sub_definitions.size() >= 1)
    {
      main_definition = std::move(sub_definitions.front());

      sub_definitions.pop_front();
    }


  return true;
}


Definition
Book::
read_definition(const Node&  base)
{
  Cursor  cur(base);

  Definition  def;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          std::string  s;

          nd.collect_characters(s);

          def.change_identifier(s.data());
        }

      else
        if(nd == "specifier")
        {
          def.set_solid_flag();
        }

      else
        if((nd == "entry") ||
           (nd == "last_entry"))
        {
          read_entry(def,nd);
        }


      cur.advance();
    }


  return std::move(def);
}


void
Book::
read_entry(Definition&  def, const Node&  base)
{
  Cursor  cur(base);

  uint32_t  flags = 0;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "mark")
        {
          flags |= read_mark(nd);
        }

      else
        if(nd == "element")
        {
          def.append_element(read_element(flags,nd));

          flags = 0;
        }

      else
        if(nd == "separator")
        {
          def.set_separator(nd.children.front()->character);
        }

      else
        if(nd == "terminator")
        {
          break;
        }


      cur.advance();
    }
}


Element
Book::
read_element(uint32_t  flags, const Node&  base)
{
  Cursor  cur(base);

  Element  elm;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          std::string  s;

          nd.collect_characters(s);

          elm.reset(flags,Identifier(s.data()));
        }

      else
        if(nd == "string_literal")
        {
          std::string  s = read_string_literal(nd);

          elm.reset(flags,String(s.data()));
        }

      else
        if(nd == "character_literal")
        {
          int  c = read_character_literal(nd);

          elm.reset(flags,c);
        }


      cur.advance();
    }


  return std::move(elm);
}


std::string
Book::
read_string_literal(const Node&  base)
{
  std::string  s;

  Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "string_element")
        {
          s.push_back(read_string_element(nd));
        }


      cur.advance();
    }


  return std::move(s);
}


int
Book::
read_character_literal(const Node&  base)
{
  Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "string_element")
        {
          return read_string_element(nd);
        }


      cur.advance();
    }


  return 0;
}


int
Book::
read_string_element(const Node&  base)
{
  Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

           if(nd == "null_character"        ){return 0;}
      else if(nd == "newline_character"     ){return '\n';}
      else if(nd == "backslash_character"   ){return '\\';}
      else if(nd == "single_quote_character"){return '\'';}
      else if(nd == "double_quote_character"){return '\"';}
      else {return nd.character;}


      cur.advance();
    }


  report;
  return '~';
}


uint32_t
Book::
read_mark(const Node&  base)
{
  Cursor  cur(base);

  uint32_t  flags = 0;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "repeat_mark")
        {
          flags |= ElementFlag::repeat;
        }

      else
        if(nd == "omittable_mark")
        {
          flags |= ElementFlag::omittable;
        }


      cur.advance();
    }


  return flags;
}


}



