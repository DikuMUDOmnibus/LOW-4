/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc      
 *
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

/*offer(sacrifice)*/
void do_offer(CHAR_DATA *ch, char *argument  )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
    one_argument( argument,arg);
 
    if (IS_NPC(ch)) return;
    if ( arg[0] == '\0' )
    {
        send_to_char( "Who do you wish to sacrifice?\n\r", ch );
	return;
    }
    if ((victim = get_char_room( ch, arg)) == NULL)
    {
    send_to_char("They arent here.\n\r",ch);
    return;
    }
    if (IS_NPC(victim))
    {
    send_to_char("You cant sacrifice them!\n\r",ch);
    return;
    }

	if (!str_cmp(victim->name, "SirMog")) return;

    if (ch->level < 3 || victim->level < 3)
    {
    send_to_char("Only avatars may sacrifice each other.\n\r",ch);
    return;
    }
    if (victim->position > POS_INCAP)
    {
    send_to_char("You can only sacrifice mortally wounded players.\n\r",ch);
    return;
    }
    if (is_safe(ch,victim) == TRUE) return;
    WAIT_STATE(ch,8);
sprintf(buf,"%s places his hand on %s's head.",ch->name,victim->name); 
act(buf,ch,NULL,NULL,TO_ROOM);
sprintf(buf,"You place your hand on %s's head.",victim->name);
send_to_char(buf,ch);
sprintf(buf,"A divine spirit snatches %s from the planet.",victim->name);
act(buf,ch,NULL,NULL,TO_ROOM);
send_to_char(buf,ch);
sprintf(buf,"%s has been sacrificed to God by %s.",victim->name,ch->name);
if (IS_CLASS(ch,CLASS_VAMPIRE))
{
sprintf(buf,"%s has been sacrificed to Caine by %s.",victim->name,ch->name);
send_to_char("You have been gifted power by Caine.\n\r",ch);
}
if (IS_CLASS(ch,CLASS_WEREWOLF))
{
sprintf(buf,"%s has been sacrificed to Gaia by %s.",victim->name,ch->name);
send_to_char("You have been gifted power by Gaia.\n\r",ch);
}
if (IS_CLASS(ch,CLASS_DEMON))
{
sprintf(buf,"%s has been sacrificed to Satan by %s.",victim->name,ch->name);
send_to_char("You have been gifted power by Satan\n\r",ch);
}
if (IS_CLASS(ch, CLASS_DROW)) 
{
sprintf(buf,"%s has been sacirificed to Lloth by %s.",victim->name,ch->name);
send_to_char("You have been gifted power by Lloth.\n\r", ch );
}
do_info(ch,buf);

    if (( ch->race - victim->race > 10 && ch->race > 0)
	|| (victim->race == 0 && ch->race > 0)  )
        {
	ch->paradox[0] += ch->race;
	ch->paradox[1] += ch->race;
	ch->paradox[2] += PARADOX_TICK;
    	do_paradox(ch,"self");
	if (IS_CLASS(victim, CLASS_VAMPIRE))
	do_mortalvamp(victim,"");
	else if (IS_SET(victim->special, SPC_WOLFMAN))
	do_unwerewolf(victim,"");
	if (IS_CLASS(victim, CLASS_MAGE) && IS_AFFECTED(victim, AFF_POLYMORPH)) 
	do_unpolymorph(victim,"");
	if (IS_CLASS(victim, CLASS_DROW) && IS_POLYAFF(victim,
POLY_SPIDERFORM))
	do_spiderform(victim,"");
	do_beastlike(ch,"");
	victim->level = 2;
	victim->trust = 0;
        raw_kill(victim, ch);
	WAIT_STATE(victim, 10);
	return;
    }

ch->hit = ch->max_hit;
ch->mana= ch->max_mana;
ch->move= ch->max_move;
if (victim->race > 0)
{
/*
if (IS_CLASS(ch, CLASS_DEMON))
    ch->pcdata->souls ++;*/
ch->practice += 10;
victim->race -= 1;
}
 
raw_kill(victim, ch);
WAIT_STATE(victim,20);
return;
}

