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

#define MONK_AUTODROP ch->pcdata->autostance

/*
 * Local functions.
 */
void	autodrop	args( ( CHAR_DATA *ch) );
bool	check_dodge	args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dt ) );
void	check_killer	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	check_parry	args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dt ) );
void	dam_message	args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dam,
			    int dt ) );
void	death_cry	args( ( CHAR_DATA *ch ) );
void	group_gain	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
int	xp_compute	args( ( CHAR_DATA *gch, CHAR_DATA *victim ) );
void	set_fighting	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
bool	can_counter	args( ( CHAR_DATA *ch) );
bool	can_bypass	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
int	number_attacks	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
int	dambonus	args( ( CHAR_DATA *ch, CHAR_DATA *victim, 
			    int dam, int stance) );
void	update_damcap	args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
int 	add_bonuses	args( ( CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt ) );



/*
 * Control the fights going on.
 * Called periodically by update_handler.
 *
*/
void violence_update( void )
{
    CHAR_DATA *ch;
    CHAR_DATA *ch_next;
    CHAR_DATA *victim;
    CHAR_DATA *rch;
    CHAR_DATA *rch_next;
    CHAR_DATA *mount;
    char buf[MAX_STRING_LENGTH];
        int chance;


      chance = number_percent();

    for ( ch = char_list; ch != NULL; ch = ch->next )
    {
	if ( chance > 60 && ch->position == POS_FIGHTING  && 
IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_SCARED))
{
 do_flee(ch,"");
 stc("You are so scared you flee from combat, COWARD!\n\r", ch );
        return;
        }

  victim = ch->blinkykill;

 	if (ch->blinkykill == NULL) continue;

	if (IS_SET(ch->flag2, AFF2_BLINK_1ST_RD))
	{
	    REMOVE_BIT(ch->flag2, AFF2_BLINK_1ST_RD);
	    SET_BIT(ch->flag2, AFF2_BLINK_2ND_RD);
	}
	else if (IS_SET(ch->flag2, AFF2_BLINK_2ND_RD))
	{

	    REMOVE_BIT(ch->flag2, AFF2_BLINK_2ND_RD);
	    REMOVE_BIT(ch->flag2, AFF2_BLINK_1ST_RD);

	    if (ch->blinkykill->in_room != ch->in_room)
	    {
		ch->blinkykill = NULL;
	 	act("$n pops back into existence.", ch, NULL, NULL,
TO_ROOM);
		stc("You pop back into existence.\n\r", ch);
		stc("Your victim is no longer in the room.\n\r", ch);
		break;
	    }


	    act("$n pops back into existence next to $N.", ch,
NULL,ch->blinkykill, TO_NOTVICT);
	    act("You pop back into existence next to $N.", ch, NULL,
ch->blinkykill, TO_CHAR);
	    act("$n pops back into existence next to you.", ch, NULL,
ch->blinkykill, TO_VICT);
	    set_fighting(ch, ch->blinkykill);
	    do_say(ch, "Muhahahahahaha");
	    ch->blinkykill = NULL;
            multi_hit(ch, victim, gsn_blinky);
	    multi_hit(ch, victim, gsn_blinky);
	    update_pos(victim);
	}
    }



    for ( ch = char_list; ch != NULL; ch = ch->next )
    {
	ch_next	= ch->next;



	if (ch->silence_timer > 0)
		{
		    ch->silence_timer--;
		    if (ch->silence_timer < 1)
		    {
			if (IS_SET(ch->newbits, NEW_SILENCE))
			{
			    act("The room is no longer silent.",ch,NULL,NULL,TO_CHAR);
			    act("The room is no longer silent.",ch,NULL,NULL,TO_ROOM);
			    REMOVE_BIT(ch->in_room->added_flags,ROOM2_SILENCE); 
			    REMOVE_BIT(ch->newbits, NEW_SILENCE);
			    ch->silence_timer = 60;
			}
			else send_to_char("Your ability to call the Silence of Death has returned.\n\r",ch);
		    }
		}
	if (ch->obeah_timer > 0 && !IS_SET(ch->newbits, NEW_NEUTRAL))
		{
		    ch->obeah_timer--;
		    if (ch->obeah_timer < 1)
		    {
			if (IS_WEREWOLF(ch))
			    send_to_char("Your healing powers have returned.\n\r",ch);
			else
			{
			    send_to_char("Your third eye stops glowing.\n\r",ch);
			    act("The eye in $n's forehead stops glowing.",ch,NULL,NULL,TO_ROOM);
			}
		    }
		}
		
		if (ch->reina_timer > 0)
		{
		    ch->reina_timer--;
		    if (ch->reina_timer < 1)
		    {
			if (IS_SET(ch->newbits, NEW_REINA))
			{
			    send_to_char("The peaceful harmony in the air gradually fades away to nothing.\n\r",ch);
			    act("The peaceful harmony in the air gradually fades away to nothing.",ch,NULL,NULL,TO_ROOM);
			    REMOVE_BIT(ch->in_room->room_flags, ROOM_SAFE); 
			    REMOVE_BIT(ch->newbits, NEW_REINA);
			    ch->reina_timer = 60;
			}
	else if (IS_WEREWOLF(ch))
{
	stc("You may once again use madness.\n\r", ch);
REMOVE_BIT(ch->affected_by, AFF_STEELSHIELD);
}
			else send_to_char("You have recovered your voice.\n\r",ch);
		REMOVE_BIT(ch->affected_by, AFF_STEELSHIELD);		   
 }
		}
if (ch->cobra_timer > 0) {
	ch->cobra_timer--;
                        if (ch->cobra_timer < 1) {
if (IS_WEREWOLF(ch))
        {       
 stc("You may once again use eyes of the cobra\n\r",ch);
}
else
stc("EMPTY PLACE FOR A NEW MESSAGE..:)\n\r",ch);
} 
}
    if (ch->majesty_timer > 0) {
			ch->majesty_timer--;
			if (ch->majesty_timer < 1) {
	if (IS_WEREWOLF(ch))
	{
	stc("You may now use your icy chill of despair\n\r",ch);
}
else			
				send_to_char("Your may once again use majesty.\n\r",ch);
			}
		}
 if (ch->darkness_timer > 0)
                ch->darkness_timer--;
 if (ch->arena_timer > 0)
                ch->arena_timer--;
 if (ch->arena_timer < 1)
                    {
 if ( IS_SET(ch->flag2, AFF2_INARENA) || IS_SET(ch->flag2,
AFF2_CHALLENGED) || IS_SET(ch->flag2, AFF2_CHALLENGER))
{
	 REMOVE_BIT(ch->flag2, AFF2_CHALLENGED);
  REMOVE_BIT(ch->flag2, AFF2_CHALLENGER);
  REMOVE_BIT(ch->flag2, AFF2_INARENA   );
  undo_arena(ch); 
 arena = FIGHT_CLEAR;
	sprintf(buf,"The arena is no longer busy!");
	do_info(ch,buf);
	stc("You waited to long, arena status cleared!\n\r", ch);
}
}

if (ch->wyld_timer > 0)
                ch->wyld_timer--;

	if (ch->fight_timer > 0)
		ch->fight_timer--;
if (ch->hit < 1)
update_pos( ch );

		if ( IS_SET(ch->monkstuff, MONK_DEATH) )
        {
	  if ( ch->hit > (ch->max_hit /2 ) )
	  {
	      ch->hit -=  number_range( 50,200 );
	      stc("Your writhe in agony as magical energies tear you asunder.\n\r",ch);
	      act("$n's writhes in agony as magical forces tear apart $s body.",ch,NULL,NULL,TO_ROOM);
	  }               
	  else
	  {
	      if ( number_range( 1,2 ) == 1 )
	      {
	         stc("You feel the magical forces leave your body.\n\r",ch);
	         act("The magical forces leave $n's body.",ch,NULL,NULL,TO_ROOM);
		 REMOVE_BIT(ch->monkstuff, MONK_DEATH);
            }
	      else
	      {
   	          ch->hit -=  number_range( 50,200 );
	          stc("Your writhe in agony as magical energies tear you asunder.\n\r",ch);
	          act("$n's writhes in agony as magical forces tear apart $s body.",ch,NULL,NULL,TO_ROOM); 
	      }
	   }
	}

        if ( IS_SET(ch->monkstuff, MONK_HEAL) )
        {
	  if ( ch->hit < (ch->max_hit /2 ) )
	  {
	    if ( ch->hit < ch->max_hit )
	      ch->hit +=  number_range( 200,400 );
	    if ( ch->move < ch->max_move )
	      ch->move += number_range( 175,400 );
	      stc("Your body emits glowing sparks.\n\r",ch);
	      act("$n's body emits glowing sparks and fizzes.",ch,NULL,NULL,TO_ROOM);
	  }               
	  else
	  {
	      if ( number_range( 1,2 ) == 1 )
	      {
	         stc("The sparks fizzle and die.\n\r",ch);
	         act("The sparks around $n's body fizzle and die.",ch,NULL,NULL,TO_ROOM);
		 REMOVE_BIT(ch->monkstuff, MONK_HEAL);
              }
	      else
	      {
	       if ( ch->hit < ch->max_hit )
		 ch->hit +=  number_range( 200,400 );
               if ( ch->move < ch->max_move )
                 ch->move += number_range( 175,400 );
                 stc("Your body emits glowing sparks.\n\r",ch);
                 act("$n's body emits glowing sparks and fizzes.",ch,NULL,NULL,TO_ROOM);
	      }
	   }
	}


	if (IS_CLASS(ch, CLASS_MONK)
	  && ch->level < 7 && IS_SET(ch->act, PLR_WIZINVIS) )
	REMOVE_BIT(ch->act, PLR_WIZINVIS);

	if ( IS_SET(ch->newbits, NEW_POWER) )
 	{
	   if ( ch->move < 75 )
	     do_spiritpower(ch,"");
	   else
	     ch->move -= 15;
        }


      if ( ch->chi[CURRENT] > 0 )
      {
        if ( IS_CLASS(ch, CLASS_MONK) && ch->move > ( 500 - ch->chi[CURRENT] * 20 ))
            ch->move -= ch->chi[CURRENT] * 20;
        else
	{
	  if ( ch->chi[CURRENT] > 0 )
          {
	    stc("You feel exhausted, and lose control of your ch'i.\n\r",ch);
	    ch->chi[CURRENT] -= 1;
	  }
	}
      }

	if ( ( victim = ch->fighting ) == NULL || ch->in_room == NULL )
	    continue;
	        if (!IS_NPC(ch) && !IS_NPC(victim) && !is_safe(ch, victim)
		  && !is_safe(victim,ch))
                ch->fight_timer = 10;

	if ( IS_AWAKE(ch) && IS_AWAKE(victim) && 
		ch->in_room == victim->in_room )
{
	    multi_hit( ch, victim, TYPE_UNDEFINED );
}
	/*
	if (IS_CLASS(ch, CLASS_DROW) && POLY_SPIDERFORM
	&& IS_SET(ch->pcdata->powers[1], DPOWER_ARMS))
	    multi_hit(ch, victim, gsn_spiderform);
	} 
*/
	else
	    stop_fighting( ch, FALSE );

	if ( ( victim = ch->fighting ) == NULL )
	    continue;

	for ( rch = ch->in_room->people; rch != NULL; rch = rch_next )
	{
	    rch_next = rch->next_in_room;

	    if ( IS_AWAKE(rch) && rch->fighting == NULL )
	    {
		if ( (mount = rch->mount) != NULL )
		{
		    if (mount == ch) multi_hit( rch, victim, TYPE_UNDEFINED );
		    continue;
		}
		if ( !IS_NPC(ch) || IS_AFFECTED(ch, AFF_CHARM) )
		{
		    if ( ( !IS_NPC(rch) || IS_AFFECTED(rch, AFF_CHARM) )
		    &&   is_same_group(ch, rch) )
			multi_hit( rch, victim, TYPE_UNDEFINED );
		    continue;
		}

		if ( IS_NPC(rch) && !IS_AFFECTED(rch, AFF_CHARM) )
		{
		    if ( rch->pIndexData == ch->pIndexData
		    ||   number_bits( 3 ) == 0 )
		    {
			CHAR_DATA *vch;
			CHAR_DATA *target;
			int number;

			target = NULL;
			number = 0;
			for ( vch = ch->in_room->people; vch; vch = vch->next )
			{
			    if ( can_see( rch, vch )
			    &&   is_same_group( vch, victim )
			    &&   number_range( 0, number ) == 0 )
			    {
				target = vch;
				number++;
			    }
			}

			if ( target != NULL )
			    multi_hit( rch, target, TYPE_UNDEFINED );
		    }
		}
	    }
	}
    }

    return;
}

/*
 * Do one group of attacks.
 */
void multi_hit( CHAR_DATA *ch, CHAR_DATA *victim, int dt )
{
    OBJ_DATA *wield;
    OBJ_DATA *wield1;
    OBJ_DATA *wield2;
    OBJ_DATA *wield3;
    OBJ_DATA *wield4;
    int	      sn;
    int	      level;
    int       chance;
    int       unarmed;
    int       wieldorig = 0;
    int       wieldtype = 0;
    int       maxcount;
    int       countup;
    int       wieldie;

    if ( ch->position < POS_SLEEPING ) return;


    if ( dt == gsn_spiket )
        {
        one_hit( ch, victim, dt, 1 );
        return;
        }

   if ( dt == gsn_magma )
        {
        one_hit( ch, victim, dt, 1 );
        return;
        }

  if ( dt == gsn_shards )
        {
        one_hit( ch, victim, dt, 1 );
        return;
        }

    if ( dt == gsn_venomt )
	{
	one_hit( ch, victim, dt, 1 );
	return;
	}

    if ( dt == gsn_headbutt )
    {
	one_hit( ch, victim, dt, 1 );
	return;
    }

    if ( dt == gsn_quills)
    {
         one_hit(ch,victim,dt,1);
         return;
    }

    if ( dt == gsn_spiderform )
    {
	one_hit( ch, victim, dt, 6 );
	return;
    }

    if ( dt == gsn_tail )
    {
	one_hit( ch, victim, dt, 1 );
	return;
    }

    if (!IS_NPC(ch) && IS_ITEMAFF(ch, ITEMA_PEACE))
    {
	send_to_char( "You are unable to attack them.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_ITEMAFF(victim, ITEMA_PEACE))
    {
	send_to_char( "You can't seem to attack them.\n\r", ch );
	return;
    }
    
    if (!IS_NPC(ch) && IS_AFFECTED(ch, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_STEELSHIELD) )
    {
	send_to_char( "You cannot attack them while they are  in majesty.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_STEELSHIELD) )
    {
	send_to_char( "They are protected by a powerful being.\n\r", ch );
	return;
    }

    wield1 = get_eq_char( ch, WEAR_WIELD );
    wield2 = get_eq_char( ch, WEAR_HOLD );
    if ( wield1 != NULL && wield1->item_type == ITEM_WEAPON ) wieldorig  = 1;
    if ( wield2 != NULL && wield2->item_type == ITEM_WEAPON ) wieldorig += 2;
    wieldtype = wieldorig;

    wield1 = get_eq_char( ch, WEAR_WIELD );
    wield2 = get_eq_char( ch, WEAR_HOLD );
    wield3 = get_eq_char( ch, WEAR_THIRD );
    wield4 = get_eq_char( ch, WEAR_FOURTH);
    if ( wield1 != NULL && wield1->item_type == ITEM_WEAPON ) wieldorig  = 1;
    if ( wield2 != NULL && wield2->item_type == ITEM_WEAPON ) wieldorig += 2;
    if ( wield3 != NULL && wield3->item_type == ITEM_WEAPON ) wieldorig += 4;
    if ( wield4 != NULL && wield4->item_type == ITEM_WEAPON ) wieldorig += 8;
    wieldtype = wieldorig;
    wieldie = number_range(1,4);

    if ( wieldorig == 15 ) 
    { 
        if (wieldie == 2) 
	  wieldtype = 8; 
	else
	  wieldtype = 4;
    }
    if ( wieldorig == 14 )
    {
	if (wieldie == 2)
	  wieldtype = 8;
        else if (wieldie == 1)
	  wieldtype = 4;
	else if (wieldie == 3)
          wieldtype = 2;
	else
	  wieldtype = 1;
    }
    if ( wieldorig == 13 )
    {
	if ( wieldie == 1)
	 wieldtype = 8;
	else if (wieldie == 2)
	 wieldtype = 4;
	else wieldtype = 1;
    }
    if ( wieldorig == 12 )
    {
	if ( wieldie == 1 )
	  wieldtype = 8;
	else
	  wieldtype = 4;
    }
    if ( wieldorig == 11 )
    {
	if ( wieldie == 1 )
	 wieldtype = 8;
	if ( wieldie == 2 )
	 wieldtype = 2;
	else wieldtype = 1;
    }
    if ( wieldorig == 10 )
    {
	if ( wieldie == 1 )
	 wieldtype = 8;
	else wieldtype = 2;
    }
    if ( wieldorig == 9 )
    {
	if ( wieldie == 1 )
	  wieldtype = 8;
	else wieldtype = 1;
    }
    if ( wieldorig == 8 )
	wieldtype = 8;
    if ( wieldorig == 7 )
    {
	if ( wieldie == 1 )
          wieldtype = 4;
	else if ( wieldie == 2 )
	  wieldtype = 2;
	else wieldtype = 1;
    }
    if ( wieldorig == 6 )
    {
       if ( wieldie == 1 || wieldie == 2)
         wieldtype = 2;
       else wieldtype = 4;
    } 
    if ( wieldorig == 5 )
    {
        if ( wieldie == 1)
          wieldtype = 4;
        else wieldtype = 1;
    }
    if ( wieldorig == 4 )
        wieldtype = 4;
    if ( wieldorig == 3 )
    {
        if ( wieldie == 2 || wieldie == 4)
          wieldtype = 2;
        else wieldtype = 1;
    }
    if ( wieldorig == 2 )
        wieldtype = 2;
    if ( wieldorig == 1 )
	wieldtype = 1;
	

         if ( wieldtype == 8 ) wield = wield4;
    else if ( wieldtype == 4 ) wield = wield3;
    else if ( wieldtype == 2 ) wield = wield2;
    else                       wield = wield1;

    if (!IS_NPC(ch) && ch->stance[0] > 0 && number_percent() == 1)
    {
	int stance = ch->stance[0];
	if (ch->stance[stance] >= 200)
	{
	    special_move(ch,victim);
	    return;
	}
    }

    
    if ( IS_CREATOR(ch) || IS_CLASS(ch, CLASS_MONK) )
    {
	if (!IS_NPC(ch))
        {
            unarmed = number_range(1,7);
            if ( !IS_NPC(ch) && ch->cmbt[unarmed] != 0 )
            {
                fightaction(ch,victim,ch->cmbt[unarmed], dt, wieldtype);
            }
        } 
    }

    unarmed = 0;
    one_hit( ch, victim, dt, wieldtype );

    if ( victim == NULL || victim->position != POS_FIGHTING ) return;


    if ( dt == TYPE_UNDEFINED )
    {
	dt = TYPE_HIT;
	if ( wield != NULL && wield->item_type == ITEM_WEAPON )
	{
	    dt += wield->value[3];
	    if (wield->value[0] >= 1)
	    {
		if (wield->value[0] >= 1000)
		    sn = wield->value[0] - ((wield->value[0] / 1000) * 1000);
		else
		    sn = wield->value[0];
		if (sn != 0 && victim->position == POS_FIGHTING)
		    (*skill_table[sn].spell_fun) (sn,wield->level,ch,victim);
	    }
	}
    }

    if ( victim == NULL || victim->position != POS_FIGHTING ) return;

    if ( ch->fighting != victim || dt == gsn_backstab || dt == gsn_headbutt )
	return;

    if ( !IS_NPC(victim) && !IS_SET(victim->special, SPC_WOLFMAN) &&
	number_percent( ) <= victim->pcdata->learned[gsn_fastdraw] )
    {
    	OBJ_DATA *obj;
    	int wpntype  = 0;
    	int wpntype2 = 0;

	if ((obj = get_eq_char(victim,WEAR_SCABBARD_R)) != NULL)
	{
	    wpntype = obj->value[3];
	    if (wpntype < 0 || wpntype > 12) wpntype = 0;
	    if ((obj = get_eq_char(victim,WEAR_WIELD)) != NULL)
	    {
		obj_from_char(obj);
		obj_to_room(obj,victim->in_room);
		act("You hurl $p aside.",victim,obj,NULL,TO_CHAR);
		act("$n hurls $p aside.",victim,obj,NULL,TO_ROOM);
	    }
	    do_draw(victim,"right");
	}
	if ((obj = get_eq_char(victim,WEAR_SCABBARD_L)) != NULL)
	{
	    wpntype2 = obj->value[3];
	    if (wpntype2 < 0 || wpntype2 > 12) wpntype2 = 0;
	    if ((obj = get_eq_char(victim,WEAR_HOLD)) != NULL)
	    {
		obj_from_char(obj);
		obj_to_room(obj,victim->in_room);
		act("You hurl $p aside.",victim,obj,NULL,TO_CHAR);
		act("$n hurls $p aside.",victim,obj,NULL,TO_ROOM);
	    }
	    do_draw(victim,"left");
	}
	if (wpntype  > 0) one_hit( victim, ch, TYPE_UNDEFINED, 1 );
	if ( victim == NULL || victim->position != POS_FIGHTING ) return;
	if (wpntype2 > 0) one_hit( victim, ch, TYPE_UNDEFINED, 2 );
	if ( victim == NULL || victim->position != POS_FIGHTING ) return;
    }

    maxcount = number_attacks(ch,victim);
    if (!IS_NPC(ch))
    {
	chance = 0;
	if (wield != NULL && wield->item_type == ITEM_WEAPON)
	{
	    int tempnum = wield->value[3];
	    chance = (ch->wpn[tempnum]) * 0.5;
	}
	else chance = (ch->wpn[0]) * 0.5;
	if (number_percent() <= chance) maxcount += 1;
    }
    if (wieldorig == 3) maxcount += 1;
    for (countup = 0; countup <= maxcount; countup++)
    {
	wieldtype = wieldorig;
	if ( wieldorig == 3 )
	{
	    if (number_range(1,2) == 2) wieldtype = 2;
	    else wieldtype = 1;
	}
	one_hit( ch, victim, -1, wieldtype );
	if ( victim == NULL || victim->position != POS_FIGHTING ) return;
	if ( ch->fighting != victim ) return;
    }

    if (!IS_NPC(ch) && IS_VAMPAFF(ch,VAM_FANGS))
	one_hit( ch, victim, ( TYPE_HIT + 10 + TYPE_ADD_AGG), 0 );
    if ( victim == NULL || victim->position != POS_FIGHTING ) return;
    if (!IS_NPC(ch))
    {

if ( IS_CLASS(ch, CLASS_WEREWOLF) && IS_GAR1(ch, WOLF_VISCERAL ) ) 
{
if ( !IS_SET(victim->newbits, NEW_VISCERAL) )
    {
SET_BIT(victim->newbits, NEW_VISCERAL);
  act("The venom on your claws mingles with $N's blood",ch, NULL, victim, TO_CHAR);
  act("Something black on $n's claws mingles with your blood.",ch,NULL,victim,TO_VICT);
  act("Something black on $n's mingles with $N's blood.",ch,NULL,victim,TO_NOTVICT);
}

}
if ((IS_CLASS(ch, CLASS_WEREWOLF) && ch->gifts[BLACKFURIES] > 2)
 && number_range(1,3) == 1)
        one_hit( ch, victim, gsn_waspt, 0);
if ( IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_SPIKETAIL)
        && number_range(1,3) == 1)
        one_hit( ch, victim, gsn_spiket, 0);
  if ( IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_SHARDS)
        && number_range(1,3) == 1)
        one_hit( ch, victim, gsn_shards, 0);
  if ( IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_MAGMA)
        && number_range(1,3) == 1)
        one_hit( ch, victim, gsn_magma, 0);
  if ( IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_VENOMTONG)
	&& number_range(1,3) == 1)
	one_hit( ch, victim, gsn_venomt, 0);
	if (IS_CLASS(ch, CLASS_DEMON)  && IS_DEMAFF(ch,DEM_HORNS) 
		&& number_range(1,3) == 1)
	   {one_hit( ch, victim, gsn_headbutt, 0 );dt += TYPE_ADD_AGG;}

if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_NINGENNO] > 0
&& number_range(1,2 ) == 1) one_hit(ch, victim, gsn_claws, 0);
	if ( IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_NINGENNO] > 3
        && number_range(1,3) == 1) one_hit( ch, victim, gsn_shiroken +TYPE_ADD_AGG,0 );
	if (IS_CLASS(ch, CLASS_DEMON)  && IS_DEMAFF(ch,DEM_TAIL)
                && number_range(1,3) == 1)   one_hit( ch, victim, gsn_tail , 0);
	if (IS_SET(ch->newbits, NEW_QUILLS) )
	  one_hit( ch, victim, gsn_quills, 0 );

 if ( IS_DROW(ch) && IS_SET(ch->pcdata->powers[1], DPOWER_ARMS) )
  {
     int ii;
     if( IS_POLYAFF(ch, POLY_SPIDERFORM) )
     {
     for( ii = 0; ii < 8; ii++ )
     {
          if( number_range(1,4) == 1 )
        {
           if( number_range(1,3) == 1 )
            one_hit( ch, victim, gsn_spiderform + TYPE_ADD_AGG, 0 );
        else one_hit(ch, victim, gsn_spiderform, 0);

        }
         }
     }
     else
     {
     for( ii = 0; ii < 4; ii++ )
 {
        if( number_range(1,3) == 1 )
        {
           if( number_range(1,2) == 1 )
            one_hit( ch, victim, gsn_spiderform + TYPE_ADD_AGG, 0 );
           else
            one_hit( ch, victim, gsn_spiderform, 0 );
        }
     }
}
}
  if ( IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_WINGS)
	 && number_range(1,3) == 1)      one_hit( ch, victim, gsn_buffet, 0 );  
        if (IS_CLASS(ch, CLASS_VAMPIRE) && IS_VAMPAFF(ch, VAM_WINGS)
	&& number_range(1,3) == 1)	one_hit( ch, victim, gsn_buffet, 0 );
	if (IS_CLASS(ch, CLASS_VAMPIRE) && IS_VAMPAFF(ch, VAM_HORNS)
	&& number_range(1,3) == 1)	one_hit( ch, victim, gsn_headbutt, 0 );
	if (IS_CLASS(ch, CLASS_VAMPIRE)  && IS_VAMPAFF(ch, VAM_TAIL)
                && number_range(1,3) == 1)   one_hit( ch, victim, gsn_tail, 0 );
    }
    if ( victim == NULL || victim->position != POS_FIGHTING ) return;

    if (!IS_NPC(ch) && IS_CLASS(ch, CLASS_VAMPIRE) && IS_VAMPAFF(ch, VAM_SERPENTIS))
	spell_poison( gsn_poison, (ch->level*number_range(5,10)),ch,victim );
    else if (!IS_NPC(ch) && IS_CLASS(ch, CLASS_WEREWOLF) && ch->pcdata->powers[WPOWER_SPIDER] > 0)
	spell_poison( gsn_poison, (ch->level*number_range(5,10)),ch,victim );
    else if (!IS_NPC(ch) && IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_NINGENNO] > 4)
	spell_poison( gsn_poison, (ch->level*number_range(5,10)),ch,victim );

    if (victim->itemaffect < 1) return;
    if (IS_NPC(victim) || victim->spl[1] < 4) level = victim->level;
    else level = (victim->spl[1] * 0.25);
	    if (IS_SET(victim->newbits, NEW_MONKFLAME) && !IS_AFFECTED(ch, AFF_FLAMING))
    {
	if (number_percent() > 65)
	{
        SET_BIT(ch->affected_by, AFF_FLAMING);
    if (!IS_CLASS(ch, CLASS_WEREWOLF))
    {
    act("Your flaming hands catch $n on fire!", ch, NULL, victim, TO_VICT);
    act("$N's flaming hands catch $n on fire!", ch, NULL, victim, TO_NOTVICT);
    act("$N's flaming hands catch you on fire!.", ch, NULL, victim, TO_CHAR);
    }
    else
    {
    act("Your flaming claws catch $n on fire!", ch, NULL, victim, TO_VICT);
    act("$N's flaming claws catch $n on fire!", ch, NULL, victim, TO_NOTVICT);
    act("$N's flaming claws catch you on fire!.", ch, NULL, victim, TO_CHAR);
    }
   }
    else
	{
	 return;
	}
    }
    if (IS_ITEMAFF(victim, ITEMA_SHOCKSHIELD) && ch->position == POS_FIGHTING)
	if ( (sn = skill_lookup( "lightning bolt" ) ) > 0)
	    (*skill_table[sn].spell_fun) (sn,level,victim,ch);
    if (IS_ITEMAFF(victim, ITEMA_FIRESHIELD) && ch->position == POS_FIGHTING)
	if ( (sn = skill_lookup( "fireball" ) ) > 0)
	    (*skill_table[sn].spell_fun) (sn,level,victim,ch);
    if (IS_ITEMAFF(victim, ITEMA_ICESHIELD) && ch->position == POS_FIGHTING)
	if ( (sn = skill_lookup( "chill touch" ) ) > 0)
	    (*skill_table[sn].spell_fun) (sn,level,victim,ch);
    if (IS_ITEMAFF(victim, ITEMA_ACIDSHIELD) && ch->position == POS_FIGHTING)
	if ( (sn = skill_lookup( "acid blast" ) ) > 0)
	    (*skill_table[sn].spell_fun) (sn,level,victim,ch);
    if (IS_ITEMAFF(victim, ITEMA_CHAOSSHIELD) && ch->position == POS_FIGHTING)
	if ( (sn = skill_lookup( "chaos blast" ) ) > 0)
	    (*skill_table[sn].spell_fun) (sn,level,victim,ch);
    return;
}

