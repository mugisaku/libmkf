#include"mkf_parsecontext.hpp"




namespace mkf{




ParseContext::
ParseContext(const Book&  book_):
book(book_),
root(nullptr)
{
}


ParseContext::
~ParseContext()
{
  delete root;
}




void
ParseContext::
push_error(const charptr&  p)
{
    if(error_p < p)
    {
      error_p        = p;
      error_defchain = defchain;
    }
}


void
ParseContext::
push(const Definition*  def)
{
  defchain.emplace_back(def);
}


void
ParseContext::
pop()
{
    if(defchain.empty())
    {
      report;
      return;
    }


  defchain.pop_back();
}


Node*
ParseContext::
release_root()
{
  auto  node = root          ;
               root = nullptr;

  return node;
}


const Node*
ParseContext::
operator()(const std::string&  s)
{
  delete root;
         root = new Node;


  charptr  p(s);

  auto&  def = book.get_main_definition();

    try
    {
        while(p)
        {
          auto  tmp = p;

          defchain.assign({&def});

          auto  node = new Node(def.get_identifier().data());

          auto  res = def.compare(*this,tmp,*node,0);

            if(!res)
            {
              p.skip_space();

                if(!p)
                {
                  break;
                }


                if(error_defchain.size())
                {
                    for(auto  def: error_defchain)
                    {
                      printf("%s:",def->get_identifier().data());
                    }


                  printf("\n");
                }


              discontinue(ErrorKind::null,error_p,"処理できない文字列が現れました");
            }


            if(p == tmp)
            {
              discontinue(ErrorKind::null,error_p,"ループしました");
            }


          p = tmp;

          root->append(node);
        }
    }


    catch(ErrorKind  k)
    {
      printf("\n以下、できた構文木\n");

      root->print();

      printf("\n構文木終わり\n");

      delete root          ;
             root = nullptr;
    }


  return root;
}


void
ParseContext::
print() const
{
    for(auto  def: defchain)
    {
      printf("%s:",def->get_identifier().data());
    }


  printf("\n");
}


}