/*
void do_outcast( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    one_argument( argument, arg );

	if ( ch->pcdata->stats[UNI_GEN] != 2 &&
		   !IS_SET(ch->special, SPC_DEMON_LORD)
		   && ch->level != 6 )
	{
		send_to_char("You are not a clan leader!\n\r", ch);
		return;
	}

    if ( arg[0] == '\0' )
    {
	send_to_char( "Outcast who?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
    
    if ( victim == ch )
    {
    send_to_char("You cannot outcast youself!\n\r", ch);
    return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

 if ( IS_CLASS(ch,CLASS_DEMON) && IS_SET(ch->special, SPC_DEMON_LORD)
      && IS_CLASS(victim, CLASS_DEMON) && !str_cmp(victim->clan,ch->clan)  )
  {
  	sprintf(buf,"%s has been outcasted from %s", victim->name, ch->clan);
	do_info(victim,buf);
	  
    if (IS_VAMPAFF(victim,VAM_FANGS) )
    {
	 send_to_char("Your fangs slide back into your gums.\n\r",victim);
	 act("$N's fangs slide back into $s gums.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FANGS);
    }
       
    if (IS_VAMPAFF(victim,VAM_CLAWS) ) 
	{
	    send_to_char("Your claws slide back under your nails.\n\r",victim);
	    act("$N's claws slide back under $s nails.", ch, NULL, victim, TO_ROOM);
	    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
	}
	
    if (IS_VAMPAFF(victim,VAM_NIGHTSIGHT) )
    {
	 send_to_char("The red glow in your eyes fades.\n\r",victim);
	 act("The red glow in $N's eyes fades.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT);
    }
    
    if (IS_IMMUNE(victim,IMM_SHIELDED) )
    {
     send_to_char("You stop shielding your aura.\n\r",victim);
     REMOVE_BIT(victim->immune, IMM_SHIELDED);
    }
	
	if (IS_SET(victim->act, PLR_HOLYLIGHT) )
	{
	 REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	 send_to_char( "Your senses return to normal.\n\r", victim );
	}

    if (IS_DEMAFF(victim,DEM_HORNS) )
    {
	 send_to_char("Your horns slide back into your head.\n\r",victim);
	 act("$N's horns slide back into $s head.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_HORNS);
	}
	
	if (IS_DEMAFF(victim,DEM_HOOVES) )
    {
	 send_to_char("Your hooves transform into feet.\n\r",victim);
	 act("$N's hooves transform back into $s feet.", ch, NULL,victim,TO_ROOM);
	 REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_HOOVES);
    }
    
    if (IS_DEMAFF(victim,DEM_WINGS) )
    {
	if (IS_DEMAFF(victim,DEM_UNFOLDED) )
	{
	    send_to_char("Your wings fold up behind your back.\n\r",victim);
	    act("$N's wings fold up behind $s back.", ch, NULL, victim, TO_ROOM);
	    REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_UNFOLDED);
	}
	send_to_char("Your wings slide into your back.\n\r",victim);
	act("$N's wings slide into $s back.", ch, NULL, victim, TO_ROOM);
	REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_WINGS);
    }
    
	if ( IS_EXTRA(victim, EXTRA_OSWITCH) ) 
	{
	 do_humanform(victim,"");
	}
	
	victim->pcdata->powers[DPOWER_FLAGS] = 0;
	victim->pcdata->stats[DEMON_TOTAL] = 0;
	victim->pcdata->stats[DEMON_CURRENT] = 0;
	
    free_string(victim->lord);
    victim->lord     = str_dup( "" );
    free_string(victim->clan);
    victim->clan     = str_dup( "" );

	REMOVE_BIT(victim->special, SPC_CHAMPION );
    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_PRINCE);
    REMOVE_BIT(victim->special, SPC_DEMON_LORD);
    victim->pcdata->stats[UNI_RAGE] = 0;
    victim->class = 0;
	send_to_char("You have been outcasted from Hell!\n\r", victim);
  }
   
else if ( ( IS_CLASS(ch, CLASS_MAGE) && ch->level == LEVEL_ARCHMAGE )
	        && ch->pcdata->powers[MPOWER_RUNE0] == victim->pcdata->powers[MPOWER_RUNE0]
	        && victim->level < LEVEL_ARCHMAGE )
  {
  	sprintf(buf,"%s has been outcasted from the Mages Guild.", victim->name);
	do_info(victim,buf);  	

    reset_spell(victim,0);
    reset_spell(victim,1);
    reset_spell(victim,2);
    reset_spell(victim,3);
    reset_spell(victim,4);	
    
	victim->trust = 0;
	victim->class = 0;
	victim->level = 3;
	send_to_char("You have been outcasted from the Mages Guild!\n\r", victim);
  }

else if ( IS_CLASS(ch,CLASS_VAMPIRE)
		  && !str_cmp(victim->clan,ch->clan) 
		  && IS_CLASS(victim, CLASS_VAMPIRE) )   
  {
  	sprintf(buf,"%s has been outcasted from %s.", victim->name, victim->clan);
	do_info(victim,buf);

	victim->pcdata->condition[COND_THIRST] = 10000;

	if ( IS_CLASS(victim, CLASS_VAMPIRE) ) do_unwerewolf(victim,"");
	if ( IS_VAMPAFF(victim,VAM_DISGUISED) ) do_mask(victim,"self");
	if ( IS_POLYAFF(victim,POLY_SERPENT) ) do_serpent(victim,"");
    
    if (IS_VAMPAFF(victim,VAM_FANGS) )
    {
	 send_to_char("Your fangs slide back into your gums.\n\r",victim);
	 act("$N's fangs slide back into $s gums.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FANGS);
    }
    
    if (IS_CLASS(victim, CLASS_VAMPIRE) && IS_VAMPAFF(victim,VAM_CLAWS) ) 
	{
	    send_to_char("Your claws slide back under your nails.\n\r",victim);
	    act("$N's claws slide back under $s nails.", ch, NULL, victim, TO_ROOM);
	    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
	}

    if (IS_VAMPAFF(victim,VAM_NIGHTSIGHT) )
    {
	 send_to_char("The red glow in your eyes fades.\n\r",victim);
	 act("The red glow in $N's eyes fades.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT);
    }
    
    if (IS_AFFECTED(victim,AFF_SHADOWSIGHT) )
    {
	 send_to_char("You can no longer see between planes.\n\r",victim);
	 REMOVE_BIT(victim->affected_by, AFF_SHADOWSIGHT);
    }
    
    if (IS_IMMUNE(victim,IMM_SHIELDED) )
    {
     send_to_char("You stop shielding your aura.\n\r",victim);
     REMOVE_BIT(victim->immune, IMM_SHIELDED);
    }
    
    if (IS_VAMPAFF(victim,VAM_DISGUISED) )
    {
     free_string( victim->morph );
     victim->morph = str_dup( victim->name );
     send_to_char("You transform into yourself.\n\r", victim);
     REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_DISGUISED);
    }
    
    if (IS_AFFECTED(victim,AFF_SHADOWPLANE) )
    {
     send_to_char("You fade back into the real world.\n\r",victim);
	 act("The shadows flicker and $N fades into existance.",ch,NULL,victim,TO_ROOM);
	 REMOVE_BIT(victim->affected_by,AFF_SHADOWPLANE);
	 do_look(victim,"auto");
	}
	
	if (IS_SET(victim->act, PLR_HOLYLIGHT) )
	{
	 REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	 send_to_char( "Your senses return to normal.\n\r", victim );
	}

	REMOVE_BIT(victim->special, SPC_INCONNU );
	REMOVE_BIT(victim->special, SPC_ANARCH );
    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_PRINCE);
	REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CHANGED);
    REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_MIST);
	REMOVE_BIT(victim->affected_by, AFF_ETHEREAL);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FLYING);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_SONIC);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_BAT);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_WOLF);

	victim->pcdata->stats[UNI_RAGE] = 0;
    free_string(victim->lord);
    victim->lord     = str_dup( "" );
    free_string(victim->clan);
    victim->clan     = str_dup( "" );
    victim->pcdata->stats[UNI_GEN]     = 0;
    victim->pcdata->stats[UNI_AFF]     = 0;
    victim->pcdata->stats[UNI_CURRENT] = -1;
    victim->pcdata->rank = 0;
    victim->class = 0;
    victim->beast = 15;
    victim->pcdata->condition[COND_THIRST] = 0;
    	
	send_to_char("You have been outcasted!\n\r", victim);
  }
  
else if ( IS_CLASS(ch, CLASS_WEREWOLF) && ch->pcdata->stats[UNI_GEN] == 2
          && !str_cmp(victim->clan,ch->clan) && IS_CLASS(victim, CLASS_WEREWOLF) )
  {
  	sprintf(buf,"%s has been outcasted from %s.", victim->name, victim->clan);
	do_info(victim,buf);

	victim->pcdata->powers[WPOWER_BEAR]   = 4;
    victim->pcdata->powers[WPOWER_LYNX]   = 4;
	victim->pcdata->powers[WPOWER_BOAR]   = 4;
	victim->pcdata->powers[WPOWER_OWL]    = 4;
	victim->pcdata->powers[WPOWER_SPIDER] = 4; 
	victim->pcdata->powers[WPOWER_WOLF]   = 4;
	victim->pcdata->powers[WPOWER_HAWK]   = 4;
	victim->pcdata->powers[WPOWER_MANTIS] = 4;
	victim->pcdata->powers[WPOWER_TIGER]  = 4;
	victim->pcdata->powers[WPOWER_GAIA]  = 4;
	
	do_unwerewolf(victim,"");
    
    if (IS_VAMPAFF(victim,VAM_FANGS) )
    {
    	send_to_char("Your talons slide back into your fingers.\n\r",victim);
	    act("$N's talons slide back into $s fingers.",ch,NULL,victim,TO_ROOM);
    	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
    }

    if (IS_VAMPAFF(victim,VAM_NIGHTSIGHT) )
    {
	 send_to_char("The red glow in your eyes fades.\n\r",victim);
	 act("The red glow in $N's eyes fades.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT);
    }
    
    if (IS_AFFECTED(victim,AFF_SHADOWSIGHT) )
    {
	 send_to_char("You can no longer see between planes.\n\r",victim);
	 REMOVE_BIT(victim->affected_by, AFF_SHADOWSIGHT);
    }
    
    if (IS_IMMUNE(victim,IMM_SHIELDED) )
    {
     send_to_char("You stop shielding your aura.\n\r",victim);
     REMOVE_BIT(victim->immune, IMM_SHIELDED);
    }

    if (IS_AFFECTED(victim,AFF_SHADOWPLANE) )
    {
     send_to_char("You fade back into the real world.\n\r",victim);
	 act("The shadows flicker and $N fades into existance.",ch,NULL,victim,TO_ROOM);
	 REMOVE_BIT(victim->affected_by,AFF_SHADOWPLANE);
	 do_look(victim,"auto");
	}
	
	if (IS_SET(victim->act, PLR_WIZINVIS) )
	{
	 REMOVE_BIT(victim->act, PLR_WIZINVIS);
	 send_to_char( "You slowly fade into existence.\n\r", victim );
	}
	
	if (IS_SET(victim->act, PLR_HOLYLIGHT) )
	{
	 REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	 send_to_char( "Your senses return to normal.\n\r", victim );
	}

	REMOVE_BIT(victim->special, SPC_INCONNU );
	REMOVE_BIT(victim->special, SPC_ANARCH );
    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_PRINCE);
	REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CHANGED);
    REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_MIST);
	REMOVE_BIT(victim->affected_by, AFF_ETHEREAL);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FLYING);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_SONIC);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_BAT);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_WOLF);
	
	victim->pcdata->powers[WPOWER_BEAR]   = 0;
    victim->pcdata->powers[WPOWER_LYNX]   = 0;
	victim->pcdata->powers[WPOWER_BOAR]   = 0;
	victim->pcdata->powers[WPOWER_OWL]    = 0;
	victim->pcdata->powers[WPOWER_SPIDER] = 0; 
	victim->pcdata->powers[WPOWER_WOLF]   = 0;
	victim->pcdata->powers[WPOWER_HAWK]   = 0;
	victim->pcdata->powers[WPOWER_MANTIS] = 0;
	victim->pcdata->powers[WPOWER_TIGER]  = 0;
	victim->pcdata->powers[WPOWER_GAIA]   = 0;

	victim->pcdata->stats[UNI_RAGE] = 0;
    free_string(victim->lord);
    victim->lord     = str_dup( "" );
    free_string(victim->clan);
    victim->clan     = str_dup( "" );
    victim->pcdata->stats[UNI_GEN]     = 0;
    victim->pcdata->stats[UNI_AFF]     = 0;
    victim->pcdata->stats[UNI_CURRENT] = -1;
    victim->pcdata->rank = 0;
    victim->class = 0;  	
     
	send_to_char("You have been outcasted!\n\r", victim);
  }
else if ( IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->stats[UNI_GEN] == 2
          && !str_cmp(victim->clan,ch->clan) && IS_CLASS(victim, CLASS_NINJA) )
  {
  	sprintf(buf,"%s has been outcasted from %s.", victim->name, victim->clan);
	do_info(victim,buf);  

    if ( IS_VAMPAFF(victim,VAM_CLAWS) ) 
	{
	 	send_to_char("You shove your iron claws up your sleeves\n\r",victim);
	    act("$N shoves $S iron claws up $e sleeves.", ch, NULL, victim, TO_ROOM);
	    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
    }
	
	if (IS_SET(victim->act, PLR_WIZINVIS) )
	{
	 REMOVE_BIT(victim->act, PLR_WIZINVIS);
	 send_to_char( "You appear from the shadows.\n\r", victim );
	}
	
	if (IS_SET(victim->act, PLR_HOLYLIGHT) )
	{
	 REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	 send_to_char( "Your senses return to normal.\n\r", victim );
	}

    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_PRINCE);
	REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CHANGED);
    REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_MIST);
	REMOVE_BIT(victim->affected_by, AFF_ETHEREAL);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FLYING);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_SONIC);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_BAT);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_WOLF);
	
  	victim->pcdata->powers[NPOWER_SORA]     = 0;
  	victim->pcdata->powers[NPOWER_CHIKYU]   = 0;
	victim->pcdata->powers[NPOWER_NINGENNO] = 0;

	victim->pcdata->stats[UNI_RAGE] = 0;
    free_string(victim->lord);
    victim->lord     = str_dup( "" );
    free_string(victim->clan);
    victim->clan     = str_dup( "" );
    victim->pcdata->stats[UNI_GEN]     = 0;
    victim->pcdata->stats[UNI_AFF]     = 0;
    victim->pcdata->stats[UNI_CURRENT] = -1;
    victim->pcdata->rank = 0;
    victim->class = 0;  	
    victim->trust = 0;
    victim->level = 3;
	send_to_char("You have been outcasted!\n\r", victim);
  }
else if ( IS_CLASS(ch, CLASS_DROW) && ch->pcdata->stats[UNI_GEN] == 2
          && !str_cmp(victim->clan,ch->clan) && IS_CLASS(victim, CLASS_DROW) )
  {
    sprintf(buf,"%s has been outcasted from %s.", victim->name, victim->clan);
	do_info(victim,buf);

    reset_weapon(victim,0);
    reset_weapon(victim,1);
    reset_weapon(victim,2);
    reset_weapon(victim,3);
    reset_weapon(victim,4);
    reset_weapon(victim,5);
    reset_weapon(victim,6);
    reset_weapon(victim,7);
    reset_weapon(victim,8);
    reset_weapon(victim,9);
    reset_weapon(victim,10);
    reset_weapon(victim,11);
    reset_weapon(victim,12);

    if (IS_VAMPAFF(victim,VAM_FANGS) )
    {
         send_to_char("Your fangs slide back into your gums.\n\r",victim);
         act("$N's fangs slide back into $s gums.", ch, NULL, victim, TO_ROOM);
         REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FANGS);
    }

    if (IS_IMMUNE(victim,IMM_SHIELDED) )
    {
     send_to_char("You stop shielding your aura.\n\r",victim);
     REMOVE_BIT(victim->immune, IMM_SHIELDED);
    }
	
	if (IS_SET(victim->act, PLR_HOLYLIGHT) || IS_SET(victim->act, PLR_DROWSIGHT) )
	{
	 REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	 REMOVE_BIT(victim->act, PLR_DROWSIGHT);
	 send_to_char( "Your senses return to normal.\n\r", victim );
	}
	
	if (IS_AFFECTED(victim, AFF_DARKNESS)) 
	{
		REMOVE_BIT(victim->affected_by, AFF_DARKNESS);
		send_to_char("The darkness around you fades away.\n\r",ch);
		return;
	}
	
	victim->pcdata->powers[1] = 0;
  
	free_string(victim->lord);
    victim->lord     = str_dup( "" );
    free_string(victim->clan);
    victim->clan     = str_dup( "" );
	REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_PRINCE);
    REMOVE_BIT(victim->special, SPC_ANARCH);
    REMOVE_BIT(victim->special, SPC_DROW_WAR );
    REMOVE_BIT(victim->special, SPC_DROW_MAG );
    REMOVE_BIT(victim->special, SPC_DROW_CLE );
    victim->pcdata->stats[UNI_RAGE] = 0;
    victim->class = 0; 
	send_to_char("You have been outcasted!\n\r", victim);
  }
else if ( IS_CLASS(ch, CLASS_MONK) && ch->pcdata->stats[UNI_GEN] == 2
          && !str_cmp(victim->clan,ch->clan) && IS_CLASS(victim, CLASS_MONK) )
  {
  	sprintf(buf,"%s has been outcasted from %s.", victim->name, victim->clan);
	do_info(victim,buf);  
	
    reset_weapon(victim,0);
    reset_weapon(victim,1);
    reset_weapon(victim,2);
    reset_weapon(victim,3);
    reset_weapon(victim,4);
    reset_weapon(victim,5);
    reset_weapon(victim,6);
    reset_weapon(victim,7);
    reset_weapon(victim,8);
    reset_weapon(victim,9);
    reset_weapon(victim,10);
    reset_weapon(victim,11);
    reset_weapon(victim,12);

	if (IS_SET(victim->act, PLR_WIZINVIS) )
	{
	 REMOVE_BIT(victim->act, PLR_WIZINVIS);
	 send_to_char( "You appear from a shroud of light.\n\r", victim );
	}
	
	if (IS_SET(victim->act, PLR_HOLYLIGHT) )
	{
	 REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	 send_to_char( "Your view shimmers into mortal vision.\n\r", victim );
	}
	
    if (IS_IMMUNE(victim,IMM_SHIELDED) )
    {
     send_to_char("You stop shielding your aura.\n\r",victim);
     REMOVE_BIT(victim->immune, IMM_SHIELDED);
    }

    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_PRINCE);
	REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CHANGED);
    REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_MIST);
	REMOVE_BIT(victim->affected_by, AFF_ETHEREAL);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FLYING);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_SONIC);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_BAT);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_WOLF);
	
	victim->pcdata->powers[PMONK] = 0;

	victim->pcdata->stats[UNI_RAGE] = 0;
    free_string(victim->lord);
    victim->lord     = str_dup( "" );
    free_string(victim->clan);
    victim->clan     = str_dup( "" );
    victim->pcdata->stats[UNI_GEN]     = 0;
    victim->pcdata->stats[UNI_AFF]     = 0;
    victim->pcdata->stats[UNI_CURRENT] = -1;
    victim->pcdata->rank = 0;
    victim->class = 0;  	
    victim->trust = 0;
    victim->level = 3;
	send_to_char("You have been outcasted!\n\r", victim);
  }
  else
  	send_to_char("They are not of your clan!\n\r", ch);
  return;
}  
*/