int number_attacks( CHAR_DATA *ch, CHAR_DATA *victim )
{
    int count = 1;

/*
 * TIJMOD: 29/12/99
 * Legend status now gives extra attacks per level 
 */

        if (!IS_NPC(ch) && !IS_NPC(victim) && (ch->lstatus > victim->lstatus))
        {
        count += (ch->lstatus - victim->lstatus);
        }
        if (IS_NPC(victim)) count += ch->lstatus;

    if ( IS_NPC(ch) )
    {
	if (ch->level >= 50)  count++;
	if (ch->level >= 100) count += ( ch->level / 50 );
	return count;
    }

    if ( IS_STANCE(ch, STANCE_VIPER) && number_percent() > 
	ch->stance[STANCE_VIPER] * 0.5) count += 1;
    else if ( IS_STANCE(ch, STANCE_MANTIS) && number_percent() > 
	ch->stance[STANCE_MANTIS] * 0.5) count += 1;
	else if ( IS_STANCE(ch, STANCE_RABBIT) && number_percent() > 
	ch->stance[STANCE_RABBIT] * 0.5) count += 2;
    else if ( IS_STANCE(ch, STANCE_TIGER) && number_percent() > 
	ch->stance[STANCE_TIGER] * 0.5) count += 2;
	  else if ( IS_STANCE(ch, STANCE_BEAR) && number_percent() > 
	ch->stance[STANCE_BEAR] * 0.7) count += 3;

    if (!IS_NPC(ch))
    {
    	if ( IS_CLASS(ch, CLASS_VAMPIRE) && IS_VAMPAFF(ch, VAM_CELERITY) )
		count += 1;
	else if ( IS_CLASS(ch, CLASS_MONK) && ch->monkab[COMBAT] > 0 )
		count += ch->monkab[COMBAT];
   	else if ( !IS_NPC(ch) && IS_CLASS(ch, CLASS_DEMON) && IS_DEMPOWER(ch, DEM_SPEED) )
		count += 1;
else if ( IS_CLASS(ch, CLASS_DEMON) && !IS_SET(ch->warp, WARP_QUICKNESS) ) 
	count += 1;
	else if (IS_CLASS(ch, CLASS_DROW) && (IS_SET(ch->special, SPC_DROW_WAR)
	         || ch->pcdata->stats[UNI_GEN] < 3))
		count += 3;
	else if (IS_CLASS(ch, CLASS_DROW) && !IS_SET(ch->special, SPC_DROW_WAR) )
     		count += 2;
	else if (is_garou(ch) && ch->gifts[SILENTSTRIDERS] > 0 )
        {
          count++;
	  if ( ch->gifts[SILENTSTRIDERS] > 1 )
	  count++;
	  if ( ch->gifts[SILENTSTRIDERS] > 1 )
	  count++;
	}
    }
	if (!IS_NPC(ch) && IS_CLASS(ch, CLASS_DROW) && 
	IS_SET(ch->pcdata->powers[1],DPOWER_SPEED))
	count += 1;


    if ( IS_ITEMAFF(ch, ITEMA_SPEED) ) count += 1;


    if ( !IS_NPC(ch) && !IS_NPC(victim) && ch->lstatus > victim->lstatus )
      count += ( ch->lstatus - victim->lstatus );
	if(IS_CLASS(ch,CLASS_DROW))count /= 4;
    return count;
}


/*
 * Hit one guy once.
 */
void one_hit( CHAR_DATA *ch, CHAR_DATA *victim, int dt, int handtype)
{
    OBJ_DATA *wield;
    OBJ_DATA *gloves;
    int victim_ac;
    int thac0;
    int thac0_00;
    int thac0_32;
    int dam;
    int diceroll;
    int wdam;
    int level;
    bool right_hand;

    /*
     * Can't beat a dead char!
     * Guard against weird room-leavings.
     */
    if ( victim->position == POS_DEAD || ch->in_room != victim->in_room )
	return;

    if (!IS_NPC(ch) && IS_ITEMAFF(ch, ITEMA_PEACE))
    {
	send_to_char( "You are unable to attack them.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_ITEMAFF(victim, ITEMA_PEACE))
    {
	send_to_char( "You can't seem to attack them.\n\r", ch );
	return;
    }
    
    if (!IS_NPC(ch) && IS_AFFECTED(ch, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return;
    }


    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_STEELSHIELD) )
    {
	send_to_char( "There are far to imposing.\n\r", ch );
	return;
    }

    /*
     * Figure out the type of damage message.
     */
    if (handtype == 2)
    {
    	wield = get_eq_char( ch, WEAR_HOLD );
	right_hand = FALSE;
    }
    else if (handtype == 4 )
    {
        wield = get_eq_char( ch, WEAR_THIRD );
	right_hand = FALSE;
    }
    else if ( handtype == 8 )
    {
        wield = get_eq_char( ch, WEAR_FOURTH );
        right_hand = FALSE;
    }
    else
    {
    	wield = get_eq_char( ch, WEAR_WIELD );
	right_hand = TRUE;
    }

    if ( dt == TYPE_UNDEFINED )
    {
	dt = TYPE_HIT;
	if ( wield != NULL && wield->item_type == ITEM_WEAPON )
	    dt += wield->value[3];
	    if (IS_CLASS(victim, CLASS_WEREWOLF))
            {
                if ((right_hand && IS_ITEMAFF(ch, ITEMA_RIGHT_SILVER)) ||   
                    (!right_hand && IS_ITEMAFF(ch, ITEMA_LEFT_SILVER)) )
                    dt += TYPE_ADD_AGG;
            }
    }

    if (ch->wpn[dt-1000] > 5) level = (ch->wpn[dt-1000] / 5);
    else level = 1;
    if (level > 40) level = 40;

    /*
     * Calculate to-hit-armor-class-0 versus armor.
     */
    if ( IS_NPC(ch) )
    {
	thac0_00 = 20;
	thac0_32 =  0;
    }
    else
    {
	thac0_00 = SKILL_THAC0_00;
	thac0_32 = SKILL_THAC0_32;
    }
    thac0     = interpolate( level, thac0_00, thac0_32 ) - char_hitroll(ch);
    victim_ac = UMAX( -100, char_ac(victim) / 10 );
    if ( !can_see( ch, victim ) )
	victim_ac -= 100;

    /*
     * The moment of excitement!
     */
    while ( ( diceroll = number_bits( 5 ) ) >= 20 )
	;

    if ( diceroll == 0
    || ( diceroll != 19 && diceroll < thac0 - victim_ac ) )
    {
	/* Miss. */
	damage( ch, victim, 0, dt );
	tail_chain( );
	if (!is_safe(ch,victim))
	{
	    improve_wpn(ch,dt,right_hand);
    	    improve_stance(ch);
	}
	return;
    }

    /*
     * Hit.
     * Calc damage.
     */

    if ( IS_NPC(ch) )
    {
	dam = number_range( ch->level, ch->level * 3 / 2 );
	if ( wield != NULL )
	    dam += dam * 0.5;
    }
    else
    {
	if ( IS_VAMPAFF(ch,VAM_CLAWS) && wield == NULL)
	    {dam = number_range( 10, 20 );dt += TYPE_ADD_AGG;}

        else if ( IS_SET(ch->newbits, NEW_MONKADAM))
           {dam = dice( 10, 25 );dt += TYPE_ADD_AGG;}
	else if ( wield != NULL && wield->item_type == ITEM_WEAPON )
	    dam = number_range( wield->value[1], wield->value[2] );
	else
	    dam = number_range( 1, 4 );
    }

    if ( number_range(1,5) == 2 )
    {
        if ( ch->fighting == victim && IS_CLASS(ch, CLASS_MONK)
          && !IS_NPC(ch) && ch->monkab[BODY] > 3 )
        {
            wdam = number_range( (ch->chi[CURRENT]*6),(ch->chi[CURRENT]*10) );
            if ( victim->alignment < 0 )
             wdam *= 1.5;
            act("$n's hands glow with a heavenly aura.",ch,NULL,victim,TO_VICT);
            act("$n's aura sears your flesh!",ch,NULL,victim,TO_VICT);
            act("Your heavenly aura sears $N's flesh.",ch,NULL,victim,TO_CHAR);
            act("$n's hands' heavenly aura sears $N's flesh.",ch,NULL,victim,TO_ROOM);
            victim->hit -= wdam;
            update_pos( victim );
        }
    }

    /* Fun with weapons */
        if ( !IS_NPC(ch) && wield != NULL )
        {
          if ( number_range( 1,5 ) == 2 )
          {
            if ( ch->fighting == victim )
            {
              if ( IS_WEAP(wield, WEAPON_FLAMING) )
              {
                wdam = number_range( 1,wield->level / 4 + 1);
                act("$n is burned by $p.",victim,wield,NULL,TO_ROOM);
                act("$p sears your flesh.",victim,wield,NULL,TO_CHAR);
                victim->hit -= wdam;
                update_pos( victim );
              }

              if ( IS_WEAP(wield, WEAPON_FROST) )
              {
                wdam = number_range( 1, wield->level / 6 + 2);
                act("$p freezes $n.",victim,wield,NULL,TO_ROOM);
                act("The cold touch of $p surrounds you with ice.",victim,wield,NULL,TO_CHAR);
                victim->hit -= wdam;
                update_pos(victim);
              }

              if ( IS_WEAP(wield, WEAPON_POISON) )
              {
                wdam = number_range( 1, wield->level / 6 + 2);
                act("$n turns green as $p poisons $m.",victim,wield,NULL,TO_ROOM);
                act("You feel sick as $p's poisoned edge pierces you.",victim,wield,NULL,TO_CHAR);
                victim->hit -= wdam;
                update_pos(victim);
              }
            }
          }
        }

    dam += char_damroll(ch);
    dam = add_bonuses( ch, victim, dam, dt );
    
    /* Werewolf Silver Stuff.. */
    if ( !IS_NPC(victim) && IS_CLASS(victim, CLASS_WEREWOLF) )
    {
      if ( number_percent() > victim->pcdata->powers[WPOWER_SILVER] )
      {
        if ( is_garou(ch) )
        {
	    if ( IS_GAR1(ch, GAROU_AVENGER) )
	        dam *= 3;
            else if ( ch->gifts[AHROUN] >= 4 || ch->gifts[SILVERFANGS] >= 2 )
	        dam *= 2.2;
            else if ( wield != NULL && IS_SET(wield->spectype, SITEM_SILVER) )
	        dam *= 2;
            else if ( ( gloves = get_eq_char( ch, WEAR_HANDS ) ) != NULL && IS_SET(gloves->spectype, SITEM_SILVER) )
	        dam *= 2;
	}
        else if ( !is_garou(ch) )
        {  
          if ( wield != NULL && IS_SET(wield->spectype, SITEM_SILVER) )
	    dam *= 2;
          else if ( ( gloves = get_eq_char( ch, WEAR_HANDS ) ) != NULL && IS_SET(gloves->spectype, SITEM_SILVER) )
	    dam *= 2;
	 }
      }
    }


    if ( dt == gsn_backstab )
    {
      if ( IS_CLASS(ch, CLASS_DROW) )
        dam *= number_range( 3, 4 );
      else
        dam *= number_range( 2, 3 );
    }

        if(dt == gsn_spiderform)dam /= 2.25;
        if(dt == gsn_blinky)dam /= 2.25;
    damage( ch, victim, dam, dt );
    tail_chain( );
    if (!is_safe(ch,victim))
    {
	improve_wpn(ch,dt,right_hand);
	improve_stance(ch);
    }
    return;
}

int add_bonuses( CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt )
{
    float mult = 1;
    float reduct = 1;
    int stance;
    int wpn;

    if ( !IS_AWAKE(victim) )
	dam *= 2;

    if ( !IS_NPC(ch) )
    {
      /* Stance Bonuses.. */
        stance = ch->stance[0];
	if ( IS_STANCE(ch, STANCE_NORMAL) ) mult += .25;
	else dam = dambonus(ch,victim,dam,stance);
      /* ----------------- */

        if ( IS_CLASS(ch, CLASS_VAMPIRE) )
	{
	    if ( ch->pcdata->powers[VAM_POTE] > 0 )
                mult += ( ch->pcdata->powers[VAM_POTE] / 3 );

	    /* Vampire Day\Night Bonus Shit */
	    if ( weather_info.sunlight == SUN_LIGHT && dam > 1 )
                mult -= .5;
            else
	        mult += .5;
        }
 	if ( IS_CLASS(ch, CLASS_WEREWOLF) )
	{
	    if ( ch->gifts[PHILODOX] >= 4 )
              mult += .7;
            if ( ch->gifts[SHADOWLORDS] >= 1 )
 	      mult += .9;
	    if ( ch->gifts[GETOFFENRIS] >= 3 )
	      mult += 3;
	    if ( ch->gifts[STARGAZERS] >= 1 )
              mult += .4;
            if ( ch->gifts[AHROUN] >= 1 )
	      mult += .5;
	    if ( ch->gifts[AHROUN] >= 2 )
	      mult += .3;
	    if ( ch->gifts[BLACKFURIES] >= 3 )
	      mult += .3;
	}
	if ( IS_CLASS(ch, CLASS_MAGE) )
	{
	    if ( IS_SET(ch->mflags, MAGE_TELEKINETICS) )
	      mult += .4;
	    if ( IS_SET(ch->mflags, MFLAGS_DIMMAK) )
	      mult += .3;
	    if ( ch->spheres[MENT] >= 1 )
	      mult += ( ch->spheres[MENT] *.2 );
	}
	if ( IS_CLASS(ch, CLASS_MONK) )
	{
	    if ( ch->chi[CURRENT] > 0 )
	      mult += ( ch->chi[CURRENT] / 2 );
	}
	if ( IS_CLASS(ch, CLASS_DROW) )
        {
	    mult += .7;
	}


    if ( !IS_NPC(ch) && IS_CLASS(ch, CLASS_VAMPIRE))
{ 
      mult  += (ch->pcdata->powers[VAM_POTE] / 5);  
}
	if ( IS_CLASS(ch, CLASS_DEMON) )
	{
	    if ( IS_DEMPOWER(ch, DEM_MIGHT) )
	        mult += 1.9;
        }
if ( IS_CLASS(ch, CLASS_MONK))
{
mult += .1;
}
if (IS_CLASS(ch, CLASS_WEREWOLF) &&  IS_GAR1(ch, WOLF_RAZORCLAWS ) )
{
mult += 1; 
}
       if (IS_CLASS(ch, CLASS_WEREWOLF))
	{
	if (ch->gifts[FIANNA] > 2)
	mult += 2;
}
      
        if ( IS_CLASS(ch, CLASS_DEMON) &&  IS_SET(ch->warp, WARP_WEAK))
        {
          mult   -= .5;
        }

if ( IS_CLASS(ch, CLASS_DEMON) &&  IS_SET(ch->warp, WARP_GBODY))
        {
          mult   -= .5;
        }

	if ( IS_CLASS(ch, CLASS_DEMON) &&  IS_SET(ch->warp, WARP_STRONGARMS))
	{
          mult   += 1;
	} 
	 
	if ( IS_CLASS(ch, CLASS_NINJA) )
	{
	    if ( ch->pcdata->powers[NPOWER_CHIKYU] > 1 )
	        mult += 3;
	}
    }

   if ( !IS_NPC( victim ) )
    {
	if ( IS_ITEMAFF(victim, ITEMA_RESISTANCE) )
	    reduct += 1;

	if ( IS_CLASS(victim, CLASS_HIGHLANDER) )
	{
	    reduct += 2;
	}
if (IS_CLASS(victim, CLASS_MONK))
{
reduct += .2;
}

if (IS_CLASS(victim, CLASS_MAGE))
{
reduct += 2;
}
	if ( IS_CLASS(victim, CLASS_VAMPIRE) )
	{
	    if ( victim->pcdata->powers[VAM_FORT] > 0 )
	        reduct += ( victim->pcdata->powers[VAM_FORT] - 1.5 );
	}
	if ( IS_CLASS(victim, CLASS_WEREWOLF) )
	{
	    if ( IS_GAR1(victim, WOLF_COCOON) )
	      reduct += .5;
	    if ( victim->gifts[PHILODOX] >= 1 )
	      reduct += .2;
	    if ( victim->gifts[PHILODOX] >= 3 )
	      reduct += .3;
	    if ( victim->gifts[SHADOWLORDS] >= 2 )
	      reduct += .3;
	    if ( victim->gifts[SHADOWLORDS] >= 4 )
	      reduct += .4;
	}
	if ( IS_CLASS(victim, CLASS_MAGE) )
	{
	    if ( victim->spheres[MENT] >= 1 )
	      reduct += 1.5;
        }
	if ( IS_CLASS(victim, CLASS_DEMON) )
	{
	    if ( IS_DEMPOWER(victim, DEM_TOUGH) )
	      reduct += 1.4;
	}

if ( IS_CLASS(ch, CLASS_DEMON) &&  IS_SET(ch->warp, WARP_STAMINA))
{
        reduct +=  1;
        }

    if ( IS_CLASS(ch, CLASS_DEMON) &&  IS_SET(ch->warp, WARP_WEAK))
{
        reduct -=  .5;
        }

      if ( IS_CLASS(victim, CLASS_DEMON) && IS_SET(victim->warp, WARP_SBODY))
{
        reduct +=  1;
        }

       if ( IS_CLASS(victim, CLASS_DEMON) && IS_SET(victim->warp, WARP_CBODY))  
{
	reduct +=  1.5;
	}

        if ( IS_CLASS(victim, CLASS_MONK) )
        {
	   if ( victim->chi[CURRENT] > 0 )
	       reduct += victim->chi[CURRENT];
	   if ( victim->monkab[BODY] >= 2 )
	       reduct += .5;
        }
	if ( IS_CLASS(victim, CLASS_DROW) )
	{
	    reduct += 1.3;
	}
	if ( IS_CLASS(victim, CLASS_NINJA) )
	{
	    reduct += 1.4;
	}
    }

    if ( !IS_NPC(ch) && dt >= TYPE_HIT )
    {
        wpn = ( dt - 1000 );
        dam = dam + ( dam * ((ch->wpn[wpn]+1) / 100 ) );
    }

    if ( !IS_NPC(victim) )
    {
        if ( dt >= TYPE_HIT )
        {
            wpn = ( dt - 1000 );
	    if ( (wpn == 1 || wpn == 3) && IS_IMMUNE(victim, IMM_SLASH) )
	      dam /= ( number_range( 1, 4 ) );
            if ( (wpn == 2 || wpn == 11) && IS_IMMUNE(victim, IMM_STAB) )
              dam /= ( number_range( 1, 4 ) );
	    if ( (wpn == 6 || wpn == 7 || wpn == 8) && IS_IMMUNE(victim, IMM_SMASH) )
	      dam /= ( number_range( 1, 4 ) );
	    if ( (wpn == 5 || wpn == 10) && IS_IMMUNE(victim, IMM_ANIMAL) )
	      dam /= ( number_range( 1, 4 ) );
	    if ( (wpn == 4 || wpn == 9 || wpn == 12) && IS_IMMUNE(victim, IMM_MISC) )
	      dam /= ( number_range( 1, 4 ) );
	}
    }


    if ( IS_NPC(ch) && ch->level > 200 )
    {
      mult += ( ch->level / 200 );
      reduct += ( ch->level / 200 );
      reduct += 1;
    }


    if ( IS_NPC(victim) && victim->level > 200 )
    {
      mult += ( victim->level / 200 );
      reduct += ( victim->level / 200 );
      reduct += 1;
    }

    dam *= mult;
    dam /= reduct;
    
    return dam;
}    


bool can_counter( CHAR_DATA *ch)
{
    if (!IS_NPC(ch) && IS_STANCE(ch, STANCE_MONKEY)) return TRUE;
    if (!IS_NPC(ch) && IS_STANCE(ch, STANCE_COUGAR)) return TRUE;
    return FALSE;
}

bool can_bypass( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if (IS_NPC(ch) || IS_NPC(victim)) return FALSE;
    else if (IS_STANCE(ch, STANCE_VIPER)) return TRUE;
    else if (IS_STANCE(ch, STANCE_MANTIS)) return TRUE;
     else if (IS_STANCE(ch, STANCE_RABBIT)) return TRUE;
    else if (IS_STANCE(ch, STANCE_TIGER)) return TRUE;
    else if (IS_STANCE(ch, STANCE_BEAR)) return TRUE;
    else if (IS_STANCE(ch, STANCE_COBRA)) return TRUE;
    return FALSE;
}

void update_damcap( CHAR_DATA *ch, CHAR_DATA *victim )
{
    int max_dam = 1000;
    
    if ( !IS_NPC(ch) )
    {
        if ( IS_CLASS(ch, CLASS_DROW) )
	{
	    max_dam += 1000;
	    if ( weather_info.sunlight == SUN_DARK )
	        max_dam += 500;
	    if ( IS_SET(ch->newbits, NEW_DROWHATE) )
	        max_dam += 750;
	}
if ( IS_SET(victim->garou1, GAROU_PAWS) )
{
max_dam =- 500;
}

	if ( IS_CLASS(ch, CLASS_DEMON) )
	{
	    if ( ch->in_room != NULL )
	        if ( ch->in_room->vnum == 30000 ) max_dam = 10000;
	    max_dam += ( ch->pcdata->stats[DEMON_POWER] * 20 );
	    max_dam += 1000;
	}
	if (IS_SET(ch->warp, WARP_DAMCAP))
	max_dam += 800;
	if ( IS_CLASS(ch, CLASS_VAMPIRE) )
	{
	         if ( ch->pcdata->stats[UNI_GEN] < 2 ) max_dam = 1500;
	    else if ( ch->pcdata->stats[UNI_GEN] < 3 ) max_dam = 1400;	    
	    else if ( ch->pcdata->stats[UNI_GEN] < 4 ) max_dam = 1300;
	    else if ( ch->pcdata->stats[UNI_GEN] < 5 ) max_dam = 1200;
	    else				       max_dam = 1100;
	    max_dam += ( ch->pcdata->stats[UNI_RAGE] );
	    if ( ch->pcdata->powers[VAM_POTE] > 0 )
	      max_dam += ( 100 * ch->pcdata->powers[VAM_POTE] );
	    if ( ch->pcdata->rank == AGE_METHUSELAH ) max_dam += 300;
	    else if ( ch->pcdata->rank == AGE_ELDER ) max_dam += 200;
	    else if ( ch->pcdata->rank == AGE_ANCILLA ) max_dam += 100;
	}
	if ( IS_CLASS(ch, CLASS_MONK) )
	{
	    max_dam += 300;
	    if ( ch->monkab[COMBAT] > 0 )
	      max_dam += ( ch->monkab[COMBAT] * 100 );
	    if ( ch->chi[CURRENT] > 0 )
	      max_dam += ( ch->chi[CURRENT] * 200 );
	}
	if ( IS_CLASS(ch, CLASS_NINJA) )
	{
	         if ( ch->pcdata->stats[UNI_GEN] < 3 ) max_dam = 1500;
	    else if ( ch->pcdata->stats[UNI_GEN] < 4 ) max_dam = 1400;
	    else if ( ch->pcdata->stats[UNI_GEN] < 5 ) max_dam = 1300;
	    else				       max_dam = 1200;
	    max_dam += (ch->pcdata->stats[UNI_RAGE] * 5);
	    if ( ch->pcdata->powers[NPOWER_CHIKYU] >= 6 && ch->pcdata->powers[HARA_KIRI] > 0 )
	        max_dam += 600;
	    if ( ch->pcdata->powers[NPOWER_CHIKYU] >= 2 )
	        max_dam += 500;
	}
	if ( IS_CLASS(ch, CLASS_MAGE) )
	{
	    max_dam = 1500;
	    if ( ch->spheres[MENT] > 0 )
	      max_dam += ( 200 * ch->spheres[MENT] );
	}
	if ( IS_CLASS(ch, CLASS_WEREWOLF) )
	{
	         if ( ch->pcdata->stats[UNI_GEN] < 2 ) max_dam = 2000;
	    else if ( ch->pcdata->stats[UNI_GEN] < 3 ) max_dam = 1900;
	    else if ( ch->pcdata->stats[UNI_GEN] < 4 ) max_dam = 1800;
	    else				       max_dam = 1700;
	    if ( IS_SET(ch->special, SPC_WOLFMAN) )
		max_dam += ( ch->pcdata->stats[UNI_RAGE] );
	    if ( ch->gifts[PHILODOX] >= 3 )
	        max_dam += 200;
	    if ( ch->gifts[SILVERFANGS] > 0 )
	        max_dam += 150;
	    if ( ch->gifts[GETOFFENRIS] >= 3 )
	        max_dam += 300;
if (IS_ITEMAFF(ch, ITEMA_SUNSHIELD)) max_dam += 500;
	}
	if ( IS_CLASS(ch, CLASS_HIGHLANDER) )
        {
	    if ( get_eq_char(ch, WEAR_WIELD) != NULL )
	    {
	        max_dam += (ch->wpn[1] / 2);
	        max_dam += (ch->race * 10);
	    }
	}
	if ( IS_ITEMAFF(ch, ITEMA_ARTIFACT)) max_dam += 500;
	if ( IS_ITEMAFF(victim, ITEMA_ARTIFACT)) max_dam -= 500;
    }
    else max_dam += ( ch->level * 100 );  // for NPCs


/* Legend Status Bonuses
 * BUGFIX: 29/12/99
 * Damcap fixed by Tijer original code wasnt giving dmcap bonusses
 * At all for legend
 */
      if (!IS_NPC(ch))
      {
         if ( ch->lstatus == 1 )
       max_dam += 50;
         if ( ch->lstatus == 2 )
       max_dam += 100;
         if ( ch->lstatus == 3 )
       max_dam += 200;
         if ( ch->lstatus == 4 )
       max_dam += 300;
         if ( ch->lstatus == 5 )
       max_dam += 400;
         if ( ch->lstatus == 6 )
       max_dam += 500;
         if ( ch->lstatus == 7)
       max_dam += 1000;
         if ( ch->lstatus == 8)
       max_dam += 1500;
         if ( ch->lstatus == 9) 
       max_dam += 2000;
       }

    if ( max_dam < 1000 ) max_dam = 1000;
    if ( max_dam > 6000 ) max_dam = 6000;
    ch->damcap[DAM_CAP] = max_dam;
    ch->damcap[DAM_CHANGE] = 0;
    return;
}

/*
 * Inflict damage from a hit.
 */
void damage( CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt )
{
    int max_dam = ch->damcap[DAM_CAP];
    bool agg_dam = FALSE;

    if ( victim->position == POS_DEAD )
	return;

    /*
     * Stop up any residual loopholes.
     */

    if (ch->damcap[DAM_CHANGE] == 1) update_damcap(ch,victim);

    if ( dam > max_dam ) dam = max_dam;

    if ( victim != ch )
    {
	/*
	 * Certain attacks are forbidden.
	 * Most other attacks are returned.
	 */
	if ( is_safe( ch, victim ) )
	    return;
	check_killer( ch, victim );

	if ( victim->position > POS_STUNNED )
	{
	    if ( victim->fighting == NULL )
		set_fighting( victim, ch );
	    victim->position = POS_FIGHTING;
	}

	if ( victim->position > POS_STUNNED )
	{
	    if ( ch->fighting == NULL )
		set_fighting( ch, victim );

	    /*
	     * If victim is charmed, ch might attack victim's master.
	     */
	    if ( IS_NPC(ch)
	    &&   IS_NPC(victim)
	    &&   IS_AFFECTED(victim, AFF_CHARM)
	    &&   victim->master != NULL
	    &&   victim->master->in_room == ch->in_room
	    &&   number_bits( 3 ) == 0 )
	    {
		stop_fighting( ch, FALSE );
		multi_hit( ch, victim->master, TYPE_UNDEFINED );
		return;
	    }
	}

	/*
	 * More charm stuff.
	 */
	if ( victim->master == ch )
	    stop_follower( victim );

	/*
	 * Damage modifiers.
	 */
	// First Round Check
	if(IS_SET(ch->extra,FROUND))
	{if(IS_CLASS(ch,CLASS_WEREWOLF) && ch->gifts[BLACKFURIES] >= 1)
	 {stc("You devise the best place to strike your opponent.\n\r",ch);
	  dam *= 2;}
         
	REMOVE_BIT(ch->extra,FROUND);
	}
	if ( IS_AFFECTED(ch, AFF_HIDE) )
	{
	    if (!can_see(victim,ch)) {dam *= 1.5;
		send_to_char("You use your concealment to get a surprise attack!\n\r",ch);}
	    REMOVE_BIT( ch->affected_by, AFF_HIDE );
	    act( "$n leaps from $s concealment.", ch, NULL, NULL, TO_ROOM );
	}

	if ( IS_CLASS(ch, CLASS_NINJA) && IS_SET(ch->act, PLR_WIZINVIS) )
	{
	    if (!can_see(victim,ch)) 
	    {
	    dam *= 1.3;
		send_to_char("You leap from the shadows.\n\r", ch);
		}
	    REMOVE_BIT( ch->act, PLR_WIZINVIS );
	    act( "$n leaps from the shadows.", ch, NULL, NULL, TO_ROOM );
	}
	else if ( IS_CLASS(ch, CLASS_MONK) && IS_SET(ch->act, PLR_WIZINVIS) )
        {
            if (!can_see(victim,ch))
            {
            dam *= 1.2;
                send_to_char("You from a flash of light.\n\r", ch);
                }
            REMOVE_BIT( ch->act, PLR_WIZINVIS );
            act( "$n bursts from a flash of light.", ch, NULL, NULL, TO_ROOM );
        }

	if ( IS_AFFECTED(victim, AFF_SANCTUARY) && dam > 1  )
	    dam *= 0.5;

	if ( IS_AFFECTED(victim, AFF_PROTECT) && IS_EVIL(ch) && dam > 1  )
	    dam -= dam * 0.25;

	if ( dam < 0 )
	    dam = 0;


	/*
	 * Check if damage is aggravated.
	 */
	if ( dt >= TYPE_ADD_AGG )
	{
	    agg_dam = TRUE;
	    dt -= TYPE_ADD_AGG;
	    while ( dt >= TYPE_ADD_AGG ) dt -= TYPE_ADD_AGG;
	}


	/*
	 * Check for disarm, trip, parry, and dodge.
	 */
	if ( dt >= TYPE_HIT )
	{
		
	 if ( IS_NPC(ch) && number_percent( ) < ch->level * 0.5 )
		disarm( ch, victim );
	    if ( IS_NPC(ch) && number_percent( ) < ch->level * 0.5 )
		trip( ch, victim );
	    if ( check_parry( ch, victim, dt ) )

		return;
	    if ( !IS_NPC(victim) && IS_STANCE(victim, STANCE_CRANE) && 
		victim->stance[STANCE_CRANE] > 100 && !can_counter(ch)
		&& !can_bypass(ch,victim) && check_parry( ch, victim, dt ))
		return;
	    else if ( !IS_NPC(victim) && IS_STANCE(victim, STANCE_MANTIS) && 
		victim->stance[STANCE_MANTIS] > 100 && !can_counter(ch)
		&& !can_bypass(ch,victim) && check_parry( ch, victim, dt ))
		return;
		  else if ( !IS_NPC(victim) && IS_STANCE(victim, STANCE_RABBIT) && 
		victim->stance[STANCE_RABBIT] > 100 && !can_counter(ch)
		&& !can_bypass(ch,victim) && check_parry( ch, victim, dt ))
		return;
	    if ( check_dodge( ch, victim, dt ) )
		return;
	    if ( !IS_NPC(victim) && IS_STANCE(victim, STANCE_MONGOOSE) && 
		victim->stance[STANCE_MONGOOSE] > 100 && !can_counter(ch)
		&& !can_bypass(ch,victim) && check_dodge( ch, victim, dt ))
		return;
	    else if ( !IS_NPC(victim) && IS_STANCE(victim, STANCE_SWALLOW) && 
		victim->stance[STANCE_SWALLOW] > 100 && !can_counter(ch)
		&& !can_bypass(ch,victim) && check_dodge( ch, victim, dt ))
		return;
		 else if ( !IS_NPC(victim) && IS_STANCE(victim, STANCE_EAGLE) && 
		victim->stance[STANCE_EAGLE] > 100 && !can_counter(ch)
		&& !can_bypass(ch,victim) && check_dodge( ch, victim, dt ))
		return;
	}

	if(dt == 10 && ch->gifts[GETOFFENRIS] >= 5)
	  dam *= 1.25;
	dam_message( ch, victim, dam, dt );
    }
    hurt_person(ch,victim,dam,agg_dam);
    return;
}

void adv_damage( CHAR_DATA *ch, CHAR_DATA *victim, int dam )
{
    if ( victim->position == POS_DEAD )
	return;

    if ( dam > 1500 ) dam = 1500;

    if ( victim != ch )
    {
	if ( is_safe( ch, victim ) )
	    return;
	check_killer( ch, victim );

	if ( victim->position > POS_STUNNED )
	{
	    if ( victim->fighting == NULL )
		set_fighting( victim, ch );
	    victim->position = POS_FIGHTING;
	}

	if ( victim->position > POS_STUNNED )
	{
	    if ( ch->fighting == NULL )
		set_fighting( ch, victim );

if (victim->embracing == NULL)
{
stop_embrace(ch,victim);
}
	    /*
	     * If victim is charmed, ch might attack victim's master.
	     */
	    if ( IS_NPC(ch)
	    &&   IS_NPC(victim)
	    &&   IS_AFFECTED(victim, AFF_CHARM)
	    &&   victim->master != NULL
	    &&   victim->master->in_room == ch->in_room
	    &&   number_bits( 3 ) == 0 )
	    {
		stop_fighting( ch, FALSE );
		multi_hit( ch, victim->master, TYPE_UNDEFINED );
		return;
	    }
	}

	if ( victim->master == ch )
	    stop_follower( victim );

	if ( IS_AFFECTED(victim, AFF_SANCTUARY) && dam > 1 )
	    dam /= 2;

	if ( IS_AFFECTED(victim, AFF_PROTECT) && IS_EVIL(ch) && dam > 1  )
	    dam -= dam / 4;
	if (!IS_NPC(victim) && !IS_NPC(ch)) dam = dam *2/3;

	if ( dam < 0 )
	    dam = 0;
    }
    return;
}

void hurt_person( CHAR_DATA *ch, CHAR_DATA *victim, int dam, bool agg_dam )
{
    
    int vnum;

    /*
     * Hurt the victim.
     * Inform the victim of his new state.
     */
    victim->hit -= dam;

    if ( IS_SET(victim->flag2, AFF2_INARENA) && victim->hit < 0 )
      clean_arena(victim, ch);


if (agg_dam && victim->agg < 100) victim->agg++;

    if (agg_dam)
    {
	if (victim->position == POS_MORTAL) victim->agg = 100;
	if (victim->agg < 100) victim->agg++;
	if (!IS_NPC(victim)) SET_BIT(victim->act, PLR_LAST_AGG);
    }

    else if (!IS_NPC(victim)) REMOVE_BIT(victim->act, PLR_LAST_AGG);

//MAYBE NOT LINE BELOW??
// victim->hit -= dam;

    if ( !IS_NPC(victim)
    &&   victim->level >= LEVEL_IMMORTAL
    &&   victim->hit < 1 )
	victim->hit = 1;
    update_pos( victim );


    switch( victim->position )
    {
    case POS_MORTAL:
	act( "$n is mortally wounded, and spraying blood everywhere.\n\r",victim, NULL, NULL, TO_ROOM );
	send_to_char( 
	    "You are mortally wounded, and spraying blood everywhere.\n\r",victim );
	if ( IS_CLASS(victim, CLASS_DROW) && IS_SET(victim->in_room->room_flags, ROOM_TOTAL_DARKNESS) )
	REMOVE_BIT(victim->in_room->room_flags, ROOM_TOTAL_DARKNESS);

	break;

    case POS_INCAP:
	act( "$n is incapacitated, and bleeding badly.", victim, NULL, NULL, TO_ROOM );
	send_to_char(
	    "You are incapacitated, and bleeding badly.\n\r", victim );
	break;

    case POS_STUNNED:
	act( "$n is stunned, but will soon recover.", victim, NULL, NULL, TO_ROOM );
	send_to_char("You are stunned, but will soon recover.\n\r",
	    victim );
	break;

    case POS_DEAD:
	act( "$n is DEAD!!", victim, 0, 0, TO_ROOM );
	send_to_char( "You have been KILLED!!\n\r\n\r", victim );
	break;

    default:
	if ( dam > victim->max_hit / 4 )
	    send_to_char( "That really did HURT!\n\r", victim );
	if ( victim->hit < victim->max_hit / 4 && dam > 0 )
	{
	    if (!IS_NPC(victim) && IS_CLASS(victim, CLASS_VAMPIRE)
		&& number_percent() < victim->beast)
		vamp_rage(victim);
	    else
		send_to_char( "You sure are BLEEDING!\n\r", victim );
	}
	break;
    }

    /*
     * Sleep spells and extremely wounded folks.
     */
    if ( !IS_AWAKE(victim) )
	stop_fighting( victim, FALSE );

    /*
     * Payoff for killing things.
     */
    if ( victim->position == POS_DEAD )
    {
	group_gain( ch, victim );

	if ( !IS_NPC(victim) )
	{
	    sprintf( log_buf, "%s killed by %s at %d",
		victim->name,
		(IS_NPC(ch) ? ch->short_descr : ch->name),
		victim->in_room->vnum );
	    log_string( log_buf );

	    /*
	     * Dying penalty:
	     * 1/2 your current exp.
	     */
	    if ( victim->exp > 0 )
		victim->exp = victim->exp / 2;
	}

    	if (IS_NPC(victim) && !IS_NPC(ch))
	{
	    ch->mkill += 1;
	if ( ch->level >= 3 )
	{
	if (IS_CLASS(ch, CLASS_DROW) && IS_NPC(victim) && !IS_SET(victim->act, ACT_NOEXP ))
		ch->pcdata->stats[DROW_POWER] += victim->level*4/3;

	    if (IS_CLASS(ch, CLASS_DEMON) || IS_SET(ch->special, SPC_CHAMPION))
	    {
		if ((vnum = victim->pIndexData->vnum) > 29000)
		{
		    switch (vnum)
		    {
		    default:
			ch->pcdata->stats[DEMON_CURRENT] += victim->level/2;
			ch->pcdata->stats[DEMON_TOTAL]   += victim->level/2;
			break;
		    case 29600:
		    case 30001:
		    case 30006:
		    case 30007:
		    case 30008:
		    case 30009:
                    case 30000:
			break;
		    }
		}
		else if (IS_NPC(victim) && !IS_SET(victim->act, ACT_NOEXP))
		{
		    ch->pcdata->stats[DEMON_CURRENT] += victim->level*2;
		    ch->pcdata->stats[DEMON_TOTAL] += victim->level*2;
		}
	    }
	    }
	    if (ch->level == 1 && ch->mkill > 4)
	    {
		ch->level = 2;
		do_save(ch,"");
	    }
	}
    	if (!IS_NPC(victim) && IS_NPC(ch)) 
        {
           victim->mdeath = victim->mdeath + 1;
        }
	raw_kill( victim, ch );


	if ( IS_SET(ch->act, PLR_AUTOLOOT) )
	    do_get( ch, "all corpse" );
	else
	    do_look( ch, "in corpse" );

	if ( !IS_NPC(ch) )
	{
	    if ( IS_SET(ch->act, PLR_AUTOSAC) )
		do_sacrifice( ch, "corpse" );
	}

	return;
    }

    if ( victim == ch )
	return;

    /*
     * Take care of link dead people.
     */
    if ( !IS_NPC(victim) && victim->desc == NULL )
    {
	if ( number_range( 0, victim->wait ) == 0 )
	{
	    do_recall( victim, "" );
	    return;
	}
    }

    /*
     * Wimp out?
     */
    if ( IS_NPC(victim) && dam > 0 )
    {
	if ( ( IS_SET(victim->act, ACT_WIMPY) && number_bits( 1 ) == 0
	&&   victim->hit < victim->max_hit / 2 )
	||   ( IS_AFFECTED(victim, AFF_CHARM) && victim->master != NULL
	&&     victim->master->in_room != victim->in_room ) )
	    do_flee( victim, "" );
    }

    if ( !IS_NPC(victim)
    &&   victim->hit > 0
    &&   victim->hit <= victim->wimpy
    &&   victim->wait == 0 )
	do_flee( victim, "" );

    tail_chain( );
    return;
}

bool is_safe( CHAR_DATA *ch, CHAR_DATA *victim )
{

    if ( !IS_NPC(ch) && ch->level < 3 && !IS_NPC(victim) )
    {
        stc("You must be an avatar to fight other avatars!\n\r",ch);
        return TRUE;
    }

    if ( !IS_NPC(victim) && !IS_NPC(ch) && victim->level < 3 )
    {
        stc("They must be an avatar!\n\r",ch);
        return TRUE;
    }

 if ( !IS_NPC(victim) )
    {
	if (victim->pcdata->in_progress /* &&
	    (!victim->pcdata->in_progress->text) */ )
        {
            send_to_char ("Not while they are writting a note!\n\r", ch );
	    return TRUE;
	}                                                    
    }


    if ( victim->fight_timer > 0 )
      return FALSE;

    /* Ethereal people can only attack other ethereal people */
    if ( IS_AFFECTED(ch, AFF_ETHEREAL) && !IS_AFFECTED(victim, AFF_ETHEREAL) )
    {
	send_to_char( "You cannot while ethereal.\n\r", ch );
	return TRUE;
    }
    if ( !IS_AFFECTED(ch, AFF_ETHEREAL) && IS_AFFECTED(victim, AFF_ETHEREAL) )
    {
	send_to_char( "You cannot fight an ethereal person.\n\r", ch );
	return TRUE;
    }

    /* You cannot attack across planes */
    if ( IS_AFFECTED(ch, AFF_SHADOWPLANE) && !IS_AFFECTED(victim, AFF_SHADOWPLANE) )
    {
	act( "You are too insubstantial!", ch, NULL, victim, TO_CHAR );
	return TRUE;
    }
    if ( !IS_AFFECTED(ch, AFF_SHADOWPLANE) && IS_AFFECTED(victim, AFF_SHADOWPLANE) )
    {
	act( "$E is too insubstantial!", ch, NULL, victim, TO_CHAR );
	return TRUE;
    }

    if ( IS_SET(ch->in_room->room_flags,ROOM_SAFE) )
    {
	send_to_char( "You cannot fight in a safe room.\n\r", ch );
	return TRUE;
    }

    if ( IS_HEAD(ch,LOST_HEAD) || IS_EXTRA(ch,EXTRA_OSWITCH) )
    {
	send_to_char( "Objects cannot fight!\n\r", ch );
	return TRUE;
    }
    else if ( IS_HEAD(victim,LOST_HEAD) || IS_EXTRA(victim,EXTRA_OSWITCH))
    {
	send_to_char( "You cannot attack an object.\n\r", ch );
	return TRUE;
    }

    if ( IS_NPC(ch) || IS_NPC(victim) )
	return FALSE;

    /* Thx Josh! */
    if ( victim->fighting == ch )
	return FALSE;

    if (IS_ITEMAFF(ch, ITEMA_PEACE))
    {
	send_to_char( "You are unable to attack them.\n\r", ch );
	return TRUE;
    }

    if (IS_ITEMAFF(victim, ITEMA_PEACE))
    {
	send_to_char( "You can't seem to attack them.\n\r", ch );
	return TRUE;
    }
    
    if (!IS_NPC(ch) && IS_AFFECTED(ch, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return TRUE;
    }

    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return TRUE;
    }


    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_STEELSHIELD) )
    {
	send_to_char( "They are far to imposing.\n\r", ch );
	return TRUE;
    }

	if ( ch->trust > LEVEL_BUILDER )
    {
	send_to_char( "You cannot fight if you have implementor powers!\n\r", ch );
	return TRUE;
    }

    if ( victim->trust > LEVEL_BUILDER )
    {
	send_to_char( "You cannot fight someone with implementor powers!\n\r", ch );
	return TRUE;
    }

   else if (strlen(ch->pcdata->love) > 1 && 
	    !str_cmp(ch->pcdata->love, victim->name))
	{
	    send_to_char( "How could you attack someone you love?!\n\r",ch );
	    return TRUE;
	}
    
    if ( !CAN_PK(ch) || !CAN_PK(victim) )
    {
	send_to_char( "Both players must be avatars to fight.\n\r", ch );
	return TRUE;
    }

  return FALSE;
}	

