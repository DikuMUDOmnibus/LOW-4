/***************************************************************************
 *  God Wars Mud originally written by KaVir aka Richard Woolcock.         *
 *  Changes done to the code done by Sage aka Walter Howard, this mud is   *
 *  for the public, however if you run this code it means you agree        *
 *  to the license.low, license.gw, and license.merc have fun. :)          *
***************************************************************************/
//  For.. Configuration.. To be... vague.

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "merc.h"

void load_config args(( void ));

void initialise_config()
{
    if (config_info == NULL)
	config_info = alloc_perm( sizeof(*config_info) );

    config_info->bonus		= 0;
//    config_info->world		= 0;
    load_config();
}

void load_config()
{
    FILE *fp;

    if ((fp = fopen("config.sys","r")) == NULL)
    {
	bug("Creating config.sys",0);
	save_config();
	return;
    }

    fread_to_eol( fp );
	fread_word(fp);
    config_info->bonus		= fread_number( fp ); 
	config_info->world = fread_number(fp);
    fclose( fp );
}


void save_config()
{
    FILE *fp;

    if ((fp = fopen("config.sys","w")) == NULL)
    {
	bug("Error saving to config.sys",0);
	return;
    }

    fprintf( fp, "Config.sys - Mob Power\n");
    fprintf( fp, "Bonus  %d ",config_info->bonus );
    fprintf(fp,"%d",config_info->world);
    fclose( fp );
}

void do_configuration( CHAR_DATA *ch, char *argument )
{
  char arg[MIL];
  char buf[MSL];
  int value;

  argument = one_argument( argument, arg );

  if ( IS_NPC(ch) ) return;

  if ( arg[0] == '\0' )
  {
    stc("Syntax: configuration <number>\n\r",ch);
    stc("Where <number> is between 0 and 40,\n\r",ch);
    stc("The higher the number, the better the mobs parry|dodge.\n\r",ch);
    sprintf(buf,"Currently set at: %d",config_info->bonus);
    stc(buf,ch);
    return;
  }

  if ( !is_number(arg) )
  {
    stc("You have to enter a number, goddamnit!\n\r",ch);
    return;
  }

  value = atoi(arg);
  
  if ( value < 0 || value > 40 )
  {
    stc("Enter a value between 0 and 40.\n\r",ch);
    return;
  }

  config_info->bonus = value;
  sprintf(buf, "Ok, mob's parry|dodge chance increased by %d.\n\r",value);
  stc(buf,ch);
  save_config();
  return;
}
