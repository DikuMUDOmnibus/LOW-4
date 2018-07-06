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
#include "garou.h"

bool is_garou( CHAR_DATA *ch )
{
  if ( IS_NPC(ch) ) return FALSE;
  if ( IS_CLASS(ch, CLASS_WEREWOLF) || IS_ABOMINATION(ch))
    return TRUE;
  else
    return FALSE;
}

void do_gifts( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf [MAX_STRING_LENGTH];
    char lin [MAX_STRING_LENGTH];

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_WEREWOLF) && !IS_ABOMINATION(ch))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (arg1[0] == '\0' && arg2[0] == '\0')
    { 
	sprintf(lin,"================================================================================\n\r");
	stc(lin, ch);
	stc("                                     Breed\n\r",ch);
	stc(lin, ch);
	sprintf(buf,"        Homid     [ %d ]         Metis    [ %d ]         Lupus       [ %d ]\n\r",
			ch->gifts[HOMID], ch->gifts[METIS], ch->gifts[LUPUS] );
	stc(buf, ch);
        stc(lin, ch);
	stc("                                    Auspice\n\r",ch);
	stc(lin, ch);
	sprintf(buf,"       Ragabash   [ %d ]        Theurge   [ %d ]        Philodox     [ %d ]\n\r",
		      ch->gifts[RAGABASH], ch->gifts[THEURGE], ch->gifts[PHILODOX] );
	stc(buf, ch);
	sprintf(buf,"       Galliard   [ %d ]                                 Ahroun     [ %d ]\n\r",
	      ch->gifts[GALLIARD], ch->gifts[AHROUN] );
	stc(buf, ch);
	stc(lin, ch);
	  stc("                                     Tribe\n\r",ch);
	stc(lin, ch);
	sprintf(buf,"     Black Furies [ %d ]       Wendigo    [ %d ]    Children of Gaia [ %d ]\n\r",
			ch->gifts[BLACKFURIES], ch->gifts[WENDIGO], ch->gifts[CHILDREN] );
	stc(buf, ch);
	sprintf(buf,"     Silver Fangs [ %d ]       Uktena     [ %d ]      Get of Fenris  [ %d ]\n\r",
			ch->gifts[SILVERFANGS], ch->gifts[UKTENA],ch->gifts[GETOFFENRIS] );
	stc(buf, ch);
	sprintf(buf,"      Red Talons  [ %d ]     Shadow Lords [ %d ]     Silent Striders [ %d ]\n\r",
			ch->gifts[REDTALONS], ch->gifts[SHADOWLORDS], ch->gifts[SILENTSTRIDERS] );
	stc(buf, ch);
	sprintf(buf,"      Fianna      [ %d ]                             StarGazers     [ %d ]\n\r",
	ch->gifts[FIANNA], ch->gifts[STARGAZERS]);
	stc(buf, ch);
	stc(lin, ch);
	return;
    }
    if (arg2[0] == '\0')
    {

      if ( !str_cmp(arg1, "ragabash" ) )
      {
        if ( ch->gifts[RAGABASH] == 0 )
        {
	  stc("You have no knowledge of the Gifts of Ragabash.\n\r",ch);
	  return;
	}
	if ( ch->gifts[RAGABASH] >= 1 )
	{
	  divide_to_char(ch);
	  centre_text("The Gifts of Ragabash",ch);
	  divide_to_char(ch);
	  centre_text("Blur of the Milky Eye",ch);
	}
	if ( ch->gifts[RAGABASH] >= 2 )	
	  centre_text("(Scent of Running Water)",ch);
	if ( ch->gifts[RAGABASH] >= 3 )
	  centre_text("Violation",ch);
	if ( ch->gifts[RAGABASH] >= 4 )
	  centre_text("Luna's Blessing",ch);
	if ( ch->gifts[RAGABASH] >= 5 )
	  centre_text("Whelp's Body",ch);
	divide_to_char(ch);
	return;
      }

      if ( !str_cmp(arg1, "lupus") )
      {
	if ( ch->gifts[LUPUS] == 0 )
	{
	  stc("You have no knowledge of the Gifts of Lupus\n\r",ch);
	  return;
	}
	if ( ch->gifts[LUPUS] >= 1 )
	{
	  divide_to_char(ch);
	  centre_text("The Gifts of Lupus",ch);
	  divide_to_char(ch);
	  centre_text("Heightened Senses",ch);
	}
	if ( ch->gifts[LUPUS] >= 2 )
	  centre_text("(Catfeet)",ch);
	if ( ch->gifts[LUPUS] >= 3 )
	  centre_text("Gnaw",ch);
	if ( ch->gifts[LUPUS] >= 4 )
	  centre_text("Elemental Gift",ch);
	if ( ch->gifts[LUPUS] >= 5 )
	  centre_text("Song of the Great Beast",ch);
	divide_to_char(ch);
	return;
      }

      if ( !str_cmp(arg1, "metis") )
      {
	if ( ch->gifts[METIS] == 0 )
	{
	  stc("You have no knowledge of the Gifts of Metis.\n\r",ch);
	  return;
	}
	if ( ch->gifts[METIS] >= 1 )
	{
	  divide_to_char(ch);
	  centre_text("The Gifts of Metis",ch);
	  divide_to_char(ch);
	  centre_text("Quills",ch);
	}
	if ( ch->gifts[METIS] >= 2 )
	  centre_text("Burrow",ch);
	if ( ch->gifts[METIS] >= 3 )
	  centre_text("Eyes of the Cat",ch);
	if ( ch->gifts[METIS] >= 4 )
	  centre_text("Wither Limb",ch);
	if ( ch->gifts[METIS] >= 5 )
	  centre_text("Madness",ch);
	divide_to_char(ch);
	return;
      }

      if ( !str_cmp(arg1, "theurge") )
      {
	if ( ch->gifts[THEURGE] == 0 )
	{
	  stc("You have no knowledge of the Theurge Gifts.\n\r",ch);
	  return;
	}
        else
	{
	  divide_to_char(ch);
	  centre_text("The Gifts of Theurge",ch);
	  divide_to_char(ch);
	  centre_text("Mother's Touch",ch);
	  centre_text("(Grasp the Beyond)",ch);
	  centre_text("Spirit Drain",ch);
	  centre_text("Feral Lobotomy",ch);
	  centre_text("The Malleable Spirit",ch);
          divide_to_char(ch);
	  return;
	}
      }
      if ( !str_cmp(arg1, "Philodox" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of Philodox",ch);
	divide_to_char(ch);
	centre_text("(Resist Pain)",ch);
	centre_text("(King of the Beasts)",ch);
	centre_text("(Strength of Purpose)",ch);
	centre_text("(Weak Arm)",ch);
	centre_text("Wall of Granite",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp(arg1, "Galliard" ))
{
	divide_to_char(ch);
        centre_text("The Gifts of Galliard",ch);
        divide_to_char(ch);
	centre_text("Call of The Wyld",ch);
        centre_text("Klaive",ch);
        centre_text("Song of Rage",ch);
        centre_text("Eye of the Cobra",ch);
        centre_text("Bridge Walker",ch);
        divide_to_char(ch);
        return;
      }
      if ( !str_cmp(arg1, "Ahroun" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of Ahroun",ch);
	divide_to_char(ch);
	centre_text("(Inspiration)",ch);
	centre_text("(Razor Claws)",ch);
	centre_text("(Heart of Fury)",ch);
	centre_text("Clenched Jaw",ch);
	centre_text("(Stoking Fury's Furnace)",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp( arg1, "Black Furies" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Black Furies",ch);
	divide_to_char(ch);
	centre_text("(Coup De Grace)",ch);
	centre_text("Visceral Agony",ch);
	centre_text("Body Wrack",ch);
	centre_text("(Wasp Talons)",ch);
	centre_text("Curse of Aeolus",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp( arg1, "Children of Gaia" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Children of Gaia",ch);
	divide_to_char(ch);
	centre_text("(Luna's Armor)",ch);
	centre_text("Dazzle",ch);
	centre_text("Garou Serenity",ch);
	centre_text("Halo of the Sun",ch);
	centre_text("The Living Wood",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp(arg1, "Get of Fenris" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Get of Fenris",ch);
	divide_to_char(ch);
	centre_text("(Halt the Coward's Flight)",ch);
	centre_text("Snarl of the Predator",ch);
	centre_text("(Might of Thor)",ch);
	centre_text("(Venom Blood)",ch);
	centre_text("(Fenris' Bite)",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp(arg1, "Red Talons") )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Red Talons",ch);
	divide_to_char(ch);
	centre_text("Avalanche",ch);
	centre_text("Barrage",ch);
	centre_text("Gaia's Vengeance",ch);
	centre_text("Quicksand",ch);
	centre_text("Trackless Waste",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp( arg1, "Shadow Lords" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Shadow Lords",ch);
	divide_to_char(ch);
	centre_text("(Fatal Flaw)",ch);
	centre_text("(Aura of Confidence)",ch);
	centre_text("Clap of Thunder",ch);
	centre_text("Icy Chill of Despair",ch);
	centre_text("Paralyzing Stare",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp( arg1, "Silent Striders" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Silent Striders",ch);
	divide_to_char(ch);
	centre_text("(Speed of Thought)",ch);
	centre_text("(Speed Beyond Thought)",ch);
	centre_text("(Messenger's Speed)",ch);
	centre_text("Gate of the Moon",ch);
	centre_text("Reach the Umbra",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp(arg1, "Silver Fangs" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Silver Fangs",ch);
	divide_to_char(ch);
	centre_text("Lambent Flame",ch);
	centre_text("(Silver Claws)",ch);
	centre_text("Mindblock",ch);
	centre_text("Luna's Avenger",ch);
	centre_text("Paws of the Newborn Cub",ch);
	divide_to_char(ch);
	return;
      }
     if ( !str_cmp(arg1, "Fianna") )
      {
        divide_to_char(ch);
        centre_text("The Gifts of Fianna",ch);
        divide_to_char(ch);
        centre_text("Brew",ch);
        centre_text("Strength of the Fianna",ch);
        centre_text("Howl of the Banshee",ch);
        centre_text("Balor's Gaze",ch);
	centre_text("Gift of the Spriggan",ch);
        divide_to_char(ch);
	return;
}
      if ( !str_cmp(arg1, "Stargazers") )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the StarGazers",ch);
	divide_to_char(ch);
	centre_text("(Inner Strength)",ch);
	centre_text("Merciful Blow",ch);
	centre_text("(Preternatural Awareness)",ch);
	centre_text("Circular Attack",ch);
        centre_text("Sight from Beyond",ch);  
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp(arg1, "Uktena" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Uktena",ch);
	divide_to_char(ch);
	centre_text("Dark Shroud",ch);
	centre_text("Spirit of the Bird",ch);
	centre_text("Call Flame Spirit",ch);
	centre_text("Fetish Doll",ch);
	centre_text("Hand of the Earth Lords",ch);
	divide_to_char(ch);
	return;
      }
      if ( !str_cmp(arg1, "Wendigo" ) )
      {
	divide_to_char(ch);
	centre_text("The Gifts of the Wendigo",ch);
	divide_to_char(ch);
	centre_text("(Camouflage)",ch);
	centre_text("Cutting Wind",ch);
	centre_text("Call the Cannibal Spirit",ch);
	centre_text("Heart of Ice",ch);
	centre_text("Chill of the Early Frost",ch);
	divide_to_char(ch);
	return;
      }

      if ( !str_cmp(arg1, "homid") )
      {
        if ( ch->gifts[HOMID] == 0 )
        {
	  stc("You have no knowledge of the Gift of Homid.\n\r",ch);
	  return;
        }
        if ( ch->gifts[HOMID] >= 1 )
        {
	  divide_to_char(ch);
	  centre_text("The Gifts of Homid",ch);
	  divide_to_char(ch);
	  centre_text("(Persuasion)",ch);
	}
	if ( ch->gifts[HOMID] >= 2 )
	  centre_text("Staredown",ch);
	if ( ch->gifts[HOMID] >= 3 )
	  centre_text("Disquiet",ch);
	if ( ch->gifts[HOMID] >= 4 )
	  centre_text("Reshape Object",ch);
	if ( ch->gifts[HOMID] >= 5 )
	  centre_text("Cocoon",ch);
	divide_to_char(ch);
	return;
      }
      else
      {
        do_gifts(ch, "");
        return;
      }
      return;
    }

    if (!str_cmp(arg2,"learn"))
    {
	int improve;
	int cost;
	int max = 5;

if (IS_ABOMINATION(ch))
{
max = 3;
}
	     if (!str_cmp(arg1,"homid"            )) improve = HOMID;
	else if (!str_cmp(arg1,"metis"            )) improve = METIS;
	else if (!str_cmp(arg1,"lupus"            )) improve = LUPUS;
	else if (!str_cmp(arg1,"ragabash"         )) improve = RAGABASH;
	else if (!str_cmp(arg1,"theurge"          )) improve = THEURGE;
	else if (!str_cmp(arg1,"philodox"         )) improve = PHILODOX;
        else if (!str_cmp(arg1,"galliard"	  )) improve = GALLIARD;
 	else if (!str_cmp(arg1,"fianna"         )) improve = FIANNA;  
	else if (!str_cmp(arg1,"ahroun"           )) improve = AHROUN;
	else if (!str_cmp(arg1,"black furies"     )) improve = BLACKFURIES;
        else if (!str_cmp(arg1,"children of gaia" )) improve = CHILDREN;
	else if (!str_cmp(arg1,"get of fenris"    )) improve = GETOFFENRIS;
        else if (!str_cmp(arg1,"red talons"       )) improve = REDTALONS;
	else if (!str_cmp(arg1,"shadow lords"     )) improve = SHADOWLORDS;
	else if (!str_cmp(arg1,"silent striders"  )) improve = SILENTSTRIDERS;
	else if (!str_cmp(arg1,"silver fangs"     )) improve = SILVERFANGS;
	else if (!str_cmp(arg1,"stargazers"       )) improve = STARGAZERS;
	else if (!str_cmp(arg1,"uktena"           )) improve = UKTENA;
	else if (!str_cmp(arg1,"wendigo"          )) improve = WENDIGO;
        else
	{
	    do_gifts(ch,"");
	    return;
	}

	cost = (ch->gifts[improve]+1) * 10;
	arg1[0] = UPPER(arg1[0]);
	if ( ch->gifts[improve] >= max )
	{
	    sprintf(buf,"You have already gained all of the %s gifts.\n\r", arg1);
	    send_to_char(buf,ch);
	    return;
	}

	if ( cost > ch->practice )
	{
	    sprintf(buf,"It costs you %d primal to learn a new %s gift.\n\r", cost, arg1);
	    send_to_char(buf,ch);
	    return;
	}

	ch->gifts[improve] += 1;
	ch->practice -= cost;
	sprintf(buf,"You have learned a new %s gift.\n\r", arg1);
	send_to_char(buf,ch);
	return;
    }

    else send_to_char("To learn a new gift, type: gifts '<name>' learn.\n\r",ch);
    return;
}


/*
 * Homid Gifts
 * Level One  - Persuasion    - Like Awe for Vampires.  Automatic
 * Level Two  - Staredown     - Mobs flee
 * Level Three- Disquiet      - Spell effect, -hit\dam in combat for opponent.
 * Level Four - Reshape Object- Rename objects
 * Level Five - Cocoon        - Damage Reduction
 */

/*
 * Homid - 2 - Staredown 
 */


void do_madness( CHAR_DATA *ch, char *argument )
{
   CHAR_DATA *vch;
   CHAR_DATA *vch_next;
   CHAR_DATA *mount;
   char arg[MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

   argument = one_argument( argument, arg );

   if ( IS_NPC(ch) ) return;
 
   if ( !IS_CLASS(ch, CLASS_WEREWOLF) )
   {
     stc("Huh?\n\r",ch);
     return;
   }
   
if ( ch->gifts[METIS] < 5 )
    {
      stc("You have not learned the Metis gift of Madness.\n\r",ch);
      return;
    }



  if (ch->reina_timer > 0)
    {
        if (ch->reina_timer > 1)
            sprintf(buf,"You may not use madness for another %d seconds.\n\r",ch->reina_timer);
        else
            sprintf(buf,"You may not use madness  for another 1 second.\n\r");
        send_to_char(buf,ch);
        return;
    }

   if ( IS_SET(ch->in_room->room_flags, ROOM_SAFE) )
   {
     stc("Not while in a safe room.\n\r",ch);
     return;
   }

 

    for ( vch = char_list; vch != NULL; vch = vch_next )
    {
        vch_next        = vch->next;

        if ( vch->in_room == NULL )
            continue;
        if ( !IS_NPC(vch) && vch->pcdata->chobj != NULL )
            continue;
        if ( ch == vch )
              continue;
        if ( vch->in_room == ch->in_room )
        {
            if ( ( mount = ch->mount ) != NULL )
            {
                if ( mount == vch )
                continue;
            }
            if (can_see(ch,vch))
            {
              if ( number_range( 1, (7 - ch->gifts[METIS])) ==2 )
              {
                act("A look of concentration crosses $n face.",ch,NULL,vch,TO_ROOM);
		ch->reina_timer = 60;
                stc("You lose control of your mind and you begin to wander around.\n\r",vch);
               // vch->position = POS_STUNNED;
               do_south(vch, "");
	       do_east(vch, "");
		do_east(vch, "");
               do_south(vch, "");
               do_south(vch, "");
               do_west(vch, "");
               do_north(vch, "");
               do_north(vch, "");
               do_east(vch, "");
               do_east(vch, "");
               do_south(vch, "");
                act("$n begins to lose control and, starts to wander around.",vch,NULL,vch,TO_NOTVICT);
                return;
              }
	      else
	      {
                act("A look of concentration crosses $n face.",ch,NULL,vch,TO_ROOM);
	        return;
	      }
	    }
	    else continue;

	    return;
        }
    }

  return;
}

void do_paralyzing( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    argument = one_argument( argument, arg );

    if ( IS_NPC(ch) ) return;

    if ( !IS_CLASS(ch, CLASS_WEREWOLF) )
    {
	stc("Huh?\n\r",ch);
	return;
    }

    if ( ch->gifts[SHADOWLORDS] < 5 )
    {
      stc("You have not learned the Shadow Lords gift of Paralyzing Stare.\n\r",ch);
      return;
    }

    if ( ( victim = get_char_room( ch, arg) ) == NULL )
    {
      stc("They aren't here.\n\r",ch);
      return;
    }

    arg[0] = UPPER(arg[0]);    

    if ( ch->fighting == NULL )
    {
      stc("You must be fighting to use the gift of paralyzing stare.\n\r",ch);
      return;
    }

    if ( victim->fighting == NULL )
    {
      sprintf(buf, "%s is not fighting anyone.", arg);
      stc(buf, ch);
      return;
    }  
    
    if ( IS_NPC(victim) )
    {
    stc("Not on mobiles!\n\r",ch);
    return;
    }

    WAIT_STATE( ch, 16 );
/*
    if ( !IS_NPC(victim) )
    {
      if ( ch->gifts[SHADOWLORDS] < 4 )
      {
	  if ( number_range( 1, 3 ) != 1 )
        {
          act("You stare deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_CHAR);
          act("$n stares deeply into your eyes.",ch,NULL,victim,TO_VICT);
          act("$n stares deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_NOTVICT);
	    return;
        }
      }

      act("You stare into $N's eyes, and $E is paralyzed with fear.",ch,NULL,victim,TO_CHAR);
      act("$n stares deeply into your eyes, and you are paralyzed with fear.",ch,NULL,victim,TO_VICT);
      act("$n stares deeply into $N's eyes, and $E seems paralyzed.",ch,NULL,victim,TO_NOTVICT);
      WAIT_STATE(victim, 40 );
      return;
    }

    else
    {
    */
      if ( ch->gifts[SHADOWLORDS] < 5 )
      {
        if ( number_range( 1, 4 ) != 2 )
        {
          act("You stare deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_CHAR);
          act("$n stares deeply into your eyes.",ch,NULL,victim,TO_VICT);
          act("$n stares deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_NOTVICT);
	    return;
        }
      }

      act("You stare into $N's eyes, and $E seems paralyzed.",ch,NULL,victim,TO_CHAR);
      act("$n stares deeply into your eyes, and you are paralyzed.",ch,NULL,victim,TO_VICT);
      act("$n stares deeply into $N's eyes, and $E seems paralyzed.",ch,NULL,victim,TO_NOTVICT);
      WAIT_STATE(victim, 40 );
      return;
    }

//  return;

//}


void do_staredown( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    argument = one_argument( argument, arg );

    if ( IS_NPC(ch) ) return;

    if ( !IS_CLASS(ch, CLASS_WEREWOLF) && !IS_ABOMINATION(ch))
    {
	stc("Huh?\n\r",ch);
	return;
    }

    if ( ch->gifts[HOMID] < 2 )
    {
      stc("You have not learned the Homid gift of Staredown.\n\r",ch);
      return;
    }

    if ( ( victim = get_char_room( ch, arg) ) == NULL )
    {
      stc("They aren't here.\n\r",ch);
      return;
    }

    arg[0] = UPPER(arg[0]);    

    if ( ch->fighting == NULL )
    {
      stc("You must be fighting to use the gift of Staredown.\n\r",ch);
      return;
    }

    if ( victim->fighting == NULL )
    {
      sprintf(buf, "%s is not fighting anyone.", arg);
      stc(buf, ch);
      return;
    }  

    WAIT_STATE( ch, 16 );

    if ( IS_NPC(victim) )
    {
      if ( ch->gifts[HOMID] < 4 )
      {
	  if ( number_range( 1, 3 ) != 1 )
        {
          act("You stare deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_CHAR);
          act("$n stares deeply into your eyes.",ch,NULL,victim,TO_VICT);
          act("$n stares deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_NOTVICT);
	    return;
        }
      }

      act("You stare into $N's eyes, and $E flees in terror.",ch,NULL,victim,TO_CHAR);
      act("$n stares deeply into your eyes, and you are filled with terror.",ch,NULL,victim,TO_VICT);
      act("$n stares deeply into $N's eyes, and $E flees in terror.",ch,NULL,victim,TO_NOTVICT);
      do_flee( victim, "" );
      return;
    }

    else
    {
      if ( ch->gifts[HOMID] < 5 )
      {
        if ( number_range( 1, 4 ) != 2 )
        {
          act("You stare deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_CHAR);
          act("$n stares deeply into your eyes.",ch,NULL,victim,TO_VICT);
          act("$n stares deeply into $N's eyes, but nothing happens.",ch,NULL,victim,TO_NOTVICT);
	    return;
        }
      }

      act("You stare into $N's eyes, and $E flees in terror.",ch,NULL,victim,TO_CHAR);
      act("$n stares deeply into your eyes, and you are filled with terror.",ch,NULL,victim,TO_VICT);
      act("$n stares deeply into $N's eyes, and $E flees in terror.",ch,NULL,victim,TO_NOTVICT);
      do_flee( victim, "" );
      return;
    }

  return;

}

void do_disquiet( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    AFFECT_DATA af;
    char arg [MAX_INPUT_LENGTH];
    int sn;
    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_WEREWOLF) && !IS_ABOMINATION(ch)) 
    {
      send_to_char("Huh?\n\r", ch);
      return;
    }

    if ( ch->gifts[HOMID] < 3 )
    {
      send_to_char("You have not learned the Homid gift of Disquiet.\n\r", ch);
      return;
    }

    if ( ( victim = get_char_room(ch, arg) ) == NULL ) 
    {
      stc("They are not here.\n\r",ch);
      return;
    }

    if ( is_safe( ch, victim) ) return;

    if ( ch->gnosis[GCURRENT] < 1 )
    {
      stc("You need one point of gnosis power to use the gift of Disquiet.\n\r",ch);
      return;
    }

   if ( ( sn = skill_lookup( "disquiet" ) ) < 0 )
    {
        send_to_char( "Bug - please inform a coder.\n\r", ch );
        return;
    }
/* TIJMOD: 29/12/99
 * Needs a slot number and a skill "disquiet"
 * other wise crashes out when player type affects
 */
    af.type	 = sn;
    af.duration  = ch->gifts[HOMID];
    af.location  = APPLY_DAMROLL;
    af.modifier  = -( ch->gifts[HOMID] * 5 );
    af.bitvector = 0;
    affect_to_char( victim, &af );

    af.type	 = sn;
    af.duration  = ch->gifts[HOMID];
    af.location  = APPLY_HITROLL;
    af.modifier  = -( ch->gifts[HOMID] * 5 );
    af.bitvector = 0;
    affect_to_char( victim, &af );

    ch->gnosis[CURRENT]--;
    act("Your eyes glow a sinister red as you glare at $N.",ch,NULL,victim,TO_CHAR);
    act("$n's eyes glow a sinister red as $e glares at you.\n\rYou feel odd.",ch,NULL,victim,TO_VICT);
    act("$n's eyes glow a sinister red as $e glares at $N.",ch,NULL,victim,TO_NOTVICT);
    
    return;

}

void do_reshape(CHAR_DATA *ch, char *argument)
{
    char arg1[MAX_STRING_LENGTH];
    char arg2[MAX_STRING_LENGTH];
    OBJ_DATA *obj; 
 
    argument=one_argument(argument,arg1);
    strcpy(arg2,argument);

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch,CLASS_WEREWOLF))
    {
      send_to_char("Huh?\n\r",ch);
      return;
    }

    if (ch->gifts[HOMID] < 4)
    {
      send_to_char("You have not achieved the Homid gift of Reshape Object.\n\r",ch);
      return;
    }

    if (arg1 == NULL || arg2 == NULL)
    {
       send_to_char("Syntax: Reshape (Item) (Description).\n\r",ch);
       return;
    }

    if ( ( obj = get_obj_carry( ch,arg1 ) ) == NULL )
    {
      send_to_char("You dont have that item.\n\r",ch);
      return;
    }
 if (IS_SET(obj->quest, QUEST_RELIC))
  {
      send_to_char("Not on a relic.\n\r",ch);
      return;
  }
  if (IS_SET(obj->quest, QUEST_ARTIFACT))
  {
      send_to_char("Not on an Artifact.\n\r",ch);
      return;
  }  

    if (strlen(arg2) > 40 || strlen(arg2) < 3)
    {
      send_to_char("The name should be between 3 and 40 characters.\n\r",ch);
      return;
    }

       if( !str_cmp(arg2, "NONAME") || !str_cmp(arg2, "NONAME") ||
!str_cmp(arg2, "NONAME") || !str_cmp(arg2, "NONAME"))
    {
        send_to_char( "You failed!\r\n", ch);
        return;
    }


    free_string(obj->name);
    obj->name = str_dup(arg2);
    free_string(obj->short_descr);
    obj->short_descr=str_dup(arg2);
    if (obj->questmaker != NULL) free_string(obj->questmaker);
    obj->questmaker = str_dup(ch->name);
    send_to_char("Ok.\n\r",ch);
    return;
}

void do_cocoon( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC(ch) ) return;

    if ( !IS_CLASS(ch, CLASS_WEREWOLF) )
    {
	stc("Huh?\n\r",ch);
	return;
    }

    if ( ch->gifts[HOMID] < 5 )
    {
      stc("You haven't learned the Homid gift of Cocoon.\n\r",ch);
      return;
    }


    if ( IS_GAR1(ch, WOLF_COCOON) )
    {
      stc("Your cocoon breaks and falls to the ground.\n\r",ch);
      act("$n's cocoon breaks and falls to the ground.",ch,NULL,NULL,TO_ROOM);
      REMOVE_BIT(ch->garou1, WOLF_COCOON);
      return;
    } 

    if ( ch->gnosis[GCURRENT] < 2 )
    {
      stc("You do not have enough gnosis to use Cocoon.\n\r",ch);
      return;
    }

    else
    {
      stc("Your body is surrounded by a thick, opaque epidermis.\n\r",ch);
      act("$n's body is surrounded by a thick, opaque epidermis.",ch,NULL,NULL,TO_ROOM);
      SET_BIT(ch->garou1, WOLF_COCOON);
      ch->gnosis[GCURRENT]--;
      return;
    }
  return;
}

/*
 * Metis Gifts
 * Level One  - Gift of the Porcupine - Quills
 * Level Two  - Burrow          - Like Demon Travel
 * Level Three- Eyes of the Cat - Nightsight
 * Level Four - Wither Limb	- Withers a limb, easier on NPCs
 * Level Five - Totem Gift	- Random, Special Power. Ooo.
 */

void do_quills( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC(ch) ) return;

    if ( !IS_CLASS(ch, CLASS_WEREWOLF) && !IS_ABOMINATION(ch)) 
    {
   	stc("Huh?\n\r",ch);
	return;
    }

    if ( ch->gifts[METIS] < 1 )
    {
        stc("You haven't learned the Gift of the Porcupine.\n\r",ch);
	return;
    }

    if ( IS_SET(ch->newbits, NEW_QUILLS) )
    {
        stc("Your quills soften and twist into fur.\n\r",ch);
	act("$n's quills soften and revert back to fur.",ch,NULL,NULL,TO_ROOM);
        REMOVE_BIT(ch->newbits, NEW_QUILLS);
	return;
    }

    if ( !IS_SET(ch->newbits, NEW_QUILLS) )
    {
        stc("Your fur becomes bristly and sharp.\n\r",ch);
	act("$n's fur becomes bristly and sharp.",ch,NULL,NULL,TO_ROOM);
	SET_BIT(ch->newbits, NEW_QUILLS);
	return;
    }
  return;
}

void do_burrow( CHAR_DATA *ch, char *argument )
{
    char      arg [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if ( !IS_CLASS(ch, CLASS_WEREWOLF) && !IS_ABOMINATION(ch)) 
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }

    if ( ch->gifts[METIS] < 2 )
    {
        send_to_char("You haven't learned the Metis gift of Burrow.\n\r", ch);
        return;
    }

    if ( arg[0] == '\0' )
    {
        send_to_char("Burrow to who?\n\r", ch);
        return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
        send_to_char( "They are not here.\n\r", ch );
        return;
    }

    if ( IS_NPC(victim) )
    {
        send_to_char( "Not on NPC's.\n\r", ch );
        return;
    }

    if (IS_IMMUNE(victim, IMM_TRAVEL))
    {
        send_to_char("I don't think they want you to do that.\n\r",ch);
        return;
    }        

    if ( victim == ch )
    {
        send_to_char( "You cannot burrow to yourself.\n\r", ch);
        return;
    }

    if ( victim->level != LEVEL_AVATAR || !IS_CLASS(victim, CLASS_WEREWOLF))
    {
        send_to_char( "Nothing happens.\n\r", ch );
        return;
    }

    if (victim->in_room == NULL)
    {
        send_to_char( "Nothing happens.\n\r", ch );
        return;
    }

    send_to_char("You burrow into the ground.\n\r",ch);
    act("$n burrows into the ground.",ch,NULL,NULL,TO_ROOM);
    char_from_room(ch);
    char_to_room( ch, victim->in_room );
    do_look(ch,"");
    send_to_char("You burrow out of the ground.\n\r",ch);
    act("$n burrows out of the ground.",ch,NULL,NULL,TO_ROOM);
    return;
}
  
// Eyes of the Cat - Nightsight.  clan.c

void do_wither( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA *obj;
    char arg[MAX_INPUT_LENGTH];
    bool blah = FALSE;
    int chance = 0;

    argument = one_argument( argument, arg );

    if ( IS_NPC(ch) ) return;

    if ( !IS_CLASS(ch, CLASS_WEREWOLF)  && !IS_VAMPIRE(ch))
   {
	stc("Huh?\n\r",ch);
	return;
    }

if IS_VAMPIRE(ch) 
{
do_withering(ch, arg);
return;
}
    if ( ch->gifts[METIS] < 4 )
    {
	stc("You haven't learned the Metis gift of Wither Limb.\n\r",ch);
	return;
    }

    if ( ch->gnosis[GCURRENT] < 3 )
    {
	stc("You do not have enough gnosis power stored to use the gift of Wither Limb.\n\r",ch);
	return;
    }

    if ( arg[0] == '\0' )
    {
	stc("Who's limb do you wish to wither?\n\r",ch);
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	stc("They aren't here.\n\r",ch);
	return;
    }

    if ( IS_ARM_R(victim, LOST_ARM) && IS_ARM_L(victim, LOST_ARM) )
    {
	stc("They have already lost both their arms.\n\r",ch);
	return;
    }
 
    WAIT_STATE(ch, 32);
    ch->gnosis[CURRENT] -= 3;
    if ( IS_NPC( victim ) )
    {
      chance = number_range( 45, 55 );

      if ( number_percent( ) > chance )
      {
	stc("Nothing happened.\n\r",ch);
	return;
      }

       if ( !IS_ARM_R(victim, LOST_ARM) )
         blah = FALSE;
       else blah = TRUE;

	 if ( !blah )
         {
 	  if (!IS_ARM_R(victim,LOST_ARM))
	      SET_BIT(victim->loc_hp[3],LOST_ARM);
	  if (!IS_BLEEDING(victim,BLEEDING_ARM_R))
	      SET_BIT(victim->loc_hp[6],BLEEDING_ARM_R);
	  if (IS_BLEEDING(victim,BLEEDING_HAND_R))
	      REMOVE_BIT(victim->loc_hp[6],BLEEDING_HAND_R);
	  act("You concentrate deeply and $N's arm starts to wither!",ch,NULL,victim,TO_CHAR);
	  act("$n's eyes glow dark red as $e gazes at you, and your arm begins withering!",ch,NULL,victim,TO_NOTVICT);
	  act("$n gazes evilly at $N, and $S arm begins withering!",ch,NULL,victim,TO_VICT);
	  make_part(victim,"arm");
	  if (IS_ARM_L(victim,LOST_ARM) && IS_ARM_R(victim,LOST_ARM))
	  {
	      if ((obj = get_eq_char( victim, WEAR_ARMS )) != NULL)
		  take_item(victim,obj);
	  }
	  if ((obj = get_eq_char( victim, WEAR_WIELD )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_HANDS )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_WRIST_R )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_FINGER_R )) != NULL)
	      take_item(victim,obj);
	  return;
         }
       
	 else if ( blah )
	 {
 	  if (!IS_ARM_L(victim,LOST_ARM))
	      SET_BIT(victim->loc_hp[2],LOST_ARM);
	  else blah = TRUE;
	  if (!IS_BLEEDING(victim,BLEEDING_ARM_L))
	      SET_BIT(victim->loc_hp[6],BLEEDING_ARM_L);
	  if (IS_BLEEDING(victim,BLEEDING_HAND_L))
	      REMOVE_BIT(victim->loc_hp[6],BLEEDING_HAND_L);
	  act("You concentrate deeply and $N's arm starts to wither!",ch,NULL,victim,TO_CHAR);
	  act("$n's eyes glow dark red as $e gazes at you, and your arm begins withering!",ch,NULL,victim,TO_NOTVICT);
	  act("$n gazes evilly at $N, and $S arm begins withering!",ch,NULL,victim,TO_VICT);
	  make_part(victim,"arm");
	  if (IS_ARM_L(victim,LOST_ARM) && IS_ARM_R(victim,LOST_ARM))
	  {
	      if ((obj = get_eq_char( victim, WEAR_ARMS )) != NULL)
		  take_item(victim,obj);
	  }
	  if ((obj = get_eq_char( victim, WEAR_WIELD )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_HANDS )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_WRIST_L )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_FINGER_L )) != NULL)
	      take_item(victim,obj);
	  return;
        }
    }

    else if ( !IS_NPC(victim) )
    {
	chance = 15;
      if ( number_percent( ) > chance )
      {
	act("You gaze intently at $N.\n\rNothing happens.",ch,NULL,victim,TO_CHAR);
	act("$n gazes eerily at you.\n\rNothing happens.",ch,NULL,victim,TO_VICT);
	act("$n gazes eerily at $N.",ch,NULL,victim,TO_NOTVICT);
	return;
      }


       if ( !IS_ARM_R(victim, LOST_ARM) )
         blah = FALSE;
       else blah = TRUE;

	 if ( !blah )
         {
 	  if (!IS_ARM_R(victim,LOST_ARM))
	      SET_BIT(victim->loc_hp[3],LOST_ARM);
	  if (!IS_BLEEDING(victim,BLEEDING_ARM_R))
	      SET_BIT(victim->loc_hp[6],BLEEDING_ARM_R);
	  if (IS_BLEEDING(victim,BLEEDING_HAND_R))
	      REMOVE_BIT(victim->loc_hp[6],BLEEDING_HAND_R);
	  act("You concentrate deeply and $N's arm starts to wither!",ch,NULL,victim,TO_CHAR);
	  act("$n's eyes glow dark red as $e gazes at you, and your arm begins withering!",ch,NULL,victim,TO_NOTVICT);
	  act("$n gazes evilly at $N, and $S arm begins withering!",ch,NULL,victim,TO_VICT);
	  make_part(victim,"arm");
	  if (IS_ARM_L(victim,LOST_ARM) && IS_ARM_R(victim,LOST_ARM))
	  {
	      if ((obj = get_eq_char( victim, WEAR_ARMS )) != NULL)
		  take_item(victim,obj);
	  }
	  if ((obj = get_eq_char( victim, WEAR_WIELD )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_HANDS )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_WRIST_R )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_FINGER_R )) != NULL)
	      take_item(victim,obj);
	  return;
	 }

	 else if ( blah )
	 {
 	  if (!IS_ARM_L(victim,LOST_ARM))
	      SET_BIT(victim->loc_hp[2],LOST_ARM);
	  else blah = TRUE;
	  if (!IS_BLEEDING(victim,BLEEDING_ARM_L))
	      SET_BIT(victim->loc_hp[6],BLEEDING_ARM_L);
	  if (IS_BLEEDING(victim,BLEEDING_HAND_L))
	      REMOVE_BIT(victim->loc_hp[6],BLEEDING_HAND_L);
	  act("You concentrate deeply and $N's arm starts to wither!",ch,NULL,victim,TO_CHAR);
	  act("$n's eyes glow dark red as $e gazes at you, and your arm begins withering!",ch,NULL,victim,TO_NOTVICT);
	  act("$n gazes evilly at $N, and $S arm begins withering!",ch,NULL,victim,TO_VICT);
	  make_part(victim,"arm");
	  if (IS_ARM_L(victim,LOST_ARM) && IS_ARM_R(victim,LOST_ARM))
	  {
	      if ((obj = get_eq_char( victim, WEAR_ARMS )) != NULL)
		  take_item(victim,obj);
	  }
	  if ((obj = get_eq_char( victim, WEAR_WIELD )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_HANDS )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_WRIST_L )) != NULL)
	      take_item(victim,obj);
	  if ((obj = get_eq_char( victim, WEAR_FINGER_L )) != NULL)
	      take_item(victim,obj);
	  return;
        }
      }
  return;
}

/* Lupus Gifts
 * Heightened Senses-do_truesight
 * Catfeet-Auto
 * Gnaw
 * Elemental Gift
 * Song of the Great Beast
 */
void do_heightened( CHAR_DATA *ch, char *argument )
{
  if ( IS_NPC(ch) ) return;

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[LUPUS] < 1 )
  {
    stc("You must obtain level one Lupus to use Heightened Senses.\n\r",ch);
    return;
  }

    if ( IS_SET(ch->act, PLR_HOLYLIGHT) )
    {
        REMOVE_BIT(ch->act, PLR_HOLYLIGHT);
        send_to_char( "Your senses return to normal.\n\r", ch );
    }
    else
    {
        SET_BIT(ch->act, PLR_HOLYLIGHT);
        send_to_char( "Your senses increase to incredible proportions.\n\r", ch);
    }
    
    return;
}

void do_gnaw( CHAR_DATA *ch, char *argument )
{
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[LUPUS] < 3 )
  {
    stc("You must obtain level three Lupus to use Gnaw.\n\r",ch);
    return;
  }

    stc("You try to gnaw through your restrains.\n\r",ch);
    act("$n gnaws at $s restrains.",ch,NULL,NULL,TO_ROOM);

    if ( IS_EXTRA(ch, TIED_UP) )
    {
        act("The ropes restraining you snap.",ch,NULL,NULL,TO_CHAR);
        act("The ropes restraining $n snap.",ch,NULL,NULL,TO_ROOM);
        REMOVE_BIT(ch->extra, TIED_UP);
    }
    if (is_affected(ch, gsn_web))
    {
        act("The webbing entrapping $n breaks away.",ch,NULL,NULL,TO_ROOM);
        send_to_char("The webbing entrapping you breaks away.\n\r",ch);
        affect_strip(ch, gsn_web);
    }
    if (IS_AFFECTED(ch, AFF_WEBBED))
    {
        act("The webbing entrapping $n breaks away.",ch,NULL,NULL,TO_ROOM);
        send_to_char("The webbing entrapping you breaks away.\n\r",ch);
        REMOVE_BIT(ch->affected_by, AFF_WEBBED);
    }
    if (IS_AFFECTED(ch, AFF2_TENDRILS))
    {
      act("The tendrils entrapping $n break away.",ch,NULL,NULL,TO_ROOM);
      send_to_char("The tendrils entrapping you break away.\n\r",ch);
      REMOVE_BIT(ch->affected_by, AFF2_TENDRILS);
    }

    return;
}

void do_elementalgift( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  int dam;

  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[LUPUS] < 4 )
  {
    stc("You must obtain level 5 Lupus to use Elemental Gift.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 1 )
  {
    stc("You must have one point of Gnosis to use this power.\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    stc("You cannot find them here.\n\r",ch);
    return;
  }

  dam = ch->gifts[LUPUS] * 100;
  if ( IS_NPC(victim) ) dam *= 3;
  if ( IS_CLASS(victim, CLASS_VAMPIRE) ) dam *= 2.3;

  act("You call upon the forces of Gaia to annihilate $N.",ch,NULL,victim,TO_CHAR);
  act("$n throws back $s head and howls loudly, causing the room to shake.\nThe room turns dark, and a blast of elemental fire consumes you.",ch,NULL,victim,TO_VICT);
  act("$n throws back $s head and howls loudly, causing the room to shake.\nThe room turns dark.\nA blast of elemental fire consumes $N!",ch,NULL,victim,TO_NOTVICT);
  mage_damage(ch, victim, dam, "elemental blast", MAGEDAM_FIRE);
  ch->gnosis[GCURRENT] -= 1;
  WAIT_STATE(ch, 16);
  return;
}  

void do_songbeast( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  AFFECT_DATA af;

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[LUPUS] < 5 )
  {
    stc("You must obtain level 5 Lupus to use this power.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 3 )
  {
    stc("You need 3 points of gnosis to use this power.\n\r",ch);
    return;
  }

    if ( ch->pcdata->followers > 3 )
    {
      stc("Nothing happens..\n\r",ch);
      return;
    }

    ch->pcdata->followers++;

    victim=create_mobile( get_mob_index( MOB_VNUM_GUARDIAN ) );
    victim->short_descr = str_dup("A huge, bloodthirsty Dinosaur");
    victim->name = str_dup("dinosaur");
    victim->long_descr = str_dup("A huge dinosaur towers over you, roaring loudly and looking for prey.\n\r");
    victim->level = 500;
    victim->hit = 15000;
    victim->max_hit = 15000;
    victim->hitroll = 250;
    victim->damroll = 250;
    victim->armor = -1500;
    SET_BIT(victim->act, ACT_NOEXP);
    
    act("You howl loudly at the sky.\n\rThe ground beneath your feet begins to shake.\n\rA huge dinosaur bursts from the ground with a loud roar!",ch,NULL,NULL,TO_CHAR);
    act("$n howls loudly at the sky.\n\rThe ground beneath your feet begins to shake.\n\rA huge dinosaur bursts from the ground with a loud roar!",ch,NULL,NULL,TO_ROOM);
    char_to_room( victim, ch->in_room );

    add_follower( victim, ch );
    af.duration  = 666;
    af.location  = APPLY_NONE;
    af.modifier  = 0;
    af.bitvector = AFF_CHARM;
    affect_to_char( victim, &af );
    ch->gnosis[GCURRENT] -= 3;
    return;
}

/*
 * Ahroun Gifts
 * 1=razorclaws
 */

void do_razorclaws(CHAR_DATA *ch, char *argument)
{

   if (IS_CLASS(ch, CLASS_WEREWOLF))
   {
	if ( ch->gifts[AHROUN] <= 1 )
        {
	    stc("Huh?\n\r",ch);
	    return;
	}
   }
   else
    return;

   if ( !IS_VAMPAFF(ch, VAM_CLAWS) )
   {
	stc("Your talons aren't even extended!\n\r",ch);
	return;
   }

   if ( IS_GAR1(ch, WOLF_RAZORCLAWS ) )
   {
      stc("Your claws lose their razor-sharp edge.\n\r",ch);
      act("$n's claws lose their razor-sharp edge.",ch,NULL,NULL,TO_ROOM);
      REMOVE_BIT(ch->garou1, WOLF_RAZORCLAWS);
   }
   else
   {
	send_to_char("You hone your claws to a razor sharpness.\n\r",ch);
	act("$n hones $s claws to a razor sharpness.",ch, NULL, NULL, TO_ROOM);
	SET_BIT( ch->garou1, WOLF_RAZORCLAWS );
   }

  return;

}

/* Ragabash
 * Vanish
 * Scent of Running Water - No hunt\track(auto)
 * Blissful Ignorance
 * Luna's Blessing
 * Whelp Body
 */
/*
void do_blissful( CHAR_DATA *ch, char *argument )
{
  if ( !is_garou(ch) ) return;
  
  if ( ch->gifts[RAGABASH] < 3 )
  {
    stc("You must obtain level three Ragabash to use Blissful Ignorance.\n\r",ch);
    return;
  }

  if ( has_timer(ch) ) return;

  if ( IS_GAR1(ch, GAROU_BLISSFUL) )
  {
    stc("You fade back into view.\n\r",ch);
    REMOVE_BIT(ch->garou1, GAROU_BLISSFUL);
    return;
  }
  else
  {
    stc("You become completely invisible.\n\r",ch);
    SET_BIT(ch->garou1, GAROU_BLISSFUL);
    return;
  }
  return;
}
*/
void do_lunasblessing( CHAR_DATA *ch, char *argument )
{
  int sn,level;
  
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[RAGABASH] < 4 )
  {
    stc("You must obtain level 4 Ragabash to use Luna's Blessing.\n\r",ch);
    return;
  }

  if ( ( sn = skill_lookup( "lunas blessing" ) ) < 0 ) return;

  if ( is_affected(ch,skill_lookup("lunas blessing")) )
  {
    stc("You already have Luna's Blessing!\n\r",ch);
    return;
  }

  stc("A beam of moonlight shoots out of the sky and surrounds you.\n\r",ch);
  act("$n is engulfed by a beam of moonlight from the sky.",ch,NULL,NULL,TO_ROOM);
  level = (ch->gifts[RAGABASH]*5);
  (*skill_table[sn].spell_fun) ( sn, level, ch, ch );
  WAIT_STATE( ch, 12 );
  return;
}
void do_whelp( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  int dam;  

  argument = one_argument( argument, arg );

  if ( !is_garou( ch ) ) return;

  if ( ch->gifts[RAGABASH] < 5 )
  {
    stc("You must obtain level 5 Ragabash to use Whelp's Body\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    stc("You cannot find them here.\n\r",ch);
    return;
  }

  if(is_safe(ch,victim))
  {
    stc("Not in a safe room!\n\r",ch);return;}
  if ( victim->level < 3 )
  {
    stc("You can only use this power on Avatars!\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 6 )
  {
    stc("You require six points of gnosis to use this power.\n\r",ch);
    return;
  }

  if ( IS_SET(victim->garou1, GAROU_WHELP2)
	|| IS_SET(victim->garou1, GAROU_WHELP1) )
  {
    stc("They are already affected by a Whelp Curse.\n\r",ch);
    return;
  }


  SET_BIT(victim->garou1, GAROU_WHELP2);
  act("You lay your hands on $N, and $S body starts to shake and quiver.",ch,NULL,victim,TO_CHAR);
  act("$n lays $s hands on you, and you feel your body quiver and weaken.",ch,NULL,victim,TO_VICT);
  act("$n lays $s hands on $N, and $N's body starts to shake and quiver.",ch,NULL,victim,TO_NOTVICT);
  dam = number_range( 1500, 2500 );
  mage_damage(ch, victim, dam, "curse", MAGEDAM_OTHER);
  if ( victim->max_hit > 3001 )
    victim->max_hit -= 3000;
  WAIT_STATE(victim, 8);
  WAIT_STATE(ch, 16);
  ch->gnosis[GCURRENT] -= 6;
  return;
}

/* Theurge
 * Mother's Touch
 * Grasp the Beyond
 * Spirit Drain
 * Feral Lobotomy
 * The Malleable Spirit
 */

void do_mothers( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  
  argument = one_argument( argument, arg );
  
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[THEURGE] < 1 )
  {
    stc("You must obtain level 1 Theurge to use Mother's Touch.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to heal?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    stc("You cannot find them here.\n\r",ch);
    return;
  }

  if ( victim == ch )
  {
    stc("You cannot use this power on yourself!\n\r",ch);
    return;
  }

  if ( victim->hit >= victim->max_hit )
  {
    stc("They are already at full health!\n\r",ch);
    return;
  }
 victim->agg -= victim->agg / 3.5;
                if (victim->agg < 0) victim->agg = 0;
  act("You lay your hands on $N, rejuvenating them.",ch,NULL,victim,TO_CHAR);
  act("$n lays $s hands on you, and you feel healthier.",ch,NULL,victim,TO_VICT);
  act("$n lays $s hands on $N, and $N's wounds begin to close.",ch,NULL,victim,TO_NOTVICT);
  victim->hit += ( number_range((ch->gifts[THEURGE]*100),(ch->gifts[THEURGE]*140)));
  if ( victim->hit > victim->max_hit )
    victim->hit = victim->max_hit;

  WAIT_STATE(ch, 12);
  return;
}

// grasp the beyond. auto. lets you get shit from shadowplane.

void do_spiritdrain( CHAR_DATA *ch, char *argument )
{
  char arg[MAX_INPUT_LENGTH];
  OBJ_DATA *obj;
  int hpgain;
 
  one_argument( argument, arg );

  if ( !is_garou(ch) ) return; 
 
  if ( arg[0] == '\0' )
  {
    send_to_char("Drain the spirit of which corpse?\n\r",ch);
    return;
  }

  obj = get_obj_list( ch, arg, ch->in_room->contents );
  if ( obj == NULL )
  {
    send_to_char( "You can't find it.\n\r", ch );
    return;
  }

  if (obj->item_type != ITEM_CORPSE_NPC)
  {
    act( "You are unable to drain the energy of $p.", ch, obj, 0, TO_CHAR);
    return; 
  }
  else if (obj->chobj != NULL && !IS_NPC(obj->chobj)
    && obj->chobj->pcdata->obj_vnum != 0)
  {
    act( "You are unable to drain the energy of $p.", ch, obj, 0, TO_CHAR);
    return;
  }

  hpgain = number_range(50,150);
  ch->hit += hpgain;
  if (ch->hit > ch->max_hit)
    ch->hit = ch->max_hit;
  act( "You drain the spirit energy out of $p.", ch, obj, NULL, TO_CHAR );
  act( "$p is drained of energy by $n.", ch, obj, NULL, TO_ROOM );
  extract_obj( obj );
  WAIT_STATE(ch, 4);
  return;
}

void do_feral( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  int dam;

  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[THEURGE] < 4 )
  {
    stc("You must obtain level 4 Theurge to use Feral Lobotomy.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    stc("They are not here.\n\r",ch);
    return;
  }
  if(is_safe(ch,victim)){stc("Not in a safe room!\n\r",ch);return;}
  if ( victim->level < 3 )
  {
    stc("You can only use this power on Avatars!\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 3 )
  {
    stc("You need three points of gnosis to use this power.\n\r",ch);
    return;
  }

  dam = (ch->gifts[THEURGE] * 100) + (ch->gifts[UKTENA] * 50);
  if ( IS_NPC(victim) )
    dam *= 4;
  dam = number_range( (dam - 100), (dam+100) );
  act("You focus your gnosis power on $N.",ch,NULL,victim,TO_CHAR);
  act("$n's claws deliver a power blow of energy to your head.",ch,NULL,victim,TO_VICT);
  act("$n's claws slash open $N's forehead.",ch,NULL,victim,TO_NOTVICT);
  mage_damage(ch, victim, dam, "mind blast", MAGEDAM_OTHER);
  ch->gnosis[GCURRENT] -= 3;
  return;
}
  
void do_malleable( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA *obj;
  char arg[MIL];
  
  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[THEURGE] < 5 )
  {
    stc("You must obtain level 5 Theurge to use Malleable Spirit\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Which object do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ( obj = get_obj_carry( ch, arg ) ) == NULL )
  {
    stc("You aren't even carrying that object.\n\r",ch);
    return;
  }

  if ( obj->item_type != ITEM_WEAPON ) 
  {
    stc("This power can only be used on weapons.\n\r",ch);
    return;
  }

  if ( IS_SET(obj->quest, QUEST_MALLEABLE) )
  {
    stc("This object has already been modified.\n\r",ch);
    return;
  }

  if (IS_SET(obj->quest, QUEST_ARTIFACT))
  {
      send_to_char("Not on an Artifact.\n\r",ch);
      return;
  }

  obj->value[1] += number_range( 6, 11 );
  obj->value[2] += number_range( 6, 11 );
  act("You manipulate the spirit within $p.\n\r$p's effectiveness has been increased\n\r.",ch,obj,obj,TO_CHAR);
  SET_BIT(obj->quest, QUEST_MALLEABLE);
  WAIT_STATE(ch, 8);
  return;
}
  
/* Philodox Gifts
 * Resist Pain (Auto)
 * King of the Beasts (Auto)
 * Strength of Purpose (Auto)
 * Weak Arm (Auto)
 * Wall of Granite
 */

void do_wallofgranite( CHAR_DATA *ch, char *argument )
{
  if (!is_garou(ch) ) return;

  if ( ch->gifts[PHILODOX] < 5 )
  {
    stc("You must obtain level 5 Philodox to use Wall of Granite.\n\r",ch);
    return;
  }

  if ( IS_SET(ch->garou1, WW_GRANITE) )
  {
    stc("Your wall of granite fades away.\n\r",ch);
    REMOVE_BIT(ch->garou1, WW_GRANITE);
  }

  if ( !IS_SET(ch->garou1, WW_GRANITE) )
  {
    stc("A wall of granite arises around your body to protect you.\n\r",ch);
    SET_BIT(ch->garou1, WW_GRANITE);
    return;
  }

  return;
}

/* Ahroun
 * Inspiration (Auto)
 * Razor Claws (Auto)
 * The Falling Touch (Auto)
 * Silver Claws (Auto)
 * Clenched Jaw
 * Stoking Fury's Furnace (Auto)
 */

void do_clenched( CHAR_DATA *ch, char *argument )
{
  if ( !is_garou(ch) ) return;
 
  if ( ch->gifts[AHROUN] < 4 )
  {
    stc("You must obtain level 4 Ahroun to use this power.\n\r",ch);
    return;
  }

  if ( IS_SET(ch->garou1, GAROU_CLENCHED) )
  {
    stc("You relax your jaw.\n\r",ch);
    REMOVE_BIT(ch->garou1, GAROU_CLENCHED);
    return;
  }

  if ( !IS_GAR1(ch, GAROU_CLENCHED) )
  {
    stc("You prepare to clench your jaw on your opponents.\n\r",ch);
    SET_BIT(ch->garou1, GAROU_CLENCHED);
    return;
  }
  return;
}

/* Black Furies
 * Coup De Grace (Auto)
 * Visceral Agony
 * Body Wrack
 * Wasp Talons (Auto)
 */

void do_visceral(CHAR_DATA *ch, char *argument)
{

   if (IS_CLASS(ch, CLASS_WEREWOLF))
   {
        if ( ch->gifts[BLACKFURIES] <= 1 )
        {
            stc("Huh?\n\r",ch);
            return;
        }
   }
   else
    return;

   if ( !IS_VAMPAFF(ch, VAM_CLAWS) )
   {
        stc("Your claws aren't even extended!\n\r",ch);
        return;
   }
   if ( IS_GAR1(ch, WOLF_VISCERAL ) )
   {
      stc("You wipe the venom from your claws.\n\r",ch);
      act("$n wipes something from $s claws.\n\r",ch,NULL,NULL,TO_ROOM);
      REMOVE_BIT(ch->garou1, WOLF_VISCERAL);
   }
   else
   {
        send_to_char("You coat your claws with black venom.\n\r",ch);
        act("$n coat $s claws with black venom.\n\r",ch, NULL, NULL, TO_ROOM);
        SET_BIT( ch->garou1, WOLF_VISCERAL );
   }

  return;

}


void do_bodywrack( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  int dam;

  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[BLACKFURIES] < 3 )
  {
    stc("You must obtain level 3 Black Furies to use Body Wrack.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
      stc("Whom do you wish to use this on?\n\r",ch);
      return;
  }

  if ( ( victim = get_char_room(ch,arg) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 5 )
  {
    stc("You need five points of gnosis to use this power.\n\r",ch);
    return;
  }

  if ( victim->hit < 1000 )
  {
    stc("They are almost dead already.  It wouldn't be any fun.\n\r",ch);
    return;
  }

  dam = number_range((ch->gifts[BLACKFURIES]*175),(ch->gifts[BLACKFURIES]*200));
  act("You focus a blast of gnosis on $N.",ch,NULL,victim,TO_CHAR);
  act("A blast of energy shoots out of $n's claws and wracks your body.",ch,NULL,victim,TO_VICT);
  mage_damage(ch,victim,dam,"gnosis warp",MAGEDAM_OTHER);
  ch->gnosis[GCURRENT] -= 5;
  WAIT_STATE(ch, 16);
  return;
}
  

/* Children of Gaia
 * Luna's Armor (Auto)
 * Dazzle
 * Calm the Beast
 * Halo of the Sun
 * The Living Wood
 */

void do_dazzle( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
   int chance;


      chance = number_percent();


  argument = one_argument( argument, arg );
 
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[CHILDRENOFGAIA] < 2 )
  {
    stc("You must obtain level 2 Children of Gaia to use Dazzle.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }
if ( chance > 40 && IS_CLASS(ch, CLASS_WEREWOLF))
{
 stc("You failed.\n\r", ch );
        return;
        }

  if ( ( victim = get_char_room(ch, arg) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }

  if ( victim->wait > 0 )
  {
    stc("You failed...\n\r",ch);
    return;
  }

  act("You gaze at $N, dazzling $M with Gaia's Glory.",ch,NULL,victim,TO_CHAR);
  act("You catch $n's gaze, and are dazzled by $s glory.",ch,NULL,victim,TO_VICT);
  victim->position = POS_STUNNED;
  WAIT_STATE(ch, 8);
  return;
}

void do_garouserenity( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  
  argument = one_argument( argument, arg);

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[CHILDRENOFGAIA] < 3 )
  {
    stc("You must obtain the third Children of Gaia gift to use Serenity.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to calm?\n\r",ch);
    return;
  }
  
  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }
 
  if ( number_range(1,4) != 3 )
  {    
      stc("You sing a blissful and soothing song.\n\r",ch);
      act("$n starts singing a blissful and soothing song.",ch,NULL,victim,TO_VICT);
      stc("Nothing seems to happen..\n\r",ch);
      WAIT_STATE(ch,12);
      return;
  }

 
  if ( IS_CLASS(victim, CLASS_VAMPIRE) )
  {
    if ( victim->pcdata->stats[UNI_RAGE] < 1 )
    {
      stc("They aren't even raged!\n\r",ch);
      return;
    }
    else
    {
      stc("You sing a blissful and soothing song.\n\r",ch);
      act("$n starts singing a blissful and soothing song.",ch,NULL,victim,TO_VICT);
      do_calm(victim,"");
      return;
    }
    WAIT_STATE(ch, 16);
    return;
  }
  else if ( IS_CLASS(victim, CLASS_WEREWOLF) )
  {
    if ( victim->pcdata->stats[UNI_RAGE] < 100 )
    {
	stc("They aren't even raged!\n\r",ch);
	return;
    }
    else
    {
      stc("You sing a blissful and soothing song.\n\r",ch);
      act("$n starts singing a blissful and soothing song.",ch,NULL,victim,TO_VICT);
      do_unwerewolf(victim,"");
      return;
    }
    WAIT_STATE(ch, 16);
  }
  else
   return;
  return;
}

void do_livingwood( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  
  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[CHILDRENOFGAIA] < 5 )
  {
    stc("You must obtain the fifth Children of Gaia gift to use this power.\n\r",ch);
    return;
  }

  if ( ch->in_room->sector_type != SECT_FOREST )
  {
    stc("You can only use this power in the forest.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this power on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }

  if ( IS_SET(victim->mflags, MAGE_EMBRACED2) || IS_SET(victim->mflags, MAGE_EMBRACED1) )
  {
    stc("They are already embraced by the earth.\n\r",ch);
    return;
  }

  act("You call upon the forest to entrap your foe.",ch,NULL,NULL,TO_CHAR);
  act("$n chants softly.\nThe ground around you begins to rise up, entrapping you.",ch,NULL,victim,TO_VICT);
  act("$n begins to chant softly.\nSuddenly, the ground surrounding $N begins to rise up and entrap $M!",ch,NULL,victim,TO_NOTVICT);
  SET_BIT(victim->mflags, MAGE_EMBRACED2);
  WAIT_STATE(ch, 16);
  return;
}

/* Get of Fenris
 * Halt the Coward's Flight (Auto)
 * Snarl of the PRedator
 * MIght of Thor (Auto)
 * Venom Blood (Auto)
 * Fenris' Bite (Auto)
 */

void do_snarl( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
 int chance;
 chance = number_percent();

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[GETOFFENRIS] < 2 )
  {
    stc("You must obtain the second gift of Get Of Fenris to use this power.\n\r",ch);
    return;
  }

  if ( ch->fighting == NULL )
  {
    stc("You must be fighting to use this power.\n\r",ch);
    return;
  }


  victim = ch->fighting;

if ( chance > 50 && IS_CLASS(ch, CLASS_WEREWOLF))
{
 stc("You snarl visciously, but nothing seems to happen.\n\r", ch );
        return;
        }

  if ( victim->wait > 0 )
  {
    stc("You snarl visciously, but nothing seems to happen.\n\r",ch);
    return;
  }

  act("You snarl visciously at $N, $e panics.",ch,NULL,victim,TO_CHAR);
  act("$n snarls visciously at you.\n\rYou panic and try to escape.",ch,NULL,victim,TO_VICT);
  do_recall(victim,"");  
  WAIT_STATE(ch, 12);
  return;
}

/* Red Talons
 * Avalanche
 * Quicksand
 * Gaia's Vengeance
 * ONLY THREE POWERS IN THIS SONUVABITCH.
 */

void do_avalanche( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *vch;
  CHAR_DATA *vch_next;
  CHAR_DATA *mount;

  if ( !is_garou(ch) ) return;
  
  if ( ch->gifts[REDTALONS] < 1 )
  {
    stc("You must obtain the level one Red Talons gift to use Avalanche.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 5 )
  {
    stc("You must have 5 points of gnosis to use this power.\n\r",ch);
    return;
  }
  
  stc("You call upon the power of Gaia to unleash an avalanche on your foes.\n\r",ch);
  for ( vch = char_list; vch != NULL; vch = vch_next )
  {
    vch_next	= vch->next;
    if ( vch->in_room == NULL ) continue;
    if ( vch->in_room != ch->in_room ) continue;
    if ( vch->level < 3 ) continue;
    if ( !IS_NPC(vch) && vch->pcdata->chobj != NULL ) continue;
    if ( is_safe(ch,vch) ) continue;
    if ( ch == vch ) continue;
    if ( ( mount = ch->mount ) != NULL )
      if ( mount == vch ) continue;
    act("$n calls upon the power of Gaia to unleash an Avalanche on the area!",ch,NULL,vch,TO_VICT);
    mage_damage(ch,vch, number_range(400,500),"avalanche",MAGEDAM_OTHER);
  }
  ch->gnosis[GCURRENT] -= 5;
  WAIT_STATE(ch, 16);
  return;
}

void do_barrage( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *vch;
  CHAR_DATA *vch_next;
  CHAR_DATA *mount;

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[REDTALONS] < 2 )
  {
    stc("You must obtain the second gift of the Red Talons to use Barrage.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] <= 5 )
  {
    stc("You must have 5 points of gnosis to use this power.\n\r",ch);
    return;
  }

  for ( vch = char_list; vch != NULL; vch = vch_next )
  {
    vch_next	= vch->next;
    if ( vch->in_room == NULL ) continue;
    if ( vch->in_room != ch->in_room ) continue;
    if ( vch->level < 3 ) continue;
    if ( !IS_NPC(vch) ) continue;
    if ( is_safe(ch,vch) ) continue;
    if ( ch == vch ) continue;
    if ( ( mount = ch->mount ) != NULL )
      if ( mount == vch ) continue;
    mage_damage(ch,vch, number_range(4000,5000),"elemental barrage",MAGEDAM_OTHER);
  }
  ch->gnosis[GCURRENT] -= 5;
  WAIT_STATE(ch, 16);
  return;
}

void do_vengeance( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *vch;
  CHAR_DATA *vch_next;
  CHAR_DATA *mount;
  
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[REDTALONS] < 3 )
  {
    stc("You must obtain the third gift of the Red Talons to use Gaia's Vengeance.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 10 )
  {
    stc("You need 10 points of gnosis to use this power.\n\r",ch);
    return;
  }

  stc("You stir up the essence of Gaia in the land around you, summoning her vegeance to strike down your foes.\n\r",ch);
  act("$n summons the essence of Gaia into $s body, and the room bursts with a blinding white light.",ch,NULL,NULL,TO_ROOM);
  for ( vch = char_list; vch != NULL; vch = vch_next )
  {
    vch_next	= vch->next;
    if ( vch->in_room == NULL ) continue;
    if ( vch->in_room != ch->in_room ) continue;
    if ( vch->level < 3 ) continue;
    if ( !IS_NPC(vch) && ch->pcdata->chobj != NULL ) continue;
    if ( ch == vch ) continue;
    if ( is_safe(ch,vch)) continue;
    if ( ( mount = ch->mount ) != NULL )
      if ( mount == vch ) continue;
    mage_damage(ch,vch, number_range(2000,3000),"vengeance of Gaia",MAGEDAM_OTHER);
  }
  ch->gnosis[GCURRENT] -= 10;
  WAIT_STATE(ch, 24);
  return;
}

/* Shadow Lords
 * Fatal Flaw (Auto)
 * Aura of Confidence (Auto)
 * Clap of Thunder
 * Icy Chill of Dispair (Auto)
 * Strength of the Dominator (Auto)
 */

void do_clapofthunder( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *vch;
  CHAR_DATA *vch_next;
  CHAR_DATA *mount;

  if ( !is_garou(ch) ) return;
 
  if ( ch->gifts[SHADOWLORDS] < 3 )
  {
    stc("You must obtain the third gift of the Shadow Lords to use Clap of Thunder.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 5 )
  {
    stc("You must have 5 points of gnosis to use this power.\n\r",ch);
    return;
  }
 
  stc("You clap your hands together, sending forth a shockwave that stuns everyone in the room.\n\r",ch);
  act("$n claps $s hands together, sending forth a shockwave that stuns you instantly!",ch,NULL,NULL,TO_ROOM);
  for ( vch = char_list; vch != NULL; vch = vch_next )
  {
    vch_next	= vch->next;
    if ( vch->in_room == NULL ) continue;
    if ( vch->in_room != ch->in_room ) continue;
    if ( vch->level < 3 ) continue;
    if ( !IS_NPC(vch) ) continue;
    if ( is_safe(ch,vch) ) continue;
    if ( ch == vch ) continue;
    if ( ( mount = ch->mount ) != NULL )
      if ( mount == vch ) continue;
    mage_damage(ch,vch,number_range(50,100),"clap of thunder",MAGEDAM_OTHER);
    vch->position = POS_STUNNED;
  }
  ch->gnosis[GCURRENT] -= 5;
  WAIT_STATE(ch, 16);
  return;
}

/* Silent Striders
 * Speed of Thought (Auto)
 * Speed beyond Thought (Auto)
 * Messenger's Speed (Auto)
 * Gate of the Moon
 * Reach the Umbra
 */

void do_gatemoon( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  OBJ_DATA *obj;
  char arg[MIL];
  
  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[SILENTSTRIDERS] < 4 )
  {
    stc("You must obtain the fourth Silent Striders gift to use Gate of the Moon.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this power on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_world(ch,arg) ) == NULL )
  {
    stc("They aren't anywhere to be found.\n\r",ch);
    return;
  }

  if ( !IS_NPC(victim) && !IS_IMMUNE(victim, IMM_SUMMON) )
  {
    stc("You can't manage to open a moongate to them.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 2 )
  {
    stc("You need two points of Gnosis to use this power.\n\r",ch);
    return;
  }

if (weather_info.sunlight == SUN_LIGHT || weather_info.sunlight == SUN_RISE) {
			send_to_char("The moon is not out.\n\r", ch);
			return;
		}


/*
  if ( weather_info.sunlight != SUN_DARK )
  {
    stc("The moon must be showing in the sky to use this power..\n\r",ch);
    return;
  }
*/
  if ( ( obj = create_object(get_obj_index(OBJ_VNUM_MOONGATE),0)) == NULL )
  {
    stc("Hrm.  Slight problem here.  Uhm. Tell SaGe the moongate object is missing.\n\r",ch);
    return;
  }

  obj_to_room(obj,ch->in_room);
  obj->item_type = ITEM_PORTAL;
  obj = create_object(get_obj_index(OBJ_VNUM_MOONGATE),0);
  obj->item_type = ITEM_PORTAL;
  obj_to_room(obj,victim->in_room);
   obj->timer = 5;
  stc("A shimmering moongate appears before you.\n\r",ch);
  stc("A shimmering moongate opens before you.\n\r",victim);
  char_from_room(ch);
  char_to_room( ch, victim->in_room );
  stc("You step out of the moongate.\n\r",ch);
  do_look(ch,"auto");
  stc("Someone steps out of the moongate..\n\r",victim);
  WAIT_STATE(ch, 8);
  ch->gnosis[GCURRENT] -= 2;
  return;
}


/* Silver Fangs
 * Lambent Flame
 * Silver Claws (Auto)
 * Mindblock (Auto)
 * Luna's Avenger 
 * Paws of the Newborn Cub
 */
void do_lunasavenger( CHAR_DATA *ch, char *argument )
{
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[SILVERFANGS] < 4 )
  {
    stc("You must obtain the fourth gift of the Silver Fangs to use Luna's Avenger.\n\r",ch);
    return;
  }

  if ( IS_SET(ch->garou1, GAROU_AVENGER) )
  {
    stc("Your body warps and shrinks, losing it's silver composition.\n\r",ch);
    REMOVE_BIT(ch->garou1, GAROU_AVENGER);
    return;
  }

  else
  {
    stc("Your body warps and grows, becoming imbued with silver.\n\r",ch);
    SET_BIT(ch->garou1, GAROU_AVENGER);
    return;
  }
  return;
}


void do_lambent(CHAR_DATA *ch,char *argument)
{
  CHAR_DATA *vch;
  if(!IS_CLASS(ch,CLASS_WEREWOLF))
  {do_huh(ch,"");return;}
  if(ch->gifts[SILVERFANGS]<1)
  {
    stc("You require level three in Silver Fangs to use this.\n\r",ch);
    return;
  }

  if(ch->gnosis[GCURRENT]< 6)
  {
    stc("You require 6 gnosis to use this power.\n\r",ch);
    return;
  }
  if(IS_SET(ch->in_room->room_flags,ROOM_SAFE))
  {stc("Not in a safe room!\n\r",ch);return;}

  ch->gnosis[GCURRENT]-= 6;
  act("A silvery glow ignights around $n's body.",ch,NULL,NULL,TO_ROOM);
  act("A silvery light ignights around your body.",ch,NULL,NULL,TO_CHAR);

  for(vch=ch->in_room->people;vch!=NULL;vch=vch->next_in_room)
  {
	if(vch==ch)continue;

    if(number_range(1,4)<=3)
    {
      act("$N is blinded!",ch,NULL,vch,TO_NOTVICT);
      act("$N is blinded!",ch,NULL,vch,TO_CHAR);
      act("You are blinded!",ch,NULL,vch,TO_VICT);
      SET_BIT(vch->affected_by,AFF_BLIND);
    }
    else continue;
  }
  WAIT_STATE(ch,8);
}

void do_paws( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  
  argument = one_argument( argument, arg );
  
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[SILVERFANGS] < 5 )
  {
    stc("You must obtain the fifth gift of the Silver Fangs to use Paws of the Newborn Cub.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room(ch,arg) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }

  if ( ch == victim )
  {
    stc("It might be a bad idea to use this on yourself..\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 15 )
  {
    stc("You need 15 points of gnosis to use this power.\n\r",ch);
    return;
  }

  if ( IS_NPC(victim) ) 
  {
    stc("This power is useless on beasts..\n\r",ch);
    return;
  }

  if ( IS_SET(victim->garou1, GAROU_PAWS) )
  {
    stc("They are already afflicted with this disease..\n\r",ch);
    return;
  }

  act("You focus your gnosis power into your hands, and lay them on $N.",ch,NULL,victim,TO_CHAR);
  act("$n's hands start to glow violently, and $e reaches out and lays them on you.",ch,NULL,victim,TO_VICT);
  act("$n's hands start to glow brightly, and $e reaches out and presses them against $N's forehead.",ch,NULL,victim,TO_NOTVICT);
  act("$N's body starts to weaken and shrink!",ch,NULL,victim,TO_CHAR);
  act("$N's body starts to weaken and shrink!",ch,NULL,victim,TO_NOTVICT);
  stc("Your body starts to weaken and shrink!\n\r",victim);
  SET_BIT(victim->garou1, GAROU_PAWS);
  ch->gnosis[GCURRENT] -= 15;
  WAIT_STATE(ch, 24);
  return;
}

/* Stargazers
 * Inner Strength (Auto)
 * Merciful Blow 
 * Preternatural Awareness (Auto)
 * Circular Attack (Auto)
 * Sight from Beyond (shadowsight)
 */
void do_merciful( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[STARGAZERS] < 2 )
  {
    stc("You must obtain the second gift of the Stargazers to use Merciful Blow.\n\r",ch);
    return;
  }

  if ( ch->fighting == NULL )
  {
    stc("You must be fighting to use this power.\n\r",ch);
    return;
  }

  victim = ch->fighting;
  
  if ( ((victim->hit / victim->max_hit)*100) >= 50 )
  {
    stc("They are far too healthy to be affected by this power.\n\r",ch);
    return;
  }

  if ( number_range(1,8) != 4 )
  {
    act("You deliver a blow to $N's neck, but nothing happens.",ch,NULL,victim,TO_CHAR);
    act("$n delivers a powerful blow to your neck, but shrug it off.",ch,NULL,victim,TO_VICT);
    act("$n delivers a powerful blow to $N's neck, but $E shrugs it off.",ch,NULL,victim,TO_NOTVICT);
    return;
  }
  else
  {
    act("You deliver a blow to $N's neck, and $N falls to the ground.",ch,NULL,victim,TO_CHAR);
    act("$n delivers a powerful blow to your neck, and you fall to the ground.",ch,NULL,victim,TO_VICT);
    act("$n delivers a powerful blow to $N's neck, and $E falls to the ground.",ch,NULL,victim,TO_NOTVICT);
    do_peace(ch,"");
    victim->position = POS_STUNNED;
    return;
  }
  return;
}


void do_sightfrombeyond( CHAR_DATA *ch, char *argument )
{
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_WEREWOLF(ch) )
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }


  if ( ch->gifts[STARGAZERS] < 5 )
  {
    stc("You must obtain the fifth gift of the Stargazers to use Sight from Beyond.\n\r",ch);
    return;
  }

    if (IS_AFFECTED(ch,AFF_SHADOWSIGHT) )
    {
	send_to_char("You refocus your eyes and stop looking into the beyond.\n\r",ch);
	REMOVE_BIT(ch->affected_by, AFF_SHADOWSIGHT);
	return;
    }
    send_to_char("You refocus your eyes to look into the beyond.\n\r",ch);
    SET_BIT(ch->affected_by, AFF_SHADOWSIGHT);
    return;
}



/* Uktena
 * Shroud
 * Spirit of the Bird (Auto)
 * Call Flame Spirit
 * Invisibility
 * Hand of the Earth Lords (Auto)
 */

void do_halosun( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;

    if (!IS_WEREWOLF(ch) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

   if (ch->gifts[CHILDRENOFGAIA] < 4)
    {
	send_to_char("You require the level 4 Children of Gaia power to use the Halo of the Sun.\n\r",ch);
	return;
    }

    if (IS_ITEMAFF(ch,ITEMA_SUNSHIELD) )
    {
	send_to_char("Your Halo of the Sun gradually fades away.\n\r",ch);
	act("$n's Halo of the Sun gradually fades away.", ch, NULL, NULL,
TO_ROOM);
	REMOVE_BIT(ch->itemaffect, ITEMA_SUNSHIELD);
	return;
    }
    send_to_char("You are surrounded by a halo of sunlight!\n\r",ch);
    act("$n is surrounded by a halo of sunlight!", ch, NULL, NULL,
TO_ROOM);
    SET_BIT(ch->itemaffect, ITEMA_SUNSHIELD);
    return;
}


/*

void do_darkshroud( CHAR_DATA *ch, char *argument )
{
  if ( !is_garou(ch) ) return;

  if ( ch->gifts[UKTENA] < 1 )
  {
    stc("You must obtain the first gift of the Uktena to use Dark Shroud.\n\r",ch);
    return;
  }

  if ( IS_SET(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS) )
  {
    stc("You banish the darkness from the room.\n\r",ch);
    REMOVE_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);
    return;
  }

  if ( IS_SET(ch->in_room->room_flags, ROOM_SAFE) )
  {
    stc("Not in a safe room!\n\r",ch);
    return;
  }



    if (IS_SET(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS))
    {
        send_to_char("The room is already in darkness.\n\r", ch);
        return;
    }

  stc("You summon a shroud of inky blackness to cover the room.\n\r",ch);
  act("$n summons a shroud of inky blackness to cover the room.\n\r",ch,NULL,NULL,TO_ROOM);
  SET_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);
  WAIT_STATE(ch,8);
  return;
}

*/void do_flamespirit( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  int dam;
  
  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;
  
  if ( ch->gifts[UKTENA] < 3 )
  {
    stc("You must obtain the third gift of the Uktena to use Call the Flame Spirit.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room(ch,arg) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }

  if ( is_safe(ch,victim) ) return;

  if ( ch->gnosis[GCURRENT] < 2 )
  {
    stc("You need two points of gnosis to use this power.\n\r",ch);
    return;
  }

  dam = number_range( (ch->gifts[UKTENA]*100), (ch->gifts[UKTENA]*120) );
  if ( IS_CLASS(victim, CLASS_VAMPIRE) )
    dam *= number_range(2,3);
  act("You summon a spirit of Flames to disintegrate $N.",ch,NULL,victim,TO_CHAR);
  act("$n conjures a spirit of flames to smite you.",ch,NULL,victim,TO_VICT);
  act("$n conjures a spirit of flames to smite $N!",ch,NULL,victim,TO_NOTVICT);
  mage_damage(ch,victim,dam,"flame spirit",MAGEDAM_OTHER);
  ch->gnosis[GCURRENT] -= 2;
  WAIT_STATE(ch, 16);
  return;
}


void do_fetishdoll( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA  *obj;
    char       buf [MAX_INPUT_LENGTH];
    char       arg [MAX_INPUT_LENGTH];
    char     part1 [MAX_INPUT_LENGTH];
    char     part2 [MAX_INPUT_LENGTH];
    int       worn;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_WEREWOLF(ch) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

   if (ch->gifts[UKTENA] < 4)
    {
	send_to_char( "You require the level 4 power of the Uktena to create a Fetish Doll.\n\r", ch );
	return;
    }

    if (arg[0] == '\0')
    {
	send_to_char( "Who do you wish to make a Fetish Doll of?\n\r", ch);
	return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "Nobody by that name is playing.\n\r", ch );
	return;
    }

    if ( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL )
    {
    	if ( ( obj = get_eq_char( ch, WEAR_HOLD ) ) == NULL )
	{
	    send_to_char( "You are not holding any body parts.\n\r", ch );
	    return;
	}
	else worn = WEAR_HOLD;
    }
    else worn = WEAR_WIELD;

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    if      (obj->value[2] == 12) sprintf(part1,"head %s",victim->name);
    else if (obj->value[2] == 13) sprintf(part1,"heart %s",victim->name);
    else if (obj->value[2] == 14) sprintf(part1,"arm %s",victim->name);
    else if (obj->value[2] == 15) sprintf(part1,"leg %s",victim->name);
    else if (obj->value[2] == 30004) sprintf(part1,"entrails %s",victim->name);
    else if (obj->value[2] == 30005) sprintf(part1,"brain %s",victim->name);
    else if (obj->value[2] == 30006) sprintf(part1,"eye eyeball %s",victim->name);
    else if (obj->value[2] == 30012) sprintf(part1,"face %s",victim->name);
    else if (obj->value[2] == 30013) sprintf(part1,"windpipe %s",victim->name);
    else if (obj->value[2] == 30014) sprintf(part1,"cracked head %s",victim->name);
    else if (obj->value[2] == 30025) sprintf(part1,"ear %s",victim->name);
    else if (obj->value[2] == 30026) sprintf(part1,"nose %s",victim->name);
    else if (obj->value[2] == 30027) sprintf(part1,"tooth %s",victim->name);
    else if (obj->value[2] == 30028) sprintf(part1,"tongue %s",victim->name);
    else if (obj->value[2] == 30029) sprintf(part1,"hand %s",victim->name);
    else if (obj->value[2] == 30030) sprintf(part1,"foot %s",victim->name);
    else if (obj->value[2] == 30031) sprintf(part1,"thumb %s",victim->name);
    else if (obj->value[2] == 30032) sprintf(part1,"index finger %s",victim->name);
    else if (obj->value[2] == 30033) sprintf(part1,"middle finger %s",victim->name);
    else if (obj->value[2] == 30034) sprintf(part1,"ring finger %s",victim->name);
    else if (obj->value[2] == 30035) sprintf(part1,"little finger %s",victim->name);
    else if (obj->value[2] == 30036) sprintf(part1,"toe %s",victim->name);
    else
    {
	sprintf(buf,"%s isn't a part of %s!\n\r",obj->name,victim->name);
	send_to_char( buf, ch );
	return;
    }

    sprintf(part2,obj->name);

    if ( str_cmp(part1,part2) )
    {
	sprintf(buf,"But you are holding %s, not %s!\n\r",obj->short_descr,victim->name);
	send_to_char( buf, ch );
	return;
    }

    act("$p vanishes from your hand in a puff of smoke.", ch, obj, NULL,
TO_CHAR);
    act("$p vanishes from $n's hand in a puff of smoke.", ch, obj, NULL,
TO_ROOM);
    obj_from_char(obj);
    extract_obj(obj);

    obj = create_object( get_obj_index( OBJ_VNUM_VOODOO_DOLL ), 0 );

    sprintf(buf,"%s voodoo doll",victim->name);
    free_string(obj->name);
    obj->name=str_dup(buf);

    sprintf(buf,"a voodoo doll of %s",victim->name);
    free_string(obj->short_descr);
    obj->short_descr=str_dup(buf);

    sprintf(buf,"A voodoo doll of %s lies here.",victim->name);
    free_string(obj->description);
    obj->description=str_dup(buf);

    obj_to_char(obj,ch);
    equip_char(ch,obj,worn);

    act("$p appears in your hand.", ch, obj, NULL, TO_CHAR);
    act("$p appears in $n's hand.", ch, obj, NULL, TO_ROOM);

    return;
}

void do_violation( CHAR_DATA *ch, char *argument)
{

  CHAR_DATA *victim;
   char      arg [MAX_INPUT_LENGTH];


 argument = one_argument( argument, arg );

    if ( IS_NPC(ch) )
     return;

    if (!IS_CLASS(ch, CLASS_WEREWOLF) && !IS_ABOMINATION(ch)) 
    {
	  send_to_char("Huh?\n\r",ch);
	  return;
    }

    if (ch->gifts[RAGABASH] < 3)
    {
	  send_to_char("You need level 3 Ragabash to use Violation.\n\r",ch);
	  return;
    }



    if ( arg[0] == '\0' )
    {
        send_to_char( "Who do you wish to use Violation on?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if (IS_NPC(victim))
    {
        send_to_char("Why use Violation on a mob?\n\r", ch);
        return;
    }

    if ( IS_IMMORTAL(victim) && victim != ch )
    {
        send_to_char( "You can only use Violation on Avatar's or lower.\n\r", ch );
	return;
    }

    if (is_safe(ch,victim) == TRUE) return;



    if (IS_SET(victim->newbits, NEW_VIOLATION))
    {
	  REMOVE_BIT(victim->newbits, NEW_VIOLATION);
        send_to_char("Your emotions return to normal.\n\r",victim);
	  act("$n seems to relax a little.\n\r",victim,NULL,NULL,TO_ROOM);
	  return;
    }
    if (!IS_SET(victim->newbits, NEW_VIOLATION))
    {
	  SET_BIT(victim->newbits, NEW_VIOLATION);

  act("You reach out and lay your hand on $N's forehead.\n\r",ch,NULL,victim,TO_CHAR);
  act("$n lays $s hand on your forehead!\n\rYour emotions begin to take control!\n\r",ch,NULL,victim,TO_VICT);
  act("$n lays $s hand on $N's forehead!\n\r",ch,NULL,victim,TO_NOTVICT);
	  return;
    }
}

/*
void do_invisibility( CHAR_DATA *ch, char *argument )
{
  if (!is_garou(ch) ) return;

  if ( ch->gifts[UKTENA] < 4 )
  {
    stc("You must obtain the fourth gift of the Uktena to use Invisibility.\n\r",ch);
    return;
  }

  if ( IS_GAR1(ch, GAROU_BLISSFUL) )
  {
    stc("You fade out of your invisibility.\n\r",ch);
    REMOVE_BIT(ch->garou1, GAROU_BLISSFUL);
    return;
  }
  else
  {
    stc("Your body fades out of existance.\n\r",ch);
    SET_BIT(ch->garou1, GAROU_BLISSFUL);
    return;
  }
  return;
}
*/
/* Wendigo
 * Camouflage
 * Cutting Wind
 * Call the Cannibal Spirit
 * Heart of Ice
 * Chill of the Early Frost
 */

void do_cuttingwind( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  int dam;

  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[WENDIGO] < 2 )
  {
    stc("You must obtain the second gift of the Wendigo to use Cutting Wind.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 2 )
  {
    stc("You need two points of gnosis to use this power.\n\r",ch);
    return;
  }

  dam = number_range( 1000, 1250 );
  if ( IS_NPC(victim) )
    dam *= 2;
  act("You summon the bitter winds of the Great Wendigo to rip $N.",ch,NULL,victim,TO_CHAR);
  act("$n summons the bitter winds of the Great Wendigo to tear you apart.",ch,NULL,victim,TO_VICT);
  act("$n summons the bitter winds of the Great Wendigo to tear $N apart.",ch,NULL,victim,TO_NOTVICT);
  mage_damage(ch,victim,dam,"blast of wind",MAGEDAM_OTHER);
  ch->gnosis[GCURRENT] -= 2;
  WAIT_STATE(ch, 24);
  return;
}

void do_cannibalspirit( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  CHAR_DATA *mob;
  char arg[MIL];

  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[WENDIGO] < 3 )
  {
    stc("You must obtain the third gift of the Wendigo to Call the Cannibal Spirit.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_world( ch, arg ) ) == NULL )
  {
    stc("You cannot find them in this realm.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 15 )
  {
    stc("You need 15 gnosis points to use this power.\n\r",ch);
    return;
  }

  if ( is_safe(ch,victim) )
  {
    stc("They are in a holy place.\n\r",ch);
    return;
  }

  if ( victim->level < 3 )
  {
    stc("They must be an avatar!\n\r",ch);
    return;
  }

  if ( ( mob = create_mobile( get_mob_index( MOB_VNUM_CANNIBAL ) ) ) == NULL )
  {
    stc("Shit.  The Mob is missing.  Fuck.  Tell someone. Fuck!\n\r",ch);
    return;
  }
  
  SET_BIT(mob->affected_by, AFF_DETECT_INVIS);
  SET_BIT(mob->affected_by, AFF_DETECT_HIDDEN);
  SET_BIT(mob->affected_by, AFF_SHADOWSIGHT);
  SET_BIT(mob->act, ACT_NOEXP);
  char_to_room( mob, ch->in_room );
  act("You summon a Great Wendigo avatar to hunt your foe.",ch,NULL,victim,TO_CHAR);
  act("$N bursts out of the ground and grins evilly.",ch,NULL,mob,TO_CHAR);
  char_from_room( mob );
  char_to_room( mob, victim->in_room );
  stc("The huge beast quickly burrows into the ground and seeks out your foe.\n\r",ch);
  stc("A huge werewolf bursts out of the ground and growls ferociously.\n\r", victim);
  stc("The werewolf turns to you and grins.\n\r",victim);
  do_kill(mob,victim->name);
  ch->gnosis[GCURRENT] -= 15;
  WAIT_STATE(ch, 16);
  return;
}

void do_heartofice( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *victim;
  char arg[MIL];
  int dam;

  argument = one_argument( argument, arg );

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[WENDIGO] < 4 )
  {
    stc("You must obtain the fourth gift of the Wendigo to use this power.\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    stc("Whom do you wish to use this power on?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_world( ch, arg ) ) == NULL )
  {
    stc("They aren't here.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 10 )
  {
    stc("You must have 10 points of gnosis to use this power.\n\r",ch);
    return;
  }

  if ( is_safe(ch,victim) ) return;

  if ( victim->level < 3 )
  {
    stc("They must be an Avatar.\n\r",ch);
    return;
  }

  dam = number_range( 400, 600 );
  if ( IS_NPC(victim) ) dam *= 3;
  act("You summon the frost of the Wendigo to chill $N.",ch,NULL,victim,TO_CHAR);
  act("A cold air fills the room.\nYou are gripped with pain as the cold freezes your body.",ch,NULL,victim,TO_VICT);
  mage_damage(ch, victim, dam, "ice blast",MAGEDAM_OTHER);
  ch->gnosis[GCURRENT] -= 10;
  WAIT_STATE(ch,16);
  return;
}


void do_chillfrost( CHAR_DATA *ch, char *argument )
{
  CHAR_DATA *vch;
  CHAR_DATA *vch_next;
  CHAR_DATA *mount;
  int number_hit = 0;

  if ( !is_garou(ch) ) return;

  if ( ch->gifts[WENDIGO] < 5 )
  {
    stc("You must obtain the fifth gift of the Wendigo to use this power.\n\r",ch);
    return;
  }

  if ( ch->gnosis[GCURRENT] < 20 )
  {
    stc("You need 20 points of gnosis to use this power.\n\r",ch);
    return;
  }

  stc("You conjure the very essence of the Great Wendigo to blanket the area.\n\rThe skies turn white and the air turns bitter cold.\n\r",ch);

  for ( vch = char_list; vch != NULL; vch = vch_next )
  {
    vch_next	= vch->next;
	number_hit ++;


    if ( number_hit >= 20) return;
    if ( vch->in_room == NULL ) continue;
    if ( vch->in_room->area != ch->in_room->area ) continue;
    if ( vch->level < 3 ) continue;
    if ( !IS_NPC(vch) && vch->pcdata->chobj != NULL ) continue;
    if ( is_safe(ch,vch) ) continue;
    if ( ch == vch ) continue;
    if ( ( mount = ch->mount ) != NULL )
      if ( mount == vch ) continue;
    stc("The skies turn white and the sun is banished.\nThe room becomes bitterly cold, and your body starts to shiver.\n\r",vch);
    mage_damage(ch,vch, number_range(400,500),"chill frost",MAGEDAM_OTHER);
  }

  ch->gnosis[GCURRENT] -= 20;
  WAIT_STATE(ch, 24);
  return;
}



void do_wyld( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;
    CHAR_DATA *vch;
    CHAR_DATA *victim;
    char buf [MAX_STRING_LENGTH];
    
    if (IS_NPC(ch)) return;

    if (!IS_WEREWOLF(ch) && !IS_ABOMINATION(ch) && ch->in_room == NULL)
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }


    if ( ch->gifts[GALLIARD] < 1 )
    {
      stc("You have not learned the Galliard gift of Call Of The Wyld.\n\r",ch);
      return;
    }

    if ( ( victim = ch->fighting ) == NULL && ch->hit > 0 )
    {
	send_to_char("You can only call for assistance in times of great need.\n\r",ch);
	return;
    }

    if (ch->wyld_timer > 0)
    {
	send_to_char("Your voice has not yet recovered.\n\r",ch);
	return;
    }

    ch->wyld_timer = 5;

    for ( d = descriptor_list; d != NULL; d = d->next )
    {
	if ( d->connected != CON_PLAYING ) continue;
	if ( (vch = d->character) == NULL ) continue;
	if ( vch->in_room == NULL) continue;
	if ( IS_NPC(vch) ) continue;
	if ( ch->beast >= 40 && vch->beast < 40 ) continue;
	if ( ch->beast < 40 && vch->beast >= 40 ) continue;
	if ( vch == ch )
	    act("You call for assistance!", ch, NULL, argument, TO_CHAR);
	if (ch != vch && (IS_WEREWOLF(vch) || IS_IMMORTAL(vch)))
	{
	    if (victim != NULL)
	    {
		sprintf(buf,"CALL OF THE WYLD:[$n is under attack by %s at %s]", 
		    IS_NPC(victim) ? victim->short_descr : victim->name,
                    ch->in_room->name);
		act(buf,ch,NULL,vch, TO_VICT);
	    }
	    else if (ch->hit < 1)
	    {
		sprintf(buf,"CALL OF THE WYLD:[$n is badly wounded at %s]", 
                    ch->in_room->name);
		act(buf,ch,NULL,vch, TO_VICT);
	    }
	    else
	    {
		sprintf(buf,"CALL OF THE WYLD:[$n needs assistance at %s]", 
                    ch->in_room->name);
		act(buf,ch,NULL,vch, TO_VICT);
	    }
	}
    }
    return;
}

void do_brew( CHAR_DATA *ch, char *argument)
{
    OBJ_DATA	*obj;
    char	arg[MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if ( IS_NPC( ch ) ) return;

    if (!IS_WEREWOLF(ch))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }
if ( ch->gifts[FIANNA] < 1 )
    {
      stc("You have not learned the Fianna gift of brew.\n\r",ch);
      return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "You must state what you wish to brew?\n\r", ch );
	return;
    }

    if ( ( obj = get_obj_here( ch, arg ) ) == NULL )
    {
	send_to_char( "That isn't here.\n\r", ch );
	return;
    }

    if ( obj->item_type != ITEM_FOUNTAIN )
    {
	send_to_char( "You can only brew fountains.\n\r", ch );
	return;
    }

    if ( strlen( obj->questmaker ) > 2 && obj->questmaker != NULL
    &&	 !str_cmp( obj->questmaker, ch->name ) )
    {
	send_to_char( "You can't brew a fountain that belongs to someone else.\n\r", ch );
	return;
    }

    if ( obj->value[2] == 1 )
    {
	obj->value[2] = 0;
	act( "You transform the beer in $p into water.", ch, obj, NULL,
TO_CHAR );
	act( "$n transforms the beer in $p into water.", ch, obj, NULL, TO_ROOM );
    }
    else if ( obj->value[2] == 0 )
    {
	obj->value[2] = 1;
	act( "You change the water in $p into beer.", ch, obj, NULL,
TO_CHAR );
	act( "$n change the water in $p into beer.", ch, obj, NULL,
TO_ROOM );
    }
    else
	send_to_char( "You can only change water and beer.\n\r", ch );

    return;
}


void do_icychill( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
	char      buf [MAX_STRING_LENGTH];

    smash_tilde( argument );
    argument = one_argument( argument, arg1 );
    strcpy( arg2, argument );

    if ( IS_NPC(ch) )
	return;

	if (ch->fight_timer >0) {
        send_to_char("Not until your fight timer expires.\n\r", ch );
        return;}

    if (!IS_CLASS(ch, CLASS_WEREWOLF) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }
    if (ch->gifts[SHADOWLORDS] < 4  )
    {
        send_to_char("You must obtain at least level 4 in Shadow Lords to use Icy Chill.\n\r",ch);
	return;
    }
    
    if (ch->majesty_timer > 0)
    {
        if (ch->majesty_timer > 1)
            sprintf(buf,"You may not use icy chill for another %d seconds.\n\r",ch->majesty_timer);
        else
            sprintf(buf,"You may not use icy chill for another 1 second.\n\r");
        send_to_char(buf,ch);
        return;
    }

    if (has_timer(ch)) return;

    if (IS_AFFECTED(ch, AFF_STEELSHIELD))
    {
        REMOVE_BIT(ch->affected_by, AFF_STEELSHIELD);
        act( "You lower your icy chill of despair.",  ch, NULL, NULL, TO_CHAR );
        act( "$n looks less scary.",  ch, NULL, NULL, TO_NOTVICT );
        return;
    }
  

  
    SET_BIT(ch->affected_by, AFF_STEELSHIELD);
    act( "You raise your icy chill of despair.",  ch, NULL, NULL, TO_CHAR
);
    act( "$n suddenly looks very scary.",  ch, NULL, NULL, TO_NOTVICT);
    ch->majesty_timer = 60;
    return;
}

void do_eyeofcobra( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;
    
    if (!IS_WEREWOLF(ch))
     {
        send_to_char("Huh?\n\r",ch);
        return;
    }

   if (ch->gifts[GALLIARD] < 4)
  {
     send_to_char("You need Galliard 4 to use the eye of the cobra.\n\r",ch);
     return;
  }

    if (ch->cobra_timer > 0)
    {
        if (ch->cobra_timer > 1)
            sprintf(buf,"Your eyes will not recover for another %d seconds.\n\r", ch->cobra_timer);
        else
            sprintf(buf,"Your eyes will not recover for another 1 second.\n\r");
        send_to_char(buf,ch);
        return;
         }

    if ( arg[0] == '\0' )
    {
        send_to_char( "Who do you wish to use the eye of the cobra on?\n\r", ch );
        return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
    stc("They aren't here.\n\r",ch);
            return;
    }

    if ( ch == victim )
    {
        send_to_char( "You cannot put yourself into a trance.\n\r", ch );
        return;
    }

    if ( IS_NPC(victim) )
    {
        send_to_char( "Not on NPC's\n\r", ch );
        return;
    }


    if (is_safe(ch,victim)) return;

    if ( ch->gnosis[GCURRENT] < 10 )
    {
      stc("You need ten point of gnosis power to use Eye of the Cobra.\n\r",ch);
      return;
    }


    send_to_char("You use the eye of the cobra.\n\r", ch);
    act("$n uses the eye of the cobra.", ch, NULL, NULL, TO_ROOM );
     ch->cobra_timer = 60;

    if (strlen(victim->pcdata->love) > 2)
    {
        if (!str_cmp(victim->pcdata->love,ch->name))
        {
            act("You remove $N's trance!", ch, NULL, victim, TO_CHAR);
            act("You are no longer in a trance!", ch, NULL, victim, TO_VICT);
            free_string(victim->pcdata->love);
            victim->pcdata->love = str_dup( "" );
	    ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] - 10;
            if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
{
                guardian_message( victim );
                act("$n just used eye of the cobra on you.",ch,NULL,victim,TO_VICT);
            }
        }
        else
        {
        send_to_char( "They are already in a trance.\n\r",ch);
	ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] - 10;
            if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
{
            guardian_message( victim );
                act("$n just failed to use eye of the cobra on you.",ch,NULL,victim,TO_VICT);
            }
        }
        return;
    }

  if (!IS_NPC(victim) && (IS_WEREWOLF(victim)))
   {
        send_to_char("They resist you.\n\r",ch);
	ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] - 10;
        if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
        {
            guardian_message( victim );
            act("$n just failed to use eye of the cobra on you.",ch,NULL,victim,TO_VICT);
        }
        return;
    }
     if (!IS_NPC(victim) && victim->pcdata->resist[WILL_PRESENCE] > 0)
    {
        send_to_char("They resist you.\n\r",ch);
	ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] - 10;
        if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
        {
            guardian_message( victim );
            act("$n just failed to use the eye of the cobra on you.",ch,NULL,victim,TO_VICT);
        }
        return;
}        
        if (!IS_NPC(victim) && IS_WILLPOWER(victim, RES_PRESENCE) &&
        victim->pcdata->willpower[0] >= 10)
    {
        victim->pcdata->willpower[0] -= 10;
        victim->pcdata->resist[WILL_PRESENCE] = 60;
        if (!IS_WILLPOWER(victim, RES_TOGGLE))
            REMOVE_BIT(victim->pcdata->resist[0], RES_PRESENCE);
        send_to_char("You burn some willpower to resist the eye of the cobra.\n\r",victim);
  send_to_char("They resist you.\n\r",ch);
ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] -10;
        if (!IS_NPC(victim) && ch != victim && IS_MORE(victim,
MORE_GUARDIAN))
        {
            guardian_message( victim );
            act("$n just failed to use eye of the cobra on you.",ch,NULL,victim,TO_VICT);
        }
        return;
    }

    act("$N is now in a trance like state!", ch, NULL, victim, TO_CHAR);
     act("You now obey $n!", ch, NULL, victim, TO_VICT);
    act("$N gazes into $n's eyes!", ch, NULL, victim, TO_NOTVICT);

    free_string(victim->pcdata->love);
ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] -10;
    victim->pcdata->love = str_dup( ch->name );

    if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
    {
        guardian_message( victim );
        act("$n just used eye of the cobra on you.",ch,NULL,victim,TO_VICT);
            }
    return;
}
    

       

void do_giant( CHAR_DATA *ch, char *argument )
{
    char arg [MAX_INPUT_LENGTH];
    char buf [MAX_STRING_LENGTH]; 
    argument = one_argument( argument, arg ); 

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_WEREWOLF))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (ch->gifts[FIANNA] < 5)
    {
        send_to_char("You have not learned this Fianna gift.\n\r",ch);
	return;
    }

    
    if (IS_POLYAFF(ch, POLY_ZULO))
    {   
        REMOVE_BIT(ch->polyaff, POLY_ZULO);
        REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
        act( "You transform into human form.", ch, NULL, NULL, TO_CHAR );
        act( "$n's shrinks back into human form.", ch, NULL, NULL, TO_ROOM

);
/*
        ch->max_hit = ch->max_hit - 1500;
        ch->hit = ch->hit - 1500;
        if (ch->hit < 1) ch->hit = 1;
        ch->damroll = ch->damroll - 150;
        ch->hitroll = ch->hitroll - 150; 
*/
        free_string( ch->morph );
        ch->morph = str_dup( "" );
if (IS_SET(ch->special, SPC_WOLFMAN))  
{
 SET_BIT(ch->affected_by, AFF_POLYMORPH);
    SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
    sprintf(buf,"%s the werewolf",ch->name);
    free_string(ch->morph);
    ch->morph = str_dup(buf);
}
        return;
    }
  
/*
  else if (IS_AFFECTED(ch,AFF_POLYMORPH))
    {
send_to_char("You cant use Gift of the Spriggan when changed.\n\r",ch);
return;
}
*/  
 

        if (ch->stance[0] != -1) do_stance(ch,"");
	if (ch->mounted == IS_RIDING) do_dismount(ch,"");
        act( "You transform into large beast.", ch, NULL, NULL, TO_CHAR );
        act( "$n's body grows and distorts into a giant werewolf.", ch,
NULL, NULL, TO_ROOM );
        
        ch->pcdata->mod_str = 15;
        ch->pcdata->mod_dex = 15;
        SET_BIT(ch->polyaff, POLY_ZULO);
        SET_BIT(ch->affected_by, AFF_POLYMORPH);
        if (!str_cmp(ch->name,"sage")) sprintf(buf,"A huge giant werewolf  Sage");    
	sprintf(buf, "%s A huge giant werewolf", ch->name);
        free_string( ch->morph );
        ch->morph = str_dup( buf );
/*
        ch->max_hit = ch->max_hit + 1500;
        ch->hit = ch->hit + 1500;
        ch->damroll = ch->damroll + 150;
        ch->hitroll = ch->hitroll + 150;
*/
        return;
    }
void do_balorsgaze( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
 
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_WEREWOLF))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
 
    if (ch->gifts[FIANNA] < 4)
    {
        send_to_char("You have not yet learned the Fianna gift of Balor's gaze.\n\r",ch);
	return;
    }
 
 
    if ( arg[0] == '\0' )
    {
        send_to_char( "Who do you wish to use Balor's gaze on?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if (IS_NPC(victim))
    {
        send_to_char("Not on mobs.\n\r", ch);
        return;
    }

    if ( IS_IMMORTAL(victim) && victim != ch )
    {
        send_to_char( "You can only use Balor's gaze on Avatar's or lower.\n\r", ch );
	return;
    }

    if (is_safe(ch,victim) == TRUE) return;

    if (victim->hit < victim->max_hit)
    {
      send_to_char("They are hurt and suspicious.\n\r", ch);
      return;
    }
    act("You close your eyes and concentrate on $N.",ch,NULL,victim,TO_CHAR);
    act("$n's right eye begins to glow a baleful red!",ch,NULL,victim,TO_VICT);
    act("$n closes $s eyes and cencentrates on $N.",ch,NULL,victim,TO_NOTVICT);
    WAIT_STATE(ch, 12);
    if (number_percent( ) < 50)
    {
        send_to_char("You failed.\n\r",ch);
        return;
    }
 
    act("You scream in pain as your body is torn apart from the inside out!", victim,NULL,NULL,TO_CHAR);
    act("$n screams in pain as there body is torn apart from the inside out!", victim,NULL,NULL,TO_ROOM);
    SET_BIT(victim->flag2, AFF2_BALOR);
    return;
}

void do_banshee( CHAR_DATA *ch, char *argument )
{
   CHAR_DATA *vch;
   CHAR_DATA *vch_next;
   CHAR_DATA *mount;
   char arg[MAX_INPUT_LENGTH];

   argument = one_argument( argument, arg );

   if ( IS_NPC(ch) ) return;
 
   if ( !IS_CLASS(ch, CLASS_WEREWOLF) )
   {
     stc("Huh?\n\r",ch);
     return;
   }
   
if ( ch->gifts[FIANNA] < 3 )
    {
      stc("You have not learned the Fianna gift of Howl of the Banshee.\n\r",ch);
      return;
    }


   if ( IS_SET(ch->in_room->room_flags, ROOM_SAFE) )
   {
     stc("Not while in a safe room.\n\r",ch);
     return;
   }
 
    if ( ch->gnosis[GCURRENT] < 6 )
    {
      stc("You need six point of gnosis power to use Howl of the Banshee.\n\r",ch);
      return;
    }

    for ( vch = char_list; vch != NULL; vch = vch_next )
    {
        vch_next        = vch->next;

        if ( vch->in_room == NULL )
            continue;
        if ( !IS_NPC(vch) && vch->pcdata->chobj != NULL )
            continue;
        if ( ch == vch )
              continue;
        if ( vch->in_room == ch->in_room )
        {
            if ( ( mount = ch->mount ) != NULL )
            {
                if ( mount == vch )
                continue;
            }
            if (can_see(ch,vch))
            {
              if ( number_range( 1, (7 - ch->gifts[FIANNA])) ==2 )
              {
                act("A look of concentration crosses $n face.",ch,NULL,vch,TO_ROOM);
		WAIT_STATE( ch, 25 );
                stc("You hear an ear poping howl and are suddenly attacked from all sides.\n\r",vch);
               // vch->position = POS_STUNNED;
      			vch->hit -= 1000;
      			vch->position = POS_STUNNED;
		ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] -6;
                act("You hear an ear poping howl, $n is suddenly attacked from all sides.",vch,NULL,vch,TO_NOTVICT);

                return;
              }
	      else
	      {
                act("A look of concentration crosses $n face.",ch,NULL,vch,TO_ROOM);
	        return;
	      }
	    }
	    else continue;

	    return;
        }
    }

  return;
}






void do_bridgegate(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;

	
        if (!IS_CLASS(ch, CLASS_WEREWOLF))
{
        stc("Huh?\n\r",ch);
        return;
        }	

     if ( ch->gifts[GALLIARD] < 5 )
    {
      stc("You have not learned the Galliard gift of Bridge Walker.\n\r",ch);
      return;
    }

    if (ch->fighting == NULL && argument[0] == '\0')
    {
	stc("Who do you wish to bridge into combat with?\n\r", ch);
	return;
    }

    if (ch->fighting == NULL)
    {
	if ( (victim = get_char_room(ch, argument) ) == NULL)
	{
	    stc("They aren't here.\n\r", ch);
	    return;
	}


    if (ch == victim)
    {
        stc("You can't bridge into combat with yourself.\n\r", ch);
        return;
    }
    if (is_safe(ch, victim)) return;

    if ( ch->gnosis[GCURRENT] < 1 )
    {
      stc("You need one point of gnosis power to use Bridge Walker.\n\r",ch);
      return;
    }


	ch->gnosis[GCURRENT] = ch->gnosis[GCURRENT] -1;
	WAIT_STATE(ch, 24);
	SET_BIT(ch->flag2, AFF2_BLINK_1ST_RD);
	stop_fighting(ch, TRUE);
	stc("You open a minor Moon Bridge and step inside.\n\r", ch);
	act("$n opens a minor Moon Bridge and steps inside.", ch, NULL, NULL, TO_ROOM);
	ch->bridgekill = victim;
	return;
    }
    WAIT_STATE(ch, 24);
    victim = ch->fighting;
    SET_BIT(ch->flag2, AFF2_BLINK_2ND_RD);
    stop_fighting(ch, TRUE);
    stc("You open a minor Moon Bridge and step inside.\n\r", ch);
    act("$n opens a minor Moon Bridge and steps inside.", ch, NULL, NULL, TO_ROOM);
    ch->bridgekill = victim;
	WAIT_STATE(ch, 24);
//return;
} 

void do_ragesong(CHAR_DATA *ch,char *argument)
{
  CHAR_DATA *victim;
  char arg[MSL];

  if(!IS_CLASS(ch,CLASS_WEREWOLF) && !IS_ABOMINATION(ch)) 
  {do_huh(ch,"");return;}
  if(ch->gifts[GALLIARD] < 3)
  {
    stc("You require level 3 in the gift of Galliard to use the Song of Rage.\n\r",ch);
    return;
  }
  argument=one_argument(argument,arg);
  if((victim=get_char_room(ch,arg))==NULL)
  {stc("They are not here.\n\r",ch);return;}
  if (is_garou(ch)  && IS_AFFECTED(victim,AFF_POLYMORPH))
  {
    stc("They are already raged.\n\r",ch);
    return;
  }
  else
  if(IS_CLASS(victim,CLASS_VAMPIRE)&&victim->pcdata->stats[UNI_RAGE]>0)
  {
    stc("They are already in a blood frenzy.\n\r",ch);
    return;
  }
    WAIT_STATE(ch,14);
    act("You sing the Song of Rage to $N.\n\r",ch,NULL,victim,TO_CHAR);
    act("$n sings the Song of Rage to $N.",ch,NULL,victim,TO_NOTVICT);
    act("$n sings the Song of Rage to you.",ch,NULL,victim,TO_VICT);

    if(number_range(1,5)!=2)
    {
	stc("You failed.\n\r",ch);
	return;
    }
    else
    if(IS_CLASS(victim,CLASS_WEREWOLF))
    {
	act("You send them into a frenzied rage!",ch,NULL,victim,TO_CHAR);
	act("$n sends $N into a frenzied rage!",ch,NULL,victim,TO_NOTVICT);
	act("$n sends you into a frenzied rage!",ch,NULL,victim,TO_VICT);
	victim->pcdata->stats[UNI_RAGE] = number_range(100,130);
	do_werewolf(victim,"");
	return;
    }
    else if(IS_CLASS(victim,CLASS_VAMPIRE))
    {
        act("You send them into a frenzied rage!",ch,NULL,victim,TO_CHAR);
        act("$n sends $N into a frenzied rage!",ch,NULL,victim,TO_NOTVICT);
        act("$n sends you into a frenzied rage!",ch,NULL,victim,TO_VICT);
	victim->pcdata->stats[UNI_RAGE] = number_range(100,130);
        if (victim->beast > 0) do_beastlike(victim,"");
        return;
    }
    else
    {
	act("You send them into a frenzied rage!",ch,NULL,victim,TO_CHAR);
	act("$n sends $N into a frenzied rage!",ch,NULL,victim,TO_NOTVICT);
	act("$n sends you into a frenzied rage!",ch,NULL,victim,TO_VICT);
	do_berserk(victim,"");
 	return;
    }
}
void do_aeolus(CHAR_DATA *ch,char *argument)
{
 CHAR_DATA *rch;
 int chance;


      chance = number_percent();


  
  if(!IS_CLASS(ch,CLASS_WEREWOLF))
  {do_huh(ch,"");return;}
  if(ch->gifts[BLACKFURIES] < 5)
  {
    stc("You require level 5 in Black Furies to use the Curse of Aeolus.\n\r",ch);
    return;
  }

  if(ch->fighting == NULL)
  {
    stc("You are fighting no one.\n\r",ch);
    return;
  }


if ( chance > 40 && IS_CLASS(ch, CLASS_WEREWOLF))
{
 stc("You failed.\n\r", ch );
        return;
        }


  act("$n fills the room with fog.",ch,NULL,NULL,TO_ROOM);
  act("You fill the room with fog.",ch,NULL,NULL,TO_CHAR);
  for(rch=ch->in_room->people;rch != NULL;rch=rch->next_in_room)
  {
    if(rch->fighting == ch || rch== ch)
      {
	stop_fighting(rch,TRUE);
	if(rch==ch)continue;
	act("You find it impossible to continue battle with $n.",ch,NULL,rch,TO_VICT);
	act("$N is blinded by fog.",ch,NULL,rch,TO_NOTVICT);
	WAIT_STATE(rch,8);
      }
  }

}
void do_quicksand(CHAR_DATA *ch,char *argument)
{

  if(!IS_WEREWOLF(ch)){do_huh(ch,"");return;}
  if(ch->gifts[REDTALONS] < 4)
  {
    stc("This gift requires level 4 Red Talons.\n\r",ch);
    return;
  }
  if(IS_GAR1(ch,WOLF_QUICKSAND))
  {
    sta("The ground around you resumes its firmness.\n\r",ch->in_room->area);
    REMOVE_BIT(ch->garou1,WOLF_QUICKSAND);
    return;
  }
  if(ch->gnosis[GCURRENT] < 15){
	stc("You must have 15 points of gnosis to use this.\n\r",ch);
	return;}
  ch->gnosis[GCURRENT]-=15;
  sta("The ground around you becomes soft.\n\r",ch->in_room->area);
  SET_BIT(ch->garou1,WOLF_QUICKSAND);
}

void do_waste(CHAR_DATA *ch,char *argument)
{

  if(!IS_WEREWOLF(ch)){do_huh(ch,"");return;}
  if(ch->gifts[REDTALONS] < 5)
  {
    stc("This gift requires level 5 Red Talons.\n\r",ch);
    return;
  }
  if(IS_SET(ch->in_room->area->bits,WASTE))
  {
    sta("The land shifts into something more recognizable.\n\r",ch->in_room->area);
    REMOVE_BIT(ch->in_room->area->bits,WASTE);
    return;
  }
  if(ch->gnosis[GCURRENT] < 25){
        stc("You must have 25 points of gnosis to use this.\n\r",ch);        return;}
  ch->gnosis[GCURRENT]-=25;
  sta("The land around you blurs and shifts.",ch->in_room->area);
  SET_BIT(ch->in_room->area->bits,WASTE);
  REMOVE_BIT(ch->in_room->area->bits,UPDATEWASTE);
}

