#ifndef ASSVM_CONTEXT_HPP_INCLUDED
#define ASSVM_CONTEXT_HPP_INCLUDED


#include<cstdint>
#include<cstddef>
#include<cstdio>
#include"assvm_program.hpp"
#include"assvm_memory.hpp"


namespace assvm{


struct
FileSet
{
  FILE*   in=nullptr;
  FILE*  out=nullptr;
  FILE*  err=nullptr;

  void  flush_all() const
  {
      if(in ){fflush(in );}
      if(out){fflush(out);}
      if(err){fflush(err);}
  }

  void  close_all()
  {
      if(in ){  fclose(in );  in  = nullptr;}
      if(out){  fclose(out);  out = nullptr;}
      if(err){  fclose(err);  err = nullptr;}
  }

};


struct
Context
{
  static constexpr int  display_flag     = 1;
  static constexpr int  halted_flag      = 2;
  static constexpr int  enable_halt_flag = 4;

  Memory&  memory;

  FileSet  fileset;

  word_t  pc;
  word_t  bp;
  word_t  sp;
  word_t  tm;

  unsigned int  state;


public:
  Context(const Program&  prog, Memory&  mem, const FileSet*  fset=nullptr);

  void    push(word_t  v);
  word_t  pop();

  word_t  get_bottom() const;
  word_t  get_top(   ) const;

  void  set_bottom(word_t  v) const;
  void  set_top(   word_t  v) const;

  word_t  get_instruction();

  void    set_flag(int  f);
  void  unset_flag(int  f);

  bool  test_flag(int  f) const;

  void  step();

};



}




#endif




