#include"mkf_book.hpp"
#include"mkf_cursor.hpp"
#include<cstdlib>




namespace mkf{




void
Book::
change_main_definition(Definition&&  def)
{
  main_definition = std::move(def);
}


void
Book::
append_sub_definition(Definition&&  def)
{
  sub_definitions.emplace_back(std::move(def));
}


void
Book::
make(const std::string&  s)
{
  auto  p = s.data();

  const char*  last = nullptr;

  bool  lost_first = false;

    while(*p)
    {
      auto  last = p;

        if(lost_first)
        {
          sub_definitions.emplace_back();

          sub_definitions.back().reset(p);
        }

      else
        {
          main_definition.reset(p);

          lost_first = true;
        }


      skip_space(p);

        if(p == last)
        {
          report;
          printf("**loop**%s\n",p);
          break;
        }
    }
}


void
Book::
clear()
{
  sub_definitions.clear();
}


const Definition*
Book::
find(const std::string&  id) const
{
    for(auto&  def: sub_definitions)
    {
        if(def.get_identifier() == id)
        {
          return &def;
        }
    }


  return nullptr;
}


Node*
Book::
parse(const std::string&  s) const
{
  auto  root = new Node;

  auto        p0 =    s.data();
  auto  const p1 = p0+s.size();

    while(*p0 && (p0 < p1))
    {
      auto  child = new Node(main_definition.get_identifier().data());

      auto  p = p0;

        if(!main_definition.test_solid_flag())
        {
          skip_space(p);
        }


      CompareContext  ctx(p,p1,child);

      auto  res = compare(ctx,main_definition);

        if(!res)
        {
          printf("定義に一致しない文字列が現れました。\n");
          printf("ここまでで、%3d個の一致がありました。以下は失敗のノード\n",root->children.size());

          Printer  pr;

          child->print(pr);

          delete child;

          printf("失敗のノード終わり\n");
          printf("以下は残りのテキスト\n");
          printf("%s\n",p);
          printf("残りのテキスト終わり\n");
/*
          printf("続いて、副定義による解釈\n");

          auto  nd = subparse(p);

          nd.print();

          printf("\n");
*/
          delete root          ;
                 root = nullptr;

          break;
        }


        if(!main_definition.test_solid_flag())
        {
          skip_space(p);
        }
        

        if(p0 == p)
        {
          report;
          printf("ループしました。\n以下残りのテキスト\n%s\n",p0);

          printf("\n残りのテキスト　終わり\n");
          printf("続いて最終ノード\n");

          child->print();

          printf("\n最終ノード　終わり\n");

          delete root          ;
                 root = nullptr;
          break;
        }


      p0 = p;


      root->append(child);
    }


  return root;
}


void
Book::
print(FILE*  f) const
{
  Printer  pr(0,f);

  print(pr);
}


void
Book::
print(Printer&  pr) const
{
  pr.puts("book has a main definition.\n");

  main_definition.print(pr);

  pr.putc('\n',true);

  pr.printf("book has %4d sub definitions.\n",sub_definitions.size());

  pr.printf("--------\n");

    for(auto&  def: sub_definitions)
    {
      def.print(pr);

      pr.putc('\n',true);
    }


  pr.printf("--------\n");
}




}