void do_affects( CHAR_DATA *ch, char *argument )
{
   char buf[MAX_STRING_LENGTH];
   AFFECT_DATA *paf;

     if (IS_NPC(ch)) return;
     if ( ch->affected == NULL )
        {			   
 		send_to_char( "You have nothing affecting you at this time.\n\r", ch);
        return;
        }
     if ( ch->affected != NULL )
       {

         send_to_char( "You are affected by:\n\r", ch );
         for ( paf = ch->affected; paf != NULL; paf = paf->next )
            {
               sprintf( buf, "Spell: '%s'", skill_table[paf->type].name );
               send_to_char( buf, ch );
               if ( ch->level >= 0 )
                   {
   sprintf( buf, " modifies %s by %d for %d hours with bits %s.\n\r",
                      affect_loc_name( paf->location ),
                      paf->modifier,                    
                      paf->duration,
                      affect_bit_name( paf->bitvector ) );
                      send_to_char( buf, ch );
                   }

            }

     }

     return;

}

/*
void do_level( CHAR_DATA *ch, char *argument )
{
    char arg       [MAX_INPUT_LENGTH];
     char buf[MAX_STRING_LENGTH];
    char skill  [20];  
    char stance [20];
    one_argument( argument, arg );

    if (IS_NPC(ch)) return;  
   
   
    sprintf(buf,"********************************************\n\r");
    send_to_char(buf,ch);
    sprintf(buf,"* Weapon Skills|   Stances     |  Magic    *\n\r");
    send_to_char(buf,ch);
    sprintf(buf,"********************************************\n\r");
    send_to_char(buf,ch);
    sprintf(buf,"Unarmed : %3d  | Bull    : %3d | Purple: %3d\n\r",
 ch->wpn[0],ch->stance[STANCE_BULL],ch->spl[0]);
    send_to_char(buf,ch);
    sprintf(buf,"Slash   : %3d  | Viper   : %3d | Red   : %3d\n\r",
    ch->wpn[3],ch->stance[STANCE_VIPER],ch->spl[1]);
    send_to_char(buf,ch);
    sprintf(buf,"Slice   : %3d  | Crane   : %3d | Blue  : %3d\n\r",
    ch->wpn[1],ch->stance[STANCE_CRANE],ch->spl[2]);
    send_to_char(buf,ch);
    sprintf(buf,"Stab    : %3d  | Crab    : %3d | Green : %3d\n\r",
    ch->wpn[2],ch->stance[STANCE_CRAB],ch->spl[3]);   
 send_to_char(buf,ch);
    sprintf(buf,"Whip    : %3d  | Mongoose: %3d | Yellow: %3d\n\r",
    ch->wpn[4],ch->stance[STANCE_MONGOOSE],ch->spl[4]);
    send_to_char(buf,ch);
    sprintf(buf,"Claw    : %3d  | Tiger   : %3d |\n\r",
    ch->wpn[5],ch->stance[STANCE_TIGER]);
    send_to_char(buf,ch);
    sprintf(buf,"Blast   : %3d  | Mantis  : %3d |\n\r",
    ch->wpn[6],ch->stance[STANCE_MANTIS]);
    send_to_char(buf,ch);
 sprintf(buf,"Pound   : %3d  | Dragon  : %3d |\n\r",
    ch->wpn[7],ch->stance[STANCE_DRAGON]);
    send_to_char(buf,ch);
    sprintf(buf,"Crush   : %3d  | Swallow : %3d |\n\r",
    ch->wpn[8],ch->stance[STANCE_SWALLOW]);
    send_to_char(buf,ch);
    sprintf(buf,"Grep    : %3d  | Monkey  : %3d |\n\r",
    ch->wpn[9],ch->stance[STANCE_MONKEY]);
    send_to_char(buf,ch);
    sprintf(buf,"Bite    : %3d  |               |\n\r",ch->wpn[10]);
  send_to_char(buf,ch);
    sprintf(buf,"Pierce  : %3d  |               |\n\r",ch->wpn[11]);
    send_to_char(buf,ch);
    sprintf(buf,"Suck    : %3d  |               |\n\r",ch->wpn[12]);
    send_to_char(buf,ch);
    
 
      
    send_to_char("*************-= Misc. Things =-*************\n\r", ch);
    sprintf(skill, "Recall Room : %d                      \n\r",ch->home);
    send_to_char( skill, ch );

     if ( ch->stance[11] == 1 )
      sprintf(stance, " Viper" );
     else if ( ch->stance[11] == 2 )
      sprintf(stance, " Crane" );
     else if ( ch->stance[11] == 3 )
      sprintf(stance, " Crab" );  
     else if ( ch->stance[11] == 4 )
      sprintf(stance, " Mongoose" );  
     else if ( ch->stance[11] == 5 )
      sprintf(stance, " Bull" );  
     else if ( ch->stance[11] == 6 )
      sprintf(stance, " Mantis" );  
     else if ( ch->stance[11] == 7 )
      sprintf(stance, " Dragon" );  
     else if ( ch->stance[11] == 8 )
      sprintf(stance, " Tiger" );  
     else if ( ch->stance[11] == 9 )
      sprintf(stance, " Monkey" );  
     else if ( ch->stance[11] == 10 )
      sprintf(stance, " Swallow" ); 
     else if ( ch->stance[11] == -1 || ch->stance[11] == 15 )
      sprintf(stance, " None" );
     else
      sprintf(stance, " None" );
      sprintf(skill, "Autostance:  %s \n\r",stance);
      send_to_char( skill, ch );

	 send_to_char("*************-= Class Things =-*************\n\r",
ch);
    
    if ( IS_CLASS(ch, CLASS_DEMON) )
     send_to_char("You are a demon!                       \n\r", ch);
    if ( IS_CLASS(ch, CLASS_MAGE) )
     send_to_char("You are a mage!                        \n\r", ch);    
     if ( IS_CLASS(ch, CLASS_WEREWOLF) )
     send_to_char("You are a werewolf!                    \n\r", ch);
     if ( IS_CLASS(ch, CLASS_NINJA) )
     send_to_char("You are a ninja!                       \n\r", ch);
    if ( IS_CLASS(ch, CLASS_VAMPIRE) )
     send_to_char("You are a vampire!                     \n\r", ch);
    if ( IS_CLASS(ch, CLASS_HIGHLANDER) )
     send_to_char("You are a highlander!                  \n\r", ch);
    if ( IS_CLASS(ch, CLASS_DROW) )
     send_to_char("You are a drow!                     \n\r", ch);    
 if ( IS_ABOMINATION(ch))
stc("You are an Abomination!				\n\r",ch);


 if (IS_CLASS(ch, CLASS_VAMPIRE) )
 {

    sprintf(skill, "Generation : %d                       \n\r", ch->pcdata->stats[UNI_GEN]);
    send_to_char( skill, ch );	
	if (ch->pcdata->rank == AGE_METHUSELAH)
	  send_to_char("You are a Methuselah!                 \n\r", ch);
	else if (ch->pcdata->rank == AGE_ELDER)
	  send_to_char("You are an Elder!                     \n\r", ch);
	else if (ch->pcdata->rank == AGE_ANCILLA)
	  send_to_char("You are an Ancilla!                   \n\r", ch);
	else if (ch->pcdata->rank == AGE_NEONATE)
	  send_to_char("You are a Neonate!                    \n\r", ch);
	else
	  send_to_char(" You are a Childe!                     \n\r", ch);
	if ( IS_SET(ch->special, SPC_PRINCE) )
	  send_to_char("You are a prince!                     \n\r", ch);
 }
 
 if (IS_CLASS(ch, CLASS_NINJA) )
 {
    sprintf(skill, "Generation : %d\n\r", ch->pcdata->stats[UNI_GEN]);
    send_to_char( skill, ch );	
	if ( IS_SET(ch->special, SPC_PRINCE) )
	  send_to_char("You can discipline people!\n\r", ch);
 }
 
 if (IS_CLASS(ch, CLASS_WEREWOLF) )
 {
    sprintf(skill, "Generation : %d                         \n\r", ch->pcdata->stats[UNI_GEN]);
    send_to_char( skill, ch );	
    if ( IS_SET(ch->special, SPC_SIRE) && ch->pcdata->stats[UNI_GEN] > 2 )
      send_to_char("You are able to spread the gift!        \n\r", ch);
    if ( IS_SET(ch->special, SPC_PRINCE) && ch->pcdata->stats[UNI_GEN] > 2 )
	  send_to_char("You are a shaman!                   \n\r", ch);
 }
  
    sprintf(buf,"********************************************\n\r");
    send_to_char(buf,ch);
      return;
}
*/