bool no_attack( CHAR_DATA *ch, CHAR_DATA *victim )
{


    if ( !IS_NPC(ch) && ch->level < 3 && !IS_NPC(victim) )
    {
        stc("You must be an avatar to fight other avatars!\n\r",ch);
        return TRUE;
    }

    if ( !IS_NPC(victim) && !IS_NPC(ch) && victim->level < 3 )
    {
        stc("They must be an avatar!\n\r",ch);
        return TRUE;
    }

    if ( victim->fight_timer > 0 )
      return FALSE;

    /* Ethereal people can only attack other ethereal people */
    if ( IS_AFFECTED(ch, AFF_ETHEREAL) && !IS_AFFECTED(victim, AFF_ETHEREAL) )
    {
	send_to_char( "You cannot while ethereal.\n\r", ch );
	return TRUE;
    }
    if ( !IS_AFFECTED(ch, AFF_ETHEREAL) && IS_AFFECTED(victim, AFF_ETHEREAL) )
    {
	send_to_char( "You cannot fight an ethereal person.\n\r", ch );
	return TRUE;
    }

    /* You cannot attack across planes */
    if ( IS_AFFECTED(ch, AFF_SHADOWPLANE) && !IS_AFFECTED(victim, AFF_SHADOWPLANE) )
    {
	act( "You are too insubstantial!", ch, NULL, victim, TO_CHAR );
	return TRUE;
    }
    if ( !IS_AFFECTED(ch, AFF_SHADOWPLANE) && IS_AFFECTED(victim, AFF_SHADOWPLANE) )
    {
	act( "$E is too insubstantial!", ch, NULL, victim, TO_CHAR );
	return TRUE;
    }

    if ( IS_SET(ch->in_room->room_flags,ROOM_SAFE) )
    {
	send_to_char( "You cannot fight in a safe room.\n\r", ch );
	return TRUE;
    }

    if ( IS_HEAD(ch,LOST_HEAD) || IS_EXTRA(ch,EXTRA_OSWITCH) )
    {
	send_to_char( "Objects cannot fight!\n\r", ch );
	return TRUE;
    }
    else if ( IS_HEAD(victim,LOST_HEAD) || IS_EXTRA(victim,EXTRA_OSWITCH) )
    {
	send_to_char( "You cannot attack objects.\n\r", ch );
	return TRUE;
    }

    return FALSE;
}



/*
 * See if an attack justifies a KILLER flag.
 */
void check_killer( CHAR_DATA *ch, CHAR_DATA *victim )
{
    /*
     * Follow charm thread to responsible character.
     * Attacking someone's charmed char is hostile!
     */
    while ( IS_AFFECTED(victim, AFF_CHARM) && victim->master != NULL )
	victim = victim->master;

    /*
     * NPC's are fair game.
     * So are killers and thieves.
     */
    if ( IS_NPC(victim) )
	return;

    /*
     * Charm-o-rama.
     */
    if ( IS_SET(ch->affected_by, AFF_CHARM) )
    {
	if ( ch->master == NULL )
	{
	    affect_strip( ch, gsn_charm_person );
	    REMOVE_BIT( ch->affected_by, AFF_CHARM );
	    return;
	}
	stop_follower( ch );
	return;
    }
    return;
}



/*
 * Check for parry.
 */
bool check_parry( CHAR_DATA *ch, CHAR_DATA *victim, int dt )
{
    OBJ_DATA *obj = NULL;
    int chance = 0;
    int thingy;
    bool claws = FALSE;
    bool hands = FALSE;

    if ( !IS_AWAKE(victim) )
	return FALSE;

    else if ( IS_CLASS(victim, CLASS_WEREWOLF)	&& 
	victim->gifts[AHROUN] >= 2		&& 
	IS_VAMPAFF(victim, VAM_CLAWS)		&&
	get_eq_char(victim, WEAR_WIELD) == NULL	&&
	get_eq_char(victim, WEAR_HOLD) == NULL)
    {
	obj = NULL;
	claws = TRUE;
    }
    else if ( IS_CLASS(victim, CLASS_MONK) &&
              IS_SET(victim->newbits, NEW_MONKADAM) &&
              get_eq_char(victim, WEAR_WIELD) == NULL &&
              get_eq_char(victim, WEAR_HOLD) == NULL)
    {
        obj = NULL;
        claws = TRUE;
    }
    else
    {
	if ( ( obj = get_eq_char( victim, WEAR_WIELD ) ) == NULL 
		|| obj->item_type != ITEM_WEAPON )
	{
	    if ( ( obj = get_eq_char( victim, WEAR_HOLD ) ) == NULL 
		|| obj->item_type != ITEM_WEAPON ) return FALSE;
	}
    }

    if (dt < 1000 || dt > 1012) return FALSE;
    if (!IS_NPC(ch))     chance -= (ch->wpn[dt-1000] * 0.1);
	else             chance -= (ch->level * 0.2);
    if (!IS_NPC(victim)) chance += (victim->wpn[dt-1000] * 0.5);
	else             chance += victim->level;
    if (!IS_NPC(victim) && IS_STANCE(victim, STANCE_CRANE) &&
	victim->stance[STANCE_CRANE] > 0 && !can_counter(ch) &&
	!can_bypass(ch,victim))
	chance += (victim->stance[STANCE_CRANE] * 0.25);
    else if (!IS_NPC(victim) && IS_STANCE(victim, STANCE_MANTIS) &&
	victim->stance[STANCE_MANTIS] > 0 && !can_counter(ch) &&
	!can_bypass(ch,victim))
	chance += (victim->stance[STANCE_MANTIS] * 0.25);
//    chance -= (char_hitroll(ch) * 0.1);
     else if (!IS_NPC(victim) && IS_STANCE(victim, STANCE_RABBIT) &&
	victim->stance[STANCE_RABBIT] > 0 && !can_counter(ch) &&
	!can_bypass(ch,victim))
	chance += (victim->stance[STANCE_RABBIT] * 0.30);
    chance -= (char_hitroll(ch) * 0.3);

    if (claws) 
    {
        chance += (char_hitroll(victim) * 0.075);
    }
    else chance += (char_hitroll(victim) * 0.1);

    if (hands) 
    {
	    chance += (char_hitroll(victim) * 0.075);
    }
    else chance += (char_hitroll(victim) * 0.1);

    if (!IS_NPC(ch))
    {
        if ( IS_CLASS(ch, CLASS_VAMPIRE) )
	{
	    if ( ch->pcdata->powers[VAM_CELE] > 0 )
	        chance -= ( 4 * ch->pcdata->powers[VAM_CELE] );
	}
	if ( IS_CLASS(ch, CLASS_NINJA) )
	{
	    if ( ch->pcdata->powers[NPOWER_CHIKYU] >= 6 && ch->pcdata->powers[HARA_KIRI] > 0 )
	        chance -= 25;
	    if ( ch->pcdata->powers[NPOWER_CHIKYU] > 2 )
	        chance -= 20;
	    if ( ch->pcdata->powers[NINJAKI] > 4 )
	        chance -= ( ch->pcdata->powers[NINJAKI] / 4 );
	} 
	if ( IS_CLASS(ch, CLASS_DEMON) )
	{
	    if ( IS_DEMPOWER(ch, DEM_SPEED) )
	        chance -= 15;
	}
    if ( IS_CLASS(ch, CLASS_DEMON) && !IS_SET(ch->warp, WARP_QUICKNESS) )
        chance -= 10;
	if ( IS_CLASS(ch, CLASS_MAGE) )
	{
	    if ( IS_SET(ch->mflags, MAGE_POLYAPPEAR) )
	        chance -= 10;
	    if ( ch->spheres[MTIM] > 0 )
	        chance -= ( ch->spheres[MTIM] * 3 );
	}
	if ( IS_CLASS(ch, CLASS_DROW) )
	{
	    if ( IS_SET(ch->pcdata->powers[1], DPOWER_ARMS) )
	        chance -= 20;
	    chance -= 40;
	}
	if ( IS_CLASS(ch, CLASS_WEREWOLF) )
	{
	    if ( IS_SET(ch->special, SPC_WOLFMAN) )
	        chance -= 5;
	    if ( ch->gifts[SILENTSTRIDERS] > 0 )
	        chance -= 5;
	    if ( ch->gifts[SILENTSTRIDERS] > 1 )
	        chance -= 10;
	    if ( ch->gifts[SILENTSTRIDERS] > 2 )
	        chance -= 10;
            if ( ch->gifts[STARGAZERS] >= 3 )
	        chance -= 5;
	}
	if ( IS_CLASS(ch, CLASS_MONK) )
	{
	    if ( ch->chi[CURRENT] > 0 )
	        chance -= ( ch->chi[CURRENT] * 7 );
	}
	if ( IS_CLASS(ch, CLASS_HIGHLANDER) )
	{
	    if ( get_eq_char(ch, WEAR_WIELD) != NULL )
	      chance -= ch->race*2/3;
	}
    }

  /* Some shit for Earth Embrace )Mage Power(, works on NPC's.. */
    if ( IS_SET(victim->mflags, MAGE_EMBRACED2) )
      chance += 10;
    if ( IS_SET(victim->mflags, MAGE_EMBRACED1) )
      chance += 5;
    if ( IS_SET(ch->mflags, MAGE_EMBRACED2) )
      chance -= 10;
    if ( IS_SET(ch->mflags, MAGE_EMBRACED1) )
      chance -= 5;

    if(IS_CLASS(ch,CLASS_DROW)) chance *= 2;
    if(IS_CLASS(ch,CLASS_DROW)) chance /= 3;
    if (!IS_NPC(victim))
    {
        if ( IS_CLASS(victim, CLASS_VAMPIRE) )
	{
	    if ( victim->pcdata->powers[VAM_CELE] > 0 )
	        chance += ( 3 * victim->pcdata->powers[VAM_CELE] );
	}
	if ( IS_CLASS(victim, CLASS_NINJA) )
	{
	    if ( victim->pcdata->powers[NPOWER_CHIKYU] >= 6 && victim->pcdata->powers[HARA_KIRI] > 0 )
	        chance += 25;
	    if ( victim->pcdata->powers[NPOWER_CHIKYU] > 2 )
	        chance += 20;
	    if ( victim->pcdata->powers[NINJAKI] > 4 )
	        chance += ( victim->pcdata->powers[NINJAKI] / 4 );
	}
	if ( IS_CLASS(victim, CLASS_DEMON) )
	{
	    if ( IS_DEMPOWER(victim, DEM_SPEED) )
	        chance += 15;
	}
if ( IS_CLASS(ch, CLASS_DEMON) && !IS_SET(ch->warp, WARP_QUICKNESS) )
        chance -= 10;
	if ( IS_CLASS(victim, CLASS_DROW) )
	{
	    if ( IS_SET(victim->pcdata->powers[1], DPOWER_ARMS) )
	        chance += 20;
		chance += 40;
	}
	if ( IS_CLASS(victim, CLASS_MAGE) )
	{
	    if ( IS_SET(victim->mflags, MAGE_POLYAPPEAR) )
	        chance += 10;
	    if ( victim->spheres[MTIM] > 0 )
	        chance += ( victim->spheres[MTIM] * 2 );
	}
	if ( IS_CLASS(victim, CLASS_MONK) )
	{
	    if ( victim->chi[CURRENT] > 0 )
	        chance += ( victim->chi[CURRENT] * 7 );
	}
	if ( IS_CLASS(victim, CLASS_WEREWOLF) )
	{
	    if ( IS_SET(victim->special, SPC_WOLFMAN) )
	        chance += 5;
	    if ( victim->gifts[SILENTSTRIDERS] > 0 )
	        chance += 5;
	    if ( victim->gifts[SILENTSTRIDERS] > 1 )
	        chance += 10;
	    if ( victim->gifts[SILENTSTRIDERS] > 2 )
	        chance += 10;
            if ( victim->gifts[STARGAZERS] >= 3 )
	        chance += 5;
	}
	if ( IS_CLASS(victim, CLASS_HIGHLANDER) )
	{
	    if ( get_eq_char(victim, WEAR_WIELD) != NULL )
	      chance += ch->race*2/3;
	}

    }

    if      (chance > 75) chance = 75;
    else if (chance < 25) chance = 25;

    if (!IS_NPC(ch) && ch->pcdata->powers[VAM_CELE] > 0 && 
	IS_CLASS(ch, CLASS_VAMPIRE))
    {
	if (ch->pcdata->rank == AGE_METHUSELAH) chance -= 10;
	else if (ch->pcdata->rank == AGE_ELDER) chance -= 7;
	else if (ch->pcdata->rank == AGE_ANCILLA) chance -= 5;
    }
    if (!IS_NPC(victim) && victim->pcdata->powers[VAM_CELE] > 0 && 
	IS_CLASS(victim, CLASS_VAMPIRE))
    {
	if (victim->pcdata->rank == AGE_METHUSELAH) chance += 10;
	else if (victim->pcdata->rank == AGE_ELDER) chance += 7;
	else if (victim->pcdata->rank == AGE_ANCILLA) chance += 5;
    }
   if ( !IS_NPC(victim) && IS_CLASS(victim, CLASS_MONK) )
    {
     if ( victim->monkblock / 4 > 0 )
        chance += victim->monkblock / 4;
    }
           
    if ( IS_NPC(victim) )
    {
      if ( victim->level < 100 )
        chance = 15;
      if ( victim->level >= 100 )
        chance = ( victim->level * .01 );
      if ( victim->level >= 500 )
        chance = 50;
      chance += config_info->bonus;
    }
	if(IS_CLASS(victim,CLASS_DROW))
	chance /= 1.35;
    thingy = number_range(1,100);
    if ( thingy >= chance )
	return FALSE;

    if (claws)
    {
	if (IS_NPC(victim) || !IS_SET(victim->act, PLR_BRIEF))
	    act( "You parry $n's blow with your claws.",  ch, NULL, victim, TO_VICT );
	if (IS_NPC(ch) || !IS_SET(ch->act, PLR_BRIEF))
	    act( "$N parries your blow with $S claws.", ch, NULL, victim, TO_CHAR );
	return TRUE;
    }
	if (hands)
    {
	if (IS_NPC(victim) || !IS_SET(victim->act, PLR_BRIEF))
	    act( "You parry $n's blow with your adamantium hands.",  ch, NULL, victim, TO_VICT);
	if (IS_NPC(ch) || !IS_SET(ch->act, PLR_BRIEF))
	    act( "$N parries your blow with $S adamantium hands.", ch, NULL, victim, TO_CHAR);
	return TRUE;
    }
          if (!IS_NPC(victim) && IS_CLASS(victim, CLASS_MONK)
                 && victim->monkblock < 150 )
              victim->monkblock++;

    if (!IS_NPC(victim) && obj != NULL && obj->item_type == ITEM_WEAPON &&
	obj->value[3] >= 0 && obj->value[3] <= 12)
    {
	if (IS_NPC(victim) || !IS_SET(victim->act, PLR_BRIEF))
	    act( "You parry $n's blow with $p.",  ch, obj, victim, TO_VICT );
	if (IS_NPC(ch) || !IS_SET(ch->act, PLR_BRIEF))
	    act( "$N parries your blow with $p.", ch, obj, victim, TO_CHAR );
	return TRUE;
    }
    if (IS_NPC(victim) || !IS_SET(victim->act, PLR_BRIEF))
	act( "You parry $n's attack.",  ch, NULL, victim, TO_VICT    );
    if (IS_NPC(ch) || !IS_SET(ch->act, PLR_BRIEF))
	act( "$N parries your attack.", ch, NULL, victim, TO_CHAR    );
    return TRUE;
}



/*
 * Check for dodge.
 */
