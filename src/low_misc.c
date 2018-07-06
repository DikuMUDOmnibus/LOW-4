
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
 /**************************************************************************
 *  God Wars Mud originally written by KaVir aka Richard Woolcock.         *
 *  Changes done to the code done by Sage aka Walter Howard, this mud is   *
 *  for the public, however if you run this code it means you agree        *
 *  to the license.low, license.gw, and license.merc have fun. :)          *
 ***************************************************************************/
 /**************************************************************************
 *  Entire contents of this file coded from scratch by Malawar             *
 *  For more information contact at Malawar@HotMail.com                    *
 ***************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "merc.h"


// Corpse Timers
#define CS1 75
#define CS2 60
#define CS3 45
#define CS4 30
#define CS5 15
#define CS6 7


void make_corpse(CHAR_DATA *ch)
{
    char buf[MSL],buf2[MSL];
    char missing[MSL];
    OBJ_DATA *corpse;
    OBJ_DATA *obj_next;
    OBJ_DATA *obj;
    int amt = 0;
    missing[0] = '\0';
    missing[1] = '\0';
    if(!IS_NPC(ch))
    corpse = create_object(get_obj_index(OBJ_VNUM_CORPSE_PC),0);
    else
        corpse = create_object(get_obj_index(OBJ_VNUM_CORPSE_NPC),0);
    if(IS_NPC(ch))
    corpse->timer = number_range(150,175);
    else corpse->timer = number_range(75,85);
    if(IS_NPC(ch))corpse->value[2] = ch->pIndexData->vnum;
    
//  Transfer Gold to Corpse (Its GW, why do this? Oh hell, lets do it anyway)
    if(ch->gold > 0)
    {
	obj_to_obj(create_money(ch->gold),corpse);
	ch->gold = 0;
    }

//  Leave crap in the corpse
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

//  Make corpse shadowplane

    if (IS_AFFECTED(ch, AFF_SHADOWPLANE))
	SET_BIT(corpse->extra_flags, ITEM_SHADOWPLANE);
//  Add affects
	if(ch->in_room->blood != 0){
	if(ch->in_room->blood > 100)
		strcat(missing,"blood-soaked ");
	else if(ch->in_room->blood > 50)
		strcat(missing,"bloody ");
	else if(ch->in_room->blood > 25)
		strcat(missing,"blood-stained ");
	else    strcat(missing,"blood-spattered ");
	if(amt++ >= 3) goto assign;
	}
	
	        if (IS_HEAD(ch,LOST_EYE_L) || IS_HEAD(ch,LOST_EYE_R))
                {strcat(missing,"eyeless");if(amt++ >= 3) goto assign;
		else strcat(missing,", ");}
        if (IS_HEAD(ch,LOST_HEAD))
                {strcat(missing,"headless");if(amt++ >= 3) goto assign;
		else strcat(missing,", ");}
        if (IS_HEAD(ch,LOST_TONGUE))
                {strcat(missing,"tongueless");if(amt++ >= 3) goto assign;
		else strcat(missing,", ");}
        if (IS_ARM_L(ch,LOST_ARM) || IS_ARM_R(ch,LOST_ARM))
                {strcat(missing,"armless");if(amt++ >= 3) goto assign;
		else strcat(missing,", ");}
//	Random stuff to make it look good every time
	switch(number_range(1,7))
	{
	default: strcat(missing,"shredded");break;
	case 1:strcat(missing,"hacked-up");break;
	case 2:SET_BIT(corpse->spectype,C_TWITCHING);break;
	case 3:strcat(missing,"impaled");break;
	case 4:strcat(missing,"mutilated");break;
	case 5:strcat(missing,"disemboweled");break;
	case 6:strcat(missing,"mangled");break;
        case 7:strcat(missing,"flayed");break;
	}
assign:

if(IS_NPC(ch))
{  
if(!IS_SET(corpse->spectype,C_TWITCHING) || amt > 0)
strcat(missing," ");

   sprintf(buf,"the %scorpse of %s",missing,ch->short_descr);

   sprintf(buf2,"The %scorpse of %s is lying here.",missing,ch->short_descr);
}
else
{
if(!IS_SET(corpse->spectype,C_TWITCHING) || amt > 0)
strcat(missing," ");
  sprintf(buf,"the %scorpse of %s",missing,ch->name);

  sprintf(buf2,"The %scorpse of %s is lying here.",missing,ch->name);
}
  free_string(corpse->description);
  free_string(corpse->short_descr);
  free_string(corpse->real_name);
  corpse->real_name=str_dup(buf);
  corpse->description = str_dup(buf2);
  corpse->short_descr=str_dup(buf);
  obj_to_room(corpse,ch->in_room);
}
	
void mageupkeep(CHAR_DATA *ch)
{
	const char *mcolor[5] =
{
	"{mPurple{x",	"{RRed{x",
	"{Blue",	"{GGreen{x",
	"{YYellow{x"
};
	char buf[MSL];
	cent_to_char("-----------------------------------------------------------------",ch);
	centre_text("{b(<{B Warlock Powers{b >){x",ch);
	cent_to_char("-----------------------------------------------------------------",ch);
	sprintf(buf,"You are a %s Mage.\n\r\n\r",mcolor[ch->pcdata->powers[MPOWER_RUNE0]]);
	stc(buf,ch);
	if(IS_SET(ch->act,PLR_HOLYLIGHT))
		stc("You have heightened Perception.\n\r",ch);
	if(IS_SET(ch->mflags,MAGE_POLYAPPEAR))
		stc("You are seen as multiple figures.\n\r",ch);
	if(IS_SET(ch->mflags,MAGE_TELEKINETICS))
		stc("You focus your mental energies into your attacks.\n\r",ch);
	if(IS_SET(ch->mflags,MFLAGS_DIMMAK))
		stc("You focus your attacks on your opponents weaknesses.\n\r",ch);
	if(IS_SET(ch->mflags,MAGE_BETTERBODY))
		stc("Your body is of supernatural size.\n\r",ch);
	if(IS_AFFECTED(ch,AFF_POLYMORPH))
		{sprintf(buf,"You are %s.\n\r",ch->morph);stc(buf,ch);}
	if(IS_AFFECTED(ch,AFF_FLYING))
		stc("You are hovering.\n\r",ch);
	if(IS_AFFECTED(ch,AFF_SHADOWPLANE))
		stc("You are in the Shadowplane.\n\r",ch);
	if(is_affected(ch,skill_lookup("spirit kiss")))
		stc("You are blessed by spirits.\n\r",ch);
	if(IS_IMMUNE(ch,IMM_SHIELDED))
		stc("Your aura is shielded.\n\r",ch);



	if(ch->spheres[MPRI]>0)
	{
	  sprintf(buf,"\n\rYou have %d quintessence stored in within your body.\n\rYou have %d quintessence stored within your Avatar.\n\r",
	  ch->quint[BODY],ch->quint[AVATAR]);
	  stc(buf,ch);
	}
}


void wwupkeep(CHAR_DATA *ch)
{
  char buf[MSL];
  


cent_to_char("-----------------------------------------------------------------",ch);
	centre_text("{Y({yWerewolf Upkeep{Y){x",ch);
	cent_to_char("-----------------------------------------------------------------",ch);

        if(IS_GAR1(ch,WOLF_COCOON))
		stc("Your body is surrounded by a thick, opaque epidermis.\n\r",ch);
	if(IS_SET(ch->newbits,NEW_QUILLS))
		stc("Your fur is bristly and sharp.\n\r",ch);
	if(IS_SET(ch->act,PLR_HOLYLIGHT))
		stc("You have heightened senses.\n\r",ch);
	if(IS_SET(ch->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT))
		stc("You have the eyes of a cat.\n\r",ch);
	if(IS_VAMPAFF(ch,VAM_CLAWS))
	{
		stc("Your talons are extended.\n\r",ch);
		if(IS_GAR1(ch,WOLF_RAZORCLAWS))
		stc("Your claws have a razor-sharp edge.\n\r",ch);
	}
	if(IS_GAR1(ch,GAROU_BLISSFUL))
		stc("You are completely invisible.\n\r",ch);
	if(is_affected(ch,skill_lookup("lunas blessing")))
		stc("You have Luna's Blessing.\n\r",ch);
	if(IS_GAR1(ch,WW_GRANITE))
		stc("You are surrounded by a wall of granite.\n\r",ch);
	if(IS_GAR1(ch,GAROU_CLENCHED))
		stc("Your jaws are clenched.\n\r",ch);
	if(IS_GAR1(ch,GAROU_AVENGER))
		stc("Your body is imbued with silver.\n\r",ch);
	if(IS_AFFECTED(ch,AFF_SHADOWSIGHT))
		stc("You can see into the beyond.\n\r",ch);
	if(IS_AFFECTED(ch,AFF_STEELSHIELD))
		stc("Your icy chill of despair scares everyone.\n\r",ch);
	if(IS_POLYAFF(ch,POLY_ZULO))
		stc("You are incredibly huge.\n\r",ch);
	if(IS_IMMUNE(ch,IMM_SHIELDED))
		stc("Your aura is shielded.\n\r",ch);	
	sprintf(buf,"You have %d gnosis points.\n\rYou can have a maximum of %d make gnosis points.\n\r",
		   ch->gnosis[GCURRENT],ch->gnosis[GMAXIMUM]);
		stc(buf,ch);
}

void drowupkeep(CHAR_DATA *ch)
{

	cent_to_char("-----------------------------------------------------------------",ch);
	centre_text("{GoO{gDrow Upkeep{GOo{x",ch);
	cent_to_char("-----------------------------------------------------------------",ch);

	if(IS_SET(ch->newbits,NEW_DROWHATE))
		stc("Your hatred for others has been invoked.\n\r",ch);
	if(IS_POLYAFF(ch,POLY_SPIDERFORM))
		stc("You are in spiderform.\n\r",ch);
	if(IS_SET(ch->act,PLR_HOLYLIGHT))
		stc("Your vision is enhanced.\n\r",ch);
	if(IS_IMMUNE(ch,IMM_SHIELDED))
		stc("Your aura is shielded.\n\r",ch);
}
void monkupkeep(CHAR_DATA *ch)
{
	char buf[MSL];
	cent_to_char("-----------------------------------------------------------------",ch);
	centre_text("Monk Upkeep",ch);
	cent_to_char("-----------------------------------------------------------------",ch);

  if(IS_SET(ch->newbits,NEW_MONKFLAME))
	stc("Your hands are engulfed in flames.\n\r",ch);
  if(IS_SET(ch->newbits,NEW_MONKADAM))
  	stc("Your hands are as hard as adamantium.\n\r",ch);
  if(IS_SET(ch->newbits,NEW_POWER))
	stc("Your body is pulsing with spiritual energy.\n\r",ch);
  sprintf(buf,"You have %d Ch'i.\n\r",ch->chi[CURRENT]++);
	stc(buf,ch);
}


void do_rolldirt( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    ROOM_INDEX_DATA *inroom;
    one_argument( argument, arg );
    inroom=ch->in_room;
    
    if (!IS_AFFECTED(ch, AFF_FLAMING))
    {
	send_to_char( "You aren't on fire\n\r", ch );
	return;
    }

    if ( number_percent() > (ch->level*1.75) )
    {
	send_to_char("You roll in the dirt trying to put out the flames.\n\r", ch);
	act( "$n rolls in the dirt trying to stop the burning flames", ch, NULL, NULL, TO_ROOM );
	return;
    }

	send_to_char("You manage to roll off the flames around you.\n\r", ch);
	act( "$n manages to roll of the flames around them",  ch, NULL, NULL, TO_ROOM );
    REMOVE_BIT(ch->affected_by, AFF_FLAMING);
    return;
}



void test_crap(CHAR_DATA *ch,char *argument)
{
  char arg[MSL];
  char *p;
  argument=one_argument(argument,arg);

  p=strstr(argument,arg);
  stc(p,ch);

}


void do_dismember(CHAR_DATA *ch,char *argument)
{
  char arg[MSL];
  CHAR_DATA *victim;
  argument=one_argument(argument,arg);

  if(arg[0]== '\0')
  {
    stc("Dismember whom?\n\r",ch);
    return;
  }
  if((victim = get_char_room(ch,arg))==NULL)
  {
    stc("They are not here.\n\r",ch);
    return;
  }
  if(victim->trust > ch->trust)
  {
    stc("I don't THINK so!\n\r",ch);
    return;
  }

            SET_BIT(victim->loc_hp[2],LOST_ARM);
            SET_BIT(victim->loc_hp[6],BLEEDING_ARM_L);
	    SET_BIT(victim->loc_hp[0],LOST_EYE_L);
	    SET_BIT(victim->loc_hp[0],LOST_EYE_R);
	    SET_BIT(victim->loc_hp[0],LOST_EYE_L);
	    SET_BIT(victim->loc_hp[0],LOST_EAR_L);
	    SET_BIT(victim->loc_hp[0],LOST_EAR_R);
	    SET_BIT(victim->loc_hp[0],LOST_EAR_L);
	    SET_BIT(victim->loc_hp[0],LOST_NOSE);
	    SET_BIT(victim->loc_hp[0],BROKEN_NOSE);
	    SET_BIT(victim->loc_hp[0],BROKEN_JAW);
	    SET_BIT(victim->loc_hp[2],LOST_ARM);
	    SET_BIT(victim->loc_hp[6],BLEEDING_ARM_L);
	    SET_BIT(victim->loc_hp[3],LOST_ARM);
	    SET_BIT(victim->loc_hp[6],BLEEDING_ARM_R);
	    SET_BIT(victim->loc_hp[2],BROKEN_ARM);
	    SET_BIT(victim->loc_hp[3],BROKEN_ARM);
	    SET_BIT(victim->loc_hp[2],LOST_HAND);
	    SET_BIT(victim->loc_hp[6],BLEEDING_HAND_L);
	    SET_BIT(victim->loc_hp[3],LOST_HAND);
	    SET_BIT(victim->loc_hp[6],BLEEDING_HAND_R);
            SET_BIT(victim->loc_hp[2],LOST_THUMB);
            SET_BIT(victim->loc_hp[2],LOST_FINGER_I);
            SET_BIT(victim->loc_hp[2],LOST_FINGER_M);
            SET_BIT(victim->loc_hp[2],LOST_FINGER_R);
            SET_BIT(victim->loc_hp[2],LOST_FINGER_L);
            SET_BIT(victim->loc_hp[2],BROKEN_THUMB);
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_I);
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_M);
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_R);
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_L);
            SET_BIT(victim->loc_hp[3],LOST_THUMB);
            SET_BIT(victim->loc_hp[3],LOST_FINGER_I);
            SET_BIT(victim->loc_hp[3],LOST_FINGER_M);
            SET_BIT(victim->loc_hp[3],LOST_FINGER_R);
            SET_BIT(victim->loc_hp[3],LOST_FINGER_L);
            SET_BIT(victim->loc_hp[3],BROKEN_THUMB);
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_I);
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_M);
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_R);
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_L);
	    SET_BIT(victim->loc_hp[4],LOST_LEG);
	    SET_BIT(victim->loc_hp[6],BLEEDING_LEG_L);
	    SET_BIT(victim->loc_hp[5],LOST_LEG);
	    SET_BIT(victim->loc_hp[6],BLEEDING_LEG_R);
	    SET_BIT(victim->loc_hp[4],BROKEN_LEG);
	    SET_BIT(victim->loc_hp[5],BROKEN_LEG);
	    SET_BIT(victim->loc_hp[4],LOST_FOOT);
	    SET_BIT(victim->loc_hp[6],BLEEDING_FOOT_L);
	    SET_BIT(victim->loc_hp[5],LOST_FOOT);
	    SET_BIT(victim->loc_hp[6],BLEEDING_FOOT_R);
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_16);
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_8);
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_4);
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_2);
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_1);
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_16);
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_8);
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_4);
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_2);
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_1);
        SET_BIT(victim->loc_hp[LOC_LEG_L],BROKEN_LEG);
        SET_BIT(victim->loc_hp[LOC_LEG_R],BROKEN_LEG);
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_SPINE);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);
make_part(victim,"arm");
make_part(victim,"arm");
make_part(victim,"leg");
make_part(victim,"leg");
make_part(victim,"blood");
make_part(victim,"blood");

	act("$n has dismembered $N!",ch,NULL,victim,TO_NOTVICT);
	act("You dismembered $N!",ch,NULL,victim,TO_CHAR);
	act("$n has dismembered you!",ch,NULL,victim,TO_VICT);
	victim->in_room->blood += 200;
}
void alter_corpse(OBJ_DATA *obj)
{
  CHAR_DATA *rch;
  char *p;
  char buf[MSL];
  char message[MSL];
  char newname[MSL];

  if(obj->item_type != ITEM_CORPSE_NPC && obj->item_type != ITEM_CORPSE_PC)
  {
    sprintf(buf,"BUG! Alter_Corpse: %s[%d] Not a Corpse!",obj->name,obj->pIndexData->vnum);
    return;
  }

  if((obj->in_obj)|| (obj->carried_by))
    return;

  rch = obj->in_room->people;
  switch(obj->timer)
  {
    default: if(IS_SET(obj->spectype,C_TWITCHING)){
	     if(number_range(1,50)==5)
	     {sprintf(message,"%s twitches violently.",obj->real_name);break;}
	     else if(number_range(1,15)==1)
	     {sprintf(message,"%s twitches.",obj->real_name);break;}
	     else return;}
	     return;
   case CS1: sprintf(message,"%s begins to smell bad.",obj->real_name);
	     sprintf(buf,"foul-smelling ");
	     break;
   case CS2: sprintf(message,"%s is growing mold.",obj->real_name);
	     sprintf(buf,"moldy ");
	     break;
   case CS3: sprintf(message,"%s begins to crumble.",obj->real_name);
	     sprintf(buf,"rotting ");
	     break;
   case CS4: sprintf(message,"%s is starting to be unbearable.",obj->real_name);
	     sprintf(buf,"putrid ");
	     break;
   case CS5: sprintf(message,"Maggots begin to pour out of %s.",obj->real_name);
	     sprintf(buf,"maggot-infested ");
	     break;
   case CS6: sprintf(buf,"maggot-infested remains of the ");
	     sprintf(message,"The maggots munch noisily on %s.",obj->real_name);
	     break;
  }

  if(rch != NULL){
  act(message,rch,NULL,NULL,TO_ROOM);
  act(message,rch,NULL,NULL,TO_CHAR);}
if(IS_SET(obj->spectype,C_TWITCHING))return;
  p = obj->real_name;
  sprintf(newname,"The %s%s is lying here.",buf,p+4);
  obj->description = str_dup(newname);
}



void do_chardump(CHAR_DATA *ch,char *argument)
{
char buf[MSL];
char arg[MSL];
CHAR_DATA *vch;
DESCRIPTOR_DATA *d;

argument=one_argument(argument,arg);
if(!arg[0])
{
  stc("View a dump of whom?\n\r",ch);
  return;
}

if((vch=get_char_world(ch,arg))==NULL)
{
  stc("They ain't here, dammit!\n\r",ch);
  return;
}
d=vch->desc;
sprintf(buf,"d->host             %s\n\r",d->host);
stc(buf,ch);
sprintf(buf,"d->descriptor       %d\n\r",d->descriptor);
stc(buf,ch);
sprintf(buf,"d->connected        %d\n\r",d->connected);
stc(buf,ch);
sprintf(buf,"ch->hunting         %s\n\r",vch->hunting);
stc(buf,ch);
sprintf(buf,"ch->name            %s\n\r",vch->name);
stc(buf,ch);
sprintf(buf,"ch->pload           %s\n\r",vch->pload);
stc(buf,ch);
sprintf(buf,"ch->short_descr     %s\n\r",vch->short_descr);
stc(buf,ch);
sprintf(buf,"ch->long_descr      %s\n\r",vch->long_descr);
stc(buf,ch);
sprintf(buf,"ch->description     %s\n\r",vch->description);
stc(buf,ch);
sprintf(buf,"ch->lord            %s\n\r",vch->lord);
stc(buf,ch);
sprintf(buf,"ch->clan            %s\n\r",vch->clan);
stc(buf,ch);
sprintf(buf,"ch->kingdom         %s\n\r",vch->kingdom);
stc(buf,ch);
sprintf(buf,"ch->objdesc         %s\n\r",vch->objdesc);
stc(buf,ch);
sprintf(buf,"ch->morph           %s\n\r",vch->morph);
stc(buf,ch);
sprintf(buf,"ch->createtune      %s\n\r",vch->createtime);
stc(buf,ch);
sprintf(buf,"ch->lasttime        %s\n\r",vch->lasttime);
stc(buf,ch);
sprintf(buf,"ch->lasthost        %s\n\r",vch->lasthost);
stc(buf,ch);
sprintf(buf,"ch->poweraction     %s\n\r",vch->poweraction);
stc(buf,ch);
sprintf(buf,"ch->powertype       %s\n\r",vch->powertype);
stc(buf,ch);
sprintf(buf,"ch->prompt          %s\n\r",vch->prompt);
stc(buf,ch);
sprintf(buf,"ch->cprompt         %s\n\r",vch->cprompt);
stc(buf,ch);
sprintf(buf,"ch->prefix          %s\n\r",vch->prefix);
stc(buf,ch);
sprintf(buf,"ch->sex             %d\n\r",vch->sex);
stc(buf,ch);
sprintf(buf,"ch->race            %d\n\r",vch->race);
stc(buf,ch);
sprintf(buf,"ch->class           %d\n\r",vch->class);
stc(buf,ch);
sprintf(buf,"ch->warpcount       %d\n\r",vch->warpcount);
stc(buf,ch);
sprintf(buf,"ch->fight_timer     %d\n\r",vch->fight_timer);
stc(buf,ch);
sprintf(buf,"ch->obeah_timer     %d\n\r",vch->obeah_timer);
stc(buf,ch);
sprintf(buf,"ch->reina_timer     %d\n\r",vch->reina_timer);
stc(buf,ch);
sprintf(buf,"ch->silence_timer   %d\n\r",vch->silence_timer);
stc(buf,ch);
sprintf(buf,"ch->darkness_timer  %d\n\r",vch->darkness_timer);
stc(buf,ch);
sprintf(buf,"ch->arena_timer     %d\n\r",vch->arena_timer);
stc(buf,ch);
sprintf(buf,"ch->majesty_timer   %d\n\r",vch->majesty_timer);
stc(buf,ch);
sprintf(buf,"ch->cobra_timer     %d\n\r",vch->cobra_timer);
stc(buf,ch);
sprintf(buf,"ch->wyld_timer      %d\n\r",vch->wyld_timer);
stc(buf,ch);
sprintf(buf,"ch->embraced        %s\n\r",
vch->embraced != NULL ? vch->embraced->name:"None");
stc(buf,ch);
sprintf(buf,"ch->embracing       %s\n\r",
vch->embracing != NULL ? vch->embracing->name:"None");
stc(buf,ch);
sprintf(buf,"ch->Not.. Finished.. yet.... heh.... too... boring......\n\r");
stc(buf,ch);
return;
}