void do_level( CHAR_DATA *ch, char *argument )
{
    char arg       [MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    char skill  [20];  
    char stance [20];
    one_argument( argument, arg );

    if (IS_NPC(ch)) return;  
    sprintf(buf, "-=+=-=+=-=+=-=+=-=+=-=+=-#r[#cThe Lords of War#r]#n-=+=-=+=-=+=-=+=-=+=-=+=-#n\n\r");
    send_to_char(buf,ch);
    sprintf(buf, "                           Weapons Skills\n\r\n\r");
    send_to_char(buf,ch);
    sprintf(buf, " Unarmed: %3d  Slash: %3d  Slice: %3d    Stab: %3d  Whip: %3d\n\r",
                     ch->wpn[0],         ch->wpn[3],       ch->wpn[1],       ch->wpn[2],       ch->wpn[4]);
    send_to_char(buf,ch);
    sprintf(buf, "   Blast: %3d   Claw: %3d  Pound: %3d   Crush: %3d  Grep: %3d\n\r",
                       ch->wpn[6],        ch->wpn[5],      ch->wpn[7],        ch->wpn[8],       ch->wpn[9]);
    send_to_char(buf,ch);
    sprintf(buf, "                Bite: %3d   Suck: %3d  Pierce: %3d\n\r",
                                          ch->wpn[10],     ch->wpn[12],     ch->wpn[11]);
    send_to_char(buf,ch);
    sprintf(buf, " -=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=***=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-#n\n\r");
    send_to_char(buf,ch);
    sprintf(buf, "                               Stances\n\r\n\r");
    send_to_char(buf,ch);
    sprintf(buf, "  Bull: %3d    Viper: %3d    Crane: %3d     Crab: %3d  Mongoose: %3d\n\r",
    ch->stance[STANCE_BULL], ch->stance[STANCE_VIPER], ch->stance[STANCE_CRANE], ch->stance[STANCE_CRAB], ch->stance[STANCE_MONGOOSE]);
    send_to_char(buf,ch);
    sprintf(buf, " Tiger: %3d   Mantis: %3d   Dragon: %3d  Swallow: %3d    Monkey: %3d\n\r",
    ch->stance[STANCE_TIGER], ch->stance[STANCE_MANTIS], ch->stance[STANCE_DRAGON], ch->stance[STANCE_SWALLOW], ch->stance[STANCE_MONKEY]);
    send_to_char(buf,ch);
    sprintf(buf, " Rabbit:%3d    Cobra: %3d     Bear: %3d    Eagle: %3d    Cougar: %3d\n\r", 
    ch->stance[STANCE_RABBIT], ch->stance[STANCE_COBRA], ch->stance[STANCE_BEAR], ch->stance[STANCE_EAGLE], ch->stance[STANCE_COUGAR]);
    send_to_char(buf,ch);

    sprintf(buf, " -=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=***=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-\n\r");
    send_to_char(buf,ch);
    sprintf(buf, "                               Spells\n\r\n\r");
    send_to_char(buf,ch);
    sprintf(buf, "   #PPurple#n: %3d   #RRed#n: %3d   #G Green#n: %3d   #BBlue#n: %3d   #yYellow#n: %3d\n\r",
                        ch->spl[0],       ch->spl[1],     ch->spl[3],       ch->spl[2],      ch->spl[4]);
    send_to_char(buf,ch);
    sprintf(buf, " -=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=***=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-\n\r");
    send_to_char(buf,ch);
    sprintf(buf, "                            Misc and Class\n\r\n\r");
    send_to_char(buf,ch);
    sprintf(skill, " Recall Room : %d          \n\r",ch->home);
    send_to_char( skill, ch );
    if ( ch->pcdata->autostance == 1 )
      sprintf(stance, " Viper" );
     else if ( ch->pcdata->autostance == 2 )
      sprintf(stance, " Crane" );
     else if ( ch->pcdata->autostance == 3 )
      sprintf(stance, " Crab" );  
     else if ( ch->pcdata->autostance == 4 )
      sprintf(stance, " Mongoose" );  
     else if ( ch->pcdata->autostance == 5 )
      sprintf(stance, " Bull" );  
     else if ( ch->pcdata->autostance == 6 )
      sprintf(stance, " Mantis" );  
     else if ( ch->pcdata->autostance == 7 )
      sprintf(stance, " Dragon" );  
     else if ( ch->pcdata->autostance == 8 )
      sprintf(stance, " Tiger" );  
     else if ( ch->pcdata->autostance == 9 )
      sprintf(stance, " Monkey" );  
     else if ( ch->pcdata->autostance == 10 )
      sprintf(stance, " Swallow" ); 
     else if ( ch->pcdata->autostance == 11 )
      sprintf(stance, " Rabbit" );
     else if ( ch->pcdata->autostance == 12 )
      sprintf( stance, " Cobra");
     else if ( ch->pcdata->autostance == 13 )
      sprintf( stance, " Bear");
     else if ( ch->pcdata->autostance == 14 )
      sprintf( stance, " Cougar");
     else if ( ch->pcdata->autostance == 15 )
      sprintf( stance, " Eagle");
     else if ( ch->pcdata->autostance == -1 || ch->pcdata->autostance == 16 )
      sprintf(stance, " None" );
     else
      sprintf(stance, " None" );
      sprintf(buf, " Autostance:  %s \n\r",stance);
     send_to_char(buf, ch);
     if ( IS_CLASS(ch, CLASS_DEMON) )
     send_to_char(" You are a demon!                       \n\r", ch);
     if ( IS_CLASS(ch, CLASS_MAGE) )
     send_to_char(" You are a mage!                        \n\r", ch);    
     if ( IS_CLASS(ch, CLASS_WEREWOLF) )
     send_to_char(" You are a werewolf!                    \n\r", ch);
     if ( IS_CLASS(ch, CLASS_NINJA) )
     send_to_char(" You are a ninja!                       \n\r", ch);
     if ( IS_CLASS(ch, CLASS_VAMPIRE) )
     send_to_char(" You are a vampire!                     \n\r", ch);
     if ( IS_CLASS(ch, CLASS_HIGHLANDER) )
     send_to_char(" You are a highlander!                  \n\r", ch);
     if ( IS_CLASS(ch, CLASS_DROW) )
     send_to_char(" You are a drow!                        \n\r", ch);    
     if ( IS_CLASS(ch, CLASS_PALADIN) )
     send_to_char(" You are a paladin!                     \n\r", ch);    
     if ( IS_CLASS(ch, CLASS_DRAGON) )
     send_to_char(" You are a dragon!                      \n\r", ch);    
 if (IS_CLASS(ch, CLASS_VAMPIRE) )
 {

    sprintf(skill, " Generation : %d                       \n\r", ch->pcdata->stats[UNI_GEN]);
    send_to_char( skill, ch );	
	if (ch->pcdata->rank == AGE_METHUSELAH)
	  send_to_char(" You are a Methuselah!                 \n\r", ch);
	else if (ch->pcdata->rank == AGE_ELDER)
	  send_to_char(" You are an Elder!                     \n\r", ch);
	else if (ch->pcdata->rank == AGE_ANCILLA)
	  send_to_char(" You are an Ancilla!                   \n\r", ch);
	else if (ch->pcdata->rank == AGE_NEONATE)
	  send_to_char(" You are a Neonate!                    \n\r", ch);
	else
	  send_to_char(" You are a Childe!                     \n\r", ch);
	if ( IS_SET(ch->special, SPC_PRINCE) )
	  send_to_char(" You are a prince!                     \n\r", ch);
 }
 
 if (IS_CLASS(ch, CLASS_NINJA) )
 {
    sprintf(skill, " Generation : %d\n\r", ch->pcdata->stats[UNI_GEN]);
    send_to_char( skill, ch );	
	if ( IS_SET(ch->special, SPC_PRINCE) )
	  send_to_char("You can discipline people!\n\r", ch);
 }
 
 if (IS_CLASS(ch, CLASS_WEREWOLF) )
 {
    sprintf(skill, " Generation : %d                         \n\r", ch->pcdata->stats[UNI_GEN]);
    send_to_char( skill, ch );	
    if ( IS_SET(ch->special, SPC_SIRE) && ch->pcdata->stats[UNI_GEN] > 2 )
      send_to_char(" You are able to spread the gift!        \n\r", ch);
    if ( IS_SET(ch->special, SPC_PRINCE) && ch->pcdata->stats[UNI_GEN] > 2 )
	  send_to_char(" You are a shaman!                   \n\r", ch);
 }
  
    sprintf(buf, "-=+=-=+=-=+=-=+=-=+=-=+=-#r[#cThe Lords of War#r]#n-=+=-=+=-=+=-=+=-=+=-=+=-#n\n\r");
    send_to_char(buf,ch);
      return;
}

void do_class( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
        
    if ( IS_NPC(ch) ) return;
    
    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Syntax: class <char> <class>.\n\r", ch );
	send_to_char("      Classes:\n\r", ch );
    send_to_char("None, ", ch);
    send_to_char("Demon, ", ch);
    send_to_char("Demon Lord , ", ch);
    send_to_char("Purple Mage, Blue Mage, Yellow Mage, Green Mage, Red Mage, ", ch);
    send_to_char("Werewolf, ", ch);
    send_to_char("Vampire, ", ch);
    send_to_char("Highlander, ", ch);
    //stc("Dragon.",ch);
	return;
    }
    
    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "That player is not here.\n\r", ch);
	return;
    }
    if ((victim->class != 0) && str_cmp(arg2, "none") ) 
    {
	stc("You must clear their class first.\n\r", ch);
	stc("Class <victim> none.\n\r", ch);
	return;
    }

         if ( !str_cmp( arg2, "none"       ) ) 
    {
    /* Used to make sure the person has enough "stuff" to change */
	victim->pcdata->condition[COND_THIRST] = 10000;
	victim->move = 10000;
	victim->mana = 10000;

	victim->pcdata->powers[WPOWER_BEAR]   = 4;
    victim->pcdata->powers[WPOWER_LYNX]   = 4;
	victim->pcdata->powers[WPOWER_BOAR]   = 4;
	victim->pcdata->powers[WPOWER_OWL]    = 4;
	victim->pcdata->powers[WPOWER_SPIDER] = 4; 
	victim->pcdata->powers[WPOWER_WOLF]   = 4;
	victim->pcdata->powers[WPOWER_HAWK]   = 4;
	victim->pcdata->powers[WPOWER_MANTIS] = 4;
	victim->pcdata->powers[WPOWER_TIGER]  = 4;
	victim->pcdata->powers[WPOWER_GAIA]   = 4;

	if ( IS_CLASS(victim, CLASS_WEREWOLF)
	     || IS_CLASS(victim, CLASS_VAMPIRE) ) do_unwerewolf(victim,"");
	if (IS_VAMPAFF(victim,VAM_DISGUISED) ) do_mask(victim,"self");
    victim->pcdata->stats[UNI_FORM0] = 0;
free_string( victim->clan ); 
/* All classes in general */   
    if (IS_VAMPAFF(victim,VAM_FANGS) )
    {
	send_to_char("Your fangs slide back into your gums.\n\r",victim);
	act("$n's fangs slide back into $s gums.", ch, NULL, victim, TO_ROOM);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FANGS);
    }
    if (IS_CLASS(victim, CLASS_VAMPIRE) && IS_VAMPAFF(victim,VAM_CLAWS) ) 
	{
	    send_to_char("Your claws slide back under your nails.\n\r",victim);
	    act("$N's claws slide back under $s nails.", ch, NULL, victim, TO_ROOM);
	    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
	}
	else if (IS_CLASS(victim, CLASS_NINJA) && IS_VAMPAFF(victim,VAM_CLAWS) ) 
 	{
	 	send_to_char("You shove your iron claws up your sleeves\n\r",victim);
	    act("$N shoves $S iron claws up $e sleeves.", ch, NULL, victim, TO_ROOM);
	    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
    }
    else if (IS_CLASS(victim, CLASS_WEREWOLF) && IS_VAMPAFF(victim,VAM_CLAWS) ) 
    {
    	send_to_char("Your talons slide back into your fingers.\n\r",victim);
	    act("$N's talons slide back into $s fingers.",ch,NULL,victim,TO_ROOM);
    	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
    }

    if (IS_VAMPAFF(victim,VAM_NIGHTSIGHT) )
    {
	 send_to_char("The red glow in your eyes fades.\n\r",victim);
	 act("The red glow in $N's eyes fades.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT);
    }
    if (IS_AFFECTED(victim,AFF_SHADOWSIGHT) )
    {
	 send_to_char("You can no longer see between planes.\n\r",victim);
	 REMOVE_BIT(victim->affected_by, AFF_SHADOWSIGHT);
    }
    
    if (IS_IMMUNE(victim,IMM_SHIELDED) )
    {
     send_to_char("You stop shielding your aura.\n\r",victim);
     REMOVE_BIT(victim->immune, IMM_SHIELDED);
    }
    
    if (IS_VAMPAFF(victim,VAM_DISGUISED) )
    {
     free_string( victim->morph );
     victim->morph = str_dup( victim->name );
     send_to_char("You transform into yourself.\n\r", victim);
     REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_DISGUISED);
    }
    
    if (IS_AFFECTED(victim,AFF_SHADOWPLANE) )
    {
     send_to_char("You fade back into the real world.\n\r",victim);
	 act("The shadows flicker and $N fades into existance.",ch,NULL,victim,TO_ROOM);
	 REMOVE_BIT(victim->affected_by,AFF_SHADOWPLANE);
	 do_look(ch,"auto");
	}
	
	if (IS_SET(victim->act, PLR_WIZINVIS) )
	{
	 REMOVE_BIT(victim->act, PLR_WIZINVIS);
	 send_to_char( "You slowly fade into existence.\n\r", victim );
	}
	
	if (IS_SET(victim->act, PLR_HOLYLIGHT) )
	{
	 REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	 REMOVE_BIT(victim->act, PLR_DROWSIGHT);
	 send_to_char( "Your senses return to normal.\n\r", victim );
	}
	