bool check_dodge( CHAR_DATA *ch, CHAR_DATA *victim, int dt )
{
    int chance = 0;
    int thingy;

    if ( !IS_AWAKE(victim) )
	return FALSE;

    if (!IS_NPC(ch))     chance -= (ch->wpn[dt-1000] * 0.1);
	else             chance -= (ch->level * 0.2);
    if (!IS_NPC(victim)) chance += (victim->wpn[0] * 0.5);
	else             chance += victim->level;

    if (!IS_NPC(victim) && IS_STANCE(victim, STANCE_MONGOOSE) &&
	victim->stance[STANCE_MONGOOSE] > 0 && !can_counter(ch) &&
	!can_bypass(ch,victim))
	(chance += victim->stance[STANCE_MONGOOSE] * 0.25);
    if (!IS_NPC(victim) && IS_STANCE(victim, STANCE_SWALLOW) &&
	victim->stance[STANCE_SWALLOW] > 0 && !can_counter(ch) &&
	!can_bypass(ch,victim))
	(chance += victim->stance[STANCE_SWALLOW] * 0.25);
 if (!IS_NPC(victim) && IS_STANCE(victim, STANCE_EAGLE) &&
	victim->stance[STANCE_EAGLE] > 0 && !can_counter(ch) &&
	!can_bypass(ch,victim))
	(chance += victim->stance[STANCE_EAGLE] * 0.30);
    if (!IS_NPC(ch))
    {
        if ( IS_CLASS(ch, CLASS_VAMPIRE) )
	{
	    if ( ch->pcdata->powers[VAM_CELE] > 0 )
	        chance -= ( 4 * ch->pcdata->powers[VAM_CELE] );
	}
	if ( IS_CLASS(ch, CLASS_NINJA) )
	{
	    if ( ch->pcdata->powers[NPOWER_CHIKYU] >= 6 && ch->pcdata->powers[HARA_KIRI] > 0 )
	        chance -= 25;
	    if ( ch->pcdata->powers[NPOWER_CHIKYU] > 2 )
	        chance -= 20;
	    if ( ch->pcdata->powers[NINJAKI] > 4 )
	        chance -= ( ch->pcdata->powers[NINJAKI] / 4 );
	}
	if ( IS_CLASS(ch, CLASS_DEMON) )
	{
	    if ( IS_DEMPOWER(ch, DEM_SPEED) )
	        chance -= 15;
	}
if ( IS_CLASS(ch, CLASS_DEMON) && !IS_SET(ch->warp, WARP_QUICKNESS) )
        chance -= 10;
	if ( IS_CLASS(ch, CLASS_MAGE) )
	{
	    if ( IS_SET(ch->mflags, MAGE_POLYAPPEAR) )
	        chance -= 10;
	    if ( ch->spheres[MTIM] > 0 )
	        chance -= ( ch->spheres[MTIM] * 2 );
	}
	if ( IS_CLASS(ch, CLASS_DROW) )
	{
	    if ( IS_SET(ch->pcdata->powers[1], DPOWER_ARMS) )
	        chance -= 20;
	    chance -= 40;
	}
	if ( IS_CLASS(ch, CLASS_WEREWOLF) )
	{
	    if ( IS_SET(ch->special, SPC_WOLFMAN) )
	        chance -= 5;
	    if ( ch->gifts[SILENTSTRIDERS] > 0 )
	        chance -= 5;
	    if ( ch->gifts[SILENTSTRIDERS] > 1 )
	        chance -= 10;
	    if ( ch->gifts[SILENTSTRIDERS] > 2 )
	        chance -= 10;
            if ( ch->gifts[STARGAZERS] >= 3 )
	        chance -= 5;
	}
	if ( IS_CLASS(ch, CLASS_MONK) )
	{
	    if ( ch->chi[CURRENT] > 0 )
	        chance -= ( ch->chi[CURRENT] * 7 );
	}
	if ( IS_CLASS(ch, CLASS_HIGHLANDER) )
	{
	    if ( get_eq_char(ch, WEAR_WIELD) != NULL )
	      chance -= ch->race*2/3;
	}
    }


  /* Some shit for Earth Embrace )Mage Power(, works on NPC's.. */
    if ( IS_SET(victim->mflags, MAGE_EMBRACED2) )
      chance += 10;
    if ( IS_SET(victim->mflags, MAGE_EMBRACED1) )
      chance += 5;
    if ( IS_SET(ch->mflags, MAGE_EMBRACED2) )
      chance -= 10;
    if ( IS_SET(ch->mflags, MAGE_EMBRACED1) )
      chance -= 5;

    if (!IS_NPC(victim))
    {
        if ( IS_CLASS(victim, CLASS_VAMPIRE) )
	{
	    if ( victim->pcdata->powers[VAM_CELE] > 0 )
	        chance += ( 3 * victim->pcdata->powers[VAM_CELE] );
	}
	if ( IS_CLASS(victim, CLASS_NINJA) )
	{
	    if ( victim->pcdata->powers[NPOWER_CHIKYU] >= 6 && victim->pcdata->powers[HARA_KIRI] > 0 )
	        chance += 25;
	    if ( victim->pcdata->powers[NPOWER_CHIKYU] > 2 )
	        chance += 20;
	    if ( victim->pcdata->powers[NINJAKI] > 4 )
	        chance += ( victim->pcdata->powers[NINJAKI] / 4 );
	}
	if ( IS_CLASS(victim, CLASS_DEMON) )
	{
	    if ( IS_DEMPOWER(victim, DEM_SPEED) )
	        chance += 15;
	}
if ( IS_CLASS(ch, CLASS_DEMON) && !IS_SET(ch->warp, WARP_QUICKNESS) )
        chance -= 10;
	if ( IS_CLASS(victim, CLASS_DROW) )
	{
	    if ( IS_SET(victim->pcdata->powers[1], DPOWER_ARMS) )
	        chance += 20;
		chance += 40;
	}
	if ( IS_CLASS(victim, CLASS_MAGE) )
	{
	    if ( IS_SET(victim->mflags, MAGE_POLYAPPEAR) )
	        chance += 10;
	    if ( victim->spheres[MTIM] > 0 )
	        chance += ( victim->spheres[MTIM] * 2 );
	}
	if ( IS_CLASS(victim, CLASS_MONK) )
	{
	    if ( victim->chi[CURRENT] > 0 )
	        chance += ( victim->chi[CURRENT] * 7 );
	}
	if ( IS_CLASS(victim, CLASS_WEREWOLF) )
	{
	    if ( IS_SET(victim->special, SPC_WOLFMAN) )
	        chance += 5;
	    if ( victim->gifts[SILENTSTRIDERS] > 0 )
	        chance += 5;
	    if ( victim->gifts[SILENTSTRIDERS] > 1 )
	        chance += 10;
	    if ( victim->gifts[SILENTSTRIDERS] > 2 )
	        chance += 10;
            if ( victim->gifts[STARGAZERS] >= 3 )
	        chance += 5;
	}
	if ( IS_CLASS(victim, CLASS_HIGHLANDER) )
	{
	    if ( get_eq_char(victim, WEAR_WIELD) != NULL )
	      chance += ch->race*2/3;
	}

    }

    if      (chance > 75) chance = 75;
    else if (chance < 25) chance = 25;

    if (!IS_NPC(ch) && IS_VAMPAFF(ch, VAM_CELERITY) && 
	IS_CLASS(ch, CLASS_VAMPIRE))
    {
	if (ch->pcdata->rank == AGE_METHUSELAH) chance -= 10;
	else if (ch->pcdata->rank == AGE_ELDER) chance -= 7;
	else if (ch->pcdata->rank == AGE_ANCILLA) chance -= 5;
    }
    if (!IS_NPC(victim) && IS_VAMPAFF(victim, VAM_CELERITY) && 
	IS_CLASS(victim, CLASS_VAMPIRE))
    {
	if (victim->pcdata->rank == AGE_METHUSELAH) chance += 10;
	else if (victim->pcdata->rank == AGE_ELDER) chance += 7;
	else if (victim->pcdata->rank == AGE_ANCILLA) chance += 5;
    }

   if ( !IS_NPC(victim) && IS_CLASS(victim, CLASS_MONK) )
    {
     if ( victim->monkblock / 4 > 0 )
        chance += victim->monkblock / 4;
    }

    if ( IS_NPC(victim) )
    {
      if ( victim->level < 100 )
        chance = 15;
      if ( victim->level >= 100 )
        chance = ( victim->level * .01 );
      if ( victim->level >= 500 )
        chance = 50;
      chance += config_info->bonus;
    }
	if(IS_CLASS(victim,CLASS_DROW))chance /= 1.25;
    thingy = number_range(1,100);
    if ( thingy >= chance )
	return FALSE;

    if (IS_NPC(victim) || !IS_SET(victim->act, PLR_BRIEF))
	act( "You dodge $n's attack.", ch, NULL, victim, TO_VICT );
    if (IS_NPC(ch) || !IS_SET(ch->act, PLR_BRIEF))
	act( "$N dodges your attack.", ch, NULL, victim, TO_CHAR );
    return TRUE;
}



/*
 * Set position of a victim.
 */
void update_pos( CHAR_DATA *victim )
{
    CHAR_DATA *mount;

    if ( victim->hit > 0 )
    {
    	if ( victim->position <= POS_STUNNED )
	{
	    bool gm_stance = FALSE;
	    victim->position = POS_STANDING;
	    if (!IS_NPC(victim) && victim->stance[0] > 0)
	    {
		int stance = victim->stance[0];
		if (victim->stance[stance] >= 200) gm_stance = TRUE;
	    }
	    if (IS_NPC(victim) || victim->max_hit * 0.25 > victim->hit || 
		!gm_stance)
	    {
		act( "$n clambers back to $s feet.", victim, NULL, NULL, TO_ROOM);
		act( "You clamber back to your feet.", victim, NULL, NULL, TO_CHAR);
	    }
	    else
	    {
		act( "$n flips back up to $s feet.", victim, NULL, NULL, TO_ROOM);
		act( "You flip back up to your feet.", victim, NULL, NULL, TO_CHAR);
	    }
	}
	return;
    }
    else if ( (mount = victim->mount) != NULL)
    {
	if (victim->mounted == IS_MOUNT)
	{
	    act("$n rolls off $N.",mount,NULL,victim,TO_ROOM);
	    act("You roll off $N.",mount,NULL,victim,TO_CHAR);
	}
	else if (victim->mounted == IS_RIDING)
	{
	    act("$n falls off $N.",victim,NULL,mount,TO_ROOM);
	    act("You fall off $N.",victim,NULL,mount,TO_CHAR);
	}
	mount->mount    = NULL;
	victim->mount   = NULL;
	mount->mounted  = IS_ON_FOOT;
	victim->mounted = IS_ON_FOOT;
    }

    if (!IS_NPC(victim) && victim->hit <=-11 && IS_HERO(victim))
    {
        victim->hit = -10;
        if (victim->position == POS_FIGHTING) 
           stop_fighting(victim,TRUE);
        return;
    }

    if ( IS_NPC(victim) || victim->hit <= -11 )
    {
	victim->position = POS_DEAD;
	return;
    }

         if ( victim->hit <= -6 ) victim->position = POS_MORTAL;
    else if ( victim->hit <= -3 ) victim->position = POS_INCAP;
    else                          victim->position = POS_STUNNED;

    return;
}



/*
 * Start fights.
 */
void set_fighting( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if ( ch->fighting != NULL )
    {
	bug( "Set_fighting: already fighting", 0 );
	return;
    }


     if ( !IS_NPC( ch ) && !IS_NPC( victim) )
        ch->fight_timer = 10;

    if ( !IS_NPC( victim ) && !IS_NPC( ch ) )
        victim->fight_timer = 10;

    if ( IS_AFFECTED(ch, AFF_SLEEP) )
	affect_strip( ch, gsn_sleep );

    ch->fighting = victim;
    ch->position = POS_FIGHTING;
    ch->damcap[DAM_CHANGE] = 1;

	autodrop(ch);
	autodrop(victim);

  if (IS_AFFECTED(ch, AFF_STEELSHIELD))
    {
        REMOVE_BIT(ch->affected_by, AFF_STEELSHIELD);
}

    return;
}

void stop_embrace( CHAR_DATA *ch, CHAR_DATA *victim )
{
if (victim==NULL)
{ch->embracing=NULL;return;}
victim->embraced=NULL;
ch->embracing=NULL;
stc("You release your hold on your victim!\n\r", ch );
//act("$N releases his hold on $N.",ch,NULL,victim,TO_CHAR);
return;

}


/*
 * Stop fights.
 */
void stop_fighting( CHAR_DATA *ch, bool fBoth )
{
    CHAR_DATA *fch;
    


    for ( fch = char_list; fch != NULL; fch = fch->next )
    {
	if ( fch == ch || ( fBoth && fch->fighting == ch ) )
	{
	    fch->fighting	= NULL;
	    fch->position	= POS_STANDING;
	     update_pos( fch );
	}
    }

    return;
}



/*
 * Make a corpse out of a character.
 */
/*void make_corpse( CHAR_DATA *ch )
{
    char buf[MAX_STRING_LENGTH];
    OBJ_DATA *corpse;
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;
    char *name;

    if ( IS_NPC(ch) )
    {
	name		= ch->short_descr;
	corpse		= create_object(get_obj_index(OBJ_VNUM_CORPSE_NPC), 0);
	corpse->timer	= number_range( 20, 35 );
	corpse->value[2]= ch->pIndexData->vnum;
	if ( ch->gold > 0 )
	{
	    obj_to_obj( create_money( ch->gold ), corpse );
	    ch->gold = 0;
	}
    }
    else
    {
	name		= ch->name;
	corpse		= create_object(get_obj_index(OBJ_VNUM_CORPSE_PC), 0);
	corpse->timer	= number_range( 100, 150 );
	if ( ch->gold > 0 )
	{
	    obj = create_money( ch->gold );
	    if (IS_AFFECTED(ch,AFF_SHADOWPLANE) &&
	        (!IS_SET(obj->extra_flags, ITEM_SHADOWPLANE) ) )
	        SET_BIT(obj->extra_flags, ITEM_SHADOWPLANE);
	    obj_to_obj( obj, corpse );
	    ch->gold = 0;
	}
    }

    sprintf( buf, corpse->short_descr, name );
    free_string( corpse->short_descr );
    corpse->short_descr = str_dup( buf );

    sprintf( buf, corpse->description, name );
    free_string( corpse->description );
    corpse->description = str_dup( buf );

    for ( obj = ch->carrying; obj != NULL; obj = obj_next )
    {
	obj_next = obj->next_content;

	obj_from_char( obj );
	if ( IS_SET( obj->extra_flags, ITEM_VANISH ) )
	    extract_obj( obj );
	else
	{
	    if (IS_AFFECTED(ch,AFF_SHADOWPLANE) &&
	        (!IS_SET(obj->extra_flags, ITEM_SHADOWPLANE) ) )
	        SET_BIT(obj->extra_flags, ITEM_SHADOWPLANE);
	    obj_to_obj( obj, corpse );
	}
    }

    if (IS_AFFECTED(ch, AFF_SHADOWPLANE))
	SET_BIT(corpse->extra_flags, ITEM_SHADOWPLANE);

    obj_to_room( corpse, ch->in_room );
    return;
}*/



void death_cry( CHAR_DATA *ch )
{
    ROOM_INDEX_DATA *was_in_room;
    char *msg;
    int door;

    if ( IS_NPC(ch) )
	msg = "You hear something's death cry.";
    else
	msg = "You hear someone's death cry.";

    was_in_room = ch->in_room;
    for ( door = 0; door <= 5; door++ )
    {
	EXIT_DATA *pexit;

	if ( ( pexit = was_in_room->exit[door] ) != NULL
	&&   pexit->to_room != NULL
	&&   pexit->to_room != was_in_room )
	{
	    ch->in_room = pexit->to_room;
	    act( msg, ch, NULL, NULL, TO_ROOM );
	}
    }
    ch->in_room = was_in_room;
    return;
}

void make_part( CHAR_DATA *ch, char *argument )
{
    char  arg [MAX_INPUT_LENGTH];
    int vnum;

    argument = one_argument(argument,arg);
    vnum = 0;

    if (arg[0] == '\0') return;
    if (!str_cmp(arg,"head")) vnum = OBJ_VNUM_SEVERED_HEAD;
    else if (!str_cmp(arg,"arm")) vnum = OBJ_VNUM_SLICED_ARM;
    else if (!str_cmp(arg,"leg")) vnum = OBJ_VNUM_SLICED_LEG;
    else if (!str_cmp(arg,"heart")) vnum = OBJ_VNUM_TORN_HEART;
    else if (!str_cmp(arg,"turd")) vnum = OBJ_VNUM_TORN_HEART;
    else if (!str_cmp(arg,"entrails")) vnum = OBJ_VNUM_SPILLED_ENTRAILS;
    else if (!str_cmp(arg,"brain")) vnum = OBJ_VNUM_QUIVERING_BRAIN;
    else if (!str_cmp(arg,"eyeball")) vnum = OBJ_VNUM_SQUIDGY_EYEBALL;
    else if (!str_cmp(arg,"blood")) vnum = OBJ_VNUM_SPILT_BLOOD;
    else if (!str_cmp(arg,"face")) vnum = OBJ_VNUM_RIPPED_FACE;
    else if (!str_cmp(arg,"windpipe")) vnum = OBJ_VNUM_TORN_WINDPIPE;
    else if (!str_cmp(arg,"cracked_head")) vnum = OBJ_VNUM_CRACKED_HEAD;
    else if (!str_cmp(arg,"ear")) vnum = OBJ_VNUM_SLICED_EAR;
    else if (!str_cmp(arg,"nose")) vnum = OBJ_VNUM_SLICED_NOSE;
    else if (!str_cmp(arg,"tooth")) vnum = OBJ_VNUM_KNOCKED_TOOTH;
    else if (!str_cmp(arg,"tongue")) vnum = OBJ_VNUM_TORN_TONGUE;
    else if (!str_cmp(arg,"hand")) vnum = OBJ_VNUM_SEVERED_HAND;
    else if (!str_cmp(arg,"foot")) vnum = OBJ_VNUM_SEVERED_FOOT;
    else if (!str_cmp(arg,"thumb")) vnum = OBJ_VNUM_SEVERED_THUMB;
    else if (!str_cmp(arg,"index")) vnum = OBJ_VNUM_SEVERED_INDEX;
    else if (!str_cmp(arg,"middle")) vnum = OBJ_VNUM_SEVERED_MIDDLE;
    else if (!str_cmp(arg,"ring")) vnum = OBJ_VNUM_SEVERED_RING;
    else if (!str_cmp(arg,"little")) vnum = OBJ_VNUM_SEVERED_LITTLE;
    else if (!str_cmp(arg,"toe")) vnum = OBJ_VNUM_SEVERED_TOE;

    if ( vnum != 0 )
    {
	char buf[MAX_STRING_LENGTH];
	OBJ_DATA *obj;
	char *name;

	name		= IS_NPC(ch) ? ch->short_descr : ch->name;
	obj		= create_object( get_obj_index( vnum ), 0 );
	if (IS_NPC(ch))   obj->timer = number_range(2,15);
	else              obj->timer = -1;
	if (!str_cmp(arg,"head") && IS_NPC(ch))
	    obj->value[1] = ch->pIndexData->vnum;
	else if (!str_cmp(arg,"head") && !IS_NPC(ch))
	    {ch->pcdata->chobj = obj; obj->chobj = ch;obj->timer = 
	number_range(8,14);}
	else if (!str_cmp(arg,"arm"))
	  SET_BIT(obj->extra_flags, ITEM_ARM);
	else if (!str_cmp(arg,"brain") && !IS_NPC(ch) && 
	IS_AFFECTED(ch,AFF_POLYMORPH) && IS_HEAD(ch, LOST_HEAD))
	{
	    if (ch->pcdata->chobj != NULL) ch->pcdata->chobj->chobj = NULL;
	    ch->pcdata->chobj = obj;
	    obj->chobj = ch;
	    obj->timer = number_range(2,3);
	}

	/* For blood :) KaVir */
	if (vnum == OBJ_VNUM_SPILT_BLOOD) obj->timer = 2;

	/* For voodoo dolls - KaVir */
	if (!IS_NPC(ch))
	{
	    sprintf( buf, obj->name, name );
	    free_string( obj->name );
	    obj->name = str_dup( buf );
	}
	else
	{
	    sprintf( buf, obj->name, "mob" );
	    free_string( obj->name );
	    obj->name = str_dup( buf );
	}

	sprintf( buf, obj->short_descr, name );
	free_string( obj->short_descr );
	obj->short_descr = str_dup( buf );

	sprintf( buf, obj->description, name );
	free_string( obj->description );
	obj->description = str_dup( buf );

    	if (IS_AFFECTED(ch, AFF_SHADOWPLANE))
	    SET_BIT(obj->extra_flags, ITEM_SHADOWPLANE);

	obj_to_room( obj, ch->in_room );
    }
    return;
}



void raw_kill( CHAR_DATA *victim, CHAR_DATA *ch )
{
    CHAR_DATA *mount;
  if (!IS_NPC(victim) && victim->fatal > 0) death_message(ch,victim); 
    stop_fighting( victim, TRUE );
    victim->agg = 0;
    death_cry( victim );
    make_corpse( victim );

    if ( (mount = victim->mount) != NULL)
    {
	if (victim->mounted == IS_MOUNT)
	{
	    act("$n rolls off the corpse of $N.",mount,NULL,victim,TO_ROOM);
	    act("You roll off the corpse of $N.",mount,NULL,victim,TO_CHAR);
	}
	else if (victim->mounted == IS_RIDING)
	{
	    act("$n falls off $N.",victim,NULL,mount,TO_ROOM);
	    act("You fall off $N.",victim,NULL,mount,TO_CHAR);
	}
	mount->mount    = NULL;
	victim->mount   = NULL;
	mount->mounted  = IS_ON_FOOT;
	victim->mounted = IS_ON_FOOT;
    }

    if ( IS_NPC(victim) )
    {
	victim->pIndexData->killed++;
	kill_table[URANGE(0, victim->level, MAX_LEVEL-1)].killed++;
	extract_char( victim, TRUE, FALSE );
	return;
    }

    extract_char( victim, FALSE, FALSE );
    while ( victim->affected )
	affect_remove( victim, victim->affected );
    if (IS_AFFECTED(victim,AFF_POLYMORPH) && IS_AFFECTED(victim,AFF_ETHEREAL))
    {
    	victim->affected_by	= AFF_POLYMORPH + AFF_ETHEREAL;
    }
    else if (IS_AFFECTED(victim,AFF_POLYMORPH))
    	victim->affected_by	= AFF_POLYMORPH;
    else if (IS_AFFECTED(victim,AFF_ETHEREAL))
    	victim->affected_by	= AFF_ETHEREAL;
    else
    	victim->affected_by	= 0;

    REMOVE_BIT(victim->immune, IMM_STAKE);
    REMOVE_BIT(victim->extra, TIED_UP);
    REMOVE_BIT(victim->extra, GAGGED);
    REMOVE_BIT(victim->extra, BLINDFOLDED);
    REMOVE_BIT(victim->extra, EXTRA_PREGNANT);
    REMOVE_BIT(victim->extra, EXTRA_LABOUR);
    victim->pcdata->stats[DEMON_POWER] = 0;

    victim->itemaffect	 = 0;
    victim->loc_hp[0]    = 0;
    victim->loc_hp[1]    = 0;
    victim->loc_hp[2]    = 0;
    victim->loc_hp[3]    = 0;
    victim->loc_hp[4]    = 0;
    victim->loc_hp[5]    = 0;
    victim->loc_hp[6]    = 0;
    victim->armor	 = 100;
    victim->position	 = POS_RESTING;
    victim->hit		 = UMAX( 1, victim->hit  );
    victim->mana	 = UMAX( 1, victim->mana );
    victim->move	 = UMAX( 1, victim->move );
    victim->hitroll	 = 0;
    victim->damroll	 = 0;
    victim->saving_throw = 0;
    victim->carry_weight = 0;
    victim->carry_number = 0;
    do_call(victim,"all");
    save_char_obj( victim );
    return;
}


void behead( CHAR_DATA *victim )
{
    char buf [MAX_STRING_LENGTH];
    ROOM_INDEX_DATA *location;

    if (IS_NPC(victim)) return;

    location = victim->in_room;

    stop_fighting( victim, TRUE );

    make_corpse( victim );

    extract_char( victim, FALSE, FALSE );

    char_from_room(victim);
    char_to_room(victim,location);

    if (victim == NULL)
    {bug( "Behead: Victim no longer exists.", 0 );return;}

    make_part( victim, "head" );

    while ( victim->affected )
	affect_remove( victim, victim->affected );
    if (IS_AFFECTED(victim,AFF_POLYMORPH) && IS_AFFECTED(victim,AFF_ETHEREAL))
    {
    	victim->affected_by	= AFF_POLYMORPH + AFF_ETHEREAL;
    }
    else if (IS_AFFECTED(victim,AFF_POLYMORPH))
    	victim->affected_by	= AFF_POLYMORPH;
    else if (IS_AFFECTED(victim,AFF_ETHEREAL))
    	victim->affected_by	= AFF_ETHEREAL;
    else
    	victim->affected_by	= 0;

    REMOVE_BIT(victim->immune, IMM_STAKE);
    REMOVE_BIT(victim->extra, TIED_UP);
    REMOVE_BIT(victim->extra, GAGGED);
    REMOVE_BIT(victim->extra, BLINDFOLDED);
    REMOVE_BIT(victim->extra, EXTRA_PREGNANT);
    REMOVE_BIT(victim->extra, EXTRA_LABOUR);
    victim->pcdata->stats[DEMON_POWER] = 0;

    victim->itemaffect	 = 0;
    victim->loc_hp[0]    = 0;
    victim->loc_hp[1]    = 0;
    victim->loc_hp[2]    = 0;
    victim->loc_hp[3]    = 0;
    victim->loc_hp[4]    = 0;
    victim->loc_hp[5]    = 0;
    victim->loc_hp[6]    = 0;
    victim->affected_by	 = 0;
    victim->armor	 = 100;
    victim->position	 = POS_STANDING;
    victim->hit		 = 1;
    victim->mana	 = UMAX( 1, victim->mana );
    victim->move	 = UMAX( 1, victim->move );
    victim->hitroll	 = 0;
    victim->damroll	 = 0;
    victim->saving_throw = 0;
    victim->carry_weight = 0;
    victim->carry_number = 0;

    SET_BIT(victim->loc_hp[0],LOST_HEAD);
    SET_BIT(victim->affected_by,AFF_POLYMORPH);
    sprintf(buf,"the severed head of %s",victim->name);
    free_string(victim->morph);
    victim->morph = str_dup(buf);
    do_call(victim,"all");
    save_char_obj( victim );
    return;
}



void group_gain( CHAR_DATA *ch, CHAR_DATA *victim )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *gch;
    CHAR_DATA *lch;
    CHAR_DATA *mount;
    int xp;
    int members;

    /*
     * Monsters don't get kill xp's or alignment changes.
     * P-killing doesn't help either.
     * Dying of mortal wounds or poison doesn't give xp to anyone!
     */
    if ( (IS_NPC(ch) && (mount = ch->mount) == NULL) || victim == ch )
	return;
    
    members = 0;
    for ( gch = ch->in_room->people; gch != NULL; gch = gch->next_in_room )
    {
	if ( is_same_group( gch, ch ) )
	    members++;
    }

    if ( members == 0 )
    {
	bug( "Group_gain: members.", members );
	members = 1;
    }

    lch = (ch->leader != NULL) ? ch->leader : ch;

    for ( gch = ch->in_room->people; gch != NULL; gch = gch->next_in_room )
    {
	OBJ_DATA *obj;
	OBJ_DATA *obj_next;

	if ( !is_same_group( gch, ch ) )
	    continue;

	xp = xp_compute( gch, victim ) / members;
	sprintf( buf, "You receive %d experience points.\n\r", xp );
	send_to_char( buf, gch );
	if ((mount = gch->mount) != NULL) send_to_char( buf, mount );
	gain_exp( gch, xp );

	for ( obj = ch->carrying; obj != NULL; obj = obj_next )
	{
	    obj_next = obj->next_content;
	    if ( obj->wear_loc == WEAR_NONE )
		continue;

	    if ( ( IS_OBJ_STAT(obj, ITEM_ANTI_EVIL)    && IS_EVIL(ch)    )
	    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_GOOD)    && IS_GOOD(ch)    )
	    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_NEUTRAL) && IS_NEUTRAL(ch) ) )
	    {
		act( "You are zapped by $p.", ch, obj, NULL, TO_CHAR );
		act( "$n is zapped by $p.",   ch, obj, NULL, TO_ROOM );
		obj_from_char( obj );
		obj_to_room( obj, ch->in_room );
	    }
	}
    }

    return;
}



/*
 * Compute xp for a kill.
 * Also adjust alignment of killer.
 * Edit this function to change xp computations.
 */
int xp_compute( CHAR_DATA *gch, CHAR_DATA *victim )
{
    int align;
    int xp;
    int extra;
    int level;
    int number;
    int vnum;
    int victim_level; /* put to stop mass exp give outs Rotain */

    xp    = 300 - URANGE( -3, 3 - (victim->level*5/3), 6 ) * 50;
    align = gch->alignment - victim->alignment;

    if (victim->level > 1000 )
	victim_level = 1000;
    else
	victim_level = victim->level;

    if (IS_HERO(gch))
    {
	/* Avatars shouldn't be able to change their alignment */
	gch->alignment  = gch->alignment;
    }
    else if ( align >  500 )
    {
	gch->alignment  = UMIN( gch->alignment + (align-500)/4,  1000 );
	xp = 5 * xp / 4;
    }
    else if ( align < -500 )
    {
	gch->alignment  = UMAX( gch->alignment + (align+500)/4, -1000 );
    }
    else
    {
	gch->alignment -= gch->alignment / 4;
	xp = 3 * xp / 4;
    }

     /* 
      * Put in mob vnum that you don't want players to gain exp for
      * Rotain
      */
    if (IS_NPC(victim) && (vnum = victim->pIndexData->vnum) > 29000)
    {
	switch (vnum)
	{
	default:
	    break;
	case 29600:
	case 30001:
	case 30006:
	case 30007:
	case 30008:
	case 30009:
        case 30000:
	    return 0;
	}
    }

    if (IS_NPC(victim) && (IS_SET(victim->act, ACT_NOEXP) || IS_IMMORTAL(gch))) 
	return .40;

    /*
     * Adjust for popularity of target:
     *   -1/8 for each target over  'par' (down to -100%)
     *   +1/8 for each target under 'par' (  up to + 25%)
     */
    level  = URANGE( 0, victim_level, MAX_LEVEL - 1 );
    number = UMAX( 1, kill_table[level].number );
    extra  = victim->pIndexData->killed - kill_table[level].killed / number;
/*  xp    -= xp * URANGE( -2, extra, 8 ) / 8;
    xp    -= xp * URANGE( -2, extra, 6 ) / 8; */

    xp    -= xp * number_range( -2, 2 ) / 8;

    xp     = number_range( xp * 3 / 4, xp * 5 / 4 );
    xp     = UMAX( 0, xp );
    xp     = (xp * (victim_level+1) * 0.50);
    xp     = xp / 2; /* Put in cause players compaling to much exp :P */

/* Newbie Exp - Shows to player on exp payout and saves to pfile

    if ( (( get_age(gch) - 17) * 2 ) < 5 ) xp = xp * 3;
 
 * Uncomment if you want it in */
    if (!IS_NPC(gch))
    {
	gch->pcdata->score[SCORE_TOTAL_LEVEL] += victim->level;
	if (victim->level > gch->pcdata->score[SCORE_HIGH_LEVEL])
	    gch->pcdata->score[SCORE_HIGH_LEVEL] += victim->level;
	if (victim->level > 950) return 0;
	gch->pcdata->score[SCORE_TOTAL_XP] += xp;
	if (xp > gch->pcdata->score[SCORE_HIGH_XP])
	    gch->pcdata->score[SCORE_HIGH_XP] += xp;
    }
//	xp = xp *4/3;
    return xp;
}



