#include"mkf_ascii.hpp"
#include<cstring>




namespace mkf{


struct
Pair
{
  const char*  first;

  int  second;

};


namespace{
const Pair
pairs[('~'-' '+3)] =
{
  {"newline",'\n'},
  {"tab",    '\t'},
  {"space",  ' '},

  {"a",'a'},
  {"b",'b'},
  {"c",'c'},
  {"d",'d'},
  {"e",'e'},
  {"f",'f'},
  {"g",'g'},
  {"h",'h'},
  {"i",'i'},
  {"j",'j'},
  {"k",'k'},
  {"l",'l'},
  {"m",'m'},
  {"n",'n'},
  {"o",'o'},
  {"p",'p'},
  {"q",'q'},
  {"r",'r'},
  {"s",'s'},
  {"t",'t'},
  {"u",'u'},
  {"v",'v'},
  {"w",'w'},
  {"x",'x'},
  {"y",'y'},
  {"z",'z'},

  {"A",'A'},
  {"B",'B'},
  {"C",'C'},
  {"D",'D'},
  {"E",'E'},
  {"F",'F'},
  {"G",'G'},
  {"H",'H'},
  {"I",'I'},
  {"J",'J'},
  {"K",'K'},
  {"L",'L'},
  {"M",'M'},
  {"N",'N'},
  {"O",'O'},
  {"P",'P'},
  {"Q",'Q'},
  {"R",'R'},
  {"S",'S'},
  {"T",'T'},
  {"U",'U'},
  {"V",'V'},
  {"W",'W'},
  {"X",'X'},
  {"Y",'Y'},
  {"Z",'Z'},

  {"0",'0'},
  {"1",'1'},
  {"2",'2'},
  {"3",'3'},
  {"4",'4'},
  {"5",'5'},
  {"6",'6'},
  {"7",'7'},
  {"8",'8'},
  {"9",'9'},

  {"exclamation",      '!'},
  {"quotation",        '\"'},
  {"sharp",            '#'},
  {"dollar",           '$'},
  {"percent",          '%'},
  {"ampersand",        '&'},
  {"apostrophe",       '\''},
  {"left_parenthesis", '('},
  {"right_parenthesis",')'},
  {"asterisk",         '*'},
  {"plus",             '+'},
  {"comma",            ','},
  {"hyphen",           '-'},
  {"period",           '.'},
  {"slash",            '/'},
  {"colon",            ':'},
  {"semicolon",        ';'},
  {"less_than",        '<'},
  {"equal",            '='},
  {"greater_than",     '>'},
  {"question",         '?'},
  {"at",               '@'},

  {"left_squasre_bracket",'['},
  {"backslash",           '\\'},
  {"right_square_bracket",']'},
  {"circumflex_accent",   '^'},
  {"grave_accent",        '`'},
  {"low_line",            '_'},
  {"left_curly_bracket",  '{'},
  {"vertical_bar",        '|'},
  {"right_curly_bracket", '}'},
  {"tilde",               '~'},

};
}


const char*
find_ascii_name(int  c)
{
    for(auto&  p: pairs)
    {
        if(p.second == c)
        {
          return p.first;
        }
    }


  return "unknown code";
}


int
find_ascii_code(const char*  name)
{
    if(std::strncmp(name,"ASCII_",6) == 0)
    {
      name += 6;

        for(auto&  p: pairs)
        {
            if(std::strcmp(p.first,name) == 0)
            {
              return p.second;
            }
        }
    }


  return 0;
}


}


