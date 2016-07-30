#include"pp_character.hpp"
#include"pp_unicode.hpp"
#include"pp_utf8chunk.hpp"
#include"pp_folder.hpp"
#include<cstdio>




namespace pp{




Character::
Character(Position  pos, Index  i, char16_t  c):
position(pos),
id_index(i),
unicode(c)
{
}




void
Character::
print(FILE*  f, bool  verbose) const
{
    if(verbose)
    {
      fprintf(f,"[行:%4d]\n",position.line_number  +1);
      fprintf(f,"[列:%4d]\n",position.column_number+1);

      auto  txt = get_text(id_index);

        if(!txt)
        {
          return;
        }


      fprintf(f,"[ファイルID %s]\n",txt->id.size()? txt->id.data():"**anon**");

      auto  p = get_line_pointer(*this);

        if(p)
        {
            for(;;)
            {
              auto  c = *p++;

                if((c == '\n') ||
                   (c == '\0'))
                {
                  break;
                }


              fprintf(f,"%c",c);
            }


          fprintf(f,"\n");

            for(int  n = 0;  n < position.column_number;  ++n)
            {
              auto  bn = get_utf8_byte_number(p);

              p += bn;

                switch(bn)
                {
                  case(1):
                  case(2): fprintf(f," ");break;
                  case(3): fprintf(f,"　");break;
                }
            }


            fprintf(f,"~\n");
        }
    }

  else
    {
      UTF8Chunk  chk(unicode);

      fprintf(f,"%s",chk.codes);
    }
}


}