void dam_message( CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt )
{
    static char * const attack_table[] =
    {
	"hit",
	"slice",  "stab",  "slash", "whip", "claw",
	"blast",  "pound", "crush", "grep", "bite",
	"pierce", "suck"
    };
    static char * const attack_table2[] =
    {
	"hits",
	"slices",  "stabs",  "slashes", "whips", "claws",
	"blasts",  "pounds", "crushes", "greps", "bites",
	"pierces", "sucks"
    };

    char buf1[512], buf2[512], buf3[512];
    const char *vs;
    const char *vp;
    const char *attack;
    const char *attack2;
    int damp;
    int bodyloc;
    bool critical = FALSE;
    char punct;

  if ( dt >= TYPE_ADD_AGG ) 
    {
	dt -= TYPE_ADD_AGG;
	while ( dt >= TYPE_ADD_AGG ) dt -= TYPE_ADD_AGG;
    }


         if ( dam ==   0 ) { vs = " miss";	vp = " misses";		}
    else if ( dam <=  50 ) { vs = " lightly";	vp = " lightly";	}
    else if ( dam <= 100 ) { vs = "";		vp = "";		}
    else if ( dam <= 250 ) { vs = " hard";	vp = " hard";		}
    else if ( dam <= 500 ) { vs = " very hard";	vp = " very hard";	}
    else if ( dam <= 750 ) { vs = " extremely hard";vp = " extremely hard";}
    else                   { vs = " incredibly hard";vp = " incredibly hard";}
    /* If victim's hp are less/equal to 'damp', attacker gets a death blow */
    if (IS_NPC(victim)) damp = 0;
    else                damp = -10;
    if ( (victim->hit - dam > damp ) || (dt >= 0 && dt < MAX_SKILL) ||
	(IS_NPC(victim) && IS_SET(victim->act, ACT_NOPARTS)) )
    {
    	punct   = (dam <= 250) ? '.' : '!';

    	if ( dt == TYPE_HIT && !IS_NPC(ch) && !IS_VAMPAFF(ch,VAM_CLAWS) )
    	{
	    if (dam == 0)
	    {
	    	sprintf( buf1, "$n%s $N%c",  vp, punct );
	    	sprintf( buf2, "You%s $N%c", vs, punct );
	    	sprintf( buf3, "$n%s you%c", vp, punct );
	    }
	    else
	    {
	    	sprintf( buf1, "$n hits $N%s%c",  vp, punct );
	    	sprintf( buf2, "You hit $N%s%c[%d]", vs, punct, dam );
	    	sprintf( buf3, "$n hits you%s%c[%d]", vp, punct, dam );
		critical = TRUE;
	    }
    	}
    	else
    	{
	    if ( dt == TYPE_HIT && !IS_NPC(ch) && IS_VAMPAFF(ch,VAM_CLAWS))
	    {
	    	attack  = attack_table[dt - TYPE_HIT + 5];
	    	attack2 = attack_table2[dt - TYPE_HIT + 5];
	    }
	    else if ( dt >= 0 && dt < MAX_SKILL )
	    {
	    	attack = skill_table[dt].noun_damage;
	    	attack2 = skill_table[dt].noun_damage;
	    }
	    else if ( dt >= TYPE_HIT
	    && dt < TYPE_HIT + sizeof(attack_table)/sizeof(attack_table[0]) )
	    {
	    	attack  = attack_table[dt - TYPE_HIT];
	    	attack2 = attack_table2[dt - TYPE_HIT];
	    }
	    else
	    {/*
	        bug( "Dam_mes\sage: bad dt %d.", dt );
	       */ dt  = TYPE_HIT;
	        attack  = attack_table[0];
	        attack2 = attack_table2[0];
	    }

	    if (dam == 0)
	    {
	    	sprintf( buf1, "$n's %s%s $N%c",  attack, vp, punct );
	    	sprintf( buf2, "Your %s%s $N%c",  attack, vp, punct );
	    	sprintf( buf3, "$n's %s%s you%c", attack, vp, punct );
	    }
		 else if (IS_SET(ch->newbits, NEW_MONKFLAME) && (dam == 0))
	    {
	    	sprintf( buf1, "$n's flaming %s%s $N%c[%d]", attack2, vp, punct, dam );
	    	sprintf( buf2, "Your flaming %s%s $N%c[%d]",  attack, vp, punct, dam );
	    	sprintf( buf3, "$n's flaming %s%s you%c[%d]", attack2, vp, punct, dam );
	    }
       


	    else
	    {
		if ( dt >= 0 && dt < MAX_SKILL )
		{
	    	    sprintf( buf1, "$n's %s strikes $N%s%c", attack2, vp, punct );
	    	    sprintf( buf2, "Your %s strikes $N%s%c[%d]",  attack, vp, punct, dam );
	    	    sprintf( buf3, "$n's %s strikes you%s%c[%d]", attack2, vp, punct, dam );
		}
	else if (IS_SET(ch->newbits, NEW_MONKFLAME))
            {
                sprintf( buf1, "$n's flaming %s hits $N%s%c[%d]", attack2, vp, punct, dam);
                sprintf( buf2, "Your flaming %s hits $N%s%c[%d]", attack, vp, punct, dam);
                sprintf( buf3, "$n's flaming %s hits you%s%c[%d]", attack2, vp, punct, dam);
            }


		else
		{
	    	    sprintf( buf1, "$n %s $N%s%c",  attack2, vp, punct );
	    	    sprintf( buf2, "You %s $N%s%c[%d]",  attack, vp, punct, dam );
	    	    sprintf( buf3, "$n %s you%s%c[%d]", attack2, vp, punct, dam );
		    critical = TRUE;
		}
	    }
        }
        act( buf1, ch, NULL, victim, TO_NOTVICT );
        act( buf2, ch, NULL, victim, TO_CHAR );
        act( buf3, ch, NULL, victim, TO_VICT );
	if (critical) critical_hit(ch,victim,dt,dam);
	return;
    }

    if ( dt == TYPE_HIT && !IS_NPC( ch ) && !IS_VAMPAFF(ch,VAM_CLAWS) 
	&&!IS_VAMPAFF(ch,VAM_FANGS))
    {
	damp=number_range(1,5);
	if ( damp == 1 )
	{
	    act("You ram your fingers into $N's eye sockets and rip $S face off.", ch, NULL, victim, TO_CHAR);
	    act("$n rams $s fingers into $N's eye sockets and rips $S face off.", ch, NULL, victim, TO_NOTVICT);
	    act("$n rams $s fingers into your eye sockets and rips your face off.", ch, NULL, victim, TO_VICT);
	    victim->fatal = 21;
	    make_part(victim,"face");
	}
	else if ( damp == 2 )
	{
	    act("You grab $N by the throat and tear $S windpipe out.", ch, NULL, victim, TO_CHAR);
	    act("$n grabs $N by the throat and tears $S windpipe out.", ch, NULL, victim, TO_NOTVICT);
	    act("$n grabs you by the throat and tears your windpipe out.", ch, NULL, victim, TO_VICT);
	    victim->fatal = 22;
            make_part(victim,"windpipe");
	}
	else if ( damp == 3 )
	{
	    act("You punch your fist through $N's stomach and rip out $S entrails.", ch, NULL, victim, TO_CHAR);
	    act("$n punches $s fist through $N's stomach and rips out $S entrails.", ch, NULL, victim, TO_NOTVICT);
	    act("$n punches $s fist through your stomach and rips out your entrails.", ch, NULL, victim, TO_VICT);
	    victim->fatal = 23;
             make_part(victim,"entrails");
	}
	else if ( damp == 4 )
	{
	    if (!IS_BODY(victim,BROKEN_SPINE))
		SET_BIT(victim->loc_hp[1],BROKEN_SPINE);
	    act("You hoist $N above your head and slam $M down upon your knee.\n\rThere is a loud cracking sound as $N's spine snaps.", ch, NULL, victim, TO_CHAR);
	    act("$n hoists $N above $s head and slams $M down upon $s knee.\n\rThere is a loud cracking sound as $N's spine snaps.", ch, NULL, victim, TO_NOTVICT);
	    act("$n hoists you above $s head and slams you down upon $s knee.\n\rThere is a loud cracking sound as your spine snaps.", ch, NULL, victim, TO_VICT);
            victim->fatal = 24;
	}
	else if ( damp == 5 )
	{
	    act("You lock your arm around $N's head, and give it a vicious twist.", ch, NULL, victim, TO_CHAR);
	    act("$n locks $s arm around $N's head, and gives it a vicious twist.", ch, NULL, victim, TO_NOTVICT);
	    act("$n locks $s arm around your head, and gives it a vicious twist.", ch, NULL, victim, TO_VICT);
	    if (!IS_BODY(victim,BROKEN_NECK))
	    {
		act("There is a loud snapping noise as your neck breaks.", victim, NULL, NULL, TO_CHAR);
		act("There is a loud snapping noise as $n's neck breaks.", victim, NULL, NULL, TO_ROOM);
		SET_BIT(victim->loc_hp[1],BROKEN_NECK);
	    }
            victim->fatal = 25;
	}
	return;
    }
    if ( dt >= 0 && dt < MAX_SKILL )
	attack = skill_table[dt].noun_damage;
    else if ( dt >= TYPE_HIT
    && dt < TYPE_HIT + sizeof(attack_table)/sizeof(attack_table[0]) )
	attack = attack_table[dt - TYPE_HIT];
    else
    {
	dt  = TYPE_HIT;
	attack  = attack_table[0];
    }

    if (!str_cmp(attack,"slash") || !str_cmp(attack,"slice"))
    {
	damp=number_range(1,8);
	if ( damp == 1 )
	{
	    act("You swing your blade in a low arc, rupturing $N's abdominal cavity.\n\r$S entrails spray out over a wide area.", ch, NULL, victim, TO_CHAR);
	    act("$n swings $s blade in a low arc, rupturing $N's abdominal cavity.\n\r$S entrails spray out over a wide area.", ch, NULL, victim, TO_NOTVICT);
	    act("$n swings $s blade in a low arc, rupturing your abdominal cavity.\n\rYour entrails spray out over a wide area.", ch, NULL, victim, TO_VICT);
            victim->fatal = 26;
	    make_part(victim,"entrails");
	}
	else if ( damp == 2 )
	{
	    act("You thrust your blade into $N's mouth and twist it viciously.\n\rThe end of your blade bursts through the back of $S head.", ch, NULL, victim, TO_CHAR);
	    act("$n thrusts $s blade into $N's mouth and twists it viciously.\n\rThe end of the blade bursts through the back of $N's head.", ch, NULL, victim, TO_NOTVICT);
	    act("$n thrusts $s blade into your mouth and twists it viciously.\n\rYou feel the end of the blade burst through the back of your head.", ch, NULL, victim, TO_VICT);
            victim->fatal = 27;
	}
	else if ( damp == 3 )
	{
	    if (!IS_BODY(victim,CUT_THROAT))
		SET_BIT(victim->loc_hp[1],CUT_THROAT);
	    if (!IS_BLEEDING(victim,BLEEDING_THROAT))
	    	SET_BIT(victim->loc_hp[6],BLEEDING_THROAT);
	    act("Your blow slices open $N's carotid artery, spraying blood everywhere.", ch, NULL, victim, TO_CHAR);
	    act("$n's blow slices open $N's carotid artery, spraying blood everywhere.", ch, NULL, victim, TO_NOTVICT);
	    act("$n's blow slices open your carotid artery, spraying blood everywhere.", ch, NULL, victim, TO_VICT);
            victim->fatal = 28;
	    make_part(victim,"blood");
	}
	else if ( damp == 4 )
	{
	    if (!IS_BODY(victim,CUT_THROAT))
		SET_BIT(victim->loc_hp[1],CUT_THROAT);
	    if (!IS_BLEEDING(victim,BLEEDING_THROAT))
	    	SET_BIT(victim->loc_hp[6],BLEEDING_THROAT);
	    act("You swing your blade across $N's throat, showering the area with blood.", ch, NULL, victim, TO_CHAR);
	    act("$n swings $s blade across $N's throat, showering the area with blood.", ch, NULL, victim, TO_NOTVICT);
	    act("$n swings $s blade across your throat, showering the area with blood.", ch, NULL, victim, TO_VICT);
                        victim->fatal = 29;	
           make_part(victim,"blood");
	}
	else if ( damp == 5 )
	{
	    if (!IS_HEAD(victim,BROKEN_SKULL))
	    {
	    	act("You swing your blade down upon $N's head, splitting it open.\n\r$N's brains pour out of $S forehead.", ch, NULL, victim, TO_CHAR);
	    	act("$n swings $s blade down upon $N's head, splitting it open.\n\r$N's brains pour out of $S forehead.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n swings $s blade down upon your head, splitting it open.\n\rYour brains pour out of your forehead.", ch, NULL, victim, TO_VICT);
            victim->fatal = 30;
	    	make_part(victim,"brain");
		SET_BIT(victim->loc_hp[0],BROKEN_SKULL);

	    }
	    else
	    {
		act("You plunge your blade deep into $N's chest.", ch, NULL, victim, TO_CHAR);
		act("$n plunges $s blade deep into $N's chest.", ch, NULL, victim, TO_NOTVICT);
		act("$n plunges $s blade deep into your chest.", ch, NULL, victim, TO_VICT);
            victim->fatal = 31;
	    }
	}
	else if ( damp == 6 )
	{
	    act("You swing your blade between $N's legs, nearly splitting $M in half.", ch, NULL, victim, TO_CHAR);
	    act("$n swings $s blade between $N's legs, nearly splitting $M in half.", ch, NULL, victim, TO_NOTVICT);
	    act("$n swings $s blade between your legs, nearly splitting you in half.", ch, NULL, victim, TO_VICT);
            victim->fatal = 32;
	}
	else if ( damp == 7 )
	{
	    if (!IS_ARM_L(victim,LOST_ARM))
	    {
	    	act("You swing your blade in a wide arc, slicing off $N's arm.", ch, NULL, victim, TO_CHAR);
	    	act("$n swings $s blade in a wide arc, slicing off $N's arm.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n swings $s blade in a wide arc, slicing off your arm.", ch, NULL, victim, TO_VICT);
            victim->fatal = 33;
	    	make_part(victim,"arm");
		SET_BIT(victim->loc_hp[2],LOST_ARM);
		if (!IS_BLEEDING(victim,BLEEDING_ARM_L))
		    SET_BIT(victim->loc_hp[6],BLEEDING_ARM_L);
		if (IS_BLEEDING(victim,BLEEDING_HAND_L))
		    REMOVE_BIT(victim->loc_hp[6],BLEEDING_HAND_L);
	    }
	    else if (!IS_ARM_R(victim,LOST_ARM))
	    {
	    	act("You swing your blade in a wide arc, slicing off $N's arm.", ch, NULL, victim, TO_CHAR);
	    	act("$n swings $s blade in a wide arc, slicing off $N's arm.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n swings $s blade in a wide arc, slicing off your arm.", ch, NULL, victim, TO_VICT);
            victim->fatal = 33;
	    	make_part(victim,"arm");
		SET_BIT(victim->loc_hp[3],LOST_ARM);
		if (!IS_BLEEDING(victim,BLEEDING_ARM_R))
		    SET_BIT(victim->loc_hp[6],BLEEDING_ARM_R);
		if (IS_BLEEDING(victim,BLEEDING_HAND_R))
		    REMOVE_BIT(victim->loc_hp[6],BLEEDING_HAND_R);
	    }
	    else
	    {
		act("You plunge your blade deep into $N's chest.", ch, NULL, victim, TO_CHAR);
		act("$n plunges $s blade deep into $N's chest.", ch, NULL, victim, TO_NOTVICT);
		act("$n plunges $s blade deep into your chest.", ch, NULL, victim, TO_VICT);
            victim->fatal = 31;
	    }
	}
	else if ( damp == 8 )
	{
	    if (!IS_LEG_L(victim,LOST_LEG))
	    {
	    	act("You swing your blade in a low arc, slicing off $N's leg at the hip.", ch, NULL, victim, TO_CHAR);
	    	act("$n swings $s blade in a low arc, slicing off $N's leg at the hip.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n swings $s blade in a wide arc, slicing off your leg at the hip.", ch, NULL, victim, TO_VICT);
		            victim->fatal = 34;	 
                	make_part(victim,"leg");
		SET_BIT(victim->loc_hp[4],LOST_LEG);
		if (!IS_BLEEDING(victim,BLEEDING_LEG_L))
		    SET_BIT(victim->loc_hp[6],BLEEDING_LEG_L);
		if (IS_BLEEDING(victim,BLEEDING_FOOT_L))
		    REMOVE_BIT(victim->loc_hp[6],BLEEDING_FOOT_L);
	    }
	    else if (!IS_LEG_R(victim,LOST_LEG))
	    {
	    	act("You swing your blade in a low arc, slicing off $N's leg at the hip.", ch, NULL, victim, TO_CHAR);
	    	act("$n swings $s blade in a low arc, slicing off $N's leg at the hip.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n swings $s blade in a wide arc, slicing off your leg at the hip.", ch, NULL, victim, TO_VICT);
            victim->fatal = 34;
	    	make_part(victim,"leg");

		SET_BIT(victim->loc_hp[5],LOST_LEG);
		if (!IS_BLEEDING(victim,BLEEDING_LEG_R))
		    SET_BIT(victim->loc_hp[6],BLEEDING_LEG_R);
		if (IS_BLEEDING(victim,BLEEDING_FOOT_R))
		    REMOVE_BIT(victim->loc_hp[6],BLEEDING_FOOT_R);
	    }
	    else
	    {
		act("You plunge your blade deep into $N's chest.", ch, NULL, victim, TO_CHAR);
		act("$n plunges $s blade deep into $N's chest.", ch, NULL, victim, TO_NOTVICT);
		act("$n plunges $s blade deep into your chest.", ch, NULL, victim, TO_VICT);
            victim->fatal = 31;
	    }
	}
    }
    else if (!str_cmp(attack,"stab") || !str_cmp(attack,"pierce"))
    {
	damp=number_range(1,5);
	if ( damp == 1 )
	{
	    act("You defty invert your weapon and plunge it point first into $N's chest.\n\rA shower of blood sprays from the wound, showering the area.", ch, NULL, victim, TO_CHAR);
	    act("$n defty inverts $s weapon and plunge it point first into $N's chest.\n\rA shower of blood sprays from the wound, showering the area.", ch, NULL, victim, TO_NOTVICT);
	    act("$n defty inverts $s weapon and plunge it point first into your chest.\n\rA shower of blood sprays from the wound, showering the area.", ch, NULL, victim, TO_VICT);
            victim->fatal = 31;
	    make_part(victim,"blood");
	}
	else if ( damp == 2 )
	{
	    act("You thrust your blade into $N's mouth and twist it viciously.\n\rThe end of your blade bursts through the back of $S head.", ch, NULL, victim, TO_CHAR);
	    act("$n thrusts $s blade into $N's mouth and twists it viciously.\n\rThe end of the blade bursts through the back of $N's head.", ch, NULL, victim, TO_NOTVICT);
	    act("$n thrusts $s blade into your mouth and twists it viciously.\n\rYou feel the end of the blade burst through the back of your head.", ch, NULL, victim, TO_VICT);
            victim->fatal = 35;
	}
	else if ( damp == 3 )
	{
	    act("You thrust your weapon up under $N's jaw and through $S head.", ch, NULL, victim, TO_CHAR);
	    act("$n thrusts $s weapon up under $N's jaw and through $S head.", ch, NULL, victim, TO_NOTVICT);
	    act("$n thrusts $s weapon up under your jaw and through your head.", ch, NULL, victim, TO_VICT);
            victim->fatal = 27;
	}
	else if ( damp == 4 )
	{
	    act("You ram your weapon through $N's body, pinning $M to the ground.", ch, NULL, victim, TO_CHAR);
	    act("$n rams $s weapon through $N's body, pinning $M to the ground.", ch, NULL, victim, TO_NOTVICT);
	    act("$n rams $s weapon through your body, pinning you to the ground.", ch, NULL, victim, TO_VICT);
            victim->fatal = 31;

	}
	else if ( damp == 5 )
	{
	    act("You stab your weapon into $N's eye and out the back of $S head.", ch, NULL, victim, TO_CHAR);
	    act("$n stabs $s weapon into $N's eye and out the back of $S head.", ch, NULL, victim, TO_NOTVICT);
	    act("$n stabs $s weapon into your eye and out the back of your head.", ch, NULL, victim, TO_VICT);
            victim->fatal = 36;
	    if (!IS_HEAD(victim,LOST_EYE_L) && number_percent() < 50)
		SET_BIT(victim->loc_hp[0],LOST_EYE_L);
	    else if (!IS_HEAD(victim,LOST_EYE_R))
		SET_BIT(victim->loc_hp[0],LOST_EYE_R);
	    else if (!IS_HEAD(victim,LOST_EYE_L))
		SET_BIT(victim->loc_hp[0],LOST_EYE_L);
	}
    }
    else if (!str_cmp(attack,"blast") || (!str_cmp(attack,"pound") || !str_cmp(attack,"crush")))
    {
	damp=number_range(1,3);
	bodyloc = 0;
	if ( damp == 1)
	{
	    act("Your blow smashes through $N's chest, caving in half $S ribcage.", ch, NULL, victim, TO_CHAR);
	    act("$n's blow smashes through $N's chest, caving in half $S ribcage.", ch, NULL, victim, TO_NOTVICT);
	    act("$n's blow smashes through your chest, caving in half your ribcage.", ch, NULL, victim, TO_VICT);
            victim->fatal = 37;
	    if (IS_BODY(victim,BROKEN_RIBS_1 )) {bodyloc += 1;
		REMOVE_BIT(victim->loc_hp[1],BROKEN_RIBS_1);}
	    if (IS_BODY(victim,BROKEN_RIBS_2 )) {bodyloc += 2;
		REMOVE_BIT(victim->loc_hp[1],BROKEN_RIBS_2);}
	    if (IS_BODY(victim,BROKEN_RIBS_4 )) {bodyloc += 4;
		REMOVE_BIT(victim->loc_hp[1],BROKEN_RIBS_4);}
	    if (IS_BODY(victim,BROKEN_RIBS_8 )) {bodyloc += 8;
		REMOVE_BIT(victim->loc_hp[1],BROKEN_RIBS_8);}
	    if (IS_BODY(victim,BROKEN_RIBS_16)) {bodyloc += 16;
		REMOVE_BIT(victim->loc_hp[1],BROKEN_RIBS_16);}
	    bodyloc += number_range(1,3);
	    if (bodyloc > 24) bodyloc = 24;
	    if (bodyloc >= 16) {bodyloc -= 16;
		SET_BIT(victim->loc_hp[1],BROKEN_RIBS_16);}
	    if (bodyloc >= 8) {bodyloc -= 8;
		SET_BIT(victim->loc_hp[1],BROKEN_RIBS_8);}
	    if (bodyloc >= 4) {bodyloc -= 4;
		SET_BIT(victim->loc_hp[1],BROKEN_RIBS_4);}
	    if (bodyloc >= 2) {bodyloc -= 2;
		SET_BIT(victim->loc_hp[1],BROKEN_RIBS_2);}
	    if (bodyloc >= 1) {bodyloc -= 1;
		SET_BIT(victim->loc_hp[1],BROKEN_RIBS_1);}
	}
	else if ( damp == 2)
	{
	    act("Your blow smashes $N's spine, shattering it in several places.", ch, NULL, victim, TO_CHAR);
	    act("$n's blow smashes $N's spine, shattering it in several places.", ch, NULL, victim, TO_NOTVICT);
	    act("$n's blow smashes your spine, shattering it in several places.", ch, NULL, victim, TO_VICT);
            victim->fatal = 38;
	    if (!IS_BODY(victim,BROKEN_SPINE))
		SET_BIT(victim->loc_hp[1],BROKEN_SPINE);
	}
	else if ( damp == 3)
	{
	    if (!IS_HEAD(victim,BROKEN_SKULL))
	    {
	    	act("You swing your weapon down upon $N's head.\n\r$N's head cracks open like an overripe melon, leaking out brains.", ch, NULL, victim, TO_CHAR);
	    	act("$n swings $s weapon down upon $N's head.\n\r$N's head cracks open like an overripe melon, covering you with brains.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n swings $s weapon down upon your head.\n\rYour head cracks open like an overripe melon, spilling your brains everywhere.", ch, NULL, victim, TO_VICT);
            victim->fatal = 30;
	    	make_part(victim,"brain");
		SET_BIT(victim->loc_hp[0],BROKEN_SKULL);
	    }
	    else
	    {
	    	act("You hammer your weapon into $N's side, crushing bone.", ch, NULL, victim, TO_CHAR);
	    	act("$n hammers $s weapon into $N's side, crushing bone.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n hammers $s weapon into your side, crushing bone.", ch, NULL, victim, TO_VICT);
                 victim->fatal = 37;
	    }
	}
    }
    else if ( !IS_NPC( ch ) && (!str_cmp(attack,"bite") ||IS_VAMPAFF(ch,VAM_FANGS)))
    {
	act("You sink your teeth into $N's throat and tear out $S jugular vein.\n\rYou wipe the blood from your chin with one hand.", ch, NULL, victim, TO_CHAR);
	act("$n sink $s teeth into $N's throat and tears out $S jugular vein.\n\r$n wipes the blood from $s chin with one hand.", ch, NULL, victim, TO_NOTVICT);
	act("$n sink $s teeth into your throat and tears out your jugular vein.\n\r$n wipes the blood from $s chin with one hand.", ch, NULL, victim, TO_VICT);
	make_part(victim,"blood");
            victim->fatal = 39;
	if (!IS_BODY(victim,CUT_THROAT))
	    SET_BIT(victim->loc_hp[1],CUT_THROAT);
	if (!IS_BLEEDING(victim,BLEEDING_THROAT))
	    SET_BIT(victim->loc_hp[6],BLEEDING_THROAT);
    }
    else if ( !IS_NPC(ch) && (!str_cmp(attack,"claw") || IS_VAMPAFF(ch,VAM_CLAWS)))
    {
	damp=number_range(1,2);
	if ( damp == 1 )
	{
	    act("You tear out $N's throat, showering the area with blood.", ch, NULL, victim, TO_CHAR);
	    act("$n tears out $N's throat, showering the area with blood.", ch, NULL, victim, TO_NOTVICT);
	    act("$n tears out your throat, showering the area with blood.", ch, NULL, victim, TO_VICT);
	    make_part(victim,"blood");
            victim->fatal = 40;
	    if (!IS_BODY(victim,CUT_THROAT))
		SET_BIT(victim->loc_hp[1],CUT_THROAT);
	    if (!IS_BLEEDING(victim,BLEEDING_THROAT))
	    	SET_BIT(victim->loc_hp[6],BLEEDING_THROAT);
	}
	if ( damp == 2 )
	{
	    if (!IS_HEAD(victim,LOST_EYE_L) && number_percent() < 50)
	    {
	    	act("You rip an eyeball from $N's face.", ch, NULL, victim, TO_CHAR);
	    	act("$n rips an eyeball from $N's face.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n rips an eyeball from your face.", ch, NULL, victim, TO_VICT);
	    	make_part(victim,"eyeball");
            victim->fatal = 41;
		SET_BIT(victim->loc_hp[0],LOST_EYE_L);
	    }
	    else if (!IS_HEAD(victim,LOST_EYE_R))
	    {
	    	act("You rip an eyeball from $N's face.", ch, NULL, victim, TO_CHAR);
	    	act("$n rips an eyeball from $N's face.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n rips an eyeball from your face.", ch, NULL, victim, TO_VICT);
	    	make_part(victim,"eyeball");
            victim->fatal = 41;
		SET_BIT(victim->loc_hp[0],LOST_EYE_R);
	    }
	    else if (!IS_HEAD(victim,LOST_EYE_L))
	    {
	    	act("You rip an eyeball from $N's face.", ch, NULL, victim, TO_CHAR);
	    	act("$n rips an eyeball from $N's face.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n rips an eyeball from your face.", ch, NULL, victim, TO_VICT);
	    	make_part(victim,"eyeball");
            victim->fatal = 41;
		SET_BIT(victim->loc_hp[0],LOST_EYE_L);
	    }
	    else
	    {
	    	act("You claw open $N's chest.", ch, NULL, victim, TO_CHAR);
	    	act("$n claws open $N's chest.", ch, NULL, victim, TO_NOTVICT);
	    	act("$n claws open $N's chest.", ch, NULL, victim, TO_VICT);
            victim->fatal = 42;
	    }
	}
    }
    else if (!str_cmp(attack,"whip"))
    {
	act("You entangle $N around the neck, and squeeze the life out of $S.", ch, NULL, victim, TO_CHAR);
	act("$n entangle $N around the neck, and squeezes the life out of $S.", ch, NULL, victim, TO_NOTVICT);
	act("$n entangles you around the neck, and squeezes the life out of you.", ch, NULL, victim, TO_VICT);
            victim->fatal = 25;
	if (!IS_BODY(victim,BROKEN_NECK))
	    SET_BIT(victim->loc_hp[1],BROKEN_NECK);
    }
    else if (!str_cmp(attack,"suck") || !str_cmp(attack,"grep"))
    {
	act("You place your weapon on $N's head and suck out $S brains.", ch, NULL, victim, TO_CHAR);
	act("$n places $s weapon on $N's head and suck out $S brains.", ch, NULL, victim, TO_NOTVICT);
	act("$n places $s weapon on your head and suck out your brains.", ch, NULL, victim, TO_VICT);
            victim->fatal = 43;
    }
    else
    {
	/*bug( "Dam_message: bad dt %d.", dt );*/
    }
    return;
}



