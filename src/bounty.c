/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/***************************************************************************
 *  God Wars Mud originally written by KaVir aka Richard Woolcock.         *
 *  Changes done to the code done by Sage aka Walter Howard, this mud is   *
 *  for the public, however if you run this code it means you agree        *
 *  to the license.low, license.gw, and license.merc have fun. :)          *
***************************************************************************/


#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"

void do_bounty(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char  arg1 [MAX_INPUT_LENGTH];
    char  arg2 [MAX_INPUT_LENGTH];
    char  buf  [MAX_STRING_LENGTH];

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
        
    if (arg1[0] =='\0' || arg2[0] == '\0')
    {
    send_to_char("Place what bounty on who's head?\n\rSyntax: Bounty <victim> <amount>\n\r", ch );
    return;
    }
     
    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL)
    {
    send_to_char( "They are currently not logged in!", ch );
    return;
    }

    if (ch == victim)
    {
	send_to_char( "You cannot place bounties on yourself!\n\r", ch);
	return;
    }    

    if (IS_NPC(victim))
    {
      send_to_char( "You cannot put a bounty on NPCs!\n\r", ch);
      return;
    }
    
    if (!IS_HERO(victim))
    {
      send_to_char( "You cannot place bounties on mortals!\n\r", ch);
      return;
    }

    if (IS_IMMORTAL(victim))
    {
	send_to_char( "You cannot place bounties on gods!\n\r", ch);
	return;
    }


    if ( is_number( arg2 ) )
    {
    int amount;
    amount = atoi(arg2);
 
    if (amount == 0) amount = 1;

    if (amount < 50)
    {
        send_to_char( "You have to put at least 50 questpoints as the bounty.\n\r", ch);
	return;
    }


    if (ch->pcdata->quest < amount)
    {
        send_to_char( "You don't have that many questpoints!\n\r", ch);
        return;
    }

/*    if ((victim->pcdata->bounty + amount) > 10000);
    {
	send_to_char( "Sorry, unable to raise the bounty.\n\r", ch);
	return;
    }
*/
    ch->pcdata->quest -= amount;
    victim->pcdata->bounty += amount;
    sprintf( buf, "You have placed a %d questpoint bounty on %s.\n\r", amount, victim->name);
    send_to_char(buf,ch);  
    sprintf(buf, "%s is now worth %d questpoints.", victim->name,victim->pcdata->bounty );
    do_info(ch,buf);
    return;
  }
  send_to_char("The amount has to be a number\n\rSyntax: Bounty <victim> <value>.\n\r", ch);
  return;
  } 