/* Demon Stuff */
    if (IS_DEMAFF(victim,DEM_HORNS) && IS_CLASS(victim, CLASS_DEMON) )
    {
	 send_to_char("Your horns slide back into your head.\n\r",victim);
	 act("$N's horns slide back into $s head.", ch, NULL, victim, TO_ROOM);
	 REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_HORNS);
	}
	
	if (IS_DEMAFF(victim,DEM_HOOVES) && IS_CLASS(victim, CLASS_DEMON) )
    {
	 send_to_char("Your hooves transform into feet.\n\r",victim);
	 act("$N's hooves transform back into $s feet.", ch, NULL,victim,TO_ROOM);
	 REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_HOOVES);
    }
    
    if (IS_DEMAFF(victim,DEM_WINGS) && IS_CLASS(victim, CLASS_DEMON) )
    {
	if (IS_DEMAFF(victim,DEM_UNFOLDED) && IS_CLASS(victim, CLASS_DEMON) )
	{
	    send_to_char("Your wings fold up behind your back.\n\r",victim);
	    act("$N's wings fold up behind $s back.", ch, NULL, victim, TO_ROOM);
	    REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_UNFOLDED);
	}
	send_to_char("Your wings slide into your back.\n\r",victim);
	act("$N's wings slide into $s back.", ch, NULL, victim, TO_ROOM);
	REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_WINGS);
    }
    
	if ( IS_EXTRA(victim, EXTRA_OSWITCH) ) 
	{
	 do_humanform(victim,"");
	}
	
	REMOVE_BIT(victim->affected_by, AFF_SHADOWPLANE);
	REMOVE_BIT(victim->affected_by, AFF_POLYMORPH); 
	REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
	REMOVE_BIT(victim->immune, IMM_SHIELDED); 
        REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FANGS);
        REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
        REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT);
        REMOVE_BIT(victim->affected_by, AFF_SHADOWSIGHT);   
REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_PROTEAN);  
REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_VICISSITUDE);
         REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CELERITY);
                  REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FORTITUDE);
             REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_POTENCE);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_OBTENEBRATION);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_SERPENTIS);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_AUSPEX);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_DOMINATE);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_PRESENCE);
    REMOVE_BIT(victim->polyaff, POLY_ZULO);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_DISGUISED);  
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FLYING);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_SONIC);
    REMOVE_BIT(victim->polyaff, POLY_BAT);
    REMOVE_BIT(victim->polyaff, POLY_MIST);
    REMOVE_BIT(victim->affected_by, AFF_ETHEREAL);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CHANGED);
    REMOVE_BIT(victim->extra, EXTRA_FAKE_CON);         
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_MORTAL);
    REMOVE_BIT(victim->immune, IMM_SHIELDED);
    REMOVE_BIT(victim->polyaff, POLY_SERPENT);
    REMOVE_BIT(victim->special, SPC_WOLFMAN);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CLAWS);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FANGS);
    REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT);
    REMOVE_BIT(victim->newbits, NEW_NOPAIN);
REMOVE_BIT(ch->newbits, NEW_NEUTRAL);
    REMOVE_BIT(victim->special, SPC_DEMON_LORD);

	              REMOVE_BIT(victim->warp, WARP_CBODY);
        REMOVE_BIT(victim->warp, WARP_SBODY);
	REMOVE_BIT(victim->warp, WARP_STRONGARMS);
	 REMOVE_BIT(victim->warp, WARP_STRONGLEGS);
	 REMOVE_BIT(victim->warp, WARP_VENOMTONG);
	 REMOVE_BIT(victim->warp, WARP_SPIKETAIL);
	 REMOVE_BIT(victim->warp, WARP_BADBREATH);
	 REMOVE_BIT(victim->warp, WARP_QUICKNESS);
	 REMOVE_BIT(victim->warp, WARP_STAMINA);
	 REMOVE_BIT(victim->warp, WARP_HUNT);
	 REMOVE_BIT(victim->warp, WARP_DAMCAP);
	 REMOVE_BIT(victim->warp, WARP_TERROR);
	 REMOVE_BIT(victim->warp, WARP_REGEN);
	 REMOVE_BIT(victim->warp, WARP_STEED);
	 REMOVE_BIT(victim->warp, WARP_WEAPON);
	 REMOVE_BIT(victim->warp, WARP_INFIRMITY);
	 REMOVE_BIT(victim->warp, WARP_GBODY);
	 REMOVE_BIT(victim->warp, WARP_SCARED);
	 REMOVE_BIT(victim->warp, WARP_MAGMA);
	 REMOVE_BIT(victim->warp, WARP_WEAK);
	 REMOVE_BIT(victim->warp, WARP_SLOW);
	 REMOVE_BIT(victim->warp, WARP_VULNER);
	 REMOVE_BIT(victim->warp, WARP_SHARDS);
	 REMOVE_BIT(victim->warp, WARP_WINGS);
	 REMOVE_BIT(victim->warp, WARP_CLUMSY);
	 REMOVE_BIT(victim->warp, WARP_STUPID);
	 REMOVE_BIT(victim->warp, WARP_SPOON);
	 REMOVE_BIT(victim->warp, WARP_FORK);
	 REMOVE_BIT(victim->warp, WARP_KNIFE);


        REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_HORNS);
        REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_TAIL);
        REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_HOOVES);
            REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_UNFOLDED);
            REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_UNFOLDED);
        REMOVE_BIT(victim->pcdata->powers[DPOWER_CURRENT], DEM_WINGS);
    REMOVE_BIT(victim->extra, EXTRA_OSWITCH);
            REMOVE_BIT(victim->newbits, NEW_DROWHATE);
        REMOVE_BIT(victim->polyaff, POLY_SPIDERFORM);
               REMOVE_BIT(victim->newbits, NEW_DARKNESS);
                 REMOVE_BIT(victim->monkstuff, MONK_DEATH);
                 REMOVE_BIT(victim->monkstuff, MONK_HEAL);
             REMOVE_BIT(victim->garou1, WOLF_COCOON);
        REMOVE_BIT(victim->newbits, NEW_QUILLS);
      REMOVE_BIT(victim->garou1, WOLF_RAZORCLAWS);
    REMOVE_BIT(victim->garou1, WW_GRANITE);
   REMOVE_BIT(victim->garou1, GAROU_CLENCHED);
    REMOVE_BIT(victim->garou1, GAROU_AVENGER);
        REMOVE_BIT( victim->affected_by, AFF_STEELSHIELD );
           REMOVE_BIT(victim->newbits, NEW_MONKFLAME);
          REMOVE_BIT(victim->newbits, NEW_MONKADAM);
                  REMOVE_BIT(victim->newbits, NEW_POWER);
          REMOVE_BIT(victim->act, PLR_WIZINVIS);
                  REMOVE_BIT(victim->extra, EXTRA_STANCE);                             
                        REMOVE_BIT(victim->act, OLD_PLR_DEMON);
                        REMOVE_BIT(victim->act, OLD_PLR_CHAMPION);
                        REMOVE_BIT(victim->extra, OLD_EXTRA_SIRE);
                        REMOVE_BIT( victim->extra, OLD_EXTRA_PRINCE );
                        REMOVE_BIT(victim->extra, OLD_EXTRA_PRINCE);
                        REMOVE_BIT(victim->act, OLD_PLR_WEREWOLF);
                        REMOVE_BIT(victim->act, OLD_PLR_WOLFMAN);
                        REMOVE_BIT(victim->extra, OLD_EXTRA_SIRE);
                        REMOVE_BIT( victim->extra, OLD_EXTRA_PRINCE );
                        REMOVE_BIT( victim->extra, OLD_EXTRA_ANARCH );
                        REMOVE_BIT( victim->extra, OLD_EXTRA_INCONNU );
                        REMOVE_BIT(victim->act, OLD_PLR_VAMPIRE);
                        REMOVE_BIT(victim->extra, OLD_EXTRA_HIGHLANDER);
                        REMOVE_BIT( victim->extra, OLD_EXTRA_PRINCE );
                        REMOVE_BIT( victim->extra, OLD_EXTRA_ANARCH );
                        REMOVE_BIT( victim->extra, OLD_EXTRA_INCONNU );
                        REMOVE_BIT(victim->act, OLD_PLR_VAMPIRE);
                        REMOVE_BIT(victim->extra, EXTRA_POTENCY);
                     REMOVE_BIT(victim->newbits, NEW_TIDE);
      REMOVE_BIT(victim->flag2, AFF2_SPIRITGUARD);
         REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_HORNS);
          REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_WINGS);
          REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_EXOSKELETON);
          REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_TAIL);
          REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_HEAD);
      REMOVE_BIT(victim->flag2, VAMP_OBJMASK);          
      REMOVE_BIT(victim->extra, EXTRA_AWE);   
      REMOVE_BIT(victim->extra,EXTRA_DRAGON);
            REMOVE_BIT(victim->extra, EXTRA_PLASMA);
            REMOVE_BIT(victim->newbits, NEW_COIL);
                        REMOVE_BIT(victim->affected_by, AFF_SHIFT);
            REMOVE_BIT(victim->extra, EXTRA_EARTHMELD);
            REMOVE_BIT(victim->extra, EXTRA_ASH);
            REMOVE_BIT(victim->affected_by, AFF_SHADOWSIGHT);
                REMOVE_BIT(victim->mflags, MAGE_POLYAPPEAR);
    REMOVE_BIT(victim->mflags, MAGE_TELEKINETICS);
        REMOVE_BIT(victim->mflags, MFLAGS_DIMMAK);
    REMOVE_BIT(victim->mflags, MAGE_BETTERBODY);   
       REMOVE_BIT(victim->mflags, MAGE_SHAPED); 
	
	REMOVE_BIT(victim->special, SPC_CHAMPION );
	REMOVE_BIT(victim->special, SPC_INCONNU );
	REMOVE_BIT(victim->special, SPC_ANARCH );
    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_PRINCE);
    REMOVE_BIT(victim->special, SPC_DEMON_LORD);
    REMOVE_BIT(victim->special, SPC_DROW_WAR );
    REMOVE_BIT(victim->special, SPC_DROW_MAG );
    REMOVE_BIT(victim->special, SPC_DROW_CLE );
	REMOVE_BIT(victim->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_CHANGED);
    REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_MIST);
	REMOVE_BIT(victim->affected_by, AFF_ETHEREAL);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_FLYING);
	REMOVE_BIT(victim->pcdata->stats[UNI_AFF], VAM_SONIC);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_BAT);
	REMOVE_BIT(victim->pcdata->powers[WOLF_POLYAFF], POLY_WOLF);
	 REMOVE_BIT(ch->newbits, NEW_POWER);
	victim->warpcount = 0;
	victim->monkstuff = 0;
	victim->monkcrap = 0;