/*
 * Disarm a creature.
 * Caller must check for successful attack.
 */
void disarm( CHAR_DATA *ch, CHAR_DATA *victim )
{
    OBJ_DATA *obj;
    char buf [MAX_STRING_LENGTH];

    /* I'm fed up of being disarmed every 10 seconds - KaVir */
    if (IS_NPC(ch) && victim->level > 2 && number_percent() > 5)
	return;

    if (!IS_NPC(victim) && IS_IMMUNE(victim, IMM_DISARM) &&
!IS_SET(ch->warp, WARP_CLUMSY))
	return;
/*
    if ( ( (obj = get_eq_char( ch, WEAR_WIELD ) == NULL) || obj->item_type != ITEM_WEAPON )
    &&   ( (obj = get_eq_char( ch, WEAR_HOLD  ) == NULL) || obj->item_type != ITEM_WEAPON ) )
	return;
*/
    if ( ( (obj = get_eq_char( victim, WEAR_WIELD ) ) == NULL) || obj->item_type != ITEM_WEAPON )
    {
	if ( ( (obj = get_eq_char( victim, WEAR_HOLD ) ) == NULL) || obj->item_type != ITEM_WEAPON )
	return;
    }

    sprintf(buf,"$n disarms you!");
    ADD_COLOUR(ch,buf,WHITE);
    act( buf, ch, NULL, victim, TO_VICT    );
    sprintf(buf,"You disarm $N!");
    ADD_COLOUR(ch,buf,WHITE);
    act( buf,  ch, NULL, victim, TO_CHAR    );
    sprintf(buf,"$n disarms $N!");
    ADD_COLOUR(ch,buf,WHITE);
    act( buf,  ch, NULL, victim, TO_NOTVICT );

    obj_from_char( obj );

    /* Loyal weapons come back ;)  KaVir */
    if (IS_SET(obj->extra_flags, ITEM_LOYAL) && ( !IS_NPC(victim) ) )
    {
        act( "$p leaps back into your hand!", victim, obj, NULL, TO_CHAR );
        act( "$p leaps back into $n's hand!",  victim, obj, NULL, TO_ROOM );
	obj_to_char( obj, victim );
	do_wear( victim, obj->name);
    }
    else if ( IS_NPC(victim) )
	obj_to_char( obj, victim );
    else
	obj_to_room( obj, victim->in_room );

    return;
}



/*
 * Trip a creature.
 * Caller must check for successful attack.
 */
void trip( CHAR_DATA *ch, CHAR_DATA *victim )
{
    char buf [MAX_STRING_LENGTH];

    if (IS_AFFECTED(victim,AFF_FLYING))
	return;

    if (IS_NPC(ch) && victim->level > 2 && number_percent() > 5)
	return;

    if (!IS_NPC(victim))
    {
	if (IS_CLASS(victim, CLASS_VAMPIRE) && IS_VAMPAFF(victim,VAM_FLYING))
	    return;
	if (IS_CLASS(victim, CLASS_DEMON) && IS_DEMAFF(victim, DEM_UNFOLDED))
	    return;
	if (IS_SET(victim->special, SPC_CHAMPION) && IS_DEMAFF(victim,DEM_UNFOLDED))
	    return;
	if (IS_CLASS(victim, CLASS_DROW) && IS_SET(victim->pcdata->powers[1], DPOWER_LEVITATION)) return;
    }
    if ( victim->wait == 0)
    {
    	sprintf(buf,"$n trips you and you go down!");
    	ADD_COLOUR(ch,buf,WHITE);
    	act( buf, ch, NULL, victim, TO_VICT    );
    	sprintf(buf,"You trip $N and $E goes down!");
    	ADD_COLOUR(ch,buf,WHITE);
    	act( buf,  ch, NULL, victim, TO_CHAR    );
    	sprintf(buf,"$n trips $N and $E goes down!");
    	ADD_COLOUR(ch,buf,WHITE);
    	act( buf,  ch, NULL, victim, TO_NOTVICT );

	WAIT_STATE( ch,     2 * PULSE_VIOLENCE );
	WAIT_STATE( victim, 2 * PULSE_VIOLENCE );
	victim->position = POS_RESTING;
    }

    return;
}



void do_kill( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
	send_to_char( "Kill whom?\n\r", ch );
	return;
    }

if (ch->embracing!=NULL
                  || ch->embraced!=NULL)
{
stc("Not while in an embrace!\n\r",ch);
return;
}

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( victim == ch )
    {
	send_to_char( "You cannot kill yourself!\n\r", ch );
	return;
    }

    if ( is_safe( ch, victim ) )
	return;

    if ( IS_AFFECTED(ch, AFF_CHARM) && ch->master == victim )
    {
	act( "$N is your beloved master.", ch, NULL, victim, TO_CHAR );
	return;
    }

    if ( ch->position == POS_FIGHTING )
    {
	send_to_char( "You do the best you can!\n\r", ch );
	return;
    }


  if (IS_AFFECTED(ch, AFF_STEELSHIELD))
    {
        REMOVE_BIT(ch->affected_by, AFF_STEELSHIELD);
}

/* Autostancing - Loki */
    if (!IS_NPC(victim) && IS_SET(victim->extra, EXTRA_STANCE) )
    {
      if ( victim->stance[11] == STANCE_VIPER )
        do_stance(victim,"viper");
      else if ( victim->stance[11] == STANCE_CRANE )
        do_stance(victim,"crane");
      else if ( victim->stance[11] == STANCE_CRAB )
        do_stance(victim,"crab");
      else if ( victim->stance[11] == STANCE_MONGOOSE )
        do_stance(victim,"mongoose");
      else if ( victim->stance[11] == STANCE_BULL )
        do_stance(victim,"bull");
      else if ( victim->stance[11] == STANCE_MANTIS )
        do_stance(victim,"mantis");
      else if ( victim->stance[11] == STANCE_DRAGON )
        do_stance(victim,"dragon");
      else if ( victim->stance[11] == STANCE_TIGER )
        do_stance(victim,"tiger");
      else if ( victim->stance[11] == STANCE_MONKEY )
        do_stance(victim,"monkey");
      else if ( victim->stance[11] == STANCE_SWALLOW )
        do_stance(victim,"swallow");
    }

/* Autostancing - Loki */
    if (!IS_NPC(ch) && IS_SET(ch->extra, EXTRA_STANCE) )
    {
      if ( ch->stance[11] == STANCE_VIPER )
        do_stance(ch,"viper");
      else if ( ch->stance[11] == STANCE_CRANE )
        do_stance(ch,"crane");
      else if ( ch->stance[11] == STANCE_CRAB )
        do_stance(ch,"crab");
      else if ( ch->stance[11] == STANCE_MONGOOSE )
        do_stance(ch,"mongoose");
      else if ( ch->stance[11] == STANCE_BULL )
        do_stance(ch,"bull");
      else if ( ch->stance[11] == STANCE_MANTIS )
        do_stance(ch,"mantis");
      else if ( ch->stance[11] == STANCE_DRAGON )
        do_stance(ch,"dragon");
      else if ( ch->stance[11] == STANCE_TIGER )
        do_stance(ch,"tiger");
      else if ( ch->stance[11] == STANCE_MONKEY )
        do_stance(ch,"monkey");
      else if ( ch->stance[11] == STANCE_SWALLOW )
        do_stance(ch,"swallow");
    }

    WAIT_STATE( ch, 1 * PULSE_VIOLENCE );
    check_killer( ch, victim );
    if (!IS_NPC(ch) && IS_CLASS(ch, CLASS_WEREWOLF) && number_range(1,3) == 1
	&& ch->pcdata->powers[WPOWER_BOAR] > 1 && victim->position == POS_STANDING)
    {
	act("You charge into $N, knocking $M from $S feet.",ch,NULL,victim,TO_CHAR);
	act("$n charge into $N, knocking $M from $S feet.",ch,NULL,victim,TO_NOTVICT);
	act("$n charge into you, knocking you from your feet.",ch,NULL,victim,TO_VICT);
	victim->position = POS_STUNNED;
	multi_hit( ch, victim, TYPE_UNDEFINED );
	multi_hit( ch, victim, TYPE_UNDEFINED );
	return;
    }

    else if ( !IS_NPC(ch) && IS_CLASS(ch, CLASS_NINJA) && 
    		   ch->pcdata->powers[NPOWER_NINGENNO] > 1 
    		   && IS_SET(ch->act, PLR_WIZINVIS)
    		   && victim->position == POS_STANDING)
    {
	act("Your arms multiply, hitting $N many times.",ch,NULL,victim,TO_CHAR);
	act("$n's arms multiply, hitting $N many times.",ch,NULL,victim,TO_NOTVICT);
	act("$n's arms multiply, hitting you many times.",ch,NULL,victim,TO_VICT);
	multi_hit( ch, victim, TYPE_UNDEFINED );
	multi_hit( ch, victim, TYPE_UNDEFINED );
	return;
    }
    SET_BIT(ch->extra,FROUND);
    multi_hit( ch, victim, TYPE_UNDEFINED );
    return;
}

void do_circle( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *obj;

    one_argument( argument, arg );

	if (IS_NPC(ch)) return;


	if (!IS_CLASS(ch, CLASS_NINJA) && !IS_CLASS(ch, CLASS_WEREWOLF))
        {
	  send_to_char("Huh?\n\r", ch );
	  return;
        }

        if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_NINGENNO] < 6)
	{
	 stc("You have not learned this attack.",ch);
          return;
	}

	if (IS_CLASS(ch, CLASS_WEREWOLF) && ch->gifts[STARGAZERS] < 4 )
	{
	 stc("You need the fourth gift of the Stargazers to use this power.\n\r",ch);
          return;
	}

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	if (ch->fighting == NULL) {
	send_to_char( "They aren't here.\n\r", ch );
	return;}
	else victim = ch->fighting;
    }

    if ( victim == ch )
    {
	send_to_char( "How can you circle yourself?\n\r", ch );
	return;
    }

    if ( is_safe( ch, victim ) )
      return;


        if (IS_CLASS(ch, CLASS_NINJA))
{

    if ( ( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL
    ||   obj->value[3] != 11 )
    &&   ( ( obj = get_eq_char( ch, WEAR_HOLD ) ) == NULL
    ||   obj->value[3] != 11 ) )
    {
	send_to_char( "You need to wield a piercing weapon.\n\r", ch );
	return;
    }
}

    check_killer( ch, victim );
	if (number_percent() > 10)
	multi_hit( ch, victim, gsn_circle );
    else
	damage( ch, victim, 0, gsn_circle );

    WAIT_STATE( ch, 8 );
    return;
}

void do_backstab( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *obj;

    one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
	send_to_char( "Backstab whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( victim == ch )
    {
	send_to_char( "How can you sneak up on yourself?\n\r", ch );
	return;
    }

    if ( is_safe( ch, victim ) )
      return;

    if ( ( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL
    ||   obj->value[3] != 11 )
    &&   ( ( obj = get_eq_char( ch, WEAR_HOLD ) ) == NULL
    ||   obj->value[3] != 11 ) )
    {
	send_to_char( "You need to wield a piercing weapon.\n\r", ch );
	return;
    }

    if ( victim->fighting != NULL )
    {
	send_to_char( "You can't backstab a fighting person.\n\r", ch );
	return;
    }

    if ( victim->hit < victim->max_hit && !IS_CLASS(ch, CLASS_DROW))
    {
	act( "$N is hurt and suspicious ... you can't sneak up.",
	    ch, NULL, victim, TO_CHAR );
	return;
    }

    check_killer( ch, victim );
    WAIT_STATE( ch, skill_table[gsn_backstab].beats );


    if ( !IS_CLASS(ch, CLASS_DROW) && !IS_CLASS(ch, CLASS_NINJA)
	&& !IS_NPC(victim) && IS_IMMUNE(victim, IMM_BACKSTAB) )
    {
        if (( IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_NINGENNO] < 2 )
	   || (!IS_CLASS(ch, CLASS_DROW) && !IS_CLASS(ch, CLASS_NINJA)) )
          damage( ch, victim, 0, gsn_backstab );
    }
        
    else if ( !IS_AWAKE(victim)
    ||   IS_NPC(ch)
    ||   number_percent( ) < ch->pcdata->learned[gsn_backstab] )
	multi_hit( ch, victim, gsn_backstab );
    else
    {
       one_hit( ch, victim, gsn_backstab, 1 );
    }
    return;
}



void do_flee( CHAR_DATA *ch, char *argument )
{
    ROOM_INDEX_DATA *was_in;
    ROOM_INDEX_DATA *now_in;
    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH]; 
   int attempt;

    if ( ( victim = ch->fighting ) == NULL )
    {
	if ( ch->position == POS_FIGHTING )
	    ch->position = POS_STANDING;
	send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;
    }
	if(ch->move <= 0)
	{
	   send_to_char("You can't find the energy to leave.\n\r",ch);
	   return;
	}

    if (IS_AFFECTED(ch, AFF_WEBBED))
    {
	send_to_char("You are unable to move with all this sticky webbing on.\n\r",ch);
	return;
    }
    
    if ( is_garou(victim) && victim->gifts[GETOFFENRIS] >= 1 )
    {
      if ( number_range( 1, 4 ) == 2 )
      {
        stc("Gaia prevents you from fleeing her child.\n\r",ch);
        return;
      }
    }
	


 if(IS_CLASS(victim,CLASS_WEREWOLF)&&IS_SET(victim->garou1,GAROU_CLENCHED))
   if(number_range(1,6)!=1)
   {sprintf(buf,"%s's clenched teeth prevents you from fleeing.\n\r",victim->name);
    stc(buf,ch);
    return;}
	if (IS_CLASS(victim, CLASS_VAMPIRE) && IS_SET(victim->newbits,NEW_COIL) && number_percent( ) > 15)
	{
	  sprintf(buf,"Not with %s coiled around you!",victim->name);
	  send_to_char(buf,ch);
	  act("$n cant escape with $N coiled around them.",ch,NULL,victim,TO_ROOM);
	  return;
        }

	if (IS_AFFECTED(ch,AFF2_TENDRILS))
	{
	  send_to_char("You are unable to move while tangled in tendrils.\n\r",ch);
	  return;
	}

    if (!IS_NPC(ch) && ch->pcdata->stats[UNI_RAGE] >= 0)
    {
	if (IS_CLASS(ch,CLASS_VAMPIRE) && number_percent() <= ch->pcdata->stats[UNI_RAGE])
	{
	    send_to_char("Your inner beast refuses to let you run!\n\r",ch);
	    WAIT_STATE(ch,12);
	    return;
	}
	else if (IS_CLASS(ch, CLASS_WEREWOLF) && number_percent() <= ch->pcdata->stats[UNI_RAGE] * 0.3)
	{
	    send_to_char("Your rage is too great!\n\r",ch);
	    WAIT_STATE(ch,12);
	    return;
	}
    }

    was_in = ch->in_room;
    for ( attempt = 0; attempt < 6; attempt++ )
    {
	EXIT_DATA *pexit;
	int door;

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

	ch->in_room = was_in;
	act( "$n has fled!", ch, NULL, NULL, TO_ROOM );
	ch->in_room = now_in;

	if ( !IS_NPC(ch) )
	    send_to_char( "You flee from combat!  Coward!\n\r", ch );

        if ( IS_CLASS(victim, CLASS_DROW) && IS_SET(victim->in_room->room_flags, ROOM_TOTAL_DARKNESS) )
          REMOVE_BIT(victim->in_room->room_flags, ROOM_TOTAL_DARKNESS);
	if ( IS_CLASS(victim, CLASS_DROW) && IS_SET(victim->newbits, NEW_DARKNESS) )
 	{
	    stc("You leave your darkness in a panic!\n\r",ch);
	    REMOVE_BIT(victim->newbits, NEW_DARKNESS);
	    act("$N leaves $S darkness in a panic!",ch,NULL,victim,TO_NOTVICT);
	}
	stop_fighting( ch, TRUE );
	return;
    }

    send_to_char( "You were unable to escape!\n\r", ch );
    return;
}



void do_rescue( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    CHAR_DATA *fch;

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Rescue whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( victim == ch )
    {
	send_to_char( "What about fleeing instead?\n\r", ch );
	return;
    }

    if ( !IS_NPC(ch) && IS_NPC(victim) )
    {
	send_to_char( "Doesn't need your help!\n\r", ch );
	return;
    }

    if ( ch->fighting == victim )
    {
	send_to_char( "Too late.\n\r", ch );
	return;
    }

    if ( ( fch = victim->fighting ) == NULL )
    {
	send_to_char( "That person is not fighting right now.\n\r", ch );
	return;
    }

    if ( is_safe(ch, fch) || is_safe(ch, victim) ) return;

    WAIT_STATE( ch, skill_table[gsn_rescue].beats );
    if ( !IS_NPC(ch) && number_percent( ) > ch->pcdata->learned[gsn_rescue] )
    {
	send_to_char( "You fail the rescue.\n\r", ch );
	return;
    }

    act( "You rescue $N!",  ch, NULL, victim, TO_CHAR    );
    act( "$n rescues you!", ch, NULL, victim, TO_VICT    );
    act( "$n rescues $N!",  ch, NULL, victim, TO_NOTVICT );

    stop_fighting( fch, FALSE );
    stop_fighting( victim, FALSE );

    check_killer( ch, fch );
    set_fighting( ch, fch );
    set_fighting( fch, ch );

    do_humanity(ch,"");
    return;
}



void do_kick( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA *boots;
    int dam;
    int stance;
    int hitpoints;
    int chance;

      chance = number_percent();
    if ( !IS_NPC(ch)
    &&   ch->level < skill_table[gsn_kick].skill_level)
    {
	send_to_char(
	    "First you should learn to kick.\n\r", ch );
	return;
    }

if ( chance > 40 && IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp,
WARP_CLUMSY))
        {
        stc("You are so clumsy you fall on your ass trying to kick!\n\r", ch );
	ch->move -= 500;         
	return;
        }

    if ( ( victim = ch->fighting ) == NULL )
    {
	send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;
    }

    if (!IS_NPC(ch) && IS_ITEMAFF(ch, ITEMA_PEACE))
    {
	send_to_char( "You are unable to attack them.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_ITEMAFF(victim, ITEMA_PEACE))
    {
	send_to_char( "You can't seem to attack them.\n\r", ch );
	return;
    }
    
    if (!IS_NPC(ch) && IS_AFFECTED(ch, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return;
    }

    if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_SAFE) )
    {
	send_to_char( "You cannot attack people under Gaia's protection.\n\r", ch );
	return;
    }


if (is_safe(ch, victim)) return;
    WAIT_STATE( ch, skill_table[gsn_kick].beats );
    if ( IS_NPC(ch) || number_percent( ) < ch->pcdata->learned[gsn_kick] )
    	dam = number_range(1,4);
    else
    {
    	dam = 0;
    	damage( ch, victim, dam, gsn_kick );
	return;
    }

    dam += char_damroll(ch);
    if (dam == 0) dam = 1;
    if ( !IS_AWAKE(victim) )
	dam *= 2;

      if ( IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_STRONGLEGS))
{
	dam *= 1.5;
}

    if ( !IS_NPC(ch) && IS_CLASS(ch, CLASS_VAMPIRE))
{
	dam *= (ch->pcdata->powers[VAM_POTE]); 
}
	else if ( !IS_NPC(ch) && IS_CLASS(ch, CLASS_NINJA) &&
	ch->pcdata->powers[NPOWER_CHIKYU] > 2 )
	dam *= 1.1;
     /*drow*/
	 else if (!IS_NPC(victim) && IS_CLASS(victim, CLASS_DROW)) {
	if (IS_SET(victim->pcdata->powers[1], DPOWER_TOUGHSKIN))
	dam /= 3;
	}
/*drow*/
    else if ( !IS_NPC(ch) && (IS_SET(ch->special, SPC_CHAMPION) ||
	IS_CLASS(ch, CLASS_DEMON)) && 
	IS_DEMPOWER( ch, DEM_MIGHT) )
	dam *= 1.1;
if (IS_VAMPIRE(ch))
{
dam *= (ch->pcdata->powers[VAM_POTE]);  
}
    if ( !IS_NPC(victim) && IS_CLASS(victim, CLASS_WEREWOLF) )
    {
	if (IS_SET(victim->special, SPC_WOLFMAN)) dam *= 0.5;
	if (victim->pcdata->powers[WPOWER_BOAR] > 2 ) dam *= 0.5;
	if ( ( boots = get_eq_char( ch, WEAR_FEET ) ) != NULL 
	    && IS_SET(boots->spectype, SITEM_SILVER)) dam *= 2;
    }
    /* Vampires should be tougher at night and weaker during the day. */
    if ( !IS_NPC(ch) && IS_CLASS(ch, CLASS_VAMPIRE) )
    {
	if (weather_info.sunlight == SUN_LIGHT && dam > 1)
	    dam /= 1.5;
	else if (weather_info.sunlight == SUN_DARK)
	    dam *= 1.5;
    }
    if ( !IS_NPC(ch) ) dam = dam + (dam * ((ch->wpn[0]+1) / 100));

    if ( !IS_NPC(ch) )
    {
	stance = ch->stance[0];
	if ( IS_STANCE(ch, STANCE_NORMAL) ) dam *= 1.25;
	else dam = dambonus(ch,victim,dam,stance);
    }

    if ( dam <= 0 )
	dam = 1;

    hitpoints = victim->hit;
    if ( !IS_NPC(victim) && IS_IMMUNE(victim, IMM_KICK) &&
!(IS_CLASS(ch, CLASS_DEMON) && IS_DEMAFF(ch, DEM_HOOVES)))
    {
	if (IS_CLASS(ch, CLASS_DEMON) && IS_DEMAFF(ch, DEM_HOOVES))
	dam = dam /2 ;
	victim->hit += dam;
	damage( ch, victim, dam, gsn_kick );
	victim->hit = hitpoints;
    }
    else damage( ch, victim, dam, gsn_kick );
    return;
}


int dambonus( CHAR_DATA *ch, CHAR_DATA *victim, int dam, int stance)
{
    if (dam < 1) return 0;
    if (stance < 1) return dam;
    if (!IS_NPC(ch) && !can_counter(victim))
    {
	if ( IS_STANCE(ch, STANCE_MONKEY) )
	{
	    int mindam = dam * 0.25;
	    dam *= (ch->stance[STANCE_MONKEY]+1) / 200;
	    if (dam < mindam) dam = mindam;
	}
	
	else if ( IS_STANCE(ch, STANCE_MONKEY) )
	{
	    int mindam = dam * 0.25;
	    dam *= (ch->stance[STANCE_COUGAR]+3) / 200;
	    if (dam < mindam) dam = mindam;
	}
	else if ( IS_STANCE(ch, STANCE_BULL) && ch->stance[STANCE_BULL] > 100 )
	    dam += dam * (ch->stance[STANCE_BULL] / 100);
	else if ( IS_STANCE(ch, STANCE_DRAGON) && ch->stance[STANCE_DRAGON] > 100 )
	    dam += dam * (ch->stance[STANCE_DRAGON] / 100);
	    else if ( IS_STANCE(ch, STANCE_COBRA) && ch->stance[STANCE_COBRA] > 100 )
	    dam += dam * (ch->stance[STANCE_COBRA] / 150);
	else if ( IS_STANCE(ch, STANCE_TIGER) && ch->stance[STANCE_TIGER] > 100 )
	    dam += dam * (ch->stance[STANCE_TIGER] / 100);
	else if ( ch->stance[0] > 0 && ch->stance[stance] < 100 )
	    dam *= 0.5;
    }
    if (!IS_NPC(victim) && !can_counter(ch))
    {
	if ( IS_STANCE(victim, STANCE_CRAB) && victim->stance[STANCE_CRAB] > 100 )
	    dam /= victim->stance[STANCE_CRAB]/100;
	else if ( IS_STANCE(victim, STANCE_DRAGON) && victim->stance[STANCE_DRAGON] > 100 )
	    dam /= victim->stance[STANCE_DRAGON]/100;
	    else if ( IS_STANCE(victim, STANCE_COBRA) && victim->stance[STANCE_COBRA] > 100 )
	    dam /= victim->stance[STANCE_COBRA]/150;
	else if ( IS_STANCE(victim, STANCE_SWALLOW) && victim->stance[STANCE_SWALLOW] > 100 )
	    dam /= victim->stance[STANCE_SWALLOW]/100;
	    else if ( IS_STANCE(victim, STANCE_EAGLE) && victim->stance[STANCE_EAGLE] > 100 )
	    dam /= victim->stance[STANCE_EAGLE]/150;
	    else if ( IS_STANCE(victim, STANCE_BEAR) && victim->stance[STANCE_BEAR] > 100 )
	    dam /= victim->stance[STANCE_BEAR]/150;
    }
    return dam;
}



void do_punch( CHAR_DATA *ch, char *argument )
{
    char arg [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    int dam;
    int store;
    bool broke = FALSE;

    one_argument(argument,arg);

    if ( IS_NPC(ch) ) return;

    if ( ch->level < skill_table[gsn_punch].skill_level)
    {
	send_to_char( "First you should learn to punch.\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "You cannot punch yourself!\n\r", ch );
	return;
    }

    if (is_safe(ch,victim)) return;

    if ( victim->hit < victim->max_hit )
    {
	send_to_char( "They are hurt and suspicious.\n\r", ch );
	return;
    }

    if ( victim->position < POS_FIGHTING )
    {
	send_to_char( "You can only punch someone who is standing.\n\r", ch );
	return;
    }

    act("You draw your fist back and aim a punch at $N.",ch,NULL,victim,TO_CHAR);
    act("$n draws $s fist back and aims a punch at you.",ch,NULL,victim,TO_VICT);
    act("$n draws $s fist back and aims a punch at $N.",ch,NULL,victim,TO_NOTVICT);
    WAIT_STATE( ch, skill_table[gsn_punch].beats );
    if ( IS_NPC(ch) || number_percent( ) < ch->pcdata->learned[gsn_punch] )
    	dam = number_range(1,4);
    else
    {
    	dam = 0;
    	damage( ch, victim, dam, gsn_punch );
	return;
    }

    dam += char_damroll(ch);
    if (dam == 0) dam = 1;
    if ( !IS_AWAKE(victim) )
	dam *= 2;
    if ( !IS_NPC(ch) ) dam = dam + (dam * (ch->wpn[0] / 100));

    if ( dam <= 0 )
	dam = 1;

    if (!IS_NPC(victim) && IS_CLASS(victim, CLASS_WEREWOLF) && victim->pcdata->powers[WPOWER_BOAR] > 3)
    {
	store = victim->hit;
	victim->hit += dam;
	damage( ch, victim, dam, gsn_punch );
	victim->hit = store;
	if (number_percent() <= 25 && !IS_ARM_L(ch,LOST_ARM) && 
	!IS_ARM_L(ch,LOST_HAND))
	{
	    if (!IS_ARM_L(ch, LOST_FINGER_I) && !IS_ARM_L(ch, BROKEN_FINGER_I))
		{SET_BIT(ch->loc_hp[LOC_ARM_L],BROKEN_FINGER_I);broke = TRUE;}
	    if (!IS_ARM_L(ch, LOST_FINGER_M) && !IS_ARM_L(ch, BROKEN_FINGER_M))
		{SET_BIT(ch->loc_hp[LOC_ARM_L],BROKEN_FINGER_M);broke = TRUE;}
	    if (!IS_ARM_L(ch, LOST_FINGER_R) && !IS_ARM_L(ch, BROKEN_FINGER_R))
		{SET_BIT(ch->loc_hp[LOC_ARM_L],BROKEN_FINGER_R);broke = TRUE;}
	    if (!IS_ARM_L(ch, LOST_FINGER_L) && !IS_ARM_L(ch, BROKEN_FINGER_L))
		{SET_BIT(ch->loc_hp[LOC_ARM_L],BROKEN_FINGER_L);broke = TRUE;}
	    if (broke)
	    {
		act("The fingers on your left hand shatter under the impact of the blow!",ch,NULL,NULL,TO_CHAR);
		act("The fingers on $n's left hand shatter under the impact of the blow! ",ch,NULL,NULL,TO_ROOM);
	    }
	}
	else if (number_percent() <= 25 && !IS_ARM_R(ch,LOST_ARM) && 
	!IS_ARM_R(ch,LOST_HAND))
	{
	    if (!IS_ARM_R(ch, LOST_FINGER_I) && !IS_ARM_R(ch, BROKEN_FINGER_I))
		{SET_BIT(ch->loc_hp[LOC_ARM_R],BROKEN_FINGER_I);broke = TRUE;}
	    if (!IS_ARM_R(ch, LOST_FINGER_M) && !IS_ARM_R(ch, BROKEN_FINGER_M))
		{SET_BIT(ch->loc_hp[LOC_ARM_R],BROKEN_FINGER_M);broke = TRUE;}
	    if (!IS_ARM_R(ch, LOST_FINGER_R) && !IS_ARM_R(ch, BROKEN_FINGER_R))
		{SET_BIT(ch->loc_hp[LOC_ARM_R],BROKEN_FINGER_R);broke = TRUE;}
	    if (!IS_ARM_R(ch, LOST_FINGER_L) && !IS_ARM_R(ch, BROKEN_FINGER_L))
		{SET_BIT(ch->loc_hp[LOC_ARM_R],BROKEN_FINGER_L);broke = TRUE;}
	    if (broke)
	    {
		act("The fingers on your right hand shatter under the impact of the blow!",ch,NULL,NULL,TO_CHAR);
		act("The fingers on $n's right hand shatter under the impact of the blow! ",ch,NULL,NULL,TO_ROOM);
	    }
	}
	stop_fighting(victim,TRUE);
	return;
    }

    damage( ch, victim, dam, gsn_punch );
    if (victim == NULL || victim->position == POS_DEAD || dam < 1) return;
    if (victim->position == POS_FIGHTING) stop_fighting(victim,TRUE);
    if (number_percent() <= 25 && !IS_HEAD(victim,BROKEN_NOSE)
	 && !IS_HEAD(victim,LOST_NOSE))
    {
    	act("Your nose shatters under the impact of the blow!",victim,NULL,NULL,TO_CHAR);
    	act("$n's nose shatters under the impact of the blow!",victim,NULL,NULL,TO_ROOM);
	SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);
    }
    else if (number_percent() <= 25 && !IS_HEAD(victim,BROKEN_JAW))
    {
    	act("Your jaw shatters under the impact of the blow!",victim,NULL,NULL,TO_CHAR);
    	act("$n's jaw shatters under the impact of the blow!",victim,NULL,NULL,TO_ROOM);
	SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);
    }
    act("You fall to the ground stunned!",victim,NULL,NULL,TO_CHAR);
    act("$n falls to the ground stunned!",victim,NULL,NULL,TO_ROOM);
    victim->position = POS_STUNNED;
    return;
}


