#include"assvm_context.hpp"
#include"assvm_program.hpp"
#include<cstdio>
#include<cstdlib>




namespace assvm{


Context::
Context(const Program&  prog, Memory&  mem, const FileSet*  fset):
memory(mem),
pc(prog.main_entry_point),
bp(Memory::size-(word_size  )),
sp(Memory::size-(word_size*2)),
state(0)
{
    if(fset)
    {
      fileset = *fset;
    }


  mem.fill();

  uint8_t*  p = memory.array;

    for(auto  b: prog.binary)
    {
      *p++ = b;
    }
}




word_t
Context::
get_bottom() const
{
  return memory.get32(bp);
}


word_t
Context::
get_top() const
{
  return memory.get32(sp);
}


void
Context::
set_bottom(word_t  v) const
{
  memory.put32(bp,v);
}


void
Context::
set_top(word_t  v) const
{
  memory.put32(sp,v);
}


void
Context::
push(word_t  v)
{
  sp -= word_size;

  memory.put32(sp,v);
}


word_t
Context::
pop()
{
  auto  v = memory.get32(sp);

  sp += word_size;

  return v;
}


word_t
Context::
get_instruction()
{
  return memory.get8u(pc++);
}


void    Context::set_flag(int  f){state |=  f;}
void  Context::unset_flag(int  f){state &= ~f;}

bool  Context::test_flag(int  f) const{return state&f;}


void
Context::
step()
{
    if(test_flag(halted_flag))
    {
      return;
    }


    if(fileset.out && test_flag(display_flag))
    {
      fprintf(fileset.out,"[pc] 0x%05X, [bp] 0x%05X, [sp] 0x%05X, ",pc,bp,sp);
    }


  auto  op = static_cast<Opecode>(get_instruction());

    if(fileset.out && test_flag(display_flag))
    {
      fprintf(fileset.out,"[opcode] %s\n",get_string(op));

      fflush(fileset.out);
    }


    switch(op)
    {
  case(Opecode::nop):
      break;
  case(Opecode::add ): {  auto  t = pop();  set_top(get_top()+t);}break;
  case(Opecode::sub ): {  auto  t = pop();  set_top(get_top()-t);}break;
  case(Opecode::mul ): {  auto  t = pop();  set_top(get_top()*t);}break;
  case(Opecode::div ): {  auto  t = pop();  if(t){set_top(get_top()/t);} else{report;}}break;
  case(Opecode::rem ): {  auto  t = pop();  if(t){set_top(get_top()%t);} else{report;}}break;
  case(Opecode::shl ): {  auto  t = pop();  set_top(get_top()<<t);}break;
  case(Opecode::shr ): {  auto  t = pop();  set_top(get_top()>>t);}break;
  case(Opecode::bor ): {  auto  t = pop();  set_top(get_top() |t);}break;
  case(Opecode::band): {  auto  t = pop();  set_top(get_top() &t);}break;
  case(Opecode::bxor): {  auto  t = pop();  set_top(get_top() ^t);}break;

  case(Opecode::eq  ): {  auto  t = pop();  set_top(get_top() == t);}break;
  case(Opecode::neq ): {  auto  t = pop();  set_top(get_top() != t);}break;
  case(Opecode::lor ): {  auto  t = pop();  set_top(get_top() || t);}break;
  case(Opecode::land): {  auto  t = pop();  set_top(get_top() && t);}break;

  case(Opecode::lt  ): {  auto  t = pop();  set_top(get_top() <  t);}break;
  case(Opecode::lteq): {  auto  t = pop();  set_top(get_top() <= t);}break;
  case(Opecode::gt  ): {  auto  t = pop();  set_top(get_top() >  t);}break;
  case(Opecode::gteq): {  auto  t = pop();  set_top(get_top() >= t);}break;


  case(Opecode::pop):
      pop();
      break;
  case(Opecode::dup):
      push(get_top());
      break;
  case(Opecode::hlt):
        if(test_flag(enable_halt_flag))
        {
          set_flag(halted_flag);
        }
      break;
  case(Opecode::pshz ): push(0);break;
  case(Opecode::psh8 ): push(static_cast< int8_t>(get_instruction()));break;
  case(Opecode::psh8u): push(static_cast<uint8_t>(get_instruction()));break;

  case(Opecode::psh16):
      {
        int  i  = get_instruction()<<8;
             i |= get_instruction()   ;

        push(static_cast<int16_t>(i));
      }
      break;
  case(Opecode::psh16u):
      {
        int  i  = get_instruction()<<8;
             i |= get_instruction()   ;

        push(static_cast<uint16_t>(i));
      }
      break;
  case(Opecode::psh32):
      {
        int  i  = get_instruction()<<24;
             i |= get_instruction()<<16;
             i |= get_instruction()<< 8;
             i |= get_instruction()    ;

        push(static_cast<int32_t>(i));
      }
      break;
  case(Opecode::pshpc): push(pc);break;
  case(Opecode::pshbp): push(bp);break;
  case(Opecode::pshsp): push(sp);break;
  case(Opecode::pshtm): push(tm);break;
  case(Opecode::updpc): pc = pop();break;
  case(Opecode::updbp): bp = pop();break;
  case(Opecode::updsp): sp = pop();break;
  case(Opecode::updtm): tm = pop();break;
  case(Opecode::ld8):
      {
        auto  lp = pop();
        auto  lv = memory.get8(lp);

        push(lv);
      }
      break;
  case(Opecode::ld8u):
      {
        auto  lp = pop();
        auto  lv = memory.get8u(lp);

        push(lv);
      }
      break;
  case(Opecode::ld16):
      {
        auto  lp = pop();
        auto  lv = memory.get16(lp);

        push(lv);
      }
      break;
  case(Opecode::ld16u):
      {
        auto  lp = pop();
        auto  lv = memory.get16u(lp);

        push(lv);
      }
      break;
    case(Opecode::ld32):
      {
        auto  lp = pop();
        auto  lv = memory.get32(lp);

        push(lv);
      }
      break;
    case(Opecode::st8):
      {
        auto  lv = pop();
        auto  lp = pop();

        memory.put8(lp,lv);

        push(lv);
      }
      break;
    case(Opecode::st16):
      {
        auto  lv = pop();
        auto  lp = pop();

        memory.put16(lp,lv);

        push(lv);
      }
      break;
  case(Opecode::st32):
      {
        auto  lv = pop();
        auto  lp = pop();

        memory.put32(lp,lv);

        push(lv);
      }
      break;
  case(Opecode::sx8 ): push(static_cast<  int8_t>(pop()));break;
  case(Opecode::sx16): push(static_cast< int16_t>(pop()));break;
  case(Opecode::tr8 ): push(static_cast< uint8_t>(pop()));break;
  case(Opecode::tr16): push(static_cast<uint16_t>(pop()));break;
  case(Opecode::lnot): set_top(!get_top());break;
  case(Opecode::bnot): set_top(~get_top());break;
  case(Opecode::neg ): set_top(-get_top());break;

  case(Opecode::brz ): {  auto   v = pop();  auto  p = pop();  if(!v){pc = p;}};break;
  case(Opecode::brnz): {  auto   v = pop();  auto  p = pop();  if( v){pc = p;}};break;

  case(Opecode::cal):
    {
//       NEW_BP
//       NEW_SP
//          |
//|    |    |    |
//|[BP]|[PC]|[??]|[??]
//|    |    |    |
      auto  p = pop();

      push(bp);
      push(pc);

      pc = p;

           sp -= word_size;
      bp = sp             ;
//printf("BP = 0x%05X,PC = 0x%05X,SP = 0x%05X\n",bp,pc,sp);
//set_flag(halted_flag);
    } break;
  case(Opecode::ret):
    {
      tm = pop();

      auto  ret_adr = memory.get32(bp+(word_size  ));
      auto  old_bp  = memory.get32(bp+(word_size*2));
//printf("BP = 0x%05X,PC = 0x%05X\n",old_bp,ret_adr);
//set_flag(halted_flag);
      pc = ret_adr;

      sp = bp+(word_size*3);

      bp = old_bp;
    } break;
  case(Opecode::prn):
        if(fileset.err)
        {
          fprintf(fileset.err,"[PRNint] value=%12d, address=%12d\n",get_top(),sp);

          fflush(fileset.err);
        }
      break;
    }
}




}




