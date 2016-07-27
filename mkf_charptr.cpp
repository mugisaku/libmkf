#include"mkf_charptr.hpp"




namespace mkf{


constexpr int  start_number = 1;


charptr::
charptr():
p0(nullptr),
p1(nullptr)
{
}


charptr::
charptr(const pp::String&  s):
p0(s.data()         ),
p1(s.data()+s.size())
{
}




const pp::Character&  charptr::operator*() const{return *p0;}
const pp::Character*  charptr::operator->() const{return p0;}

charptr::operator bool() const{return(p0 < p1);}


bool  charptr::operator==(const charptr&  rhs) const{return(p0 == rhs.p0);}
bool  charptr::operator!=(const charptr&  rhs) const{return(p0 != rhs.p0);}
bool  charptr::operator< (const charptr&  rhs) const{return(p0 <  rhs.p0);}


charptr&
charptr::
operator=(const charptr&  rhs)
{
  p0 = rhs.p0;
  p1 = rhs.p1;

  return *this;
}


charptr&
charptr::
operator+=(int  n)
{
    while(n--)
    {
      ++(*this);
    }


  return *this;
}


charptr&
charptr::
operator++()
{
  ++p0;

  return *this;
}


charptr
charptr::
operator++(int)
{
  auto  t = *this;

  ++(*this);

  return t;
}


void
charptr::
skip_space()
{
    while(isspace(p0->unicode))
    {
      ++(*this);
    }
}


size_t
charptr::
compare_ctype(CType  type, Node&  node)
{
  auto&  c = *p0;

    if(test_ctype_code(c.unicode,type))
    {
      node.append(new Node(get_ctype_name(type),c));

      ++(*this);

      return 1;
    }


  return 0;
}


bool
charptr::
test(const std::string&  s) const
{
  auto  a = p0;
  auto  b = s.data();
  auto  n = s.size();

    while(n--)
    {
      auto  byte_number = pp::get_utf8_byte_number(b);

      auto  c = pp::to_char16(b,byte_number);

      b += byte_number;

        if(a++->unicode != c)
        {
          return false;
        }
    }


  return true;
}


size_t
charptr::
compare_string(const std::string&  s, Node&  node)
{
    if(test(s))
    {
        for(int  i = 0;  i < s.size();  ++i)
        {
          node.append(new Node(s.data(),*p0++));
        }


      return s.size();
    }


  return 0;
}


}




