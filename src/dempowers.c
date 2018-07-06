/***************************************************************************
 *  God Wars Mud originally written by KaVir aka Richard Woolcock.         *
 *  Changes done to the code done by Sage aka Walter Howard, this mud is   *
 *  for the public, however if you run this code it means you agree        *
 *  to the license.low, license.gw, and license.merc have fun. :)          *
***************************************************************************/
/*Demon's Sage/Dunkirk*/

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

void frost_breath args(( CHAR_DATA *ch, CHAR_DATA *victim, bool all));
DECLARE_DO_FUN( do_stance );


void do_immolate(CHAR_DATA *ch, char *argument)
{
    OBJ_DATA *obj;

	
        if (!IS_CLASS(ch, CLASS_DEMON))
{
        stc("Huh?\n\r",ch);
        return;
        }

    if (!IS_DEMPOWER(ch, DEM_IMMOLATE))
    {
	stc("You have not been granted that power.\n\r",ch);
	return;
    }

    if (argument[0] == '\0')
    {
	send_to_char("Which item do you wish to immolate?\n\r", ch);
	return;
    }

    if ( (obj = get_obj_carry(ch, argument)) == NULL)
    {
	send_to_char("You are not carrying that item.\n\r", ch);
	return;
    }

    if (obj->item_type != ITEM_WEAPON)
    {
	send_to_char("That is not a weapon!\n\r", ch);
	return;
    }

    if (dice(1, 100) == 1)
    {
	act("$p explodes in a burst of flames.", ch,obj, NULL, TO_ROOM);
	act("$p explodes in a burst of flames.", ch,obj, NULL, TO_CHAR);
	damage(ch,ch,500,gsn_inferno);
	extract_obj(obj);
	return;
    }

    if (IS_WEAP(obj, WEAPON_FLAMING))
    {
	act("$p is already flaming.", ch, obj, NULL, TO_CHAR);
	return;
    }

    act("$p bursts into flames.", ch, obj, NULL, TO_CHAR);
    act("$p, carried by $n bursts into flames.", ch, obj, NULL, TO_ROOM);

    WAIT_STATE(ch, 8);
    SET_BIT(obj->weapflags, WEAPON_FLAMING);
}


void do_leech(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim = NULL;
    char buf[MAX_STRING_LENGTH];

	
        if (!IS_CLASS(ch, CLASS_DEMON))
{
        stc("Huh?\n\r",ch);
        return;
        }

    if (!IS_DEMPOWER( ch, DEM_LEECH))
    {

	stc("You do not have that power.\n\r",ch);
	return;
    }

    if (argument[0] == '\0')
    {
	stc("Who's life do you wish to leech off of?\n\r", ch);
	return;
    }

    if ((victim = get_char_room(ch, argument)) == NULL)
    {
	    stc("They aren't here.\n\r", ch);
	    return;
    }

      if (is_safe(ch, victim)) return;

	WAIT_STATE(ch, 10);

	act("$n stares intently at $N.", ch, NULL, victim, TO_NOTVICT);
	act("You stare intently at $N.", ch, NULL, victim, TO_CHAR);
	act("$n stares intently at you.", ch, NULL, victim, TO_VICT);

      if (victim->hit >= 1000)
      {
	  sh_int power;
	  sh_int dam;
	  power = (ch->pcdata->stats[UNI_GEN]);
	  dam = dice(power, power + 2);
	  if (dam > 300) dam = 300 + (dam / 10);
	  victim->hit -= dam;
	  ch->hit += dam;
	  if (ch->hit >= ch->max_hit + 500)
		ch->hit = ch->max_hit + 500;
	  sprintf(buf,"You absorb %d hitpoints.\n\r",dam);
	  stc(buf,ch);
	  sprintf(buf,"%s absorbed %d of your hitpoints!\n\r",ch->name,dam);
	  stc(buf,victim);
	  }
      else stc("Nothing seemed to happen.\n\r",ch);
	return;

}

void do_unnerve(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;


        if (!IS_CLASS(ch, CLASS_DEMON))
{
        stc("Huh?\n\r",ch);
        return;
        }

    if (!IS_DEMPOWER(ch, DEM_UNNERVE))
    {
	stc("You have not been granted that power.\n\r",ch);
	return;
    }

    if (argument[0] == '\0')
    {
	stc("Who do you wish to unnerve?\n\r", ch);
	return;
    }

    if ( ( victim = get_char_room(ch, argument) ) == NULL)
    {
	stc("They aren't here.\n\r", ch);
	return;
    }

    WAIT_STATE(ch, 7);
    do_say(ch,"{rXeus Dominus Mortai!{x");
    do_stance(victim, "");
}

void do_wfreeze(CHAR_DATA *ch, char *argument)
{
    OBJ_DATA *obj;

	
        if (!IS_CLASS(ch, CLASS_DEMON))
{
        stc("Huh?\n\r",ch);
        return;
        }

    if (!IS_DEMPOWER(ch, DEM_FREEZEWEAPON))
    {
	stc("You have not been granted that power.\n\r",ch);
	return;
    }

    if (argument[0] == '\0')
    {
	send_to_char("Which item do you wish to freeze?\n\r", ch);
	return;
    }

    if ( (obj = get_obj_carry(ch, argument)) == NULL)
    {
	send_to_char("You are not carrying that item.\n\r", ch);
	return;
    }

    if (obj->item_type != ITEM_WEAPON)
    {
	send_to_char("That is not a weapon!\n\r", ch);
	return;
    }

    if (dice(1, 100) == 1)
    {
	act("$p freezes and shatters.", ch,obj, NULL, TO_ROOM);
	act("$p freezes and shatters.", ch,obj, NULL, TO_CHAR);
	extract_obj(obj);
	return;
    }

    if (IS_WEAP(obj, WEAPON_FROST))
    {
	act("$p is already frozen.", ch, obj, NULL, TO_CHAR);
	return;
    }

    act("$p is surrounded by ice crystals.", ch, obj, NULL, TO_CHAR);
    act("$p, carried by $n is surrounded by ice crystals.", ch, obj, NULL,
TO_ROOM);

    WAIT_STATE(ch, 8);
    SET_BIT(obj->weapflags, WEAPON_FROST);
}

