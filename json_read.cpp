#include"json.hpp"




namespace json{




Element
read_json(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "element")
        {
          return read_element(nd);
        }


      cur.advance();
    }


  return Element();
}


Element
read_element(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "null")
        {
          return Element();
        }

      else
        if(nd == "false")
        {
          return Element(false);
        }

      else
        if(nd == "true")
        {
          return Element(true);
        }

      else
        if((nd == "positive_integer") ||
           (nd == "negative_integer"))
        {
          std::string  s;

          nd.collect_characters(s);

          return Element(std::stoi(s));
        }

      else
        if((nd == "fp_number_form0") ||
           (nd == "fp_number_form1"))
        {
          std::string  s;

          nd.collect_characters(s);

          return Element(std::stod(s));
        }

      else
        if(nd == "string")
        {
          return Element(new std::string(read_string(nd)));
        }

      else
        if(nd == "object")
        {
          return Element(read_object(nd));
        }

      else
        if(nd == "array")
        {
          return Element(read_array(nd));
        }

      else
        {
          report;

          printf("%s\n",nd.defname);
          break;
        }


      cur.advance();
    }


  return Element();
}


Object*
read_object(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

  auto  obj = new Object;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "object_content")
        {
          read_object_content(nd,*obj);
        }


      cur.advance();
    }


  return obj;
}


void
read_object_content(const mkf::Node&  base, Object&  obj)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if((nd == "object_member") ||
           (nd == "object_last_member"))
        {
          obj.members.emplace_back(read_object_member(nd));
        }


      cur.advance();
    }
}


ObjectMember
read_object_member(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

  ObjectMember  m;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "string")
        {
          m.name = read_string(nd);
        }

      else
        if(nd == "element")
        {
          m.value = read_element(nd);
        }


      cur.advance();
    }


  return std::move(m);
}


Array*
read_array(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

  auto  arr = new Array;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "array_content")
        {
          read_array_content(nd,*arr);
        }


      cur.advance();
    }


  return arr;
}


void
read_array_content(const mkf::Node&  base, Array&  arr)
{
  mkf::Cursor  cur(base);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "array_element")
        {
          arr.elements.emplace_back(read_json(nd));
        }

      else
        if(nd == "element")
        {
          arr.elements.emplace_back(read_element(nd));
        }


      cur.advance();
    }
}


std::string
read_string(const mkf::Node&  base)
{
  mkf::Cursor  cur(base);

  std::string  s;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "string_element")
        {
          nd.collect_characters(s);
        }


      cur.advance();
    }


  return std::move(s);
}


}




