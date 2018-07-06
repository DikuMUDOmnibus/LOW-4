/* Hmm. An attempt..
     At a godwars battle arena
     Da dun dun dun da..
*/
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
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"
#include "arena.h"

void  clean_arena	args( ( CHAR_DATA *loser, CHAR_DATA *winner ) );
void  do_ainfo		args( ( CHAR_DATA *ch, char *argument ) );

bool is_inarena( CHAR_DATA *ch )
{
  if ( IS_SET(ch->flag2, AFF2_INARENA) )
  {
    stc("You cannot do that while in the arena!\n\r",ch);
    return TRUE;
  }
  else
    return FALSE;
}

void do_decline( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char buf[MAX_STRING_LENGTH];

  if ( IS_NPC(ch) ) return;

  if ( ch->challenged == NULL )
  {
    stc("You have not been challenged.\n\r",ch);
    return;
  }

  if ( !IS_SET(ch->flag2, AFF2_CHALLENGED) )
  {
    stc("You have not been challenged.\n\r",ch);
    return;
  }

  victim = ch->challenged;
  sprintf(buf,"%s has declined %s's challenge.",ch->name, victim->name);
  do_ainfo(ch,buf);
  arena = FIGHT_CLEAR;
  undo_arena(ch);
  return;
}

void do_ainfo( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;

    if ( argument[0] == '\0' )
    {
        return;
    }

    if (!IS_NPC(ch) && IS_IMMORTAL(ch) && IS_SET(ch->act,PLR_WIZINVIS))
        return;

    for ( d = descriptor_list; d != NULL; d = d->next )
    {
        if ( d->connected == CON_PLAYING &&
                !IS_SET(d->character->deaf, CHANNEL_INFO) )
        {
            send_to_char( "[<Arena>] ",d->character );
            send_to_char( argument, d->character );
            send_to_char( " [<Arena>]\n\r",   d->character );
        }
    }

    return;
}

