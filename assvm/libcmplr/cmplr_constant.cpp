#include"cmplr_constant.hpp"




Constant::
Constant(int  i):
array(nullptr),
data(i)
{
}


Constant::
Constant(const std::u16string&  s)
{
  array = new ConstantArray;

    for(auto&  c: s)
    {
      array->emplace_back(c);
    }
}


Constant::
Constant(const Constant&   rhs):
array(nullptr)
{
  *this = rhs;
}


Constant::
Constant(Constant&&  rhs) noexcept:
array(nullptr)
{
  *this = std::move(rhs);
}


Constant::
~Constant()
{
  clear();
}




Constant&
Constant::
operator=(const Constant&   rhs)
{
  clear();

  data = rhs.data;

  array = rhs.array? new ConstantArray(*rhs.array):nullptr;

  return *this;
}


Constant&
Constant::
operator=(Constant&&  rhs) noexcept
{
  clear();

  data = rhs.data;

  array = rhs.array          ;
          rhs.array = nullptr;

  return *this;
}


void
Constant::
clear()
{
  delete array          ;
         array = nullptr;
}


void
Constant::
push(Constant&&  cs)
{
    if(!array)
    {
      array = new ConstantArray;
    }


  array->emplace_back(std::move(cs));
}


void
Constant::
print(FILE*  f) const
{
    if(array)
    {
      fprintf(f,"{");

        for(auto&  cs: *array)
        {
          cs.print(f);

          fprintf(f,",");
        }


      fprintf(f,"}");
    }

  else
    {
      fprintf(f,"%d",data);
    }
}




