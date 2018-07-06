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

void do_principles( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_NINJA))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (arg1[0] == '\0' && arg2[0] == '\0')
    {
	sprintf(buf,"Principles: Sora (%d), Chikyu (%d), Ningenno (%d).\n\r",
	ch->pcdata->powers[NPOWER_SORA], ch->pcdata->powers[NPOWER_CHIKYU],
	ch->pcdata->powers[NPOWER_NINGENNO]);
	send_to_char(buf,ch);
	return;
    }
    if (arg2[0] == '\0')
    {
	if (!str_cmp(arg1,"sora"))
	{
	    send_to_char("Sora - The finding, observing, and locating principle.\n\r\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_SORA] < 1) 
		send_to_char("You have none of the Sora principles.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_SORA] > 0) 
		send_to_char("Mitsukeru -Locate- The scrying power to find enemies.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_SORA] > 1) 
		send_to_char("Koryou -Consider- The read aura power, learn about your enemies.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_SORA] > 2) 
		send_to_char("Kakusu -Hidden- Enhanced Hide.  Only other ninjas can see you.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_SORA] > 3) 
		send_to_char("Uro-Uro -Silent Walk- You leave no footprints behind.\n\r",ch);
		if (ch->pcdata->powers[NPOWER_SORA] > 4)
		send_to_char("Kanzuite -Aware- The truesight power.\n\r", ch);
		if (ch->pcdata->powers[NPOWER_SORA] > 5)
		send_to_char("Bomuzite -Sleep Gas- By mixing an potion, you can put everyone in a room to sleep.\n\r", ch);
        if (ch->pcdata->powers[NPOWER_SORA] > 6)
		send_to_char("Mizotamouyo -Shadowwalk- You are able to walk the paths of darkness to reach another's location.\r\n", ch);
		return;
	}
	else if (!str_cmp(arg1,"chikyu"))
	{
	    send_to_char("Chikyu - Preperation for battle.\n\r\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_CHIKYU] < 1) 
		send_to_char("You have none of the Chikyu principles.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_CHIKYU] > 0) 
		send_to_char("Tsuyoku -Strength- Toughness.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_CHIKYU] > 1) 
		send_to_char("Songai -Damage- Enhanced damage.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_CHIKYU] > 2) 
		send_to_char("Isogu -Haste- Adds two extra attacks.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_CHIKYU] > 3) 
		send_to_char("Tsuiseki -Hunt- Fast hunting.\n\r",ch);
		if (ch->pcdata->powers[NPOWER_CHIKYU] > 4)
		send_to_char("Sakeru -Sonic Speed- Dodge more attacks.\n\r", ch);
	    if (ch->pcdata->powers[NPOWER_CHIKYU] > 5)
		send_to_char("HaraKiri -Blood Power- Hurt yourself to gain power.\n\r", ch );
        if (ch->pcdata->powers[NPOWER_CHIKYU] > 6)
		send_to_char("Orimasu -Mending- Regenerate your being through willpower alone.\n\r", ch );
	if (ch->pcdata->powers[NPOWER_CHIKYU] > 7)
		send_to_char("Gunaya - Entrap your foes with a spiritual net.\n\r", ch);
		return;
	}
	else if (!str_cmp(arg1,"ningenno"))
	{
	    send_to_char("Ningenno - The battle, attacking and getting away.\n\r\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_NINGENNO] < 1) 
		send_to_char("You have none of the Ningenno principles.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_NINGENNO] > 0) 
		send_to_char("Tsume -Claw- IronClaw always worn on wrist to aid in hand-to-hand.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_NINGENNO] > 1) 
		send_to_char("Hakunetsu -First Strike- You get super backstabs.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_NINGENNO] > 2) 
		send_to_char("Mienaku -Vanish- Never fail flee.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_NINGENNO] > 3) 
		send_to_char("Shiroken -Throwing Star- Added attack per round, like headbutt for demons.\n\r",ch);
		if (ch->pcdata->powers[NPOWER_NINGENNO] > 4)
		send_to_char("Dokuyaku -Poison- Adds poisons to the Shiroken\n\r", ch);
	    if (ch->pcdata->powers[NPOWER_NINGENNO] > 5)
    	send_to_char("Circle - circle behind your opponent and hit him during battle\n\r", ch );
		if (ch->pcdata->powers[NPOWER_NINGENNO] > 6)
		send_to_char("Trip - Trip your opponent and send him sprawling to the ground.\n\r", ch );

	    return;
	}
	sprintf(buf,"Principles: Sora (%d), Chikyu (%d), Ningenno (%d).\n\r",
	ch->pcdata->powers[NPOWER_SORA], ch->pcdata->powers[NPOWER_CHIKYU],
	ch->pcdata->powers[NPOWER_NINGENNO]);
	send_to_char(buf,ch);
	return;
    }
    if (!str_cmp(arg2,"improve"))
    {
	int improve;
	int cost;
	int max;

	     if (!str_cmp(arg1,"sora"   )) {improve = NPOWER_SORA;   max=7;}
	else if (!str_cmp(arg1,"chikyu"   )) {improve = NPOWER_CHIKYU;   max=8;}
	else if (!str_cmp(arg1,"ningenno"   )) {improve = NPOWER_NINGENNO; max=7;}
	else
	{
	    send_to_char("Principles: Sora, Chikyu, Ningenno.\n\r",ch);
	    return;
	}							
	cost = (ch->pcdata->powers[improve]+1) * 10;
	arg1[0] = UPPER(arg1[0]);
	if ( ch->pcdata->powers[improve] >= max )
	{
	    sprintf(buf,"You have already gained all the powers of the %s principle.\n\r", arg1);
	    send_to_char(buf,ch);
	    return;
	}
	if ( cost > ch->practice )
	{
	    sprintf(buf,"It costs you %d primal to improve your %s principle.\n\r", cost, arg1);
	    send_to_char(buf,ch);
	    return;
	}
	ch->pcdata->powers[improve] += 1;
	ch->practice -= cost;
	sprintf(buf,"You improve your ability in the %s principle.\n\r", arg1);
	send_to_char(buf,ch);
    }
    else send_to_char("To improve a principle, type: Principle <principle type> improve.\n\r",ch);
	return;
}

void do_michi(  CHAR_DATA *ch, char *argument  )
{
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}

  if ( IS_CLASS(ch, CLASS_NINJA) )
  {
	
	if ( ch->pcdata->stats[UNI_RAGE] >= 50 )
	{
	    send_to_char("But you are already in the state of Michi.\n\r",ch);
	    return;
	}
	if ( ch->pcdata->powers[NINJAKI] < 100 ) 
	{
		send_to_char("But you don't have enough Ki to perform the michi.\n\r", ch);
		return;
	} 
	
	send_to_char("You are gifted positive energy while performing the michi.\n\r",ch);
	act("$n is gifted positives energy while performing the michi.",ch,NULL,NULL,TO_ROOM);
	ch->pcdata->stats[UNI_RAGE] += 200;
	  ch->pcdata->powers[NINJAKI] -= 100;
	WAIT_STATE(ch,12);
	return;
  }
	else
    send_to_char("But you are already in the state of Michi.\n\r",ch);
    return;
}

void do_discipline( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;
	
	if ( !IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->stats[UNI_GEN] < 2)
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
    
    if ( arg[0] == '\0' )
    {
	send_to_char( "Discipline whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    if ( IS_IMMORTAL(victim) )
    {
	send_to_char( "Not on Immortals's.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "You cannot discipline yourself.\n\r", ch );
	return;
    }

    if (IS_CLASS(victim, CLASS_NINJA))
    {
	send_to_char( "They are already disciplined.\n\r", ch );
	return;
    }

    if ( victim->level != LEVEL_AVATAR && !IS_IMMORTAL(victim) )
    {
	send_to_char( "You can only teach avatars.\n\r", ch );
	return;
    }

	if (victim->class != 0) {
	send_to_char("They already have a profession.\n\r", ch );
	return;}
    if (!IS_IMMUNE(victim,IMM_VAMPIRE))
    {
	send_to_char( "You cannot discipline an unwilling person.\n\r", ch );
	return;
    }

    if (ch->exp < 100000)
    {
	send_to_char("You cannot afford the 100000 exp required to discipline them.\n\r",ch);
	return;
    }

    if (victim->exp < 100000)
    {
	send_to_char("They cannot afford the 100000 exp required to be disciplined from you.\n\r",ch);
	return;
    }

    ch->exp -= 100000;
    victim->exp -= 100000;

    act("You teach $N the ways of the ninja.", ch, NULL, victim, TO_CHAR);
    act("$n teaches $N the ways of the ninja.", ch, NULL, victim, TO_NOTVICT);
    act("$n teaches you the way of the ninja.", ch, NULL, victim, TO_VICT);
    victim->class    = CLASS_NINJA;
    send_to_char( "You are now a ninja.\n\r", victim );
    free_string(victim->lord);
    free_string(victim->clan);
    victim->clan = str_dup(ch->clan);
    victim->lord = str_dup(ch->name);
    victim->pcdata->stats[UNI_GEN] = ch->pcdata->stats[UNI_GEN] + 1;
    save_char_obj(ch);
    save_char_obj(victim);
    return;
}

void do_kakusu( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}


	
	if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_SORA] < 3 )
	{
	  send_to_char("You have not learned the Sora principle to 3.\n\r", ch);
	  return;
}
if (ch->fight_timer >0) {
        send_to_char("Not until your fight timer expires.\n\r", ch );
        return;}	



	if ( ch->pcdata->powers[NINJAKI] < 30 )
	{
		send_to_char("You don't have 30 ki to activate your power.\n\r", ch);
		return;
	} 

    if ( IS_AFFECTED(ch, AFF_HIDE) )
    {
	REMOVE_BIT(ch->affected_by, AFF_HIDE);
	act( "$n appears from the shadows.", ch, NULL, NULL, TO_ROOM );
	send_to_char( "You appear from the shadows.\n\r", ch );
    }
    else
    {
	act( "$n disappears into the shadows.", ch, NULL, NULL, TO_ROOM );
	send_to_char( "You disappear into the shadows.\n\r", ch );
	SET_BIT(ch->affected_by, AFF_HIDE);
	ch->pcdata->powers[NINJAKI] -= 30;
    }
    return;
}

void do_orimasu(CHAR_DATA *ch, char *argument)
{
	if(IS_NPC(ch)) return;
	if(!IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->powers[NPOWER_CHIKYU] < 7)
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	else if( ch->pcdata->powers[NINJAKI] < 15 )
	{
		send_to_char("You do not have the required mental energies to mend your being.\r\n", ch);
		return;
	}
	else if( ch->position == POS_FIGHTING )
	{
		send_to_char("You cannot mend your being with such distractions!\r\n", ch);
		return;
	}

	send_to_char("You take a deep breath and attempt to gain mastery over your injuries.\r\n", ch);
	act( "$n takes a deep breath and begins to concentrate.", ch, NULL, NULL, TO_ROOM );
	if( number_range(1, 5) != 1 )
	{
		send_to_char("You mend some of your injuries by force of will alone.", ch);
		ch->hit  += (int)(ch->max_hit  * (double)((double)1/(double)(number_range(8,12))));
		ch->mana += (int)(ch->max_mana * (double)((double)1/(double)(number_range(12,16))));
		ch->move += (int)(ch->max_move * (double)((double)1/(double)(number_range(12,16))));

		if( ch->hit > ch->max_hit ) ch->hit = ch->max_hit;
		if( ch->mana > ch->max_mana ) ch->mana = ch->max_mana;
		if( ch->move > ch->max_move ) ch->move = ch->max_move;
		
		ch->pcdata->powers[NINJAKI] -= 15;
		act( "$n's wounds slowly begin to close before your eyes!", ch, NULL, NULL, TO_ROOM );
		WAIT_STATE(ch, 12);
		return;
	}
	else
	{
		send_to_char("You were unable to gain mastery over your mortal being.", ch);
		ch->pcdata->powers[NINJAKI] -= 5;
		WAIT_STATE(ch, 12);
		return;
	}
}

void do_kanzuite( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	
    if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_SORA] < 5 )
	{
	  send_to_char("You have not learned the Sora principle to 5.\n\r", ch);
	  return;
	}
	
	else if ( ch->pcdata->powers[NINJAKI] < 30 )  
	{
		send_to_char("You don't have 30 Ki to increase your awareness.\n\r", ch);
		return;
	} 

    if ( IS_SET(ch->act, PLR_HOLYLIGHT) )
    {
	REMOVE_BIT(ch->act, PLR_HOLYLIGHT);
	send_to_char( "You're senses return to normal.\n\r", ch );
    }
    else
    {
	SET_BIT(ch->act, PLR_HOLYLIGHT);
	send_to_char( "You're senses increase into incredible proportions.\n\r", ch );
	 ch->pcdata->powers[NINJAKI] -= 30; 
    }

    return;
}

void do_mienaku( CHAR_DATA *ch, char *argument )
{
    ROOM_INDEX_DATA *was_in;
    ROOM_INDEX_DATA *now_in;
    CHAR_DATA *victim;
    int attempt;


	if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_NINGENNO] < 3 )
	{
	send_to_char("You have not learned the Ningenno principle to 3.\n\r", ch);
	return;
	}
	else if (!IS_CLASS(ch, CLASS_NINJA) )
	{
	send_to_char("Huh?\n\r", ch);
	return;
	}
	
	if ( IS_NPC(ch) ) return;

    if ( ( victim = ch->fighting ) == NULL )
    {
	if ( ch->position == POS_FIGHTING )
	    ch->position = POS_STANDING;
	send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;
    }
	if ( ch->pcdata->powers[NINJAKI] < 20 )  
	{
	send_to_char("You don't have enough Ki points to flee.\n\r", ch);
	return;
	} 
    if (IS_AFFECTED(ch, AFF_WEBBED))
    {
	send_to_char("You are unable to move with all this sticky webbing on.\n\r",ch);
	return;
    }
  
    was_in = ch->in_room;
    
{
	EXIT_DATA *pexit;
	int door;

	send_to_char("You move to vanish from combat!\n\r", ch );

for ( attempt =  0; attempt < 6; attempt++ ) 
	{
	door = number_door( );
	if ( ( pexit = was_in->exit[door] ) == 0
	||   pexit->to_room == NULL
	||   IS_SET(pexit->exit_info, EX_CLOSED)
	|| ( IS_NPC(ch)
	&&   IS_SET(pexit->to_room->room_flags, ROOM_NO_MOB) ) )
	      continue;


	move_char( ch, door );
	if ( ( now_in = ch->in_room ) == was_in )
	      continue;

/* Use escape instead of flee so people know it's the ninja power */
	ch->in_room = was_in;
	act( "$n has escaped!", ch, NULL, NULL, TO_ROOM );
	ch->in_room = now_in;
	
	if ( !IS_NPC(ch) )
	    send_to_char( "You escape from combat!\n\r", ch ); 

/*	if (victim->in_room == ch->in_room)
    {
    	SET_BIT(victim->extra,BLINDFOLDED);
    	act("You start to move at super speeds and blind $N.",ch,NULL,victim,TO_CHAR);
    	act("$n starts to move at super speeds and blinds $N.",ch,NULL,victim,TO_ROOM);
    	act("$n starts to move at super speeds and blinds you.",ch,NULL,victim,TO_VICT);
    	
    	return;
    }
  */  
	  ch->pcdata->powers[NINJAKI] -= 20; 
	stop_fighting( ch, TRUE );
	return;
   }
   
}
    return;
}

void do_ningentra( CHAR_DATA *ch, char *argument )
{
	sh_int rvnum;
	CHAR_DATA *victim;

	rvnum = -1;
	if (!IS_CLASS(ch, CLASS_NINJA))
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	if (ch->pcdata->stats[UNI_GEN] != 2)
	{
		send_to_char("Only the ninja leaders have knowledge of this power.\n\r", ch);
		return;
	}
	/* Define room numbers here per clan */
	if (!str_cmp(ch->clan, "Shadow")) rvnum = 31920;

	if (rvnum == -1) 
	{
		send_to_char("Your clan HQ has not been recognised...\n\r", ch);
		send_to_char("Please request Hunter to add the HQ to the list.\n\r", ch);
		return;
	}
	if (ch->in_room->vnum != rvnum)
	{
		send_to_char("You can only use this in your HQ.\n\r", ch);
		return;
	}
	
	if ((victim = get_char_world(ch, argument)) == NULL)
	{
		send_to_char("You cannot find them.\n\r", ch);
		return;
	}
	
	if (str_cmp(victim->clan, ch->clan))
	{
		send_to_char("You can only call those of your own.\n\r", ch);
		return;
	}
	else
	if (victim->position == POS_FIGHTING)
	{
		send_to_char("Sorry, they are too busy right now.\n\r", ch);
		return;
	}
	else
	{
		char_from_room( victim );
		char_to_room( victim, ch->in_room);
		send_to_char( "Ok, they are in the HQ.\n\r", ch);
		send_to_char( "You have been put in your HQ by your master.\n\r", victim);
		send_to_char( "Type HOME HERE to make this your home.\n\r", victim);
	}
	return;
}	
	

void do_bomuzite( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg1 );
        
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA))
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	else if ( ch->pcdata->powers[NPOWER_SORA] < 6 )
	{
	    send_to_char("You have not learned the Sora principle to 6.\n\r", ch);
	    return;
	}
	
    if ( arg1[0] == '\0' )
    {
	send_to_char( "Bomb who?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They are not here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "Not on yourself!\n\r", ch );
	return;
    }
	
    if ( ch->position == POS_FIGHTING )
    {
	send_to_char( "Not while fighting!\n\r", ch );
	return;
    }
    
	if ( ch->pcdata->powers[NINJAKI] < 30 )  
	{
	send_to_char("You do not have enough Ki points.\n\r", ch);
	return;
	}     
	  
    if ( victim->in_room == ch->in_room )
	{
	act("You toss your bomb onto the floor and put $N to sleep.",ch,NULL,victim,TO_CHAR);
	act("$n tosses a bomb onto the floor.  You feel sleepy.",ch,NULL,victim,TO_VICT);
	victim->position = POS_SLEEPING;
	  ch->pcdata->powers[NINJAKI] -= 20; 
	WAIT_STATE(ch, 24);
	return;
	}
	
	return;
}


void do_tsume(CHAR_DATA *ch, char *argument) {

		if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->powers[NPOWER_NINGENNO] < 1) {
	send_to_char("Huh?\n\r", ch );
	return;}

	if (IS_VAMPAFF(ch, VAM_CLAWS)) {

	send_to_char("You remove the IronClaws from your wrists.\n\r", ch );
	REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_CLAWS);
	return;}

	send_to_char("You attach IronClaws to your wrists.\n\r", ch );
	SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_CLAWS);

	return;
}

void do_hara_kiri(CHAR_DATA *ch, char *argument) {

	if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->powers[NPOWER_CHIKYU] < 6) {
	send_to_char("Huh?\n\r", ch );
	return;}

	if (ch->pcdata->powers[HARA_KIRI] > 0) {
	send_to_char("You are already experiencing the power of HaraKiri.\n\r", ch );
	return;}

	if (ch->hit < ch->max_hit/10) {
	send_to_char("You are hurt too badly already.\n\r", ch );
	return;}

	ch->pcdata->powers[HARA_KIRI] = ch->hit/500;
	if (ch->pcdata->powers[HARA_KIRI] < 5)
	ch->pcdata->powers[HARA_KIRI] = 5;	
	ch->hit = 1;
	ch->mana = 1;
	ch->move = 1;
	send_to_char("You cut your finger and bleed profusely.\n\r", ch );
	act("$n cuts his finger and obtains the power of HaraKiri.",ch,NULL,NULL,TO_ROOM);
	return;
}

void do_trip(CHAR_DATA *ch, char *argument) {

	char  arg[MAX_STRING_LENGTH];
	char  buf[MAX_STRING_LENGTH];
	CHAR_DATA *victim;
	
	argument = one_argument(argument, arg);
	
	if( IS_NPC(ch) ) return;

	if(!IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->powers[NPOWER_NINGENNO] < 7 ) {
		send_to_char("Huh?\n\r", ch);
		return;
	}

    
    if( (victim = ch->fighting) == NULL )
	{
		if( arg[0] == '\0' )
		{
			send_to_char("Trip whom?\r\n", ch);
			return;
		}
		if( (victim = get_char_room(ch, arg)) == NULL )
		{
			send_to_char("How can you trip someone who is not here?\r\n", ch);
			return;
		}
        else if( IS_NPC(victim) )
		{
			send_to_char("You cannot trip them!\r\n", ch);
			return;
		}
	}
   
	if( number_range(1,4) != 1 )
	{
		sprintf(buf, "You skillfully trip %s, and they go down!\r\n", victim->name);
		send_to_char(buf, ch);
		sprintf(buf, "%s makes an impressive fighting move, and you land on your butt!\r\n", ch->name);
		send_to_char(buf, victim);
		WAIT_STATE(ch, 10);
		WAIT_STATE(victim, 15);
		return;
	}
	else
	{
		send_to_char("You attempt an impressive fighting move, but instead land on your butt!\r\n", ch);
		sprintf(buf, "%s attempts to make an impressive fighting move, but lands on his butt!\r\n", ch->name);
	    send_to_char(buf, victim);
		WAIT_STATE(ch, 20);
		return;
    }
}


void do_mitsukeru( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    ROOM_INDEX_DATA *chroom;
    ROOM_INDEX_DATA *victimroom;
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->powers[NPOWER_SORA]
<1) {
	send_to_char("Huh?\n\r", ch );
	return;}
	if (arg[0] == '\0')
    {
	send_to_char( "Scry on whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "They are not here.\n\r", ch );
	return;
    }

    chroom = ch->in_room;
    victimroom = victim->in_room;

    char_from_room(ch);
    char_to_room(ch,victimroom);
    if (IS_AFFECTED(ch, AFF_SHADOWPLANE) && (!IS_AFFECTED(victim,
AFF_SHADOWPLANE)))
    {
	REMOVE_BIT(ch->affected_by, AFF_SHADOWPLANE);
	do_look(ch,"auto");
	SET_BIT(ch->affected_by, AFF_SHADOWPLANE);
    }
    else if (!IS_AFFECTED(ch, AFF_SHADOWPLANE) && (IS_AFFECTED(victim,
AFF_SHADOWPLANE)))
    {
	SET_BIT(ch->affected_by, AFF_SHADOWPLANE);
	do_look(ch,"auto");
	REMOVE_BIT(ch->affected_by, AFF_SHADOWPLANE);
    }
    else
	do_look(ch,"auto");
    char_from_room(ch);
    char_to_room(ch,chroom);
//    ch->fight_timer = 10;
    return;
}

void do_mizotamouyo( CHAR_DATA *ch, char *argument )
{
	CHAR_DATA *victim;
	char	  arg[MAX_INPUT_LENGTH];

	argument = one_argument(argument, arg);

	if( IS_NPC(ch) ) return;
	if( !IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->powers[NPOWER_SORA] < 7 )
	{
		send_to_char("Huh?", ch);
		return;
	}
    if (ch->fight_timer > 0) 
	{
        send_to_char("Not until your fight timer expires.\n\r", ch );
		return;
	}

	if( arg[0] == '\0' )
	{
		send_to_char("Who do you wish to walk to via the paths of darkness?\r\n", ch);
		return;
	}
	
    if ( ( victim = get_char_world( ch, arg ) ) == NULL
    ||   victim == ch
    ||   victim->in_room == NULL
    ||   ch->in_room == NULL)    
    {
		send_to_char( "You attempt to walk through the shadows, but fail.\n\r", ch );
		return;
    }

    if ( victim->in_room == ch->in_room )
    {
		send_to_char( "But you are already there!\n\r", ch );
		return;
    }

    if ( IS_SET(victim->in_room->room_flags, ROOM_SAFE)
    ||   IS_SET(victim->in_room->room_flags, ROOM_PRIVATE)
    ||   IS_SET(victim->in_room->room_flags, ROOM_SOLITARY)
    ||   IS_SET(victim->in_room->room_flags, ROOM_NO_RECALL)
    ||   (!IS_NPC(victim) && !IS_IMMUNE(victim, IMM_SUMMON) ) )
    {
		send_to_char( "You are unable to focus on their location.\n\r", ch );
		return;
    }

    send_to_char("You dissipate into the shadows.\n\r",ch);
    act("$n dissipates into the shadows, slowly vanishing from sight.",ch,NULL,NULL,TO_ROOM);
    char_from_room(ch);
    char_to_room(ch,victim->in_room);
    do_look(ch,"");
    send_to_char("You coalesce from the darkness which surrounds you.\n\r",ch);
    WAIT_STATE(ch, 5);
    return;
}    	

void do_koryou( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA  *obj;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_NINJA) || ch->pcdata->powers[NPOWER_SORA]
<2) {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Read the aura on what?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        if ( ( obj = get_obj_carry( ch, arg ) ) == NULL )
	{
	    send_to_char( "Read the aura on what?\n\r", ch );
	    return;
	}
	act("$n examines $p intently.",ch,obj,NULL,TO_ROOM);
	spell_identify( skill_lookup( "identify" ), ch->level, ch, obj );
	return;
    }

    if (!IS_NPC(victim) && (IS_IMMUNE(victim,IMM_SHIELDED) ||
(IS_CLASS(victim, CLASS_DROW) &&
IS_SET(victim->pcdata->powers[1],DPOWER_DROWSHIELD))) && !IS_ITEMAFF(ch,
ITEMA_VISION))
    {
	send_to_char("You are unable to read their aura.\n\r",ch);
	return;
    }

    act("$n examines $N intently.",ch,NULL,victim,TO_NOTVICT);
    act("$n examines you intently.",ch,NULL,victim,TO_VICT);
    if (IS_NPC(victim)) sprintf(buf, "%s is an NPC.\n\r",victim->short_descr);
    else 
    {
	if      (victim->level == 12) sprintf(buf, "%s is an Implementor.\n\r", victim->name);
	else if (victim->level == 11) sprintf(buf, "%s is a High Judge.\n\r", victim->name);
	else if (victim->level == 10) sprintf(buf, "%s is a Judge.\n\r",
victim->name);
	else if (victim->level == 9 ) sprintf(buf, "%s is an Enforcer.\n\r", victim->name);
	else if (victim->level == 8 ) sprintf(buf, "%s is a Quest Maker.\n\r", victim->name);
	else if (victim->level == 7 ) sprintf(buf, "%s is a Builder.\n\r", victim->name);
	else if (victim->level >= 3 ) sprintf(buf, "%s is an Avatar.\n\r", victim->name);
	else sprintf(buf, "%s is a Mortal.\n\r", victim->name);
    }
    send_to_char(buf,ch);
    if (!IS_NPC(victim))
    {
	sprintf(buf,"Str:%d, Int:%d, Wis:%d, Dex:%d, Con:%d.\n\r",get_curr_str(victim),get_curr_int(victim),get_curr_wis(victim),get_curr_dex(victim),get_curr_con(victim));
	send_to_char(buf,ch);
    }
    sprintf(buf,"Hp:%ld/%ld, Mana:%d/%d, Move:%d/%d.\n\r",victim->hit,victim->max_hit,victim->mana,victim->max_mana,victim->move,victim->max_move);
    send_to_char(buf,ch);
    if (!IS_NPC(victim)) sprintf(buf,"Hitroll:%d, Damroll:%d, AC:%d.\n\r",char_hitroll(victim),char_damroll(victim),char_ac(victim));
    else sprintf(buf,"AC:%d.\n\r",char_ac(victim));
    send_to_char(buf,ch);
    if (!IS_NPC(victim))
    {
	sprintf(buf,"Status:%d, ",victim->race);
	send_to_char(buf,ch);
	if (IS_CLASS(victim, CLASS_VAMPIRE))    
	{
	    sprintf(buf,"Blood:%d, ",victim->pcdata->condition[COND_THIRST]);
	    send_to_char(buf,ch);
	}
    }
    sprintf(buf,"Alignment:%d.\n\r",victim->alignment);
    send_to_char(buf,ch);
    if (!IS_NPC(victim) && IS_EXTRA(victim, EXTRA_PREGNANT))
	act("$N is pregnant.",ch,NULL,victim,TO_CHAR);
   return;
   }