void do_graft(CHAR_DATA *ch, char *argument)
{
    OBJ_DATA *obj;
    char arg[MAX_INPUT_LENGTH];
    argument = one_argument(argument, arg);

    if (IS_NPC(ch)) return; 

	if (!IS_CLASS(ch, CLASS_DEMON))
{
	stc("Huh?\n\r",ch);
	return;
	}

	if (!IS_DEMPOWER( ch, DEM_GRAFT) && IS_CLASS(ch,CLASS_DEMON))
    {
	stc("You need to get graft first.\n\r",ch);
	return;
    }

    if ( arg[0] == '\0')
    {
	stc("Which limb do you wish to graft on to yourself?\n\r",ch);
	return;
    }

    if ( ( obj = get_obj_carry(ch,arg) ) == NULL )
    {
	stc("You do not have that limb.\n\r",ch);
	return;
    }
	if(strstr(obj->name,"arm"))
//    if ( str_cmp(obj->name, "arm mob" ) )
    {
	stc("That's not even an arm!\n\r",ch);
	return;
    }

    if (IS_SET(ch->newbits, THIRD_HAND) && IS_SET(ch->newbits, FOURTH_HAND))
    {
	stc("You already have four arms!\n\r",ch);
	return;
    }


    if (!IS_SET(ch->newbits, THIRD_HAND))
    {
	act("You graft an arm onto your body.",ch,NULL,obj,TO_CHAR);
	act("$n grafts an arm onto $m body.",ch,NULL,obj,TO_ROOM);
	SET_BIT(ch->newbits, THIRD_HAND);
	WAIT_STATE(ch, 18);
	extract_obj(obj);
	return;    
    }    


    if (!IS_SET(ch->newbits, FOURTH_HAND))
    {
	act("You graft an arm onto your body.",ch,NULL,obj,TO_CHAR);
	act("$n grafts an arm onto $m body.",ch,NULL,obj,TO_ROOM);
	SET_BIT(ch->newbits, FOURTH_HAND);
	WAIT_STATE(ch, 18);
	extract_obj(obj);
	return;    
    }

    return;
}

void do_caust(CHAR_DATA *ch, char *argument)
{
    OBJ_DATA *obj;

	
        if (!IS_CLASS(ch, CLASS_DEMON))
{
        stc("Huh?\n\r",ch);
        return;
        }

    if (!IS_DEMPOWER(ch, DEM_CAUST))
    {
	stc("You have not been granted that power.\n\r",ch);
	return;
    }

    if (argument[0] == '\0')
    {
	send_to_char("Which item do you wish to caust?\n\r", ch);
	return;
    }

    if ( (obj = get_obj_carry(ch, argument)) == NULL)
    {
	send_to_char("You are not carrying that item.\n\r", ch);
	return;
    }

    if (obj->item_type != ITEM_WEAPON)
    {
	send_to_char("That is not a weapon!\n\r", ch);
	return;
    }

    if (dice(1, 100) == 1)
    {
	act("$p is disintegrated by $n's poison.", ch,obj, NULL, TO_ROOM);
	act("Your poison eats through $p.", ch,obj, NULL, TO_CHAR);
	extract_obj(obj);
	return;
    }

    if (IS_WEAP(obj, WEAPON_POISON))
    {
	act("$p is already coated with deadly poison.", ch, obj, NULL,
TO_CHAR);
	return;
    }

    act("You run your tongue along $p, coating it with a sickly venom.",
ch, obj, NULL, TO_CHAR);
    act("$n runs $m tongue along $p, coating it with a sickly venom.", ch,
obj, NULL, TO_ROOM);

    WAIT_STATE(ch, 8);
    SET_BIT(obj->weapflags, WEAPON_POISON);
    obj->value[1] += ch->pcdata->stats[UNI_GEN];
    obj->value[2] += ch->pcdata->stats[UNI_GEN];
}


void do_blink(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;

	
        if (!IS_CLASS(ch, CLASS_DEMON))
{
        stc("Huh?\n\r",ch);
        return;
        }	

    if (!IS_DEMPOWER(ch, DEM_BLINK))
    {
      stc("You have not been granted the power of Blinking.\n\r",ch);
      return;
    }

    if (ch->fighting == NULL && argument[0] == '\0')
    {
	stc("Who do you wish to blink into combat with?\n\r", ch);
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
        stc("You can't blink into combat with yourself.\n\r", ch);
        return;
    }

    if (is_safe(ch, victim)) return;

	WAIT_STATE(ch, 30);
	SET_BIT(ch->flag2, AFF2_BLINK_1ST_RD);
	stop_fighting(ch, TRUE);
	stc("You pop out of existance.\n\r", ch);
	act("$n pops out of existance.", ch, NULL, NULL, TO_ROOM);
	ch->blinkykill = victim;
	return;
    }
    WAIT_STATE(ch, 30);
    victim = ch->fighting;
    SET_BIT(ch->flag2, AFF2_BLINK_2ND_RD);
    stop_fighting(ch, TRUE);
    stc("You pop out of existance.\n\r", ch);
    act("$n pops out of existance.", ch, NULL, NULL, TO_ROOM);
    ch->blinkykill = victim;
	WAIT_STATE(ch, 30);
}

