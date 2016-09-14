#ifndef EXPRESSION_FOLDRESULT_HPP_INCLUDED
#define EXPRESSION_FOLDRESULT_HPP_INCLUDED


namespace expression{


struct
FoldResult
{
  bool  folded;

  int  value;

constexpr FoldResult(      ): folded(false), value(0){};
constexpr FoldResult(int  v): folded( true), value(v){};

};


}


#endif