victim->spheres[MCOR] = 0;			
victim->monkab[SPIRIT] = 0;
victim->monkab[BODY] = 0; 
victim->monkab[COMBAT] = 0;
victim->monkab[AWARE] = 0;
victim->spheres[MLIF] = 0;			
victim->spheres[MPRI] = 0;			
victim->spheres[MENT] = 0;			
victim->spheres[MMIN] = 0;			
victim->spheres[MSPI] = 0;			
victim->spheres[MFOR] = 0;			
victim->spheres[MMAT] = 0;			
victim->spheres[MTIM] = 0;

	victim->pcdata->powers[DPOWER_FLAGS] = 0;
  	victim->pcdata->stats[DEMON_TOTAL] = 0;
	victim->pcdata->stats[DEMON_CURRENT] = 0;
	victim->pcdata->powers[WPOWER_BEAR]   = 0;
    victim->pcdata->powers[WPOWER_LYNX]   = 0;
	victim->pcdata->powers[WPOWER_BOAR]   = 0;
	victim->pcdata->powers[WPOWER_OWL]    = 0;
	victim->pcdata->powers[WPOWER_SPIDER] = 0; 
	victim->pcdata->powers[WPOWER_WOLF]   = 0;
	victim->pcdata->powers[WPOWER_HAWK]   = 0;
	victim->pcdata->powers[WPOWER_MANTIS] = 0;
	victim->pcdata->powers[WPOWER_TIGER] = 0;
	victim->pcdata->powers[WPOWER_GAIA] = 0;
  	victim->pcdata->powers[VAM_ANIM]   = 0;
 victim->gifts[STARGAZERS] = 0; 
 victim->gifts[HOMID] = 0;      	
 victim->gifts[METIS] = 0;     	
 victim->gifts[LUPUS] = 0; 
 victim->gifts[RAGABASH] = 0; 	
 victim->gifts[THEURGE] = 0; 		
 victim->gifts[PHILODOX] = 0; 	
 victim->gifts[GALLIARD] = 0; 	
 victim->gifts[AHROUN] = 0; 		
 victim->gifts[BLACKFURIES] = 0; 	
 victim->gifts[BONEGNAWERS] = 0; 	
 victim->gifts[CHILDREN] = 0; 	
 victim->gifts[CHILDRENOFGAIA] = 0;   
 victim->gifts[FIANNA] = 0; 		
 victim->gifts[GETOFFENRIS] = 0; 	
 victim->gifts[GLASSWALKERS] = 0; 	
 victim->gifts[REDTALONS] = 0; 	
 victim->gifts[SHADOWLORDS] = 0; 	
 victim->gifts[SILENTSTRIDERS] = 0; 	
 victim->gifts[SILVERFANGS] = 0; 	
 victim->gifts[UKTENA] = 0; 		
 victim->gifts[WENDIGO] = 0; 		
