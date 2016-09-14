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




ObjectKind
compile(const Node&  l, const UnaryOperator&   op, Context&  ctx)
{
  auto  lk = l.compile(ctx);

    if(op == Operator('&'))
    {
        if(lk != ObjectKind::reference)
        {
          printf("参照でないオブジェクトのアドレスを取得しようとしました\n");

          throw;
        }


      return ObjectKind::value;
    }


    if(lk == ObjectKind::reference)
    {
      ctx.push("  ld;\n");
    }


    switch(op)
    {
      case(Operator('*')): return ObjectKind::reference;
      case(Operator('&')): break;
      case(Operator('!')): ctx.push("  lnot;\n");break;
      case(Operator('~')): ctx.push("  bnot;\n");break;
      case(Operator('-')): ctx.push("  neg ;\n");break;
    }


  return ObjectKind::value;
}


namespace{


ObjectKind
compile_arithmetic(const Node&  l, const Node&  r, const BinaryOperator&  op, Context&  ctx)
{
  auto  lk = l.compile(ctx);

    if(lk == ObjectKind::reference)
    {
      ctx.push("  ld;\n");
    }


  auto  rk = r.compile(ctx);

    if(rk == ObjectKind::reference)
    {
      ctx.push("  ld;\n");
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


  const bool  flag = ((lk == ObjectKind::constant) &&
                      (rk == ObjectKind::constant));

  return (flag? ObjectKind::constant:ObjectKind::value);
}


ObjectKind
compile_assign(const Node&  l, const Node&  r, const BinaryOperator&  op, Context&  ctx)
{
  auto  rk = r.compile(ctx);

    if(rk == ObjectKind::reference)
    {
      ctx.push("  ld;\n");
    }


  auto  lk = l.compile(ctx);

    if(lk != ObjectKind::reference)
    {
      printf("参照ではないオブジェクトに代入しようとしました;\n");

      throw;
    }


    switch(op)
    {
      case(Operator('<','<','=')): ctx.push("  ashl;\n");break;
      case(Operator('>','>','=')): ctx.push("  ashr;\n");break;
      case(Operator('+','='    )): ctx.push("  aadd;\n");break;
      case(Operator('-','='    )): ctx.push("  asub;\n");break;
      case(Operator('*','='    )): ctx.push("  amul;\n");break;
      case(Operator('/','='    )): ctx.push("  adiv;\n");break;
      case(Operator('%','='    )): ctx.push("  arem;\n");break;
      case(Operator('&','='    )): ctx.push("  aband;\n");break;
      case(Operator('|','='    )): ctx.push("  abor;\n");break;
      case(Operator('^','='    )): ctx.push("  abxor;\n");break;
      case(Operator('='        )): ctx.push("  asn;\n");break;
      default:;
    }


  return ObjectKind::value;
}


}


ObjectKind
compile(const Node&  l, const Node&  r, const BinaryOperator&  op, Context&  ctx)
{
    switch(op)
    {
      case(Operator('.')):
        break;
      case(Operator('(',')')):
        {
          auto  rk = r.compile(ctx);
          auto  lk = l.compile(ctx);

          ctx.push("  cal;\n");
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




