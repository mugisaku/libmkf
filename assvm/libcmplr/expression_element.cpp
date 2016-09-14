#include"expression_element.hpp"
#include<new>




namespace expression{




Element::
Element():
kind(ElementKind::null)
{}


Element::
Element(Operand&&  o):
kind(ElementKind::operand),
data(std::move(o))
{}


Element::
Element(const UnaryOperator&  o):
kind(ElementKind::unary_operator),
data(o)
{}


Element::
Element(const BinaryOperator&  o):
kind(ElementKind::binary_operator),
data(o)
{}


Element::
Element(const Element&  rhs):
kind(ElementKind::null)
{
  *this = rhs;
}


Element::
Element(Element&&  rhs) noexcept:
kind(ElementKind::null)
{
  *this = std::move(rhs);
}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(const Element&   rhs)
{
  clear();

  kind = rhs.kind;

    if(kind == ElementKind::operand)
    {
      new(&data.operand) Operand(rhs.data.operand);
    }

  else
    {
      data.operator_ = rhs.data.operator_;
    }
}


Element&
Element::
operator=(Element&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

    if(kind == ElementKind::operand)
    {
      new(&data.operand) Operand(std::move(rhs.data.operand));
    }

  else
    {
      data.operator_ = rhs.data.operator_;
    }
}


Element::
operator ElementKind() const
{
  return kind;
}


Element::
operator Associativity() const
{
    if(kind == ElementKind::unary_operator)
    {
        switch(data.operator_)
        {
          case(Operator('*')):
          case(Operator('&')):
          case(Operator('!')):
          case(Operator('~')):
          case(Operator('-')): return Associativity::right_to_left;
        }
    }

  else
    {
        switch(data.operator_)
        {
          case(Operator('.')):
          case(Operator('(',')')):
          case(Operator('[',']')):
          case(Operator('*')):
          case(Operator('/')):
          case(Operator('%')):
          case(Operator('+')):
          case(Operator('-')):
          case(Operator('<','<')):
          case(Operator('>','>')):
          case(Operator('&')):
          case(Operator('|')):
          case(Operator('^')):
          case(Operator('&','&')):
          case(Operator('|','|')): return Associativity::left_to_right;

          case(Operator('<')    ):
          case(Operator('<','=')):
          case(Operator('>')    ):
          case(Operator('>','=')):
          case(Operator('=','=')):
          case(Operator('!','=')): return Associativity::none;

          case(Operator('<','<','=')):
          case(Operator('>','>','=')):
          case(Operator('+','=')):
          case(Operator('-','=')):
          case(Operator('*','=')):
          case(Operator('/','=')):
          case(Operator('%','=')):
          case(Operator('&','=')):
          case(Operator('|','=')):
          case(Operator('^','=')):
          case(Operator('=')    ): return Associativity::right_to_left;

          default:;
        }
    }


  return Associativity::none;
}


Element::
operator Precedence() const
{
    if(kind == ElementKind::unary_operator)
    {
        switch(data.operator_)
        {
          case(Operator('*')):
          case(Operator('&')):
          case(Operator('!')):
          case(Operator('~')):
          case(Operator('-')): return 0x80;
        }
    }

  else
    {
        switch(data.operator_)
        {
          case(Operator('.')):
          case(Operator('(',')')):
          case(Operator('[',']')): return 0x90;

          case(Operator('*')        ):
          case(Operator('/')        ):
          case(Operator('%')        ): return 0x70;

          case(Operator('+')):
          case(Operator('-')): return 0x60;

          case(Operator('<','<')):
          case(Operator('>','>')): return 0x50;

          case(Operator('<')    ):
          case(Operator('<','=')):
          case(Operator('>')    ):
          case(Operator('>','=')): return 0x40;

          case(Operator('=','=')):
          case(Operator('!','=')): return 0x30;


          case(Operator('&')): return 0x22;
          case(Operator('|')): return 0x21;
          case(Operator('^')): return 0x20;

          case(Operator('&','&')): return 0x11;
          case(Operator('|','|')): return 0x10;

          case(Operator('<','<','=')):
          case(Operator('>','>','=')):
          case(Operator('+','=')):
          case(Operator('-','=')):
          case(Operator('*','=')):
          case(Operator('/','=')):
          case(Operator('%','=')):
          case(Operator('&','=')):
          case(Operator('|','=')):
          case(Operator('^','=')):
          case(Operator('=')    ): return 0x00;

          default:;
        }
    }


  return 0;
}


void
Element::
clear()
{
    switch(kind)
    {
      case(ElementKind::operand):
        data.operand.~Operand();
        break;
    }


  kind = ElementKind::null;
}


void
Element::
print(FILE*  f, bool  parenthesis) const
{
    if(parenthesis)
    {
      fprintf(f,"(");
    }


    switch(kind)
    {
      case(ElementKind::operand):
        data.operand.print(f);
        break;
      case(ElementKind::unary_operator):
      case(ElementKind::binary_operator):
        fprintf(f,"%s",data.operator_.codes);
        break;
    }


    if(parenthesis)
    {
      fprintf(f,")");
    }
}



}




