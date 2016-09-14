#include"assvm_context.hpp"
#include"assvm_program.hpp"
#include<cstdio>
#include<cstdlib>




namespace assvm{


Context::
Context(const Program&  prog, Memory&  mem, const FileSet*  fset):
memory(mem),
pc(prog.main_entry_point),
bp(Memory::size-(word_size*2)),
sp(Memory::size-(word_size  )),
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




word_t&
Context::
get_bottom() const
{
  return memory.get_word(bp);
}


word_t&
Context::
get_top() const
{
  return memory.get_word(sp);
}


void
Context::
set_bottom(word_t  v) const
{
  memory.get_word(bp) = v;
}


void
Context::
set_top(word_t  v) const
{
  memory.get_word(sp) = v;
}


void
Context::
push(word_t  v)
{
  sp -= word_size;

  memory.get_word(sp) = v;
}


word_t
Context::
pop()
{
  auto  v = memory.get_word(sp);

  sp += word_size;

  return v;
}


word_t
Context::
get_instruction()
{
  return memory.get_byte(pc++);
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
      fprintf(fileset.out,"[pc] %6d, [bp] %6d, [sp] %6d, ",pc,bp,sp);
    }


  auto  op = static_cast<Opecode>(get_instruction());

    if(fileset.out && test_flag(display_flag))
    {
      fprintf(fileset.out,"[opcode] %s\n",get_string(op));
    }


    switch(op)
    {
      case(Opecode::nop):
        break;
      case(Opecode::add ): {  auto  t = pop();  get_top()  += t;}break;
      case(Opecode::sub ): {  auto  t = pop();  get_top()  -= t;}break;
      case(Opecode::mul ): {  auto  t = pop();  get_top()  *= t;}break;
      case(Opecode::div ): {  auto  t = pop();  if(t){get_top()  /= t;} else{report;}}break;
      case(Opecode::rem ): {  auto  t = pop();  if(t){get_top()  %= t;} else{report;}}break;
      case(Opecode::shl ): {  auto  t = pop();  get_top() <<= t;}break;
      case(Opecode::shr ): {  auto  t = pop();  get_top() >>= t;}break;
      case(Opecode::bor ): {  auto  t = pop();  get_top()  |= t;}break;
      case(Opecode::band): {  auto  t = pop();  get_top()  &= t;}break;
      case(Opecode::bxor): {  auto  t = pop();  get_top()  ^= t;}break;

      case(Opecode::asn  ): {  auto&  r = memory.get_word(pop());  r   = get_top();  get_top() = r;}break;
      case(Opecode::aadd ): {  auto&  r = memory.get_word(pop());  r  += get_top();  get_top() = r;}break;
      case(Opecode::asub ): {  auto&  r = memory.get_word(pop());  r  -= get_top();  get_top() = r;}break;
      case(Opecode::amul ): {  auto&  r = memory.get_word(pop());  r  *= get_top();  get_top() = r;}break;
      case(Opecode::adiv ): {  auto&  r = memory.get_word(pop());  r  /= get_top();  get_top() = r;}break;
      case(Opecode::arem ): {  auto&  r = memory.get_word(pop());  r  %= get_top();  get_top() = r;}break;
      case(Opecode::ashl ): {  auto&  r = memory.get_word(pop());  r <<= get_top();  get_top() = r;}break;
      case(Opecode::ashr ): {  auto&  r = memory.get_word(pop());  r >>= get_top();  get_top() = r;}break;
      case(Opecode::abor ): {  auto&  r = memory.get_word(pop());  r  |= get_top();  get_top() = r;}break;
      case(Opecode::aband): {  auto&  r = memory.get_word(pop());  r  &= get_top();  get_top() = r;}break;
      case(Opecode::abxor): {  auto&  r = memory.get_word(pop());  r  ^= get_top();  get_top() = r;}break;

      case(Opecode::eq  ): {  auto  t = pop();  get_top() = (get_top() == t);}break;
      case(Opecode::neq ): {  auto  t = pop();  get_top() = (get_top() != t);}break;
      case(Opecode::lor ): {  auto  t = pop();  get_top() = (get_top() || t);}break;
      case(Opecode::land): {  auto  t = pop();  get_top() = (get_top() && t);}break;

      case(Opecode::lt  ): {  auto  t = pop();  get_top() = (get_top() <  t);}break;
      case(Opecode::lteq): {  auto  t = pop();  get_top() = (get_top() <= t);}break;
      case(Opecode::gt  ): {  auto  t = pop();  get_top() = (get_top() >  t);}break;
      case(Opecode::gteq): {  auto  t = pop();  get_top() = (get_top() >= t);}break;


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
      case(Opecode::psh0):
        push(0);
        break;
      case(Opecode::pshi8):
        push(static_cast<int8_t>(get_instruction()));
        break;
      case(Opecode::pshui8):
        push(static_cast<uint8_t>(get_instruction()));
        break;
      case(Opecode::pshi16):
        {
          int  i  = get_instruction()<<8;
               i |= get_instruction()   ;

          push(static_cast<int16_t>(i));
        }
        break;
      case(Opecode::pshui16):
        {
          int  i  = get_instruction()<<8;
               i |= get_instruction()   ;

          push(static_cast<uint16_t>(i));
        }
        break;
      case(Opecode::pshi32):
        {
          int  i  = get_instruction()<<24;
               i |= get_instruction()<<16;
               i |= get_instruction()<< 8;
               i |= get_instruction()    ;

          push(static_cast<int32_t>(i));
        }
        break;
      case(Opecode::arg):
        {
          auto  n = pop()+3;

          push(bp+(word_size*n));
        }
        break;
      case(Opecode::pshpc):
        push(pc);
        break;
      case(Opecode::pshbp):
        push(bp);
        break;
      case(Opecode::pshsp):
        push(sp);
        break;
      case(Opecode::updpc):
        pc = pop();
        break;
      case(Opecode::updbp):
        bp = pop();
        break;
      case(Opecode::updsp):
        sp = pop();
        break;
      case(Opecode::ld):
        {
          auto  lp = pop();
          auto  lv = memory.get_word(lp);

          push(lv);
        }
        break;
      case(Opecode::st):
        {
          auto  lp = pop();
          auto  lv = pop();

          memory.get_word(lp) = lv;
        }
        break;
      case(Opecode::cal):
        {
          auto  dst = pop();

          push(bp);
          push(pc);

          bp =  sp;
          pc = dst;
        }
        break;
      case(Opecode::ret):
        {
          auto  v = pop();

          sp = bp;

          pc = pop();
          bp = pop();

          auto  n = (std::abs(pop())&0xFF);

            while(n--)
            {
              pop();
            }


          push(v);
        }
        break;
      case(Opecode::lnot): get_top() = !get_top();break;
      case(Opecode::bnot): get_top() = ~get_top();break;
      case(Opecode::neg ): get_top() = -get_top();break;

      case(Opecode::brz ): {  auto   p = pop();  auto  v = pop();  if(!v){pc = p;}};break;
      case(Opecode::brnz): {  auto   p = pop();  auto  v = pop();  if( v){pc = p;}};break;

      case(Opecode::prn):
          if(fileset.err)
          {
            fprintf(fileset.err,"[PRNint] value=%12d, address=%12d\n",get_top(),sp);
          }
        break;
    }
}




}




