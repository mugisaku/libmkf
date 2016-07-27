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


bool
ParseContext::
enter(const char*  defname, charptr&  p, Node&  node)
{
  auto  ctype = get_ctype(defname);

    if(ctype != CType::null)
    {
      return p.compare_ctype(ctype,node);
    }


  auto  def = book.find(defname);

    if(!def)
    {
      discontinue(ErrorKind::null,p,"definition [%s] is not found.",defname);
    }


    if(defchain.size() >= 256)
    {
      discontinue(ErrorKind::null,p,"再帰深度が深すぎます。循環定義の恐れがあります");
    }


  defchain.emplace_back(def);

  auto  child = new Node(defname);

  auto  res = def->compare(*this,p,*child,0);

  defchain.pop_back();

    if(res)
    {
      node.append(child);
    }

  else
    {
      delete child;

      return false;
    }


  return true;
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
get(const Definition&  def, const pp::String&  s)
{
  root = new Node;

  charptr  p(s);

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

                if(!p || !p->unicode)
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
              p.skip_space();

                if(!p)
                {
                  break;
                }


              discontinue(ErrorKind::null,error_p,"[%s %s] ループしました",__FILE__,__func__);
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


const Node*
ParseContext::
operator()(const pp::String&  s)
{
  delete root          ;
         root = nullptr;


  return get(book.get_definition_list().front(),s);
}




const Node*
ParseContext::
operator()(const char*  defname, const pp::String&  s)
{
  delete root          ;
         root = nullptr;


  auto  def = book.find(defname);

    if(!def)
    {
      printf("定義%sが見つかりません\n",defname);

      return nullptr;
    }


  return get(*def,s);
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




