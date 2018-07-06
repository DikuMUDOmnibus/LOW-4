
 /***************************************************************************
 *  God Wars Mud originally written by KaVir aka Richard Woolcock.         *
 *  Changes done to the code done by Sage aka Walter Howard, this mud is   *
 *  for the public, however if you run this code it means you agree        *
 *  to the license.low, license.gw, and license.merc have fun. :)          *
***************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"

void load_leaders args(( void ));
void save_leaders args(( void ));

void do_leaders( CHAR_DATA *ch, char *argument )
{
  char buf[MAX_STRING_LENGTH];
  if ( IS_NPC(ch) ) return;

  centre_text("{r--==(++) The Leaders (++)==--{x",ch);
  line(ch);
  	  stc("{c       Name             Player Kills            Player Deaths{x\n\r",ch);
  line(ch);
  sprintf(buf,"      %-13s          %-4d                  %-4d\n\r",leader[0]->name,leader[0]->kills,leader[0]->deaths);
  stc(buf,ch);
  sprintf(buf,"      %-13s          %-4d                  %-4d\n\r",leader[1]->name,leader[1]->kills,leader[1]->deaths);
  stc(buf,ch);
  sprintf(buf,"      %-13s          %-4d                  %-4d\n\r",leader[2]->name,leader[2]->kills,leader[2]->deaths);
  stc(buf,ch);
  line(ch);
  centre_text("{y--==(++) The Fodder (++)==--{x",ch);
  line(ch);
  	  stc("{c       Name             Player Kills            Player Deaths{x\n\r",ch);
  line(ch);
  sprintf(buf,"      %-13s          %-4d                  %-4d\n\r",leader[5]->name,leader[5]->kills,leader[5]->deaths);
  stc(buf,ch);
  sprintf(buf,"      %-13s          %-4d                  %-4d\n\r",leader[4]->name,leader[4]->kills,leader[4]->deaths);
  stc(buf,ch);
  sprintf(buf,"      %-13s          %-4d                  %-4d\n\r",leader[3]->name,leader[3]->kills,leader[3]->deaths); 
  stc(buf,ch);
  line(ch);
  return;
}

void swap_leader1( CHAR_DATA *ch )
{
  strcpy( leader[2]->name, leader[1]->name );
  leader[2]->kills = leader[1]->kills;
  leader[2]->deaths = leader[1]->deaths;

  strcpy( leader[1]->name, leader[0]->name );
  leader[1]->kills = leader[0]->kills;
  leader[1]->deaths = leader[0]->deaths;

  strcpy( leader[0]->name, ch->name );
  leader[0]->kills = ch->pkill;
  leader[0]->deaths = ch->pdeath;
  save_leaders();
  return;
}
  
void swap_leader2( CHAR_DATA *ch )
{
  strcpy( leader[2]->name, leader[1]->name );
  leader[2]->kills = leader[1]->kills;
  leader[2]->deaths = leader[1]->deaths;

  strcpy( leader[1]->name, ch->name );
  leader[1]->kills = ch->pkill;
  leader[1]->deaths = ch->pdeath;
  save_leaders();
  return;
}

void swap_leader3( CHAR_DATA *ch )
{
  strcpy( leader[2]->name, ch->name );
  leader[2]->kills = ch->pkill;
  leader[2]->deaths = ch->pdeath;
  save_leaders();
  return;
}

void swap_death1( CHAR_DATA *ch )
{
  strcpy( leader[5]->name, leader[4]->name );
  leader[5]->kills = leader[4]->kills;
  leader[5]->deaths = leader[4]->deaths;

  strcpy( leader[4]->name, leader[3]->name );
  leader[4]->kills = leader[3]->kills;
  leader[4]->deaths = leader[3]->deaths;

  strcpy( leader[3]->name, ch->name );
  leader[3]->kills = ch->pkill;
  leader[3]->deaths = ch->pdeath;
  save_leaders();
  return;
}

void swap_death2( CHAR_DATA *ch )
{
  strcpy( leader[4]->name, leader[3]->name );
  leader[4]->kills = leader[3]->kills;
  leader[4]->deaths = leader[3]->deaths;

  strcpy( leader[3]->name, ch->name );
  leader[3]->kills = ch->pkill;
  leader[3]->deaths = ch->pdeath;
  save_leaders();
  return;
}

void swap_death3( CHAR_DATA *ch )
{
  strcpy( leader[3]->name, ch->name );
  leader[3]->kills = ch->pkill;
  leader[3]->deaths = ch->pdeath;
  save_leaders();
  return;
}

void update_leaders( CHAR_DATA *ch )
{
  if ( IS_NPC(ch) ) return;

  if ( ch->pkill > leader[0]->kills && !IS_LEADER(ch))
  {
    swap_leader1( ch );
  }
  else if ( ch->pkill > leader[1]->kills && !IS_LEADER(ch) )
  {
    swap_leader2( ch );
  }
  else if ( ch->pkill > leader[2]->kills && !IS_LEADER(ch))
  {
    swap_leader3( ch );
  }

  if ( ch->pdeath > leader[3]->deaths && !IS_FODDER(ch) )
  {
    swap_death1( ch );
  }
  else if ( ch->pdeath > leader[4]->deaths && !IS_FODDER(ch) )
  {
    swap_death2( ch );
  }
  else if ( ch->pdeath > leader[5]->deaths && !IS_FODDER(ch))
  {
    swap_death3( ch );
  }
  else return;
  save_leaders();

  return;
}

  

void init_leaders( )
{
  int i = 0;

   for ( i = 0; i < 6; i++ )
   {
    if (leader[i] == NULL)
      leader[i] = alloc_perm( sizeof(*leader[i]) );
   }

    strcpy(leader[0]->name, "Sam");
    leader[0]->kills  = 0;
    leader[0]->deaths = 0;
    strcpy(leader[1]->name, "Sam");
    leader[1]->kills  = 0;
    leader[1]->deaths = 0;
    strcpy(leader[2]->name, "Sam");
    leader[2]->kills  = 0;
    leader[2]->deaths = 0;
    strcpy(leader[3]->name, "Sam");
    leader[3]->kills  = 0;
    leader[3]->deaths = 0;
    strcpy(leader[4]->name, "Sam");
    leader[4]->kills  = 0;
    leader[4]->deaths = 0;
    strcpy(leader[5]->name, "Sam");
    leader[5]->kills  = 0;
    leader[5]->deaths = 0;
    load_leaders();
}

void load_leaders( )
{
    FILE *fp;

    if ((fp = fopen("leaders.dat","r")) == NULL)
    {
        bug("Creating leaders.dat",0);
        save_leaders();
        return;
    }

    strcpy(leader[0]->name,fread_word(fp));
    leader[0]->kills = fread_number(fp);
    leader[0]->deaths = fread_number(fp);
    strcpy(leader[1]->name,fread_word(fp));
    leader[1]->kills = fread_number(fp);
    leader[1]->deaths = fread_number(fp);
    strcpy(leader[2]->name,fread_word(fp));
    leader[2]->kills = fread_number(fp);
    leader[2]->deaths = fread_number(fp);
    strcpy(leader[3]->name,fread_word(fp));
    leader[3]->kills = fread_number(fp);
    leader[3]->deaths = fread_number(fp);
    strcpy(leader[4]->name,fread_word(fp));
    leader[4]->kills = fread_number(fp);
    leader[4]->deaths = fread_number(fp);
    strcpy(leader[5]->name,fread_word(fp));
    leader[5]->kills = fread_number(fp);
    leader[5]->deaths = fread_number(fp);
    fclose( fp );
}

void save_leaders()
{
    FILE *fp;

    if ((fp = fopen("leaders.dat","w")) == NULL)
    {
        bug("Error saving to leaders.dat",0);
        return;
    }

    fprintf( fp, "%s %d %d\n",leader[0]->name,leader[0]->kills,leader[0]->deaths);
    fprintf( fp, "%s %d %d\n",leader[1]->name,leader[1]->kills,leader[1]->deaths);
    fprintf( fp, "%s %d %d\n",leader[2]->name,leader[2]->kills,leader[2]->deaths);
    fprintf( fp, "%s %d %d\n",leader[3]->name,leader[3]->kills,leader[3]->deaths);
    fprintf( fp, "%s %d %d\n",leader[4]->name,leader[4]->kills,leader[4]->deaths);
    fprintf( fp, "%s %d %d\n",leader[5]->name,leader[5]->kills,leader[5]->deaths);
    fclose( fp );
}