void do_berserk( CHAR_DATA *ch, char *argument )
{
    char       arg [MAX_INPUT_LENGTH];
    CHAR_DATA *vch;
    CHAR_DATA *vch_next;
    CHAR_DATA *mount;
    int number_hit = 0;

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if ( ch->level < skill_table[gsn_berserk].skill_level)
    {
	send_to_char( "You are not wild enough to go berserk.\n\r", ch );
	return;
    }


if (ch->embracing!=NULL
                  || ch->embraced!=NULL)
{
stc("Not while in an embrace!\n\r",ch);
return;
}

    WAIT_STATE( ch, skill_table[gsn_berserk].beats );
    if ( number_percent( ) > ch->pcdata->learned[gsn_berserk] )
    {
    	act("You rant and rave, but nothing much happens.",ch,NULL,NULL,TO_CHAR);
    	act("$n gets a wild look in $s eyes, but nothing much happens.",ch,NULL,NULL,TO_ROOM);
	return;
    }

    act("You go BERSERK!",ch,NULL,NULL,TO_CHAR);
    act("$n goes BERSERK!",ch,NULL,NULL,TO_ROOM);

/* Autostancing - Loki */
    if (!IS_NPC(ch) && IS_SET(ch->extra, EXTRA_STANCE) )
    {
      if ( ch->stance[11] == STANCE_VIPER )
        do_stance(ch,"viper");
      else if ( ch->stance[11] == STANCE_CRANE )
        do_stance(ch,"crane");
      else if ( ch->stance[11] == STANCE_CRAB )
        do_stance(ch,"crab");
      else if ( ch->stance[11] == STANCE_MONGOOSE )
        do_stance(ch,"mongoose");
      else if ( ch->stance[11] == STANCE_BULL )
        do_stance(ch,"bull");
      else if ( ch->stance[11] == STANCE_MANTIS )
        do_stance(ch,"mantis");
      else if ( ch->stance[11] == STANCE_DRAGON )
        do_stance(ch,"dragon");
      else if ( ch->stance[11] == STANCE_TIGER )
        do_stance(ch,"tiger");
      else if ( ch->stance[11] == STANCE_MONKEY )
        do_stance(ch,"monkey");
      else if ( ch->stance[11] == STANCE_SWALLOW )
        do_stance(ch,"swallow");
    }

    for ( vch = char_list; vch != NULL; vch = vch_next )
    {
	vch_next	= vch->next;
	if (number_hit > 4) continue;
	if ( vch->in_room == NULL )
	    continue;
	if ( !IS_NPC(vch) && vch->pcdata->chobj != NULL )
	    continue;
	if ( ch == vch )
	    continue;
	if ( vch->in_room == ch->in_room )
	{
	    if ( ( mount = ch->mount ) != NULL ) {if ( mount == vch ) continue;}
	    if (can_see(ch,vch))
	    {
/* Autostancing - Loki */
    if (!IS_NPC(vch) && IS_SET(vch->extra, EXTRA_STANCE) )
    {
      if ( vch->stance[11] == STANCE_VIPER )
        do_stance(vch,"viper");
      else if ( vch->stance[11] == STANCE_CRANE )
        do_stance(vch,"crane");
      else if ( vch->stance[11] == STANCE_CRAB )
        do_stance(vch,"crab");
      else if ( vch->stance[11] == STANCE_MONGOOSE )
        do_stance(vch,"mongoose");
      else if ( vch->stance[11] == STANCE_BULL )
        do_stance(vch,"bull");
      else if ( vch->stance[11] == STANCE_MANTIS )
        do_stance(vch,"mantis");
      else if ( vch->stance[11] == STANCE_DRAGON )
        do_stance(vch,"dragon");
      else if ( vch->stance[11] == STANCE_TIGER )
        do_stance(vch,"tiger");
      else if ( vch->stance[11] == STANCE_MONKEY )
        do_stance(vch,"monkey");
      else if ( vch->stance[11] == STANCE_SWALLOW )
        do_stance(vch,"swallow");
    }
		multi_hit( ch, vch, TYPE_UNDEFINED );
		number_hit++;
	    }
	}
    }

}



/* Hurl skill by KaVir */
void do_hurl( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA       *victim;
    CHAR_DATA       *mount;
    ROOM_INDEX_DATA *to_room;
    EXIT_DATA       *pexit;
    EXIT_DATA       *pexit_rev;
    char            buf       [MAX_INPUT_LENGTH];
    char            direction [MAX_INPUT_LENGTH];
    char            arg1      [MAX_INPUT_LENGTH];
    char            arg2      [MAX_INPUT_LENGTH];
    int             door;
    int             rev_dir;
    int             dam;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( !IS_NPC(ch) && ch->pcdata->learned[gsn_hurl] < 1 )
    {
	send_to_char("Maybe you should learn the skill first?\n\r",ch);
	return;
    }

    if ( arg1[0] == '\0' )
    {
	send_to_char("Who do you wish to hurl?\n\r", ch);
	return;
    }

    if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char("They are not here.\n\r", ch);
	return;
    }

    if ( victim == ch )
    {
	send_to_char( "How can you hurl yourself?\n\r", ch );
	return;
    }

    if ( is_safe( ch, victim ) )
      return;

    if ( (mount = victim->mount) != NULL && victim->mounted == IS_MOUNT)
    {
	send_to_char("But they have someone on their back!\n\r",ch);
	return;
    }
    else if ( (mount = victim->mount) != NULL && victim->mounted == IS_RIDING)
    {
	send_to_char("But they are riding!\n\r",ch);
	return;
    }

    if ( !is_garou(ch) || ( is_garou(ch) && ch->gifts[UKTENA] < 5 ) )
    {
      if ( !IS_NPC(victim) && IS_IMMUNE(victim, IMM_HURL) )
      {
  	  send_to_char("You are unable to get their feet of the ground.\n\r",ch);
	  return;
      }
    }

    if ( !is_garou(ch) || ( is_garou(ch) && ch->gifts[UKTENA] < 5 ) )
    {
      if ( IS_NPC(victim) && victim->level > 900 )
      {
	  send_to_char("You are unable to get their feet of the ground.\n\r",ch);
	  return;
      }
    }

    if ( (victim->hit < victim->max_hit)
	 || ( victim->position == POS_FIGHTING && victim->fighting != ch) )
    {
	act( "$N is hurt and suspicious, and you are unable to approach $M.",
	    ch, NULL, victim, TO_CHAR );
	return;
    }

    WAIT_STATE( ch, skill_table[gsn_hurl].beats );
    if ( !IS_NPC(ch) && number_percent( ) > ch->pcdata->learned[gsn_hurl] )
    {
	    send_to_char("You are unable to get their feet of the ground.\n\r",ch);
	    multi_hit( victim, ch, TYPE_UNDEFINED );
	    return;
    }

    rev_dir = 0;

    if ( arg2[0] == '\0' )
	door = number_range(0,3);
    else
    {
    	if      ( !str_cmp( arg2, "n" ) || !str_cmp( arg2, "north" ) )
	    door = 0;
    	else if ( !str_cmp( arg2, "e" ) || !str_cmp( arg2, "east" ) )
	    door = 1;
    	else if ( !str_cmp( arg2, "s" ) || !str_cmp( arg2, "south" ) )
	    door = 2;
    	else if ( !str_cmp( arg2, "w" ) || !str_cmp( arg2, "west" ) )
	    door = 3;
    	else
    	{
	    send_to_char("You can only hurl people north, south, east or west.\n\r", ch);
	    return;
    	}
    }

    if (door == 0) {sprintf(direction,"north");rev_dir = 2;}
    if (door == 1) {sprintf(direction,"east");rev_dir = 3;}
    if (door == 2) {sprintf(direction,"south");rev_dir = 0;}
    if (door == 3) {sprintf(direction,"west");rev_dir = 1;}

    if (( pexit = ch->in_room->exit[door]) == NULL || (to_room = pexit->to_room) == NULL)
    {
	sprintf(buf,"$n hurls $N into the %s wall.", direction);
	act(buf,ch,NULL,victim,TO_NOTVICT);
	sprintf(buf,"You hurl $N into the %s wall.", direction);
	act(buf,ch,NULL,victim,TO_CHAR);
	sprintf(buf,"$n hurls you into the %s wall.", direction);
	act(buf,ch,NULL,victim,TO_VICT);
	dam = number_range(ch->level, (ch->level * 4));
	victim->hit = victim->hit - dam;
	update_pos(victim);
    	if (IS_NPC(victim) && !IS_NPC(ch)) ch->mkill = ch->mkill + 1;
    	if (!IS_NPC(victim) && IS_NPC(ch)) victim->mdeath = victim->mdeath + 1;
	if (victim->position == POS_DEAD) {raw_kill(victim, ch);return;}
	return;
    }

    pexit = victim->in_room->exit[door];
    if (IS_SET(pexit->exit_info, EX_CLOSED) && 
	!IS_AFFECTED(victim,AFF_PASS_DOOR ) &&
	!IS_AFFECTED(victim,AFF_ETHEREAL  ) )
    {
	if (IS_SET(pexit->exit_info, EX_LOCKED))
	    REMOVE_BIT(pexit->exit_info, EX_LOCKED);
	if (IS_SET(pexit->exit_info, EX_CLOSED))
	    REMOVE_BIT(pexit->exit_info, EX_CLOSED);
	sprintf(buf,"$n hoists $N in the air and hurls $M %s.", direction);
	act(buf,ch,NULL,victim,TO_NOTVICT);
	sprintf(buf,"You hoist $N in the air and hurl $M %s.", direction);
	act(buf,ch,NULL,victim,TO_CHAR);
	sprintf(buf,"$n hurls you %s, smashing you through the %s.", direction,pexit->keyword);
	act(buf,ch,NULL,victim,TO_VICT);
	sprintf(buf,"There is a loud crash as $n smashes through the $d.");
	act(buf,victim,NULL,pexit->keyword,TO_ROOM);

	if ( ( to_room   = pexit->to_room               ) != NULL
	&&   ( pexit_rev = to_room->exit[rev_dir] ) != NULL
	&&   pexit_rev->to_room == ch->in_room
	&&   pexit_rev->keyword != NULL )
	{
	    if (IS_SET(pexit_rev->exit_info, EX_LOCKED))
		REMOVE_BIT( pexit_rev->exit_info, EX_LOCKED );
	    if (IS_SET(pexit_rev->exit_info, EX_CLOSED))
		REMOVE_BIT( pexit_rev->exit_info, EX_CLOSED );
	    if (door == 0) sprintf(direction,"south");
	    if (door == 1) sprintf(direction,"west");
	    if (door == 2) sprintf(direction,"north");
	    if (door == 3) sprintf(direction,"east");
	    char_from_room(victim);
	    char_to_room(victim,to_room);
	    sprintf(buf,"$n comes smashing in through the %s $d.", direction);
	    act(buf,victim,NULL,pexit->keyword,TO_ROOM);
	    dam = number_range(ch->level, (ch->level * 6));
	    victim->hit = victim->hit - dam;
	    update_pos(victim);
    	    if (IS_NPC(victim) && !IS_NPC(ch)) ch->mkill = ch->mkill + 1;
    	    if (!IS_NPC(victim) && IS_NPC(ch)) victim->mdeath = victim->mdeath + 1;
	    if (victim->position == POS_DEAD) {raw_kill(victim, ch);return;}
	}
    }
    else
    {
	sprintf(buf,"$n hurls $N %s.", direction);
	act(buf,ch,NULL,victim,TO_NOTVICT);
	sprintf(buf,"You hurl $N %s.", direction);
	act(buf,ch,NULL,victim,TO_CHAR);
	sprintf(buf,"$n hurls you %s.", direction);
	act(buf,ch,NULL,victim,TO_VICT);
	if (door == 0) sprintf(direction,"south");
	if (door == 1) sprintf(direction,"west");
	if (door == 2) sprintf(direction,"north");
	if (door == 3) sprintf(direction,"east");
	char_from_room(victim);
	char_to_room(victim,to_room);
	sprintf(buf,"$n comes flying in from the %s.", direction);
	act(buf,victim,NULL,NULL,TO_ROOM);
	dam = number_range(ch->level, (ch->level * 2));
	victim->hit = victim->hit - dam;
	update_pos(victim);
    	if (IS_NPC(victim) && !IS_NPC(ch)) ch->mkill = ch->mkill + 1;
    	if (!IS_NPC(victim) && IS_NPC(ch)) victim->mdeath = victim->mdeath + 1;
	if (victim->position == POS_DEAD) {raw_kill(victim, ch);return;}
    }
    return;
}



void do_disarm( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA *obj;
    int percent;

    if ( !IS_NPC(ch)
    &&   ch->level < skill_table[gsn_disarm].skill_level)
    {
	send_to_char( "You don't know how to disarm opponents.\n\r", ch );
	return;
    }

    if ( ( get_eq_char( ch, WEAR_WIELD ) == NULL )
    &&   ( get_eq_char( ch, WEAR_HOLD  ) == NULL ) )
    {
	send_to_char( "You must wield a weapon to disarm.\n\r", ch );
	return;
    }

    if ( ( victim = ch->fighting ) == NULL )
    {
	send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;
    }

    if ( ( ( obj = get_eq_char( victim, WEAR_WIELD ) ) == NULL )
    &&   ( ( obj = get_eq_char( victim, WEAR_HOLD  ) ) == NULL ) )
    {
	send_to_char( "Your opponent is not wielding a weapon.\n\r", ch );
	return;
    }

    WAIT_STATE( ch, skill_table[gsn_disarm].beats );
    percent = number_percent( ) + victim->level - ch->level;
    if (!IS_NPC(victim) && IS_IMMUNE(victim, IMM_DISARM)) 

	send_to_char( "You failed.\n\r", ch );
    else if ( IS_NPC(ch) || percent < ch->pcdata->learned[gsn_disarm] * 2 / 3 )
	disarm( ch, victim );
    else
	send_to_char( "You failed.\n\r", ch );
    return;
}



void do_sla( CHAR_DATA *ch, char *argument )
{
    send_to_char( "If you want to SLAY, spell it out.\n\r", ch );
    return;
}



void do_slay( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Slay whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "Suicide is a mortal sin.\n\r", ch );
	return;
    }

    if (IS_SET(victim->act, PLR_GODLESS))
    {
	send_to_char( "You failed.\n\r", ch );
	return;
    }

    if ( !IS_NPC(victim) && victim->level >= ch->level )
    {
	send_to_char( "You failed.\n\r", ch );
	return;
    }

    act( "You slay $M in cold blood!",  ch, NULL, victim, TO_CHAR    );
    act( "$n slays you in cold blood!", ch, NULL, victim, TO_VICT    );
    act( "$n slays $N in cold blood!",  ch, NULL, victim, TO_NOTVICT );
    raw_kill( victim, ch );
    victim->fatal = 18;
    return;
}

/* Had problems with people not dying when POS_DEAD...KaVir */
void do_killperson( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
	return;
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
	return;
    send_to_char( "You have been KILLED!!\n\r\n\r", victim );
    if (IS_NPC(victim) && !IS_NPC(ch)) ch->mkill = ch->mkill + 1;
    if (!IS_NPC(victim) && IS_NPC(ch)) victim->mdeath = victim->mdeath + 1;
    raw_kill( victim, ch );
    return;
}

void killperson( CHAR_DATA *ch, CHAR_DATA *victim )
{
    send_to_char( "You have been KILLED!!\n\r", victim );
    raw_kill(victim, ch );
    return;
}

/* For decapitating players - KaVir */
void do_decapitate( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA  *obj;
    OBJ_DATA  *obj2;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    one_argument( argument, arg );

    if ( IS_NPC(ch) ) return;

    obj2 = get_eq_char( ch, WEAR_HOLD );
    if ( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL )
    {
    	if ( ( obj2 = get_eq_char( ch, WEAR_HOLD ) ) == NULL )
    	{
	    send_to_char( "First you better get a weapon out!\n\r", ch );
	    return;
        }
    }

    if ( ( obj != NULL && obj->item_type != ITEM_WEAPON ) )
    {
    	if ( ( obj2 != NULL && obj2->item_type != ITEM_WEAPON ) )
    	{
	    send_to_char( "But you are not wielding any weapons!\n\r", ch );
	    return;
        }
    }

    if ( ( obj  != NULL && obj->value[3]  != 1 && obj->value[3]  != 3 )
    &&   ( obj2 != NULL && obj2->value[3] != 1 && obj2->value[3] != 3 ) )
    {
	send_to_char( "You need to wield a slashing or slicing weapon to decapitate.\n\r", ch );
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Decapitate whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "That might be a bit tricky...\n\r", ch );
	return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "You can only decapitate other players.\n\r", ch );
	return;
    }

    if ( !CAN_PK(ch) )
    {
	send_to_char( "You must be an avatar to decapitate someone.\n\r", ch );
	return;
    }

    if ( !CAN_PK(victim) )
    {
	send_to_char( "You can only decapitate other avatars.\n\r", ch );
	return;
    }

    if ( victim->position > 1 )
    {
	send_to_char( "You can only do this to mortally wounded players.\n\r", ch );
	return;
    }

    if (is_safe(ch,victim)) return;

    if ( IS_CLASS(ch, CLASS_VAMPIRE) && IS_SET(ch->special, SPC_INCONNU) && 
	(IS_CLASS(victim, CLASS_VAMPIRE) || IS_VAMPAFF(victim, VAM_MORTAL)))
    {
	send_to_char( "You cannot decapitate another vampire.\n\r", ch );
	return;
    }

    if ( IS_CLASS(victim, CLASS_VAMPIRE) && IS_SET(victim->special, SPC_INCONNU) && 
	(IS_CLASS(ch, CLASS_VAMPIRE) || IS_VAMPAFF(ch, VAM_MORTAL)))
    {
	send_to_char( "You cannot decapitate an Inconnu vampire.\n\r", ch );
	return;
    }

    if ( IS_CLASS(ch, CLASS_VAMPIRE) && IS_CLASS(victim, CLASS_VAMPIRE) &&
	strlen(ch->clan) > 1 && strlen(victim->clan) > 1)
    {
	if (!str_cmp(ch->clan,victim->clan))
	{
	    send_to_char( "You cannot decapitate someone of your own clan.\n\r", ch );
	    return;
	}
    }

    act( "You bring your weapon down upon $N's neck!",  ch, NULL, victim, TO_CHAR    );
    send_to_char( "Your head is sliced from your shoulders!\n\r", victim);
    act( "$n swings $s weapon down towards $N's neck!",  ch, NULL, victim, TO_NOTVICT );
    act( "$n's head is sliced from $s shoulders!", victim, NULL, NULL, TO_ROOM);
if (strlen(victim->pcdata->love) > 1)
    {
	if (!str_cmp(ch->name, victim->pcdata->love))
	{
	    free_string(victim->pcdata->love);
	    victim->pcdata->love = str_dup( "" );
	}
    }

/*
    clan_table_dec( ch,victim );
*/
    if (IS_CLASS(ch, CLASS_DEMON) || IS_SET(ch->special, SPC_CHAMPION)) 

    if ((IS_CLASS(ch, CLASS_DEMON) || IS_SET(ch->special, SPC_CHAMPION)) && 
	!IS_CLASS(victim,CLASS_DEMON) &&
!IS_SET(victim->special,SPC_CHAMPION) && !IS_CLASS(ch, CLASS_DROW))
    {
	if (ch->race == 0 && victim->race == 0)
	{
	    ch->pcdata->stats[DEMON_CURRENT] += 1000;
	    ch->pcdata->stats[DEMON_TOTAL] += 1000;
	}
	else
	{
	    ch->pcdata->stats[DEMON_CURRENT] += victim->race * 1000;
	    ch->pcdata->stats[DEMON_TOTAL] += victim->race * 1000;
	}
    }
    if (IS_CLASS(ch, CLASS_DROW) && !IS_CLASS(victim, CLASS_DEMON) &&
	!IS_CLASS(victim, CLASS_DROW)) {
	if (victim->race == 0 && ch->race == 0 )
		ch->pcdata->stats[DROW_POWER] += 1000;
	else ch->pcdata->stats[DROW_POWER] += 1000* victim->race;
}
               if (victim->pcdata->bounty > 0)
                {
                        ch->pcdata->quest += victim->pcdata->bounty;
                        victim->pcdata->bounty = 0;
                        send_to_char("You receive your reward.\n\r", ch);
                }
if ( (( get_age(victim) - 17) * 2 ) < 5 && victim->race < 1 && victim->class == 0)
{
sprintf(buf,"#F#r%s has #ybeen newbie#n #F#rcapped by %s#n.",victim->name,ch->name); 
do_info(ch,buf);
do_paradox(ch,"self");
 victim->hit = victim->max_hit;
return;
}


	if ((victim->race == 0 && ch->race > 0)  )
    {
	ch->paradox[0] += ch->race;
	ch->paradox[1] += ch->race;
	ch->paradox[2] += PARADOX_TICK;

    	sprintf(buf,"%s has been decapitated by %s for no status.",victim->name,ch->name);
    	do_info(ch,buf);
	sprintf( log_buf, "%s decapitated by %s at %d for no status.",
	    victim->name, ch->name, victim->in_room->vnum );
	log_string( log_buf );
	do_paradox(ch,"self");
if (IS_EXTRA(victim, EXTRA_DRAGON))
{
REMOVE_BIT(victim->extra,EXTRA_DRAGON);
act( "You transform back into zuloform.", victim, NULL, NULL, TO_CHAR );
    act( "$n shrinks back into a big black monster.", victim, NULL, NULL,TO_ROOM );
    victim->max_hit = victim->max_hit - 500;
victim->hit = victim->hit - 500;

if (victim->hit < 1) victim->hit = 1;
    victim->damroll = victim->damroll / 1.2;
victim->hitroll = victim->hitroll / 1.2;
    free_string( victim->morph );
    victim->morph = str_dup( "A big black monster" );
}

 if (IS_POLYAFF(victim, POLY_ZULO))
    {
        REMOVE_BIT(victim->polyaff, POLY_ZULO);
        REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
        act( "You transform into human form.", victim, NULL, NULL, TO_CHAR
);
        act( "$n's shrinks back into human form.", victim, NULL, NULL,
TO_ROOM
);
        free_string( victim->morph );
        victim->morph = str_dup( "" );
}
 if (IS_EXTRA(victim, EXTRA_POTENCY))
                    {
                        send_to_char("You feel your blood potency fade away.\n\r",victim);
                        victim->pcdata->stats[UNI_GEN] =- 1;
                        REMOVE_BIT(victim->extra, EXTRA_POTENCY);
                    }
if (IS_SET(victim->newbits, NEW_TIDE))
                    {
                     REMOVE_BIT(victim->newbits, NEW_TIDE);
}
	if (IS_CLASS(victim, CLASS_VAMPIRE))      do_mortalvamp(victim,"");
	else if (IS_SET(victim->special, SPC_WOLFMAN)) do_unwerewolf(victim,"");
	if (IS_CLASS(victim, CLASS_MAGE) && IS_AFFECTED(victim, AFF_POLYMORPH)) 
	    do_unpolymorph(victim,"");
	ch->fight_timer += 10;
	SET_BIT(victim->loc_hp[0],LOST_HEAD);

        behead( victim );
	do_beastlike(ch,"");
	ch->pkill = ch->pkill + 1;
	victim->pdeath = victim->pdeath + 1;
	victim->level = 2;
	return;
    }

    ch->exp = ch->exp + 1000;
    if ( ch->race < 100 )
    	ch->race = ch->race + 1;
    if ( victim->race > 0 )
    	victim->race = victim->race - 1;
    act( "A misty white vapour pours from $N's corpse into your body.",  ch, NULL, victim, TO_CHAR    );
    act( "A misty white vapour pours from $N's corpse into $n's body.",  ch, NULL, victim, TO_NOTVICT );
    act( "You double over in agony as raw energy pulses through your veins.",  ch, NULL, NULL, TO_CHAR    );
    act( "$n doubles over in agony as sparks of energy crackle around $m.",  ch, NULL, NULL, TO_NOTVICT );
if (IS_EXTRA(victim, EXTRA_DRAGON))
{
REMOVE_BIT(victim->extra,EXTRA_DRAGON);
act( "You transform back into zuloform.", victim, NULL, NULL, TO_CHAR );
    act( "$n shrinks back into a big black monster.", victim, NULL, NULL,
TO_ROOM );

    ch->max_hit = ch->max_hit - 500;
ch->hit = ch->hit - 500;

if (victim->hit < 1) victim->hit = 1;
    victim->damroll = victim->damroll / 1.2;
victim->hitroll = victim->hitroll / 1.2;
    free_string( victim->morph );
    victim->morph = str_dup( "A big black monster" );
}

 if (IS_POLYAFF(victim, POLY_ZULO))
    {
        REMOVE_BIT(victim->polyaff, POLY_ZULO);
        REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
        act( "You transform into human form.", victim, NULL, NULL, TO_CHAR);
        act( "$n's shrinks back into human form.", victim, NULL, NULL,TO_ROOM);
        free_string( victim->morph );
        victim->morph = str_dup( "" );
}

 if (IS_EXTRA(victim, EXTRA_POTENCY))
                    {
                        send_to_char("You feel your blood potency fade away.\n\r",victim);
                        victim->pcdata->stats[UNI_GEN] -= 1;
                        REMOVE_BIT(victim->extra, EXTRA_POTENCY);
                    }
if (IS_SET(victim->newbits, NEW_TIDE))
                    {
                     REMOVE_BIT(victim->newbits, NEW_TIDE);
}
    if (IS_CLASS(victim, CLASS_VAMPIRE))      do_mortalvamp(victim,"");
    else if (IS_SET(victim->special, SPC_WOLFMAN)) do_unwerewolf(victim,"");
    if (IS_CLASS(victim, CLASS_MAGE) && IS_AFFECTED(victim, AFF_POLYMORPH)) 
	do_unpolymorph(victim,"");
    ch->fight_timer += 10;
    SET_BIT(victim->loc_hp[0],LOST_HEAD);
    behead( victim );
    do_beastlike(ch,"");
    ch->pkill = ch->pkill + 1;
    victim->pdeath = victim->pdeath + 1;
    victim->pcdata->stats[UNI_RAGE] = 0;
    victim->level = 2;
    victim->trust = 0;
    sprintf(buf,"%s has been decapitated by %s.",victim->name,ch->name);
    ch->exp += victim->exp / 2;
    victim->exp /= 2;
    do_info(ch,buf);
    sprintf( log_buf, "%s decapitated by %s at %d.",
	victim->name, ch->name, victim->in_room->vnum );
    log_string( log_buf );

   return;
}

void do_tear( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    one_argument( argument, arg );

    if ( IS_NPC(ch) ) return;
/*
    if ( !IS_WEREWOLF(ch) )
    {
        if ( !IS_CLASS(ch, CLASS_MONK) || !IS_VAMPIRE(ch) || (IS_VAMPIRE(ch) &&
	ch->pcdata->stats[UNI_RAGE] < 1))
        {
            send_to_char( "Huh?\n\r", ch );
            return;
        }
    }
    if ( !IS_CLASS(ch, CLASS_WEREWOLF) && !IS_CLASS(ch, CLASS_MONK))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
    if ( !IS_SET(ch->special, SPC_WOLFMAN) && IS_CLASS(ch, CLASS_WEREWOLF))
    {
	send_to_char( "You can only tear heads off while in Crinos form.\n\r", ch );
	return;
    }

*/
    if ( !IS_VAMPAFF(ch, VAM_CLAWS))
    {
	send_to_char( "You better get your claws out first.\n\r", ch );
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Who's head do you wish to tear off?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "That might be a bit tricky...\n\r", ch );
	return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "You can only tear the heads off other players.\n\r", ch );
	return;
    }

    if ( !CAN_PK(ch) )
    {
	send_to_char( "You must be an avatar to tear someone's head off.\n\r", ch );
	return;
    }

    if ( !CAN_PK(victim) )
    {
	send_to_char( "You can only tear the head off another avatar.\n\r", ch );
	return;
    }

    if ( victim->position > 1 )
    {
	send_to_char( "You can only do this to mortally wounded players.\n\r", ch );
	return;
    }

    if (is_safe(ch,victim)) return;

    act( "You tear $N's head from $S shoulders!",  ch, NULL, victim, TO_CHAR    );
    send_to_char( "Your head is torn from your shoulders!\n\r", victim);
    act( "$n tears $N's head from $S shoulders!",  ch, NULL, victim, TO_NOTVICT );
if (strlen(victim->pcdata->love) > 1)
    {
	if (!str_cmp(ch->name, victim->pcdata->love))
	{
	    free_string(victim->pcdata->love);
	    victim->pcdata->love = str_dup( "" );
	}
    }
