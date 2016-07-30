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
push_error(const pp::Character*  p)
{
    if(error_p < p)
    {
      error_p        = p;
      error_defchain = defchain;
    }
}


namespace{
size_t
compare_ctype(const pp::Character*&  p, CType  type, Node&  node)
{
    if(test_ctype_code(p->unicode,type))
    {
      node.append(new Node(get_ctype_name(type),*p++));

      return 1;
    }


  return 0;
}


int
get_unicode(const char*  name)
{
  unsigned int  n;

    if(sscanf(name,"UNICODE_%X",&n) == 1)
    {
      return n;
    }


  return -1;
}
}


bool
ParseContext::
enter(const char*  defname, const pp::Character*&  p, Node&  node)
{
    if(!p->unicode)
    {
      return false;
    }


  auto  ctype = get_ctype(defname);

    if(ctype != CType::null)
    {
      return compare_ctype(p,ctype,node);
    }


  auto  def = book.find(defname);

    if(!def)
    {
      discontinue(ErrorKind::null,p,"定義%sがみつかりません\n",defname);
    }


    if(defchain.size() >= 256)
    {
      discontinue(ErrorKind::null,p,"再帰深度が深すぎます。循環定義の恐れがあります");
    }


  defchain.emplace_back(def);

  auto  child = new Node(defname);

  auto  res = def->compare(*this,p,*child,def->test_noskip_flag()? noskip_flag:0);

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

  error_p = nullptr;

  auto  p = s.data();

    try
    {
        while(p->unicode)
        {
          auto  tmp = p;

          defchain.assign({&def});

          auto  node = new Node(def.get_identifier().data());

          auto  res = def.compare(*this,tmp,*node,def.test_noskip_flag()? noskip_flag:0);

            if(!res)
            {
              pp::skip_spaces(p);

                if(!p->unicode)
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
                if(def.test_noskip_flag())
                {
                  discontinue(ErrorKind::null,p,"ループしました");
                }

              else
                {
                  delete node;

                  pp::skip_spaces(p);

                  continue;
                }
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




