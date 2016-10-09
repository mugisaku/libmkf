#ifndef CMPLR_CONSTANT_HPP_INCLUDED
#define CMPLR_CONSTANT_HPP_INCLUDED


#include"typesystem_element.hpp"
#include<string>




struct Constant;


using ConstantArray = std::vector<Constant>;


struct
Constant
{
  struct Error{};

  int  data;

  ConstantArray*  array;

   Constant(int  i=0);
   Constant(const std::u16string&  s);
   Constant(const Constant&   rhs);
   Constant(      Constant&&  rhs) noexcept;
  ~Constant();


  Constant&  operator=(const Constant&   rhs);
  Constant&  operator=(      Constant&&  rhs) noexcept;

  void  clear();

  void  push(Constant&&  cs);

  void  print(FILE*  f=stdout) const;

};




#endif