/*
    clan_table_dec( ch,victim );
*/
    if (IS_CLASS(ch, CLASS_DEMON) || IS_SET(ch->special, SPC_CHAMPION)) 
    {
	if (ch->race == 0 && victim->race == 0)
	{
	    ch->pcdata->stats[DEMON_CURRENT] += 1000;
	    ch->pcdata->stats[DEMON_TOTAL] += 1000;
	}
	else
	{
	    ch->pcdata->stats[DEMON_CURRENT] += victim->race * 1000;
	    ch->pcdata->stats[DEMON_TOTAL] += victim->race * 1000;
	
    
}
}

               if (victim->pcdata->bounty > 0)
                {
                        ch->pcdata->quest += victim->pcdata->bounty;
                        victim->pcdata->bounty = 0;
                        send_to_char("You receive your reward.\n\r", ch);
                }
if ( (( get_age(victim) - 17) * 2 ) < 5 && victim->race < 1 && victim->class == 0)
{
sprintf(buf,"#F#r%s has #ybeen newbie#n #F#rcapped by %s#n.",victim->name,ch->name); 
do_info(ch,buf);
do_paradox(ch,"self");
 victim->hit = victim->max_hit;
return;
}

	 if (victim->race == 0 && ch->race > 0)
    {
	ch->paradox[0] += ch->race;
	ch->paradox[1] += ch->race;
	ch->paradox[2] += PARADOX_TICK;


    	sprintf(buf,"%s has been decapitated by %s.",victim->name,ch->name);
    	do_info(ch,buf);
	sprintf( log_buf, "%s decapitated by %s at %d for no status.",
	    victim->name, ch->name, victim->in_room->vnum );
	log_string( log_buf );
	do_paradox(ch,"self");
if (IS_EXTRA(victim, EXTRA_DRAGON))
{
REMOVE_BIT(victim->extra,EXTRA_DRAGON);
act( "You transform back into zuloform.", victim, NULL, NULL, TO_CHAR );
    act( "$n shrinks back into a big black monster.", victim, NULL, NULL,
TO_ROOM );
    victim->max_hit = victim->max_hit - 500;
victim->hit = victim->hit - 500;

if (victim->hit < 1) victim->hit = 1;
    victim->damroll = victim->damroll / 1.2;
victim->hitroll = victim->hitroll / 1.2;
    free_string( victim->morph );
    victim->morph = str_dup( "A big black monster" );
}
 if (IS_POLYAFF(victim, POLY_ZULO))
    {
        REMOVE_BIT(victim->polyaff, POLY_ZULO);
        REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
        act( "You transform into human form.", victim, NULL, NULL, TO_CHAR);
        act( "$n's shrinks back into human form.", victim, NULL, NULL,TO_ROOM);
        free_string( victim->morph );
        victim->morph = str_dup( "" );
}
 if (IS_EXTRA(victim, EXTRA_POTENCY))
                    {
                        send_to_char("You feel your blood potency fade away.\n\r",victim);
                        victim->pcdata->stats[UNI_GEN] -= 1;
                        REMOVE_BIT(victim->extra, EXTRA_POTENCY);
                    }
if (IS_SET(victim->newbits, NEW_TIDE))
                    {
                     REMOVE_BIT(victim->newbits, NEW_TIDE);
}

	if (IS_CLASS(victim, CLASS_VAMPIRE))      do_mortalvamp(victim,"");
	else if (IS_SET(victim->special, SPC_WOLFMAN)) do_unwerewolf(victim,"");
	if (IS_CLASS(victim, CLASS_MAGE) && IS_AFFECTED(victim, AFF_POLYMORPH)) 
	    do_unpolymorph(victim,"");
	ch->fight_timer += 10;
	SET_BIT(victim->loc_hp[0],LOST_HEAD);
        behead( victim );
	do_beastlike(ch,"");
	ch->pkill = ch->pkill + 1;
	victim->pdeath = victim->pdeath + 1;
	return;
    }

    ch->exp = ch->exp +1000;
    if ( ch->race < 100 )
      ch->race++;
    if ( victim->race > 0 )
      victim->race--;
    act( "A misty white vapour pours from $N's corpse into your body.",  ch, NULL, victim, TO_CHAR    );
    act( "A misty white vapour pours from $N's corpse into $n's body.",  ch, NULL, victim, TO_NOTVICT );
    act( "You double over in agony as raw energy pulses through your veins.",  ch, NULL, NULL, TO_CHAR    );
    act( "$n doubles over in agony as sparks of energy crackle around $m.",  ch, NULL, NULL, TO_NOTVICT );
if (IS_EXTRA(victim, EXTRA_DRAGON))
{
REMOVE_BIT(victim->extra,EXTRA_DRAGON);
act( "You transform back into zuloform.", victim, NULL, NULL, TO_CHAR );
    act( "$n shrinks back into a big black monster.", victim, NULL, NULL,
TO_ROOM );
    victim->max_hit = victim->max_hit - 500;
victim->hit = victim->hit - 500;

if (victim->hit < 1) victim->hit = 1;
    victim->damroll = victim->damroll / 1.2;
victim->hitroll = victim->hitroll / 1.2;
    free_string( victim->morph );
    victim->morph = str_dup( "A big black monster" );
}
 if (IS_POLYAFF(victim, POLY_ZULO))
    {
        REMOVE_BIT(victim->polyaff, POLY_ZULO);
        REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
        act( "You transform into human form.", victim, NULL, NULL,TO_CHAR);
        act( "$n's shrinks back into human form.", victim, NULL, NULL,TO_ROOM);
        free_string( victim->morph );
        victim->morph = str_dup( "" );
}

 if (IS_EXTRA(victim, EXTRA_POTENCY))
                    {
                        send_to_char("You feel your blood potency fade away.\n\r",victim);
                        victim->pcdata->stats[UNI_GEN] -= 1;
                        REMOVE_BIT(victim->extra, EXTRA_POTENCY);
                    }
if (IS_SET(victim->newbits, NEW_TIDE))
                    {
                     REMOVE_BIT(victim->newbits, NEW_TIDE);
}
    if (IS_CLASS(victim, CLASS_VAMPIRE))      do_mortalvamp(victim,"");
    else if (IS_SET(victim->special, SPC_WOLFMAN)) do_unwerewolf(victim,"");
    if (IS_CLASS(victim, CLASS_MAGE) && IS_AFFECTED(victim, AFF_POLYMORPH)) 
	do_unpolymorph(victim,"");
    ch->fight_timer += 10;
    SET_BIT(victim->loc_hp[0],LOST_HEAD);
    behead( victim );
    do_beastlike(ch,"");
    ch->pkill = ch->pkill + 1;
    victim->pdeath = victim->pdeath + 1;
    victim->pcdata->stats[UNI_RAGE] = 0;
    victim->level = 2;
    victim->trust = 0;
    sprintf(buf,"%s has been decapitated by %s.",victim->name,ch->name);
	ch->exp += victim->exp / 2;
    victim->exp /= 2;
    do_info(ch,buf);
    sprintf( log_buf, "%s decapitated by %s at %d.",
	victim->name, ch->name, victim->in_room->vnum );
    log_string( log_buf );
    return;
}

void do_crack( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA  *obj;
    OBJ_DATA  *right;
    OBJ_DATA  *left;

    right = get_eq_char( ch, WEAR_WIELD );
    left = get_eq_char( ch, WEAR_HOLD );
    if (right != NULL && right->pIndexData->vnum == 12) obj = right;
    else if (left != NULL && left->pIndexData->vnum == 12) obj = left;
    else
    {
	send_to_char("You are not holding any heads.\n\r",ch);
	return;
    }
    act("You hurl $p at the floor.", ch, obj, NULL, TO_CHAR);
    act("$n hurls $p at the floor.", ch, obj, NULL, TO_ROOM);
    act("$p cracks open, leaking brains out across the floor.", ch, obj, NULL, TO_CHAR);
    if (obj->chobj != NULL)
    	{act("$p cracks open, leaking brains out across the floor.", ch, obj, obj->chobj, TO_NOTVICT);
    	act("$p crack open, leaking brains out across the floor.", ch, obj, obj->chobj, TO_VICT);}
    else
    	{act("$p cracks open, leaking brains out across the floor.", ch, obj, NULL, TO_ROOM);}
    crack_head(ch,obj,obj->name);
    obj_from_char(obj);
    extract_obj(obj);
}

void crack_head( CHAR_DATA *ch, OBJ_DATA *obj, char *argument )
{
    CHAR_DATA *victim;
    MOB_INDEX_DATA *pMobIndex; 

    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    char       buf [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    if (str_cmp(arg2,"mob") && obj->chobj != NULL && !IS_NPC(obj->chobj) &&
	IS_AFFECTED(obj->chobj,AFF_POLYMORPH))
    {
	victim = obj->chobj;
	make_part(victim,"cracked_head");
	make_part(victim,"brain");
	sprintf(buf,"the quivering brain of %s",victim->name);
	free_string(victim->morph);
	victim->morph = str_dup(buf);
	return;
    }
    else if (!str_cmp(arg2,"mob"))
    {
	if ( ( pMobIndex = get_mob_index( obj->value[1] ) ) == NULL ) return;
	victim = create_mobile( pMobIndex );
	char_to_room(victim,ch->in_room);
	make_part(victim,"cracked_head");
	make_part(victim,"brain");
	extract_char(victim,TRUE,FALSE);
	return;
    }
    else
    {
	if ( ( pMobIndex = get_mob_index( 30002 ) ) == NULL ) return;
	victim = create_mobile( pMobIndex );

	sprintf( buf, capitalize(arg2) );
	free_string( victim->short_descr );
	victim->short_descr = str_dup( buf );

	char_to_room(victim,ch->in_room);
	make_part(victim,"cracked_head");
	make_part(victim,"brain");
	extract_char(victim,TRUE,FALSE);
	return;
    }
    return;
}


void do_garotte(CHAR_DATA *ch, char *argument)
{
	char buf[MAX_STRING_LENGTH];
	char arg[MAX_INPUT_LENGTH];
	CHAR_DATA *victim;
	OBJ_DATA *obj;
	int chance;

	one_argument(argument, arg);
	chance = number_percent();

	if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_DROW) || !IS_SET(ch->pcdata->powers[1], DPOWER_GAROTTE)) {
	send_to_char("Huh?\n\r", ch );
	return;}

	if ((victim = get_char_room(ch, arg)) == NULL) {
	send_to_char("Garotte whom?\n\r", ch );
	return;}

	if (victim == ch) {
	send_to_char("That would be a bad idea.\n\r", ch );
	return;}


	if (is_safe(ch, victim)) return;

    if ( ( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL
    ||   obj->value[3] != 4 )
    &&   ( ( obj = get_eq_char( ch, WEAR_HOLD ) ) == NULL
    ||   obj->value[3] != 4 ) )
    {
        send_to_char( "You need to wield a whip.\n\r", ch );
        return;
    }
     
    if ( victim->fighting != NULL )
    {
        send_to_char( "You can't garotte a fighting person.\n\r", ch );
        return;
    }

	if (victim->hit < victim->max_hit) {
	act("$N is too hurt for you to sneak up.", ch, NULL,victim,TO_CHAR);
	return;}

	check_killer(ch, victim);
	WAIT_STATE(ch, skill_table[gsn_garotte].beats);
	
	if (chance <= 5) {
        ch->fight_timer += 5;
	damage(ch, victim, 0, gsn_garotte);
	return;}

	if ( chance == 13 || chance == 31 ) { /* bad luck :) */
	act("$n wraps a whip around $N's neck! $N is choking to death!",ch,NULL,victim,TO_NOTVICT);
	act("You wrap your whip around $N's neck and refuse to let go!",ch,NULL,victim,TO_CHAR);
	act("$n wraps his whip around your neck, and you can't break free!",ch,NULL,victim,TO_VICT);
	
	if (!IS_NPC(victim)) {
        ch->fight_timer += 5;
	SET_BIT(ch->loc_hp[0],LOST_HEAD);
	behead(victim);
        ch->pkill = ch->pkill + 1;
        victim->pdeath = victim->pdeath + 1;
        victim->level = 2;
	do_call(victim,"all");
	sprintf(buf, "%s has been assassinated by %s!",victim->name,ch->name);
	do_info(ch,buf);
	} else
	{
	victim->hit = 1;
	damage(ch, victim, 1000, gsn_garotte);
	}

	return;} else
	{
	multi_hit(ch, victim, gsn_garotte);
	return;
	}
	return;
}

void do_dark_garotte(CHAR_DATA *ch, char *argument)
{
	char buf[MAX_STRING_LENGTH];
	char arg[MAX_INPUT_LENGTH];
	CHAR_DATA *victim;
	OBJ_DATA *obj;
	int chance;
	int i;

	one_argument(argument, arg);
	chance = number_percent();

	if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_DROW) || !IS_SET(ch->pcdata->powers[1], DPOWER_GAROTTE)
	|| !IS_SET(ch->pcdata->powers[1], DPOWER_DGAROTTE)) {
	send_to_char("Huh?\n\r", ch );
	return;}

	if (!IS_SET(ch->newbits, NEW_DARKNESS)) {
	send_to_char("You have to be surrounded in darkness.\n\r", ch );
	return;}

	if ((victim = get_char_room(ch, arg)) == NULL) {
	send_to_char("Dark Garotte whom?\n\r", ch );
	return;}

	if (victim == ch) {
	send_to_char("That would be a bad idea.\n\r", ch );
	return;}

	if (is_safe(ch, victim)) return;

    if ( ( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL
    ||   obj->value[3] != 4 )
    &&   ( ( obj = get_eq_char( ch, WEAR_HOLD ) ) == NULL
    ||   obj->value[3] != 4 ) )
    {
        send_to_char( "You need to wield a whip.\n\r", ch );
        return;
    }
     
    if ( victim->fighting != NULL )
    {
        send_to_char( "You can't garotte a fighting person.\n\r", ch );
        return;
    }

	if (victim->hit < victim->max_hit) {
	act("$N is too hurt for you to sneak up.", ch,
NULL,victim,TO_CHAR);
	return;}

	check_killer(ch, victim);
	WAIT_STATE(ch, skill_table[gsn_garotte].beats);
	REMOVE_BIT(ch->newbits, NEW_DARKNESS);	
	REMOVE_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);

	if ( chance > 95 ) { /* bad luck :) */
	act("$n wraps a whip around $N's neck! $N is choking to death!",ch,NULL,victim,TO_NOTVICT);
	act("You wrap your whip around $N's neck and refuse to let go!",ch,NULL,victim,TO_CHAR);
	act("$n wraps his whip around your neck, and you can't break free!",ch,NULL,victim,TO_VICT);
	
	if (!IS_NPC(victim)) {
        ch->fight_timer += 5;
	behead(victim);
        ch->pkill = ch->pkill + 1;
        victim->level = 2;
	do_call(victim,"all");
	sprintf(buf, "%s has been assassinated by %s!",victim->name,ch->name);
	do_info(ch,buf);
	} else
	{
	victim->hit = 1;
	damage(ch, victim, 1000, gsn_garotte);
	}

	return;} else
	if (chance <= 5) {
        ch->fight_timer += 5;
	damage(ch, victim, 0, gsn_garotte);
	return;}
	else 
	{
	for (i = 1; i < 4; i++)
	multi_hit(ch, victim, gsn_garotte);
	return;
	}
	return;
}

bool has_timer(CHAR_DATA *ch) 
{
	if (ch->fight_timer > 0 && !IS_NPC(ch)) {
	send_to_char("Not until your fight timer runs out!\n\r", ch );
	return TRUE;}

	return FALSE;
}

/* Voodoo skill by KaVir */

void do_voodoo( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA  *obj;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    char       buf [MAX_INPUT_LENGTH];
    char     part1 [MAX_INPUT_LENGTH];
    char     part2 [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0')
    {
	send_to_char( "Who do you wish to use voodoo magic on?\n\r", ch );
	return;
    }

    if ( ( obj = get_eq_char( ch, WEAR_HOLD ) ) == NULL )
    {
	send_to_char( "You are not holding a voodoo doll.\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They are not here.\n\r", ch );
	return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    sprintf(part2,obj->name);
    sprintf(part1,"%s voodoo doll",victim->name);

    if ( str_cmp(part1,part2) )
    {
	sprintf(buf,"But you are holding %s, not %s!\n\r",obj->short_descr,victim->name);
	send_to_char( buf, ch );
	return;
    }

    if ( arg2[0] == '\0')
    {
	send_to_char( "You can 'stab', 'burn' or 'throw' the doll.\n\r", ch );
    }
    else if ( !str_cmp(arg2, "stab") )
    {
	WAIT_STATE(ch,12);
	act("You stab a pin through $p.", ch, obj, NULL, TO_CHAR); 
 	act("$n stabs a pin through $p.", ch, obj, NULL, TO_ROOM);
	if (!IS_NPC(victim) && IS_IMMUNE(victim, IMM_VOODOO)) return;
	act("You feel an agonising pain in your chest!", victim, NULL, NULL, TO_CHAR);
 	act("$n clutches $s chest in agony!", victim, NULL, NULL, TO_ROOM);
    }
    else if ( !str_cmp(arg2, "burn") )
    {
	WAIT_STATE(ch,12);
	act("You set fire to $p.", ch, obj, NULL, TO_CHAR);
 	act("$n sets fire to $p.", ch, obj, NULL, TO_ROOM);
	act("$p burns to ashes.", ch, obj, NULL, TO_CHAR);
 	act("$p burns to ashes.", ch, obj, NULL, TO_ROOM);
	obj_from_char(obj);
	extract_obj(obj);
	if (!IS_NPC(victim) && IS_IMMUNE(victim, IMM_VOODOO)) return;
	if (IS_AFFECTED(victim,AFF_FLAMING) )
	    return;
	SET_BIT(victim->affected_by, AFF_FLAMING);
	act("You suddenly burst into flames!", victim, NULL, NULL, TO_CHAR);
 	act("$n suddenly bursts into flames!", victim, NULL, NULL, TO_ROOM);
    }
    else if ( !str_cmp(arg2, "throw") )
    {
	WAIT_STATE(ch,12);
	act("You throw $p to the ground.", ch, obj, NULL, TO_CHAR);
 	act("$n throws $p to the ground.", ch, obj, NULL, TO_ROOM);
	obj_from_char(obj);
	obj_to_room(obj, ch->in_room);
	if (!IS_NPC(victim) && IS_IMMUNE(victim, IMM_VOODOO)) return;
	if (victim->position < POS_STANDING)
	    return;
	if (victim->position == POS_FIGHTING)
	    stop_fighting(victim, TRUE);
	act("A strange force picks you up and hurls you to the ground!", victim, NULL, NULL, TO_CHAR);
 	act("$n is hurled to the ground by a strange force.", victim, NULL, NULL, TO_ROOM);
	victim->position = POS_RESTING;
	victim->hit = victim->hit - number_range(ch->level,(5*ch->level));
	update_pos(victim);
	if (victim->position == POS_DEAD && !IS_NPC(victim))
	{
	    do_killperson(ch,victim->name);
	    victim->fatal = 7;
	    return;
	}
    }
    else
    {
	send_to_char( "You can 'stab', 'burn' or 'throw' the doll.\n\r", ch );
    }
    return;
}

void do_autostance(CHAR_DATA *ch, char *argument ) {

        char    arg     [MAX_INPUT_LENGTH];

        argument = one_argument(argument,arg);

        if (IS_NPC(ch)) return;

	if (!str_cmp(arg,"none")) {
	send_to_char("You no longer autostance.\n\r", ch );
	ch->pcdata->autostance = STANCE_NONE;}
        else if (!str_cmp(arg, "crane")) {
        send_to_char("You now autostance into the crane stance.\n\r",ch );
        ch->pcdata->autostance = STANCE_CRANE;}
        else if (!str_cmp(arg, "crab")) {
        send_to_char("You now autostance into the crab stance.\n\r", ch );
        ch->pcdata->autostance = STANCE_CRAB;}
        else if (!str_cmp(arg, "bull")) {
        send_to_char("You now autostance into the bull stance.\n\r", ch );
        ch->pcdata->autostance = STANCE_BULL;}
        else if (!str_cmp(arg, "viper")) {
        send_to_char("You now autostance into the viper stance.\n\r", ch
);
        ch->pcdata->autostance = STANCE_VIPER;}
        else if (!str_cmp(arg, "mongoose")) {
        send_to_char("You now autostance into the mongoose stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_MONGOOSE;}
        else if (!str_cmp(arg, "mantis")
        && ch->stance[STANCE_CRANE] >= 200
        && ch->stance[STANCE_VIPER] >= 200) {
        send_to_char("You now autostance into the mantis stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_MANTIS;}
        else if (!str_cmp(arg, "monkey")
        && ch->stance[STANCE_CRANE] >= 200
        && ch->stance[STANCE_MONGOOSE] >= 200) {
        send_to_char("You now autostance into the monkey stance.\n\r",ch);
        ch->pcdata->autostance = STANCE_MONKEY;}

        else if (!str_cmp(arg, "swallow")  
        && ch->stance[STANCE_CRAB] >= 200
        && ch->stance[STANCE_MONGOOSE] >= 200) {
        send_to_char("You now autostance into the swallow stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_SWALLOW;}
        else if (!str_cmp(arg, "tiger")  
        && ch->stance[STANCE_BULL] >= 200
        && ch->stance[STANCE_VIPER] >= 200) {
        send_to_char("You now autostance into the tiger stance.\n\r", ch);
        ch->pcdata->autostance = STANCE_TIGER;}
        else if (!str_cmp(arg, "dragon")  
        && ch->stance[STANCE_CRAB] >= 200
        && ch->stance[STANCE_BULL] >= 200) {
        send_to_char("You now autostance into the dragon stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_DRAGON;}
        else if (!str_cmp(arg,"rabbit") && ch->stance[STANCE_SWALLOW] >= 200 
         && ch->stance[STANCE_MONKEY] >= 200) {
        stc("You now autostance into the rabbit stance.\n\r", ch);
        ch->pcdata->autostance = STANCE_RABBIT;}
        else if (!str_cmp(arg, "cobra") && ch->stance[STANCE_TIGER] >= 200
         && ch->stance[STANCE_DRAGON] >= 200)  {
        stc("You now autstance into the cobra stance.\n\r", ch);
        ch->pcdata->autostance = STANCE_COBRA;}
        else if (!str_cmp(arg, "cougar") && ch->stance[STANCE_MANTIS] >= 200
        && ch->stance[STANCE_DRAGON] >= 200)   {
	stc("You now autostance into the cougar stance.\n\r", ch);
        ch->pcdata->autostance = STANCE_COUGAR; }
        else if (!str_cmp(arg, "bear") && ch->stance[STANCE_SWALLOW] >= 200
        && ch->stance[STANCE_TIGER] >= 200) {
	stc("You now autostance into the bear stance.\n\r", ch);
	ch->pcdata->autostance = STANCE_BEAR; }
//MACA
        else if (!str_cmp(arg, "eagle") && ch->stance[STANCE_SWALLOW] >=200
        && ch->stance[STANCE_DRAGON] >= 200){
	stc("You now autostance into the eagle stance.\n\r", ch);
	ch->pcdata->autostance = STANCE_EAGLE; }
       
        else send_to_char("You can't set your autostance to that!\n\r",ch);
}

void autodrop(CHAR_DATA *ch) {
        
        int st;
        char buf [MAX_INPUT_LENGTH];
        char buf2 [MAX_INPUT_LENGTH];
        char stancename [10];

        if (IS_NPC(ch)) return;

        st = ch->pcdata->autostance;
        if (st == STANCE_VIPER) sprintf(stancename,"viper");
        else if (st == STANCE_CRANE) sprintf(stancename,"crane");
        else if (st == STANCE_CRAB) sprintf(stancename,"crab");
        else if (st == STANCE_MONGOOSE) sprintf(stancename,"mongoose");
        else if (st == STANCE_BULL) sprintf(stancename,"bull");
        else if (st == STANCE_MANTIS) sprintf(stancename,"mantis");
        else if (st == STANCE_DRAGON) sprintf(stancename,"dragon");
        else if (st == STANCE_TIGER) sprintf(stancename,"tiger");
        else if (st == STANCE_MONKEY) sprintf(stancename,"monkey");
        else if (st == STANCE_SWALLOW) sprintf(stancename,"swallow");
        else if (st == STANCE_RABBIT) sprintf(stancename, "rabbit");
        else if (st == STANCE_COBRA) sprintf(stancename, "cobra");
        else if (st == STANCE_COUGAR) sprintf(stancename, "cougar");
        else if (st == STANCE_BEAR) sprintf(stancename, "bear");
        else if (st == STANCE_EAGLE) sprintf(stancename, "eagle");
	
        else return;
     
        if (ch->stance[0] < 1) {
        ch->stance[0] = st;
    
        sprintf(buf, "You autodrop into the %s stance.", stancename);
        act(buf, ch, NULL, NULL, TO_CHAR);
        sprintf(buf2, "$n autodrops into the %s stance.", stancename);
        act(buf2, ch, NULL, NULL, TO_ROOM);
}       
}

void death_message( CHAR_DATA *ch, CHAR_DATA *victim )
{
    char buf [MAX_STRING_LENGTH];
    char *chname;
    char *chsex;
    if (ch == NULL || victim == NULL || victim->form < 1) return;
    chname = !IS_NPC(ch) ? ch->name : ch->short_descr;
    chsex = ch->sex == SEX_FEMALE ? "her" : "his";
    switch (victim->fatal)
    {
        default:
            sprintf(buf,"%s has just died!",chname);
            break;
        case 1:
            sprintf(buf,"%s has just been dissolved by %s's acid blood!",victim->name,chname);
            break;  
        case 2:
            sprintf(buf,"%s just committed suicide by tearing %s own heart out!",chname,chsex);
            break;
        case 3:  
            sprintf(buf,"%s has just sucked out all of %s's blood!",chname,victim->name);
            break;
        case 4:
            sprintf(buf,"%s has just boiled all of %s's blood!",chname,victim->name);
            break;
        case 5:
            sprintf(buf,"%s has just turned %s's blood into water!",chname,victim->name);
            break;
        case 6:   
            sprintf(buf,"%s has just evaporated all of %s's blood!",chname,victim->name);
            break;
        case 7:     
            sprintf(buf,"%s has just smashed %s to death!",chname,victim->name);
            break;
        case 8:   
            sprintf(buf,"%s has just blown apart %s's mind!",chname,victim->name);
            break;
        case 9:   
            sprintf(buf,"%s has just torn out %s's soul!",chname,victim->name);
            break;
        case 10:  
            sprintf(buf,"%s has just sucked out %s's life essence!",chname,victim->name);
            break;
        case 11:  
            sprintf(buf,"%s has just blown apart %s's eardrums!",chname,victim->name);
            break;
        case 12:  
            sprintf(buf,"%s's entrails just poured from %s torn open stomach!",chname,chsex);
           break;
        case 13:  
            sprintf(buf,"%s just died from %s wounds!",chname,chsex);
            break;
        case 14:  
            sprintf(buf,"%s just burned to death!",chname);
            break;
        case 16:  
            sprintf(buf,"%s just died a long, slow, painful death!",chname);
            break;
        case 17:  
            sprintf(buf,"%s has just torn apart %s's body!",chname,victim->name);
            break;
        case 18:  
            sprintf(buf,"%s has slain %s in cold blood!",chname,victim->name);
            break;
      case 19:  
            sprintf(buf,"%s has just shot down %s!",chname,victim->name);
            break;
        case 20:  
            sprintf(buf,"%s has struck %s a mortal wound!",chname,victim->name);
            break;
        case 21:  
            sprintf(buf,"%s has torn off %s's face!",chname,victim->name);
            break;
        case 22:  
            sprintf(buf,"%s has ripped out %s's windpipe!",chname,victim->name);
            break;
        case 23:  
            sprintf(buf,"%s has ripped out %s's entrails!",chname,victim->name);
            break;
        case 24:  
           sprintf(buf,"%s has broken %s's back!",chname,victim->name);
            break;
        case 25:  
            sprintf(buf,"%s has broken %s's neck!",chname,victim->name);
            break;
        case 26:  
            sprintf(buf,"%s has disembowelled %s!",chname,victim->name);
            break;
        case 27:  
            sprintf(buf,"%s has thrust %s weapon through %s's head!",chname,chsex,victim->name);
            break;
        case 28:  
            sprintf(buf,"%s has sliced open %s's carotid artery!",chname,victim->name);
            break;
        case 29:  
            sprintf(buf,"%s has sliced open %s's throat!",chname,victim->name);
            break;
        case 30:  
            sprintf(buf,"%s has split open %s's head!",chname,victim->name);
            break;
        case 31:  
            sprintf(buf,"%s has thrust %s weapon through %s's chest!",chname,chsex,victim->name);
            break;
        case 32:  
            sprintf(buf,"%s has swung %s weapon between %s's legs!",chname,chsex,victim->name);
            break;
        case 33:  
            sprintf(buf,"%s has sliced off %s's arm!",chname,victim->name);
            break;
        case 34:  
            sprintf(buf,"%s has sliced off %s's leg!",chname,victim->name);
            break;
       case 35:
            sprintf(buf,"%s has thrust %s weapon through %s's mouth!",chname,chsex,victim->name);
            break;
        case 36:
            sprintf(buf,"%s has thrust %s weapon through %s's eye!",chname,chsex,victim->name);
            break;
        case 37:
            sprintf(buf,"%s has smashed in %s's chest!",chname,victim->name);
            break;
        case 38:
            sprintf(buf,"%s has shattered %s's spine!",chname,victim->name);
            break;
        case 39:
            sprintf(buf,"%s has torn out %s's throat with %s teeth!",chname,victim->name,chsex);
            break;
        case 40:
           sprintf(buf,"%s has torn out %s's throat with %s claws!",chname,victim->name,chsex);
            break;
        case 41:  
            sprintf(buf,"%s has clawed out %s's eyeball!",chname,victim->name);
            break;
        case 42:  
            sprintf(buf,"%s has torn open %s's chest with %s claws!",chname,victim->name,chsex);
            break;
        case 43:  
            sprintf(buf,"%s has sucked out %s's brains!",chname,victim->name);
            break;
    }
    buf[0] = UPPER( buf[0] );
    do_fatality(ch,buf);
           
        
    if (IS_EXTRA(victim, EXTRA_PREGNANT))
    {
        sprintf(buf,"%s's unborn child has been slain!",victim->name);
        buf[0] = UPPER( buf[0] );
        do_fatality(ch,buf);
    }
    return;
}

