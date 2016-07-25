#ifndef MKF_PARSECONTEXT_HPP_INCLUDED
#define MKF_PARSECONTEXT_HPP_INCLUDED


#include"mkf_book.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_ctype.hpp"


namespace mkf{




class
ParseContext
{
  Node*  root;

  std::vector<const Definition*>        defchain;
  std::vector<const Definition*>  error_defchain;

  charptr  error_p;

  const Node*  get(const Definition&  def, const minpp::String&  s);

public:
  const Book&  book;

   ParseContext(const Book&  book_);
  ~ParseContext();


  const Node*  operator()(                      const minpp::String&  s);
  const Node*  operator()(const char*  defname, const minpp::String&  s);

  Node*  release_root();

  void  push_error(const charptr&  p);

  bool  enter(const char*  defname, charptr&  p, Node&  node);

  void  print() const;

};


}


#endif




