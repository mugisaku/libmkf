#include"expression_operator.hpp"
#include"expression_node.hpp"
#include"cmplr_context.hpp"
#include"../assvm_instruction.hpp"


using namespace assvm;


namespace expression{


Constant
make_constant(const Node&  l, const UnaryOperator&   op, PreContext&  prectx)
{
  auto  l_constant = l.make_constant(prectx);

    if(l_constant.array)
    {
      printf("定数配列には演算できません\n");

      throw Constant::Error();
    }


    if(op == Operator('&'))
    {
      printf("定数のアドレスは取得できません\n");

      throw Constant::Error();
    }


  int  i = l_constant.data;

    switch(op)
    {
      case(Operator('*')):
        printf("定数をアドレスとしては扱えません\n");

        throw Constant::Error();
        break;
      case(Operator('!')): i = !i;break;
      case(Operator('~')): i = ~i;break;
      case(Operator('-')): i = -i;break;
    }


  return Constant(i);
}


namespace{
Constant
make_constant_arithmetic(const Node&  l, const Node&  r, const BinaryOperator&  op, PreContext&  prectx)
{
  auto  l_constant = l.make_constant(prectx);

    if(l_constant.array)
    {
      printf("定数配列には演算できません\n");

      throw Constant::Error();
    }


  auto  r_constant = r.make_constant(prectx);

    if(r_constant.array)
    {
      printf("定数配列には演算できません\n");

      throw Constant::Error();
    }


  int  li = l_constant.data;
  int  ri = r_constant.data;

    switch(op)
    {
      case(Operator('*')): li *= ri; break;
      case(Operator('/')): if(!ri){  printf("ゼロ除算です\n");  throw Constant::Error();}  li /= ri; break;
      case(Operator('%')): if(!ri){  printf("ゼロ除算です\n");  throw Constant::Error();}  li %= ri; break;
      case(Operator('+')): li += ri; break;
      case(Operator('-')): li -= ri; break;
      case(Operator('<','<')): li <<= ri; break;
      case(Operator('>','>')): li >>= ri; break;

      case(Operator('<')    ): li = li <  ri; break;
      case(Operator('<','=')): li = li <= ri; break;
      case(Operator('>')    ): li = li >  ri; break;
      case(Operator('>','=')): li = li >= ri; break;
      case(Operator('=','=')): li = li == ri; break;
      case(Operator('!','=')): li = li != ri; break;
      case(Operator('&')    ): li = li &  ri; break;
      case(Operator('|')    ): li = li |  ri; break;
      case(Operator('^')    ): li = li ^  ri; break;
      case(Operator('&','&')): li = li && ri; break;
      case(Operator('|','|')): li = li || ri; break;
    }


  return Constant(li);
}
}


Constant
make_constant(const Node&  l, const Node&  r, const BinaryOperator&  op, PreContext&  prectx)
{
    switch(op)
    {
      case(Operator('.')):
        printf("できません\n");

        throw Constant::Error();
        break;
      case(Operator('(',')')):
        printf("できません\n");

        throw Constant::Error();
        break;
      case(Operator('[',']')):
        printf("できません\n");

        throw Constant::Error();
        break;
      case(Operator('*')): 
      case(Operator('/')):
      case(Operator('%')):
      case(Operator('+')):
      case(Operator('-')):
      case(Operator('<','<')):
      case(Operator('>','>')):
      case(Operator('<')    ):
      case(Operator('<','=')):
      case(Operator('>')    ):
      case(Operator('>','=')):
      case(Operator('=','=')):
      case(Operator('!','=')):
      case(Operator('&')):
      case(Operator('|')):
      case(Operator('^')):
      case(Operator('&','&')):
      case(Operator('|','|')):
        return make_constant_arithmetic(l,r,op,prectx);
        break;
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
      case(Operator('=')    ):
        printf("定数に代入はできません\n");

        throw Constant::Error();
        break;

      default:;
    }


  throw Constant::Error();
}




}




