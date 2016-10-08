#include"cmplr_value.hpp"
#include"cmplr_declaration.hpp"
#include<cstring>




Value::
Value():
base_address(0),
size(0),
data(nullptr)
{
}


Value::
Value(const std::u16string&  s):
type(ConstCharType().make_array(s.size()+1)),
base_address(0),
size(sizeof(char16_t)*(s.size()+1))
{
  data = new uint8_t[size];

  auto  dst = reinterpret_cast<char16_t*>(data);
  auto  src = s.cbegin();

    while(*src)
    {
      *dst++ = *src++;
    }


  dst = 0;
}


Value::
Value(Type&&  type_, size_t  size_, int  i):
type(std::move(type_)),
base_address(0),
size(size_),
data(new uint8_t[size_])
{
    switch(size)
    {
  case(1):                             *data = i;break;
  case(2): *reinterpret_cast<int16_t*>(data) = i;break;
  case(4): *reinterpret_cast<int32_t*>(data) = i;break;
    }
}


Value::
Value(const Declaration*  decl):
type(decl->make_value().type.make_reference()),
base_address(0),
size(sizeof(uintptr_t)),
data(new uint8_t[sizeof(uintptr_t)])
{
  reinterpret_cast<uintptr_t&>(data) = reinterpret_cast<uintptr_t>(decl);
}


Value::
Value(const Function*  fn):
type(FunctionType()),
base_address(0),
size(sizeof(uintptr_t)),
data(new uint8_t[sizeof(uintptr_t)])
{
  reinterpret_cast<uintptr_t&>(data) = reinterpret_cast<uintptr_t>(fn);
}


Value::
Value(const Value&   rhs) noexcept:
base_address(0),
size(0),
data(nullptr)
{
  *this = rhs;
}


Value::
Value(Value&&  rhs) noexcept:
base_address(0),
size(0),
data(nullptr)
{
  *this = std::move(rhs);
}


Value::
~Value()
{
  clear();
}




Value&
Value::
operator=(const Value&   rhs) noexcept
{
  clear();

  type = rhs.type;

  base_address = rhs.base_address;

  size = rhs.size;

  data = new uint8_t[size+1];

  rhs.copy(data,size);

  data[size] = 0;


  return *this;
}


Value&
Value::
operator=(Value&&  rhs) noexcept
{
  clear();

  type = std::move(rhs.type);

  base_address = rhs.base_address;

  size = rhs.size    ;
         rhs.size = 0;

  data = rhs.data          ;
         rhs.data = nullptr;


  return *this;
}


void
Value::
clear()
{
  type.clear();

  base_address = 0;

  delete[] data         ;
           data= nullptr;

  size = 0;
}


void
Value::
copy(void*  dst, size_t  dst_size) const
{
    if(dst_size < size)
    {
      report;
      throw;
    }


  std::memcpy(dst,data,size);
}




void
Value::
print(FILE*  f) const
{
/*
    if(size <= 4)
    {
      fprintf(f,"%d",data.i);
    }
*/
}




Value       VoidValue(){return Value(VoidType());}
Value       NullptrValue(){return Value(NullptrType());}

Value            CharValue(char16_t  c){return Value(     CharType(),2,c);}
Value       ConstCharValue(char16_t  c){return Value(ConstCharType(),2,c);}
Value       BoolValue(bool  b){return Value(     BoolType(),1,b);}
Value  ConstBoolValue(bool  b){return Value(ConstBoolType(),1,b);}
Value       I8Value(int8_t  i){return Value(     I8Type(),1,i);}
Value  ConstI8Value(int8_t  i){return Value(ConstI8Type(),1,i);}
Value       U8Value(uint8_t  i){return Value(     U8Type(),1,i);}
Value  ConstU8Value(uint8_t  i){return Value(ConstU8Type(),1,i);}
Value       I16Value(int16_t  i){return Value(     I16Type(),2,i);}
Value  ConstI16Value(int16_t  i){return Value(ConstI16Type(),2,i);}
Value       U16Value(uint16_t  i){return Value(     U16Type(),2,i);}
Value  ConstU16Value(uint16_t  i){return Value(ConstU16Type(),2,i);}
Value       I32Value(int32_t  i){return Value(     I32Type(),4,i);}
Value  ConstI32Value(int32_t  i){return Value(ConstI32Type(),4,i);}





