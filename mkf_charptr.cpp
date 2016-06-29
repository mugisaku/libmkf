#include"mkf_charptr.hpp"
#include<cstring>




namespace mkf{


constexpr int  start_number = 1;


charptr::
charptr(const char*  p0_, const char*  p1_):
p0(p0_),
p1(p1_),
column_number(start_number),
line_number(start_number)
{
}


charptr::
charptr(const std::string&  s):
p0(s.data()         ),
p1(s.data()+s.size()),
column_number(start_number),
line_number(start_number)
{
}




const char&  charptr::operator*() const{return *p0;}

charptr::operator bool() const{return(p0 < p1);}
charptr::operator const char*() const{return p0;}


bool  charptr::operator==(const charptr&  rhs) const{return(p0 == rhs.p0);}
bool  charptr::operator< (const charptr&  rhs) const{return(p0 <  rhs.p0);}


charptr&
charptr::
operator=(const charptr&  rhs)
{
  p0 = rhs.p0;

  column_number = rhs.column_number;
  line_number   =   rhs.line_number;

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
    if(*p0++ == '\n')
    {
      column_number  = start_number;
        line_number += 1;
    }

  else
    {
      column_number += 1;
    }


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
    while(isspace(*p0))
    {
      ++(*this);
    }
}


const char*  charptr::get_raw_pointer() const{return p0;}

int  charptr::get_column_number() const{return column_number;}
int    charptr::get_line_number() const{return   line_number;}




size_t
charptr::
compare_ctype(CType  type, Node&  node)
{
  auto  c = *p0;

    if(test_ctype_code(c,type))
    {
      node.append(new Node(get_ctype_name(type),c));

      ++(*this);

      return 1;
    }


  return 0;
}


size_t
charptr::
compare_string(const char*  string, size_t  length, Node&  node)
{
    if(std::strncmp(p0,string,length) == 0)
    {
        for(int  i = 0;  i < length;  ++i)
        {
          node.append(new Node("<STRING>",p0[i]));
        }


      (*this) += length;

      return length;
    }


  return 0;
}


void
charptr::
print() const
{
  printf("[  line:%4d]\n",  line_number);
  printf("[column:%4d]\n",column_number);

  auto  p = p0;

    if(p)
    {
        for(;;)
        {
          int  c = *p++;

            if(!c || (c == '\n'))
            {
              break;
            }


          fputc(c,stdout);
        }
    }
}


}




