#include"json.hpp"




namespace json{




namespace{
std::random_device  seed_gen;

std::default_random_engine
get_engine()
{
  return std::default_random_engine(seed_gen());
}


std::string
get_random_string()
{
  auto  engine = get_engine();

  std::uniform_int_distribution<>  len(0,8);
  std::uniform_int_distribution<>  chr('A','Z');

  std::string  s;

  int  n = len(engine);

    while(n--)
    {
      auto  c = chr(engine);

      s.push_back(c);
    }


  return std::move(s);
}


}




Element
Element::
create_random_element(int  n)
{
  auto  engine = get_engine();

  std::uniform_int_distribution<>  dist(0,6);

    switch(static_cast<ElementKind>(dist(engine)))
    {
      case(ElementKind::null):
        return Element();
      case(ElementKind::boolean):
        return create_random_boolean();
      case(ElementKind::integer):
        return create_random_integer();
      case(ElementKind::fp_number):
        return create_random_fp_number();
      case(ElementKind::string):
        return create_random_string();
      case(ElementKind::object):
          if(n)
          {
            return create_random_object(n-1);
          }
        break;
      case(ElementKind::array):
          if(n)
          {
            return create_random_array(n-1);
          }
        break;
      default:
        printf("\n\n!!!\n\n");
    }


  return Element();
}


Element
Element::
create_random_boolean()
{
  auto  engine = get_engine();

  std::uniform_int_distribution<>  dist(0,1);

  return Element(dist(engine)? true:false);
}


Element
Element::
create_random_object(int  n)
{
  auto  engine = get_engine();

  std::uniform_int_distribution<>  len(0,8);

  auto  obj = new Object;

  int  count = len(engine);

    while(count--)
    {
      obj->members.emplace_back(get_random_string(),create_random_element(n));
    }


  return Element(obj);
}


Element
Element::
create_random_array(int  n)
{
  auto  engine = get_engine();

  std::uniform_int_distribution<>  len(0,8);

  auto  arr = new Array;

  int  count = len(engine);

    while(count--)
    {
      arr->elements.emplace_back(create_random_element(n));
    }


  return Element(arr);
}


Element
Element::
create_random_integer()
{
  auto  engine = get_engine();

  std::uniform_int_distribution<>  dist(std::numeric_limits<int>::min(),std::numeric_limits<int>::max());

  return Element(dist(engine));
}


Element
Element::
create_random_fp_number()
{
  auto  engine = get_engine();

  std::uniform_real_distribution<>  dist(std::numeric_limits<double>::min(),std::numeric_limits<double>::max());

  return Element(dist(engine));
}


Element
Element::
create_random_string()
{
  return Element(new std::string(get_random_string()));
}




}

