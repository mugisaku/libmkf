#include"expression_operator.hpp"
#include"expression_node.hpp"
#include"cmplr_context.hpp"
#include"../assvm_instruction.hpp"


using namespace assvm;


namespace expression{


Value
make_value(const Node&  l, const UnaryOperator&   op, PreContext&  prectx)
{
  auto  l_value = l.make_value(prectx);

    if(op == Operator('&'))
    {
/*
        if(l_value.change_reference_to_pointer())
        {
          printf("参照でないオブジェクトのアドレスを取得しようとしました\n");

          throw;
        }
*/


      return l_value;
    }


    if(l_value.type == TypeKind::reference)
    {
//      l_value.dereference();
    }


/*
    switch(op)
    {
      case(Operator('*')):
          if(l_type != TypeKind::pointer)
          {
            printf("ポインタでないオブジェクトを参照しようとしました\n");

            throw;
          }


        return l_type.make_reference();
        break;
      case(Operator('!')): ctx.push("  lnot;\n");break;
      case(Operator('~')): ctx.push("  bnot;\n");break;
      case(Operator('-')): ctx.push("  neg ;\n");break;
    }
*/


  return Value();
}


Value
make_value(const Node&  l, const Node&  r, const BinaryOperator&  op, PreContext&  prectx)
{
/*
    switch(op)
    {
      case(Operator('.')):
        break;
      case(Operator('(',')')):
        {
          auto  r_type = r.compile(ctx);

            if(r_type != TypeKind::argument_list)
            {
              r_type.print();

              printf("\n実引数のリストではありません\n");

              throw;
            }


          auto  l_type = l.compile(ctx);

            if(l_type != TypeKind::function)
            {
              l_type.print();

              printf("\n関数ではありません\n");

              throw;
            }


//          return *l_type.get_referred_type();
        }
        break;
      case(Operator('[',']')):
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
        return compile_arithmetic(l,r,op,ctx);
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
        return compile_assign(l,r,op,ctx);
        break;

      default:;
    }
*/


  return Value();
}




}




