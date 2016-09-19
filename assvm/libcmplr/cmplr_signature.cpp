#include"cmplr_signature.hpp"




Signature::
Signature()
{
}


Signature::
Signature(const mkf::Node&  src)
{
  read(src);
}




void
Signature::
print(FILE*  f) const
{
  type.print(f);

  fprintf(f,"  %s(",name.data());

    if(parameter_list.size())
    {
      auto  it = parameter_list.cbegin();

        for(;;)
        {
          auto&  p = *it++;

          p.print(f);

            if(it == parameter_list.cend())
            {
              break;
            }


          fprintf(f,",");
        }
    }


  fprintf(f,")\n");
}




void
Signature::
read(const mkf::Node&  src)
{
  mkf::Cursor  cur(src);

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "type")
        {
          type.read(nd);
        }

      else
        if(nd == "identifier")
        {
          nd.collect_characters(name);
        }

      else
        if(nd == "parameter")
        {
          parameter_list.emplace_back(nd);
        }


      cur.advance();
    }
}