victim->pcdata->powers[VAM_OBTE]   = 0;
victim->pcdata->powers[VAM_THAU]   = 0;
victim->pcdata->powers[VAM_OBFU]   = 0;
victim->pcdata->powers[VAM_SERP]   = 0;
victim->pcdata->powers[VAM_CHIM]   = 0;
victim->pcdata->powers[VAM_NECR]   = 0;
victim->pcdata->powers[VAM_CELE]   = 0;
victim->pcdata->powers[VAM_PRES]   = 0;
victim->pcdata->powers[VAM_AUSP]   = 0;
victim->pcdata->powers[VAM_POTE]   = 0;
victim->pcdata->powers[VAM_VICI]   = 0;
victim->pcdata->powers[VAM_OBEA]   = 0;
victim->pcdata->powers[VAM_FORT]   = 0;
victim->pcdata->powers[VAM_QUIE]   = 0;
victim->pcdata->powers[VAM_DOMI]   = 0;
victim->pcdata->powers[VAM_PROT]   = 0;
victim->pcdata->powers[VAM_DAIM]   = 0;
victim->pcdata->powers[VAM_MELP]   = 0;
victim->pcdata->powers[VAM_THAN]   = 0;
        victim->pcdata->powers[NPOWER_SORA]     = 0;
  	victim->pcdata->powers[NPOWER_CHIKYU]   = 0;
	victim->pcdata->powers[NPOWER_NINGENNO] = 0;
	victim->pcdata->powers[1] = 0;
	victim->pcdata->condition[COND_THIRST] = 0;
	victim->move = victim->max_move;
	victim->mana = victim->max_mana;
	victim->hit = victim->max_hit;
	victim->pcdata->rank = 0;
	
	victim->pcdata->stats[UNI_RAGE] = 0;
    free_string(victim->lord);
    victim->lord     = str_dup( "" );
    free_string(victim->clan);
    victim->clan     = str_dup( "" );
    victim->pcdata->stats[UNI_GEN]     = 0;
    victim->pcdata->stats[UNI_AFF]     = 0;
    victim->pcdata->stats[UNI_CURRENT] = -1;
    victim->beast = 15;
    
    victim->class = 0;
    if ( !IS_IMMORTAL(victim) )
    {
       victim->trust = 0;
       victim->level = 2;
    }
    clear_stats(victim);
    send_to_char("You are classless now!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "demon"      ) ) 
    { 
    victim->class = 1;
   if (!IS_IMMORTAL(victim) )
       victim->level = 3;
    SET_BIT( victim->special, SPC_CHAMPION );
    victim->lord=str_dup(ch->name);
    send_to_char("You are now a demon!\n\r", victim);
    }
/*
    else if ( !str_cmp( arg2, "dragon" 	) )
    {
        victim->class = CLASS_DRAGON;
        victim->pcdata->disc_a[DRAGON_AGE] = 1;
        victim->pcdata->disc_a[DRAGON_COLOR] = number_range(1,9);
        stc("You are now a dragon.\n\r",victim);
    }
*/
    else if ( !str_cmp( arg2, "demon lord"      ) ) 
    {
    victim->class = 1;
  if (!IS_IMMORTAL(victim) )
    victim->level = 3;
    SET_BIT( victim->special, SPC_DEMON_LORD );
    victim->lord=str_dup(victim->name);
    send_to_char("You are now a Demon Lord!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "purple mage"     ) )
    {
    victim->class = 2;
    if ( victim->trust > 6 )
    {
    victim->trust = victim->trust;
    victim->level = victim->level;
    }
    else
    {
    victim->trust = 6;
    victim->level = 6;
    }
    victim->pcdata->powers[MPOWER_RUNE0] = 0;
    victim->pcdata->powers[MPOWER_RUNE1] = 2047;
    victim->pcdata->powers[MPOWER_RUNE2] = 1023;
    victim->pcdata->powers[MPOWER_RUNE3] = 15;    
    send_to_char("You are now a purple mage!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "red mage"     ) )
    {
    victim->class = 2;
    if ( victim->trust > 6 )
    {
    victim->trust = victim->trust;
    victim->level = victim->level;
    }
    else
    {
    victim->trust = 6;
    victim->level = 6;
    }
    victim->pcdata->powers[MPOWER_RUNE0] = 1;
    victim->pcdata->powers[MPOWER_RUNE1] = 2047;
    victim->pcdata->powers[MPOWER_RUNE2] = 1023;
    victim->pcdata->powers[MPOWER_RUNE3] = 15;    
    send_to_char("You are now a red mage!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "yellow mage"     ) )
    {
    victim->class = 2;
    if ( victim->trust > 6 )
    {
    victim->trust = victim->trust;
    victim->level = victim->level;
    }
    else
    {
    victim->trust = 6;
    victim->level = 6;
    }
    victim->pcdata->powers[MPOWER_RUNE0] = 4;
    victim->pcdata->powers[MPOWER_RUNE1] = 2047;
    victim->pcdata->powers[MPOWER_RUNE2] = 1023;
    victim->pcdata->powers[MPOWER_RUNE3] = 15;    
    send_to_char("You are now a yellow mage!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "blue mage"     ) )
    {
    victim->class = 2;
    if ( victim->trust > 6 )
    {
    victim->trust = victim->trust;
    victim->level = victim->level;
    }
    else
    {
    victim->trust = 6;
    victim->level = 6;
    }
    victim->pcdata->powers[MPOWER_RUNE0] = 2;
    victim->pcdata->powers[MPOWER_RUNE1] = 2047;
    victim->pcdata->powers[MPOWER_RUNE2] = 1023;
    victim->pcdata->powers[MPOWER_RUNE3] = 15;
    send_to_char("You are now a blue mage!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "green mage"     ) )
    {
    victim->class = 2;
    if ( victim->trust > 6 )
    {
    victim->trust = victim->trust;
    victim->level = victim->level;
    }
    else
    {
    victim->trust = 6;
    victim->level = 6;
    }
    victim->pcdata->powers[MPOWER_RUNE0] = 3;
    victim->pcdata->powers[MPOWER_RUNE1] = 2047;
    victim->pcdata->powers[MPOWER_RUNE2] = 1023;
    victim->pcdata->powers[MPOWER_RUNE3] = 15;
    send_to_char("You are now a green mage!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "werewolf"   ) ) 
    {
    victim->class = 4;
   if (!IS_IMMORTAL(victim) )
    victim->level = 3;
    send_to_char("You are now a werewolf!\n\r", victim);
    }
/*
else if ( !str_cmp( arg2, "abomination" ))
{
victim->class = 3;
if (!IS_IMMORTAL(victim) )
    victim->level = 3;
    send_to_char("You are now an abomination!\n\r", victim);
    }
*/  
  else if ( !str_cmp( arg2, "vampire"    ) ) 
    {
    victim->class = 8;
   if (!IS_IMMORTAL(victim) )
    victim->level = 3;
    send_to_char("You are now a vampire!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "highlander" ) ) 
    {
    victim->class = 16;
   if (!IS_IMMORTAL(victim) )
    victim->level = 3;
    send_to_char("You are now a highlander!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "ninja"      ) ) 
    {
     victim->class = 128;
    if ( victim->trust > 6 )
     {
       victim->trust = victim->trust;
       victim->level = victim->level;
     }
     else
     {  
     victim->trust = 6;
     victim->level = 6;
     }
     send_to_char("You are now a ninja!\n\r", victim);
    }    
    else if ( !str_cmp( arg2, "monk"      ) )
    {
     victim->class = 512;
    if ( victim->trust > 6 )
     {
       victim->trust = victim->trust;
       victim->level = victim->level;
     }
     else
     {  
     victim->trust = 6;
     victim->level = 6;
     }
     send_to_char("You are now a monk!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "drow"       ) ) 
    {
    victim->class = 32;
    if (!IS_IMMORTAL(victim) )
    ch->level = 3;
    send_to_char("You are now a drow!\n\r", victim);
    }
/*
    else if ( !str_cmp( arg2, "paladin"       ) )
    {
    victim->class = 256;
    send_to_char("You are now a paladin!\n\r", victim);
    }
*/
    else
    {
	send_to_char( "Syntax: class <char> <class>.\n\r", ch );
	send_to_char("      Classes:\n\r", ch );
    send_to_char("None, ", ch);
    send_to_char("Demon, ", ch);
    send_to_char("Demon Lord , ", ch);
    send_to_char("Purple Mage, Blue Mage, Yellow Mage, Green Mage, Red Mage, ", ch);
    send_to_char("Werewolf, ", ch);
    send_to_char("Vampire, ", ch);
    send_to_char("Ninja, ", ch);
    send_to_char("Monk, ", ch);
    send_to_char("Highlander, ", ch);
    send_to_char("Drow. ", ch);
	return;
    }
    send_to_char("Class Set.\n\r",ch);
    return;
}

void do_generation( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    int gen;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
        
    if ( IS_NPC(ch) ) return;
    
    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Syntax: generation <char> <generation>.\n\r", ch );
    send_to_char("Generation 1 is a Master <Class> and 2 is clan leader.\n\r", ch);
	return;
    }
    
    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "That player is not here.\n\r", ch);
	return;
    }
    
    gen = is_number( arg2 ) ? atoi( arg2 ) : -1;

    send_to_char("Generation Set.\n\r",ch);
    victim->pcdata->stats[UNI_GEN] = gen;
    return;
}
/*
void do_autostance( CHAR_DATA *ch, char *argument )
{
	char arg       [MAX_INPUT_LENGTH];	
	int selection;
	
	one_argument( argument, arg );

    if (IS_NPC(ch)) return;  
	
    if (!str_cmp(arg,"none")    ) 
    {
    selection = STANCE_NONE;
	send_to_char("You're autostance has been removed.\n\r",ch);
	REMOVE_BIT(ch->extra, EXTRA_STANCE);
	}
    else if (!str_cmp(arg,"viper")   ) 
    {
    selection = STANCE_VIPER;
	send_to_char("Viper stance set.\n\r",ch);
	}
    else if (!str_cmp(arg,"crane")   ) 
    {
    selection = STANCE_CRANE;
	send_to_char("Crane stance set.\n\r",ch);
	}
    else if (!str_cmp(arg,"crab")    ) 
    {
    selection = STANCE_CRAB;
	send_to_char("Crab stance set.\n\r",ch);
	}
    else if (!str_cmp(arg,"mongoose")) 
    {
    selection = STANCE_MONGOOSE;
	send_to_char("Mongoose stance set.\n\r",ch);
	}
    else if (!str_cmp(arg,"bull")    ) 
    {
    selection = STANCE_BULL;
	send_to_char("Bull stance set.\n\r",ch);
	}
    else
    {
	if (!str_cmp(arg,"mantis") && ch->stance[STANCE_CRANE] >= 200 &&
	    ch->stance[STANCE_VIPER] >= 200)
	{
	    selection = STANCE_MANTIS;
	    send_to_char("Mantis stance set.\n\r",ch);
	}
	else if (!str_cmp(arg,"dragon") && ch->stance[STANCE_BULL] >= 200 &&
	    ch->stance[STANCE_CRAB] >= 200)
	{
	    selection = STANCE_DRAGON;
	    send_to_char("Dragon stance set.\n\r",ch);
	}
	else if (!str_cmp(arg,"tiger") && ch->stance[STANCE_BULL] >= 200 &&
	    ch->stance[STANCE_VIPER] >= 200)
	{
	    selection = STANCE_TIGER;
	    send_to_char("Tiger stance set.\n\r",ch);
	}
	else if (!str_cmp(arg,"monkey") && ch->stance[STANCE_CRANE] >= 200 &&
	    ch->stance[STANCE_MONGOOSE] >= 200)
	{
	    selection = STANCE_MONKEY;
	    send_to_char("Monkey stance set.\n\r",ch);
	}
	else if (!str_cmp(arg,"swallow") && ch->stance[STANCE_CRAB] >= 200 &&
	    ch->stance[STANCE_MONGOOSE] >= 200)
	{
	    selection = STANCE_SWALLOW;
	    send_to_char("Swallow  stance set.\n\r",ch);
	}
	else
	{
	    send_to_char("Syntax is: autostance <style>.\n\r",ch);
	    send_to_char("Autotance being one of: None, Viper, Crane, Crab, Mongoose,
Bull.\n\r",ch);
	    send_to_char("      If you know them:  Mantis, Dragon, Tiger, Monkey,
Swallow.\n\r",ch);
	    return;
	}
    }
    ch->stance[11] = selection;
    SET_BIT(ch->extra, EXTRA_STANCE);
    return;
}
*/
void reset_weapon( CHAR_DATA *ch, int dtype )
{
	if ( ch->wpn[dtype] > 200 )
		ch->wpn[dtype] = 200;
	return;
}

void reset_spell( CHAR_DATA *ch, int dtype )
{
	if ( ch->spl[dtype] > 200 )
		ch->spl[dtype] = 200;
	return;
}


void do_reimburse( CHAR_DATA *ch, char *argument)
{
    char buf[MAX_STRING_LENGTH];
    char strsave[MAX_STRING_LENGTH];
    char *word;
    FILE *fp;
    bool fMatch;

if ( IS_SET(ch->flag2, AFF2_REIMB) )
    {
      stc("You already have a pfile.\n\r",ch);
      return;
    }
 
sprintf(strsave,"%s%s",BACKUP_DIR,ch->name);
if ( ( fp= fopen(strsave,"r")) == NULL)
{
send_to_char("You dont have a reimbursement file.\n\r",ch);
return;
}

if ( ( fp = fopen( strsave,"r")) != NULL)
{
 
 
    for ( ; ; )
    {
	word   = feof( fp ) ? "End" : fread_word( fp );
	fMatch = FALSE;
 
	switch ( UPPER(word[0]) )
	{
	case '*':
	    fMatch = TRUE;
	    fread_to_eol( fp );
	    break;
 
        case 'H':
	    if ( !str_cmp( word, "HpManaMove" ) )
	    {
		ch->hit		= fread_number( fp );
		ch->max_hit	= fread_number( fp );
		ch->mana	= fread_number( fp );
		ch->max_mana	= fread_number( fp );
		ch->move	= fread_number( fp );
		ch->max_move	= fread_number( fp );
                send_to_char("***Hp/Mana/Move Reimbursed.\n\r",ch);
		fMatch = TRUE;
		break;
	    }
	    break;
 
 
          
        case 'P':
           if ( !str_cmp(word, "Primal" ) )
           {
           ch->practice =  fread_number( fp );
           fMatch = TRUE;
            send_to_char("***Primal reimbursed.\n\r",ch);
           break;
           }
            if (!str_cmp(word,"PkPdMkMd"))
            {
            ch->pkill= fread_number(fp);
            ch->pdeath= fread_number(fp);
            ch->mkill= fread_number(fp);
            ch->mdeath= fread_number(fp);
            send_to_char("***Player/Mob Deaths/Kills restored.\n\r",ch);
            fMatch=TRUE;
             break;
              }           
  break; 
 
	case 'S':
 
 
 
	    if ( !str_cmp( word, "Spells" ) )
	    {
		ch->spl[0]	= fread_number( fp );
		ch->spl[1]	= fread_number( fp );
		ch->spl[2]	= fread_number( fp );
		ch->spl[3]	= fread_number( fp );
		ch->spl[4]	= fread_number( fp );
                send_to_char("***Spell level reimbursed.\n\r",ch);
		fMatch = TRUE;
		break;
	    }
 
 
	    if ( !str_cmp( word, "Stance" ) )
	    {
		ch->stance[0]	= fread_number( fp );
		ch->stance[1]	= fread_number( fp );
		ch->stance[2]	= fread_number( fp );
		ch->stance[3]	= fread_number( fp );
		ch->stance[4]	= fread_number( fp );
		ch->stance[5]	= fread_number( fp );
		ch->stance[6]	= fread_number( fp );
		ch->stance[7]	= fread_number( fp );
		ch->stance[8]	= fread_number( fp );
		ch->stance[9]	= fread_number( fp );
		ch->stance[10]	= fread_number( fp );
		fMatch = TRUE;
                send_to_char("***Stances reimbursed.\n\r",ch);
		break;
	    }
           
 
	    break;

        case 'E':
         
         if (!str_cmp(word,"End"))
         {
          send_to_char("***Reimbursed.. Player saved.\n\r",ch);
          send_to_char("***If you havnt noticed, There was a pwipe.\n\r",ch);
          send_to_char("***We have reimbursed what we could but you will have to earn the rest.\n\r",ch);
          send_to_char("***Classes will be passed out again. -Sage\n\r",ch);
          ch->level = 3;
          ch->trust = 3;
          ch->exp += 250000;
	  do_autosave(ch,"");
	  SET_BIT(ch->flag2, AFF2_REIMB);	  
          return;
          fMatch= TRUE;
           break;
         }
         break; 

	case 'W':
	    if ( !str_cmp( word, "Weapons" ) )
	    {
		ch->wpn[0]	= fread_number( fp );
		ch->wpn[1]	= fread_number( fp );
		ch->wpn[2]	= fread_number( fp );
		ch->wpn[3]	= fread_number( fp );
		ch->wpn[4]	= fread_number( fp );
		ch->wpn[5]	= fread_number( fp );
		ch->wpn[6]	= fread_number( fp );
		ch->wpn[7]	= fread_number( fp );
		ch->wpn[8]	= fread_number( fp );
		ch->wpn[9]	= fread_number( fp );
		ch->wpn[10]	= fread_number( fp );
		ch->wpn[11]	= fread_number( fp );
		ch->wpn[12]	= fread_number( fp );
                send_to_char("Weapons reimbursed.\n\r",ch);
		fMatch = TRUE;
		break;
	    }
            break;
	}
 
	if ( !fMatch )
	{
	    sprintf(buf, "Fread_char: no match. WORD: %s", word);
	    fread_to_eol( fp );
	}
       
       }
      }
return;
}

/* 
 * Class Power setting commands for Werewolves and Vampires
 * -Tijer
 */

void do_discset( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA   *victim;
    char        arg1[MAX_INPUT_LENGTH];
    char        arg2[MAX_INPUT_LENGTH];
    char        arg3[MAX_INPUT_LENGTH];
    sh_int      disc = 0;
    sh_int      value = 0;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    argument = one_argument( argument, arg3 );

    if ( IS_NPC( ch ) )
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }
    if ( arg1[0] == '\0' || arg2[0] == '\0' || arg3[0] == '\0' )
    {
        send_to_char( "Syntax : setdisc [victim] [disc/all] [level]\n\r\n\r", ch);
        send_to_char( " Disc being one of:\n\r", ch );
        send_to_char( "  animalism auspex celerity chimerstry\n\r", ch );
        send_to_char( "  daimoinon dominate fortitude melpominee\n\r", ch );
        send_to_char( "  necromancy obeah obfuscate obtenebration\n\r", ch );
        send_to_char( "  potence presence protean quietus serpentis\n\r", ch );
        send_to_char( "  thanatosis thaumaturgy vicissitude\n\r", ch );
        return;
    }
    
    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
        send_to_char( "They aren't here.\n\r", ch );
        return;
    }
     
    if ( IS_NPC(victim ) )
    {
       send_to_char( "Not on NPC's.\n\r", ch );
        return;
    }
        
    if ( !IS_CLASS(victim, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
        send_to_char( "Only on Vampires and Abomination!\n\r", ch );
        return;
    }
     
        
    if ( !str_cmp( arg2, "all" ) )
    {
        value = is_number( arg3 ) ? atoi( arg3 ) : -1;
    
        if ( value < 0 || value > 5 )
        {
            send_to_char( "Range is 0 - 5.\n\r", ch );
            return;
        }
    
        if ( value == 0 ) value = -1;
        
        for ( disc = 0 ; disc <= DISC_MAX ; disc++ )
                victim->pcdata->powers[disc] = value;
     
        send_to_char("Done.\n\r", ch );
        return;
    }
        
   else if ( !str_cmp( arg2, "animalism" ) )   disc = VAM_ANIM;
    else if ( !str_cmp( arg2, "auspex" ) )      disc = VAM_AUSP;
   else if ( !str_cmp( arg2, "celerity" ) )    disc = VAM_CELE;
    else if ( !str_cmp( arg2, "chimerstry" ) )  disc = VAM_CHIM;
    else if ( !str_cmp( arg2, "daimoinon" ) )   disc = VAM_DAIM;
    else if ( !str_cmp( arg2, "dominate" ) )    disc = VAM_DOMI;
    else if ( !str_cmp( arg2, "fortitude" ) )   disc = VAM_FORT;
    else if ( !str_cmp( arg2, "melpominee" ) )  disc = VAM_MELP;
    else if ( !str_cmp( arg2, "necromancy" ) )  disc = VAM_NECR;
    else if ( !str_cmp( arg2, "obeah" ) )       disc = VAM_OBEA;
    else if ( !str_cmp( arg2, "obfuscate" ) )   disc = VAM_OBFU;
    else if ( !str_cmp( arg2, "obtenebration" ) ) disc = VAM_OBTE;
    else if ( !str_cmp( arg2, "potence" ) )     disc = VAM_POTE;
    else if ( !str_cmp( arg2, "presence" ) )    disc = VAM_PRES;
    else if ( !str_cmp( arg2, "protean" ) )     disc = VAM_PROT;
    else if ( !str_cmp( arg2, "quietus" ) )     disc = VAM_QUIE;
    else if ( !str_cmp( arg2, "serpentis" ) )   disc = VAM_SERP;
    else if ( !str_cmp( arg2, "thanatosis" ) )  disc = VAM_THAN;
    else if ( !str_cmp( arg2, "thaumaturgy" ) ) disc = VAM_THAU;
    else if ( !str_cmp( arg2, "vicissitude" ) ) disc = VAM_VICI;
    else 
    {
        do_discset( ch, "" );
        return;
    }
    value = is_number( arg3 );
    
    if ( value < 0 || value > 5 )
    {
        send_to_char( "Range is 0 - 5.\n\r", ch );
        return;
    }
         victim->pcdata->powers[disc] = value;
         send_to_char("Done.\n\r", ch );
   return;
}
void do_giftset( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA   *victim;
    char        arg1[MAX_INPUT_LENGTH];
    char        arg2[MAX_INPUT_LENGTH];
    char        arg3[MAX_INPUT_LENGTH];
    sh_int      gift = 0;
    sh_int      value = 0;
     
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    argument = one_argument( argument, arg3 );
         
    if ( IS_NPC( ch ) )
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }
    if ( arg1[0] == '\0' || arg2[0] == '\0' || arg3[0] == '\0' )
    {
        send_to_char( "Syntax : setgift [victim] [gift/all] [level]\n\r\n\r",ch);
        send_to_char( " Gift being one of:\n\r", ch );
        send_to_char( "  homid lupus metis\n\r", ch );
        send_to_char( "  ragabash theurge galliard philodox ahroun\n\r", ch );
        
        send_to_char( "  furies gnawers children fianna get\n\r", ch );
        send_to_char( "  walkers talons lords striders fangs\n\r", ch );
        send_to_char( "  stargazers wendigos uktena\n\r", ch );
        return;
    }
   if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
        send_to_char( "They aren't here.\n\r", ch );
        return;
    }
        
    if ( IS_NPC(victim ) )
    {
        send_to_char( "Not on NPC's.\n\r", ch );
        return;
    }
        
    if ( !IS_CLASS(victim, CLASS_WEREWOLF) && !IS_ABOMINATION(ch))
    {
        send_to_char( "Only on Werewolves, and Abomination!\n\r", ch );

        return;
    }
     
        
    if ( !str_cmp( arg2, "all" ) )
    {
        value = is_number( arg3 ) ? atoi( arg3 ) : -1;
    
        if ( value < 0 || value > 5 )
        {
            send_to_char( "Range is 0 - 5.\n\r", ch );
            return;
        }
    
     
        for ( gift = 0 ; gift <= MAX_GIFTS ; gift++ )
                victim->gifts[gift] = value;
     
        send_to_char("Done.\n\r", ch );
        return;
    }
     
   else if ( !str_cmp( arg2, "homid" ) )   gift = HOMID;
    else if ( !str_cmp( arg2, "metis" ) )  gift = METIS;
    else if ( !str_cmp( arg2, "lupus" ) )  gift = LUPUS;
    else if ( !str_cmp( arg2, "ahroun" ) ) gift = AHROUN;
    else if ( !str_cmp( arg2, "theurge" ) ) gift = THEURGE;
    else if ( !str_cmp( arg2, "philodox" ) )gift = PHILODOX;
    else if ( !str_cmp( arg2, "galliard" ) )gift = GALLIARD;
    else if ( !str_cmp( arg2, "ragabash" ) )gift = RAGABASH;
    else if ( !str_cmp( arg2, "furies" ) ) gift = BLACKFURIES;
    else if ( !str_cmp( arg2, "gnawers" )) gift = BONEGNAWERS;
    else if ( !str_cmp( arg2, "children" ) )gift = CHILDREN;
    else if ( !str_cmp( arg2, "fianna" ) ) gift = FIANNA;
    else if ( !str_cmp( arg2, "get" ) )    gift = GETOFFENRIS;
    else if ( !str_cmp( arg2, "walkers" ) )gift = GLASSWALKERS;
    else if ( !str_cmp( arg2, "talons" ) ) gift = REDTALONS;
    else if ( !str_cmp( arg2, "lords" ) )  gift = SHADOWLORDS;
    else if ( !str_cmp( arg2, "striders" ) )gift = SILENTSTRIDERS;
    else if ( !str_cmp( arg2, "fangs" ) )  gift = SILVERFANGS;
    else if ( !str_cmp( arg2, "stargazers" ) ) gift = STARGAZERS;
    else if ( !str_cmp( arg2, "uktena" ) ) gift = UKTENA;
    else if ( !str_cmp( arg2, "wendigos" ) ) gift = WENDIGO;
    else 
    {
        do_giftset( ch, "" );
        return;
    }

    if ( value < 0 || value > 5 )
    {
        send_to_char( "Range is 0 - 5.\n\r", ch );
        return;
    }
         victim->gifts[gift] = value;
         send_to_char("Done.\n\r", ch );
    return;
}
