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




Character::
operator bool() const
{
  return unicode;
}


void
Character::
print(FILE*  f, bool  verbose) const
{
    if(verbose)
    {
      fprintf(f,"[");

      position.print();

      auto  txt = get_text(id_index);

      fprintf(f," %s]: ",txt? txt->id.data():"**anon**");
    }


  UTF8Chunk  chk(unicode);

  fprintf(f,"%s",chk.codes);
}


}