void do_challenge( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MAX_INPUT_LENGTH];
  char buf[MAX_STRING_LENGTH];
 
  argument = one_argument( argument, arg );

  if ( IS_NPC(ch) ) return;

  if ( arena != FIGHT_CLEAR )
  {
    stc("The arena is not ready for a fight at the moment.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Who do you want to challenge?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_world( ch, arg ) ) == NULL )
  {
    stc("They aren't even on the mud.\n\r",ch);
    return;
  }                         

  if ( IS_NPC(victim) )
  {
    stc("Challenge a mobile? You're pathetic.\n\r",ch);
    return;
  }
 
  if ( victim == ch )
  {
    stc("Oh, kill yourself. Fun.\n\r",ch);
    return;
  }

  if ( ch->hit < ch->max_hit )
  {
    stc("You must be fully healed to use the arena.\n\r",ch);
    return;
  }

  if ( victim->hit < victim->max_hit )
  {
    stc("Your victim isn't fully healed.\n\r",ch);
    return;
  }

  if ( victim->level < 3 || ch->level < 3 )
  {
    stc("Only avatars may use the Arena.\n\r",ch);
    return;
  }

  if ( IS_SET(ch->flag2, AFF2_CHALLENGED)
       || IS_SET(ch->flag2, AFF2_CHALLENGER) )
  {
    stc("Uh.  You're already involved in an arena fight.\n\r",ch);
    return;
  }

  if ( IS_SET(victim->flag2, AFF2_CHALLENGED)
       || IS_SET(victim->flag2, AFF2_CHALLENGER) )
  {
    stc("They are already involved in an arena fight.\n\r",ch);
    return;
  }

  ch->challenged = victim;
  victim->challenged = ch;
 ch->arena_timer = 30;
victim->arena_timer = 30;
   //victim->arena_timer = 20;
  sprintf(buf,"%s has challenged %s to a death match.\n",ch->name,victim->name);
  do_info(ch,buf);
  SET_BIT(ch->flag2, AFF2_CHALLENGER);
  SET_BIT(victim->flag2, AFF2_CHALLENGED);
  arena = FIGHT_PRE;
  return;
}

void do_arenaagree( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  ROOM_INDEX_DATA *chroom;
  ROOM_INDEX_DATA *victroom;
  char buf[MAX_STRING_LENGTH];
   OBJ_DATA *obj;
  if ( IS_NPC(ch) ) return;

  if ( !IS_SET(ch->flag2, AFF2_CHALLENGED) )
  {
    stc("You weren't even challenged.\n\r",ch);
    return;
  }


for ( obj = ch->carrying; obj != NULL; obj = obj->next_content )
    {
        if ( obj->chobj != NULL )
        {
	    send_to_char("You cannot enter the arena carrying living objects.\n\r",ch);
	    return;
        }
}
  if ( ch->challenged == NULL )
  {
    stc("Oddly enough, You have been challenged by someone, yet.. You haven't.\n\r",ch);
    REMOVE_BIT(ch->flag2, AFF2_CHALLENGED);
    arena = FIGHT_CLEAR;
    sprintf(buf,"The Arena is Clear.\n");
    do_ainfo(ch,buf);
  }

  victim = ch->challenged;
  sprintf(buf,"%s has accepted %s's challenge.",ch->name, victim->name);
  arena = FIGHT_START;
  SET_BIT(ch->flag2, AFF2_INARENA);
  SET_BIT(victim->flag2, AFF2_INARENA);
  char_from_room(ch);
  char_from_room(victim);
 // victim->arena_timer = 0;
  //ch->arena_timer = 0;
  chroom = get_room_index(number_range(50,70));
  victroom = get_room_index(number_range(50,70));
  if ( victroom == chroom )
   chroom = get_room_index(number_range(50,70));
  char_to_room(ch, chroom);
  char_to_room(victim, victroom);
  stc("The fight has begun! Good luck!\n\r",ch);
  stc("The fight has begun! Good luck!\n\r",victim);
  do_look(ch,"");
  do_look(victim,"");
  do_ainfo(ch,buf);
  return;
}


void clean_arena( CHAR_DATA *loser, CHAR_DATA *winner )
{
  char buf[MAX_STRING_LENGTH];
  REMOVE_BIT(loser->flag2, AFF2_CHALLENGED);
  REMOVE_BIT(loser->flag2, AFF2_CHALLENGER);
  REMOVE_BIT(loser->flag2, AFF2_INARENA   );
  loser->challenged = NULL;
  loser->hit = loser->max_hit;
  loser->move = loser->max_move;
  loser->mana = loser->max_mana;
  char_from_room(loser);
  char_to_room(loser, get_room_index(ROOM_VNUM_ALOSER));

  REMOVE_BIT(winner->flag2, AFF2_CHALLENGED);
  REMOVE_BIT(winner->flag2, AFF2_CHALLENGER);
  REMOVE_BIT(winner->flag2, AFF2_INARENA   );
  winner->challenged = NULL;
  winner->hit = winner->max_hit;
  winner->mana = winner->max_mana;
  winner->move = winner->max_move;
  char_from_room(winner);
  char_to_room(winner, get_room_index(ROOM_VNUM_AWINNER));
  
  do_look(winner,"");
  do_look(loser,"");

  sprintf(buf,"%s has defeated %s!",winner->name, loser->name);
  do_ainfo(winner,buf);
  winner->awins++;
  loser->alosses++;
  arena = FIGHT_CLEAR;
  return;
}
  
void undo_arena( CHAR_DATA *ch )
{
  CHAR_DATA *victim;
  char name[MAX_STRING_LENGTH]; 
 
  if ( ch->challenged != NULL )
  {
    victim = ch->challenged;
    sprintf(name, "%s", victim->name);
    if ( ( victim = get_char_world( ch, name ) ) == NULL )
    {
      REMOVE_BIT(ch->flag2, AFF2_CHALLENGED);
      REMOVE_BIT(ch->flag2, AFF2_CHALLENGER);
      REMOVE_BIT(ch->flag2, AFF2_INARENA);
      ch->challenged = NULL;
    }
    else
    {
      REMOVE_BIT(ch->flag2, AFF2_CHALLENGED);
      REMOVE_BIT(ch->flag2, AFF2_CHALLENGER);
      REMOVE_BIT(ch->flag2, AFF2_INARENA);
      ch->challenged = NULL;    
      REMOVE_BIT(victim->flag2, AFF2_CHALLENGED);
      REMOVE_BIT(victim->flag2, AFF2_CHALLENGER);
      REMOVE_BIT(victim->flag2, AFF2_INARENA);
      if ( victim->in_room->vnum >= 50 && victim->in_room->vnum <= 68 )
  	  clean_arena( ch, victim );
      victim->challenged = NULL;
    }
  }
  else
  {
    if ( IS_SET(ch->flag2, AFF2_CHALLENGED) )
      REMOVE_BIT(ch->flag2, AFF2_CHALLENGED);
    if ( IS_SET(ch->flag2, AFF2_CHALLENGER) )
      REMOVE_BIT(ch->flag2, AFF2_CHALLENGER);
    if ( IS_SET(ch->flag2, AFF2_INARENA) )
      REMOVE_BIT(ch->flag2, AFF2_INARENA);
  }


  if ( ch->in_room->vnum >= 50 && ch->in_room->vnum <= 68 )
  {
    char_from_room(ch);
    char_to_room(ch, get_room_index(ROOM_VNUM_TEMPLE));
  }


  return;
}
