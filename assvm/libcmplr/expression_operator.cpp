#include"expression_operator.hpp"
#include"expression_operand.hpp"
#include"expression_node.hpp"
#include"cmplr_context.hpp"
#include"../assvm_instruction.hpp"


using namespace assvm;


namespace expression{


Operator::
Operator(const char*  s):
codes{0}
{
  auto  len = std::strlen(s);

    if(len >= 4)
    {
      throw;
    }


  std::strcpy(codes,s);
}




Type
compile(const Node&  l, const UnaryOperator&   op, Context&  ctx)
{
  auto  l_type = l.compile(ctx);

    if(op == Operator('&'))
    {
        if(l_type != TypeKind::reference)
        {
          printf("参照でないオブジェクトのアドレスを取得しようとしました\n");

          throw;
        }


      return Type(TypeKind::int32);
    }


    if(l_type == TypeKind::reference)
    {
      l_type = l_type.compile_dereference(ctx);
    }


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


  return Type(TypeKind::int32);
}


namespace{


Type
compile_arithmetic(const Node&  l, const Node&  r, const BinaryOperator&  op, Context&  ctx)
{
  auto  l_type = l.compile(ctx);

    if(l_type == TypeKind::reference)
    {
      l_type = l_type.compile_dereference(ctx);
    }


  auto  r_type = r.compile(ctx);

    if(r_type == TypeKind::reference)
    {
      r_type = r_type.compile_dereference(ctx);
    }


    switch(op)
    {
      case(Operator('*'    )): ctx.push("  mul;\n");break;
      case(Operator('/'    )): ctx.push("  div;\n");break;
      case(Operator('%'    )): ctx.push("  rem;\n");break;
      case(Operator('+'    )): ctx.push("  add;\n");break;
      case(Operator('-'    )): ctx.push("  sub;\n");break;
      case(Operator('<','<')): ctx.push("  shl;\n");break;
      case(Operator('>','>')): ctx.push("  shr;\n");break;
      case(Operator('<'    )): ctx.push("  lt;\n");break;
      case(Operator('<','=')): ctx.push("  lteq;\n");break;
      case(Operator('>'    )): ctx.push("  gt;\n");break;
      case(Operator('>','=')): ctx.push("  gteq;\n");break;
      case(Operator('=','=')): ctx.push("  eq;\n");break;
      case(Operator('!','=')): ctx.push("  neq;\n");break;
      case(Operator('&'    )): ctx.push("  band;\n");break;
      case(Operator('|'    )): ctx.push("  bor;\n");break;
      case(Operator('^'    )): ctx.push("  bxor;\n");break;
      case(Operator('&','&')): ctx.push("  land;\n");break;
      case(Operator('|','|')): ctx.push("  lor;\n");break;
      default:;
    }


  const bool  flag = (l_type.test_constant() &&
                      r_type.test_constant());

  return Type();
}


Type
compile_assign(const Node&  l, const Node&  r, const BinaryOperator&  op, Context&  ctx)
{
  auto  l_type = l.compile(ctx);

    if(l_type != TypeKind::reference)
    {
      printf("参照ではないオブジェクトに代入しようとしました;\n");

      throw;
    }


  ctx.push("  dup;//\n");

  l_type = l_type.compile_dereference(ctx);

  auto  r_type = r.compile(ctx);

    if(r_type == TypeKind::reference)
    {
      r_type = r_type.compile_dereference(ctx);
    }


    switch(op)
    {
      case(Operator('<','<','=')): ctx.push("  shl;\n");break;
      case(Operator('>','>','=')): ctx.push("  shr;\n");break;
      case(Operator('+','='    )): ctx.push("  add;\n");break;
      case(Operator('-','='    )): ctx.push("  sub;\n");break;
      case(Operator('*','='    )): ctx.push("  mul;\n");break;
      case(Operator('/','='    )): ctx.push("  div;\n");break;
      case(Operator('%','='    )): ctx.push("  rem;\n");break;
      case(Operator('&','='    )): ctx.push("  band;\n");break;
      case(Operator('|','='    )): ctx.push("  bor;\n");break;
      case(Operator('^','='    )): ctx.push("  bxor;\n");break;
      default:;
    }


  return l_type.compile_assign(ctx);
}


}


Type
compile(const Node&  l, const Node&  r, const BinaryOperator&  op, Context&  ctx)
{
    switch(op)
    {
      case(Operator('.')):
        break;
      case(Operator('(',')')):
        {
          auto  r_type = r.compile(ctx);

            if(r_type != TypeKind::argument_list)
            {
              printf("実引数のリストではありません\n");

              throw;
            }


          auto  l_type = l.compile(ctx);

            if(l_type != TypeKind::function)
            {
              printf("関数ではありません\n");

              throw;
            }


          ctx.push("  pshbp   ;//********************//\n");
          ctx.push("  psh8u 12;//                    //\n");
          ctx.push("  sub     ;//                    //\n");
          ctx.push("  ld32    ;//                    //\n");
          ctx.push("  pshbp   ;//                    //\n");
          ctx.push("  psh8u  8;//関数呼び出しの後始末//\n");
          ctx.push("  sub     ;//                    //\n");
          ctx.push("  ld32    ;//                    //\n");
          ctx.push("  updbp   ;//                    //\n");
          ctx.push("  updsp   ;//                    //\n");
          ctx.push("  pshtm   ;//********************//\n");

          return *l_type.get_referred_type();
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


  return Type();
}




FoldResult
fold(const FoldResult&  l, const UnaryOperator&   op)
{
    if(op == Operator('*'))
    {
      return FoldResult();
    }


    if(l.folded)
    {
        switch(op)
        {
          case(Operator('!')): return FoldResult(!l.value);break;
          case(Operator('~')): return FoldResult(~l.value);break;
          case(Operator('-')): return FoldResult(-l.value);break;
        }
    }


  return FoldResult();
}


FoldResult
fold(const Node&  l, const UnaryOperator&   op, FoldContext&  ctx)
{
  return fold(l.fold(ctx),op);
}


FoldResult
fold(const FoldResult&  l, const FoldResult&  r, const BinaryOperator&  op)
{
    if(!l.folded ||
       !r.folded)
    {
      return FoldResult();
    }


  const int&  lv = l.value;
  const int&  rv = r.value;

    switch(op)
    {
      case(Operator('.')):
        break;
      case(Operator('(',')')):
        {
/*
          auto  rk = r.compile(ctx);
          auto  lk = l.compile(ctx);
*/
        }
        break;
      case(Operator('[',']')):
        break;


      case(Operator('*'    )): return FoldResult(lv* rv);
      case(Operator('/'    )): return FoldResult(lv/ rv);
      case(Operator('%'    )): return FoldResult(lv% rv);
      case(Operator('+'    )): return FoldResult(lv+ rv);
      case(Operator('-'    )): return FoldResult(lv- rv);
      case(Operator('<','<')): return FoldResult(lv<<rv);
      case(Operator('>','>')): return FoldResult(lv>>rv);
      case(Operator('<'    )): return FoldResult(lv< rv);
      case(Operator('<','=')): return FoldResult(lv<=rv);
      case(Operator('>'    )): return FoldResult(lv> rv);
      case(Operator('>','=')): return FoldResult(lv>=rv);
      case(Operator('=','=')): return FoldResult(lv==rv);
      case(Operator('!','=')): return FoldResult(lv!=rv);
      case(Operator('&'    )): return FoldResult(lv& rv);
      case(Operator('|'    )): return FoldResult(lv| rv);
      case(Operator('^'    )): return FoldResult(lv^ rv);
      case(Operator('&','&')): return FoldResult(lv&&rv);
      case(Operator('|','|')): return FoldResult(lv||rv);
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
        break;
      default:;
    }


  return FoldResult();
}


FoldResult
fold(const Node&  l, const Node&  r, const BinaryOperator&  op, FoldContext&  ctx)
{
  return fold(l.fold(ctx),r.fold(ctx),op);
}




}




