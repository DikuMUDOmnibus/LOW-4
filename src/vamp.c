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

void set_fighting args(( CHAR_DATA *ch, CHAR_DATA *victim));

void animalism_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_ANIM] == 0 )
  {
    stc("      Animalism: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_ANIM] >= 1 )
    stc("      Animalism:  Beckon",ch);
  if ( ch->pcdata->powers[VAM_ANIM] >= 2 )
    stc(" Serenity",ch);
  if ( ch->pcdata->powers[VAM_ANIM] >= 3 )
    stc(" Pigeon",ch);
  if ( ch->pcdata->powers[VAM_ANIM] >= 4 )
    stc(" Share",ch);
  if ( ch->pcdata->powers[VAM_ANIM] >= 5 )
    stc(" Frenzy",ch);
  stc("\n\r",ch);
  return;
} 

void obtenebration_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_OBTE] == 0 )
  {
    stc("  Obtenebration: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_OBTE] >= 1 )
    stc("  Obtenebration:  Shroud",ch);
  if ( ch->pcdata->powers[VAM_OBTE] >= 2 )
    stc(" Shroudnight",ch);
  if ( ch->pcdata->powers[VAM_OBTE] >= 3 )
    stc(" NightSight",ch);
  if ( ch->pcdata->powers[VAM_OBTE] >= 4 )
    stc(" Shadowstep",ch);
  if ( ch->pcdata->powers[VAM_OBTE] >= 5 )
    stc(" Lamprey",ch);
  stc("\n\r",ch);
  return;
}

void thaumaturgy_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_THAU] == 0 )
  {
    stc("    Thaumaturgy: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_THAU] >= 1 )
    stc("    Thaumaturgy:  Taste",ch);
  if ( ch->pcdata->powers[VAM_THAU] >= 2 )
    stc(" Cauldron",ch);
  if ( ch->pcdata->powers[VAM_THAU] >= 3 )
    stc(" Potency",ch);
  if ( ch->pcdata->powers[VAM_THAU] >= 4 )
    stc(" Theft",ch);
  if ( ch->pcdata->powers[VAM_THAU] >= 5 )
    stc(" Tide",ch);
  stc("\n\r",ch);
  return;
}

void obfuscate_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_OBFU] == 0 )
  {
    stc("      Obfuscate: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_OBFU] >= 1 )
    stc("      Obfuscate:  Vanish",ch);
  if ( ch->pcdata->powers[VAM_OBFU] >= 2 )
    stc(" Shield",ch);
  if ( ch->pcdata->powers[VAM_OBFU] >= 3 )
    stc(" Mask",ch);
  if ( ch->pcdata->powers[VAM_OBFU] >= 4 )
    stc(" Mortal",ch);
  if ( ch->pcdata->powers[VAM_OBFU] >= 5 )
    stc(" Conceal",ch);
  stc("\n\r",ch);
  return;
}


void serpentis_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_SERP] == 0 )
  {
    stc("      Serpentis: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_SERP] >= 1 )
    stc("      Serpentis:  Darkheart",ch);
  if ( ch->pcdata->powers[VAM_SERP] >= 2 )
    stc(" SerpentForm",ch);
  if ( ch->pcdata->powers[VAM_SERP] >= 3 )
    stc(" Poison",ch);
  if ( ch->pcdata->powers[VAM_SERP] >= 4 )
    stc(" Breath",ch);
  if ( ch->pcdata->powers[VAM_SERP] >= 5 )
    stc(" Tongue",ch);
  stc("\n\r",ch);
  return;
}



void chimerstry_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_CHIM] == 0 )
  {
    stc("     Chimerstry: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_CHIM] >= 1 )
    stc("     Chimerstry:  Mirror",ch);
  if ( ch->pcdata->powers[VAM_CHIM] >= 2 )
    stc(" Formillusion",ch);
  if ( ch->pcdata->powers[VAM_CHIM] >= 3 )
    stc(" Clone",ch);
  if ( ch->pcdata->powers[VAM_CHIM] >= 4 )
    stc(" Control",ch);
  if ( ch->pcdata->powers[VAM_CHIM] >= 5 )
    stc(" Objectmask",ch);
  stc("\n\r",ch);
  return;
}




void necromancy_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_NECR] == 0 )
  {
    stc("     Necromancy: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_NECR] >= 1 )
    stc("     Necromancy:  BloodWater",ch);
  if ( ch->pcdata->powers[VAM_NECR] >= 2 )
    stc(" Preserve",ch);
  if ( ch->pcdata->powers[VAM_NECR] >= 3 )
    stc(" Spiritgate",ch);
  if ( ch->pcdata->powers[VAM_NECR] >= 4 )
    stc(" SpiritGuardian",ch);
  if ( ch->pcdata->powers[VAM_NECR] >= 5 )
    stc(" Zombie",ch);
  stc("\n\r",ch);
  return;
}



void celerity_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_CELE] == 0 )
  {
    stc("       Celerity: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_CELE] >= 1 )
    stc("       Celerity:  1",ch);
  if ( ch->pcdata->powers[VAM_CELE] >= 2 )
    stc(" 2",ch);
  if ( ch->pcdata->powers[VAM_CELE] >= 3 )
    stc(" 3",ch);
  if ( ch->pcdata->powers[VAM_CELE] >= 4 )
    stc(" 4",ch);
  if ( ch->pcdata->powers[VAM_CELE] >= 5 )
    stc(" 5",ch);
  stc("\n\r",ch);
  return;
}


void presence_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_PRES] == 0 )
  {
    stc("       Presence: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_PRES] >= 1 )
    stc("       Presence:  Awe",ch);
  if ( ch->pcdata->powers[VAM_PRES] >= 2 )
    stc(" Mindblast",ch);
  if ( ch->pcdata->powers[VAM_PRES] >= 3 )
    stc(" Entrance",ch);
  if ( ch->pcdata->powers[VAM_PRES] >= 4 )
    stc(" Summoning",ch);
  if ( ch->pcdata->powers[VAM_PRES] >= 5 )
    stc(" Majesty",ch);
  stc("\n\r",ch);
  return;
}



void auspex_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_AUSP] == 0 )
  {
    stc("         Auspex: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_AUSP] >= 1 )
    stc("         Auspex:  Truesight",ch);
  if ( ch->pcdata->powers[VAM_AUSP] >= 2 )
    stc(" Scry",ch);
  if ( ch->pcdata->powers[VAM_AUSP] >= 3 )
    stc(" Unveil",ch);
  if ( ch->pcdata->powers[VAM_AUSP] >= 4 )
    stc(" Astral Walk",ch);
  if ( ch->pcdata->powers[VAM_AUSP] >= 5 )
    stc(" Readaura",ch);
  stc("\n\r",ch);
  return;
}


void potence_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_POTE] == 0 )
  {
    stc("        Potence: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_POTE] >= 1 )
    stc("        Potence:  1",ch);
  if ( ch->pcdata->powers[VAM_POTE] >= 2 )
    stc(" 2",ch);
  if ( ch->pcdata->powers[VAM_POTE] >= 3 )
    stc(" 3",ch);
  if ( ch->pcdata->powers[VAM_POTE] >= 4 )
    stc(" 4",ch);
  if ( ch->pcdata->powers[VAM_POTE] >= 5 )
    stc(" 5",ch);
  stc("\n\r",ch);
  return;
}



void vicissitude_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_VICI] == 0 )
  {
    stc("    Vicissitude: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_VICI] >= 1 )
    stc("    Vicissitude:  Zuloform",ch);
  if ( ch->pcdata->powers[VAM_VICI] >= 2 )
    stc(" Fleshcraft",ch);
  if ( ch->pcdata->powers[VAM_VICI] >= 3 )
    stc(" Bonemod",ch);
  if ( ch->pcdata->powers[VAM_VICI] >= 4 )
    stc(" DragonForm",ch);
  if ( ch->pcdata->powers[VAM_VICI] >= 5 )
    stc(" Plasma",ch);
  stc("\n\r",ch);
  return;
}


void obeah_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_OBEA] == 0 )
  {
    stc("          Obeah: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_OBEA] >= 1 )
    stc("          Obeah:  Obeah",ch);
  if ( ch->pcdata->powers[VAM_OBEA] >= 2 )
    stc(" Panacea",ch);
  if ( ch->pcdata->powers[VAM_OBEA] >= 3 )
    stc(" anesthetic",ch);
  if ( ch->pcdata->powers[VAM_OBEA] >= 4 )
    stc(" neutral",ch);
  if ( ch->pcdata->powers[VAM_OBEA] >= 5 )
    stc(" renew",ch);
  stc("\n\r",ch);
  return;
}



void fortitude_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_FORT] == 0 )
  {
    stc("      Fortitude: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_FORT] >= 1 )
    stc("      Fortitude:  1",ch);
  if ( ch->pcdata->powers[VAM_FORT] >= 2 )
    stc(" 2",ch);
  if ( ch->pcdata->powers[VAM_FORT] >= 3 )
    stc(" 3",ch);
  if ( ch->pcdata->powers[VAM_FORT] >= 4 )
    stc(" 4",ch);
  if ( ch->pcdata->powers[VAM_FORT] >= 5 )
    stc(" 5",ch);
  stc("\n\r",ch);
  return;
}



void quietus_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_QUIE] == 0 )
  {
    stc("        Quietus: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_QUIE] >= 1 )
    stc("        Quietus:  Spit",ch);
  if ( ch->pcdata->powers[VAM_QUIE] >= 2 )
    stc(" Infirmity",ch);
  if ( ch->pcdata->powers[VAM_QUIE] >= 3 )
    stc(" Bloodagony",ch);
  if ( ch->pcdata->powers[VAM_QUIE] >= 4 )
    stc(" Assassinate",ch);
  if ( ch->pcdata->powers[VAM_QUIE] >= 5 )
    stc(" silencedeath",ch);
  stc("\n\r",ch);
  return;
}


void dominate_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_DOMI] == 0 )
  {
    stc("       Dominate: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_DOMI] >= 1 )
    stc("       Dominate:  Command",ch);
  if ( ch->pcdata->powers[VAM_DOMI] >= 2 )
    stc(" Mesmerise",ch);
  if ( ch->pcdata->powers[VAM_DOMI] >= 3 )
    stc(" Possession",ch);
  if ( ch->pcdata->powers[VAM_DOMI] >= 4 )
    stc(" Acid",ch);
  if ( ch->pcdata->powers[VAM_DOMI] >= 5 )
    stc(" Coil",ch);
  stc("\n\r",ch);
  return;
}


void protean_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_PROT] == 0 )
  {
    stc("        Protean: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_PROT] >= 1 )
    stc("        Protean:  Umbravision",ch);
  if ( ch->pcdata->powers[VAM_PROT] >= 2 )
    stc(" Claws",ch);
  if ( ch->pcdata->powers[VAM_PROT] >= 3 )
    stc(" Change",ch);
  if ( ch->pcdata->powers[VAM_PROT] >= 4 )
    stc(" Earthmeld",ch);
  if ( ch->pcdata->powers[VAM_PROT] >= 5 )
    stc(" Flamehands",ch);
  stc("\n\r",ch);
  return;
}


void daimoinon_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_DAIM] == 0 )
  {
    stc("      Daimoinon: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_DAIM] >= 1 )
    stc("      Daimoinon:  Guardian",ch);
  if ( ch->pcdata->powers[VAM_DAIM] >= 2 )
    stc(" Blood Wall",ch);
  if ( ch->pcdata->powers[VAM_DAIM] >= 3 )
    stc(" Gate",ch);
  if ( ch->pcdata->powers[VAM_DAIM] >= 4 )
    stc(" Vtwist",ch);
  if ( ch->pcdata->powers[VAM_DAIM] >= 5 )
    stc(" Fear",ch);
  stc("\n\r",ch);
  return;
}


void melpominee_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_MELP] == 0 )
  {
    stc("     Melpominee: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_MELP] >= 1 )
    stc("     Melpominee:  Scream",ch);
  if ( ch->pcdata->powers[VAM_MELP] >= 2 )
    stc(" Gourge",ch);
  if ( ch->pcdata->powers[VAM_MELP] >= 3 )
    stc(" Love",ch);
  if ( ch->pcdata->powers[VAM_MELP] >= 4 )
    stc(" Reina",ch);
  if ( ch->pcdata->powers[VAM_MELP] >= 5 )
    stc(" Courage",ch);
  stc("\n\r",ch);
  return;
}


void thanatosis_disc( CHAR_DATA *ch )
{
  if (IS_NPC(ch) ) return;

  if ( ch->pcdata->powers[VAM_THAN] == 0 )
  {
    stc("     Thanatosis: None.\n\r",ch);
    return;
  }

  if ( ch->pcdata->powers[VAM_THAN] >= 1 )
    stc("     Thanatosis:  Hagswrinkles",ch);
  if ( ch->pcdata->powers[VAM_THAN] >= 2 )
    stc(" Putrefaction",ch);
  if ( ch->pcdata->powers[VAM_THAN] >= 3 )
    stc(" Ashes",ch);
  if ( ch->pcdata->powers[VAM_THAN] >= 4 )
    stc(" Wither",ch);
  if ( ch->pcdata->powers[VAM_THAN] >= 5 )
    stc(" Drain",ch);
  stc("\n\r",ch);
  return;
}

void do_vampire( CHAR_DATA *ch, char *argument )
{
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_IMMUNE(ch, IMM_VAMPIRE))
    {
	send_to_char("You will now allow vampires to bite you.\n\r",ch);
	SET_BIT(ch->immune, IMM_VAMPIRE);
	return;
    }
    send_to_char("You will no longer allow vampires to bite you.\n\r",ch);
    REMOVE_BIT(ch->immune, IMM_VAMPIRE);
    return;
}


void do_racepower( CHAR_DATA *ch, char *argument )
{


  if ( IS_NPC(ch) ) return;

  if ( IS_CLASS( ch, CLASS_VAMPIRE ) || IS_ABOMINATION(ch) )
  {
    stc("---------------------------==| Vampire Powers |==------------------------\n\r",ch);
     animalism_disc(ch);
    obtenebration_disc(ch);
    thaumaturgy_disc(ch);
    obfuscate_disc(ch);
    serpentis_disc(ch);
    chimerstry_disc(ch);
    necromancy_disc(ch);
    celerity_disc(ch);
    presence_disc(ch);
    auspex_disc(ch);
    potence_disc(ch);
    vicissitude_disc(ch);
    obeah_disc(ch);
    fortitude_disc(ch);
    quietus_disc(ch);
    dominate_disc(ch);
    protean_disc(ch);
    daimoinon_disc(ch);
    melpominee_disc(ch);
    thanatosis_disc(ch);
    divide2_to_char(ch);
    return;
  }
  else
   return;

  return;
}

/*embrace*/
void do_embrace(CHAR_DATA *ch, char *argument  )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
    int bloodpool;
    one_argument( argument, arg );
/*
	 if ( !IS_NPC(ch) && IS_CLASS(ch, CLASS_VAMPIRE) &&
                ch->pcdata->condition[COND_THIRST] >=
2000/ch->pcdata->stats[UNI_GEN]);
            send_to_char( "Your blood thirst is sated.\n\r", ch );
*/
    if (ch->pcdata->stats[UNI_GEN] < 1)
        ch->pcdata->stats[UNI_GEN] = 5;

    
    if (IS_SET(ch->newbits, NEW_TIDE))
    bloodpool = (3000 / ch->pcdata->stats[UNI_GEN]);
    else bloodpool = (2000 / ch->pcdata->stats[UNI_GEN]);
    
 
    if (IS_NPC(ch)) return;
if (IS_ABOMINATION(ch))
{
stc("Abomination may only use fountains and springs to drink blood.\n\r",ch);
return;
}
    if (!IS_CLASS(ch,CLASS_VAMPIRE))
    {
      send_to_char("Huh?\n\r",ch);
      return;
    }


    if ( arg[0] == '\0' )
    {
        send_to_char( "Who do you wish to embrace?\n\r", ch );
	return;
    }



    if ((victim = get_char_room( ch, arg)) == NULL)
    {
      send_to_char("They arent here.\n\r",ch);
      return;
    }

    if (IS_NPC(victim) && IS_SET(victim->act, ACT_NOAUTOKILL)) 
    {
	send_to_char("You can't do that to them.\n\r", ch);
	return;
    }


	if (victim->level > 75)
	{
		send_to_char("They are too powerful to embrace!\n\r",ch);
		return;
	}


        if (IS_SET(victim->act, PLR_EMBRACED))
        {
        send_to_char( "They are already being embraced.\n\r", ch );
        return;
        }

	
    if (!IS_NPC(victim))
    {
      send_to_char("You cannot embrace a person, use diablerise to embrace people.\n\r",ch);
      return;
    }

    if (IS_SET(victim->in_room->room_flags, ROOM_SAFE))
    {
	send_to_char("You cannot embrace them here.\n\r",ch);
	return;
    }

    sprintf(buf,"%s leaps toward %s baring his fangs.\n\r",ch->name,victim->short_descr);
    act(buf,ch,NULL,NULL,TO_ROOM);
    sprintf(buf,"You leap toward %s baring your fangs.\n\r",victim->short_descr);
    send_to_char(buf,ch);
    WAIT_STATE(ch, 15);
    
    if (victim->position != POS_STUNNED && victim->position != POS_SLEEPING && victim->position != POS_DEAD)
    {
      send_to_char("They lunge away from you.\n\r",ch);
      sprintf(buf,"%s lunges away from $n.",victim->name);
      act(buf,ch,NULL,NULL,TO_ROOM);
      return;
    }

    send_to_char("You bury your fangs into their neck, and shiver ecstatically as you drain their lifeblood.!\n\r",ch);
    sprintf(buf,"%s buries his fangs into %s's neck and begins drinking $s lifeblood.\n\r",ch->name,victim->short_descr);
    act(buf,ch,NULL,NULL,TO_ROOM);
		
	/* New update send routine, allows for anything to get embraced. */
	/* and sets a mobs blood to its level  Shakti */

	SET_BIT(victim->act, PLR_EMBRACED);
        ch->embracing = victim;
	if (IS_NPC(victim))
	{
		(victim->practice = victim->level  );
		(victim->practice *= 8);
	}	

	return ;


}

void do_theft( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_INPUT_LENGTH];
    int bloodpool;
	int blpr; /* Blood sucked storage variable. Shakti */

    argument = one_argument( argument, arg );

    if (ch->pcdata->stats[UNI_GEN] <= 0)
        ch->pcdata->stats[UNI_GEN] = 4;

    {
    if (IS_SET(ch->newbits, NEW_TIDE))
    bloodpool = (3000 / ch->pcdata->stats[UNI_GEN]);
    else bloodpool = (2000 / ch->pcdata->stats[UNI_GEN]);
    } 

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    if (ch->pcdata->powers[VAM_THAU] < 4)
    {
        send_to_char("You must obtain at least level 4 in Thaumaturgy to use Theft of Vitae.\n\r",ch);
	return;
    }


    if ( arg[0] == '\0' )
    {
        send_to_char( "Steal blood from whom?\n\r", ch );
	return;
    }

    if (IS_AFFECTED(ch,AFF_POLYMORPH) && !IS_VAMPAFF(ch,VAM_DISGUISED))
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

	 if (IS_NPC(victim) && IS_SET(victim->act, ACT_NOAUTOKILL))
    {
        send_to_char("You can't do that to them.\n\r", ch);
        return;
    }

        /* Shaktis check for level */

        if (victim->level > 75)
        {
                send_to_char("They are too powerful to theft!\n\r",ch);
                return;
        }

/*
    if ( IS_NPC(victim) ) 
    {
        send_to_char( "Lower life forms are immune to Theft of Vitae.\n\r", ch);
        return;
    }
*/
    if (!IS_NPC(victim) && victim->pcdata->condition[COND_THIRST] <= 0)
    {
        send_to_char( "There isn't enough blood to steal.\n\r", ch);
        return;
    }
    if (!IS_NPC(victim) && IS_IMMORTAL(victim) && victim != ch )
    {
        send_to_char( "You can only steal blood from Avatar's or lower.\n\r", ch );
	return;
    }
if (is_safe(ch,victim) == TRUE) return;

if (!IS_NPC(victim)) {
        sprintf(buf,"A stream of blood shoots from %s into your body.",victim->name);
	act(buf,ch,NULL,victim,TO_CHAR);
        sprintf(buf,"A stream of blood shoots from %s into %s.",victim->name,ch->name);
	act(buf,ch,NULL,victim,TO_ROOM);
        sprintf(buf,"A stream of blood shoots from your body into %s.",ch->name);
        act(buf,ch,NULL,victim,TO_VICT);
        } else {
        sprintf(buf,"A stream of blood shoots from %s into your body.",victim->short_descr);
	act(buf,ch,NULL,victim,TO_CHAR);
        sprintf(buf,"A stream of blood shoots from %s into %s.",victim->short_descr,ch->name);
	act(buf,ch,NULL,victim,TO_ROOM);
        sprintf(buf,"A stream of blood shoots from your body into %s.",ch->name);
        act(buf,ch,NULL,victim,TO_VICT);


	}
        ch->pcdata->condition[COND_THIRST] += number_range(20,25);
     
		
		if (IS_NPC(victim))
        {
/* Raw-killing it from one theft is stupid. Im going to use the primal */
/* stat on the mobs for blood its quick, effective, and straightford, AND */
/* no new fields have to be added to the mob.Shakti 09/07/98 */
			(blpr = number_range (30,40) );
			(victim->practice -=(blpr/2));
            (ch->pcdata->condition[COND_THIRST] += blpr);
		if (victim->practice < 0)
		{
		sprintf(buf,"%s falls over dead.",victim->short_descr);
		act(buf,ch,NULL,victim,TO_ROOM);
		act(buf,ch,NULL,victim,TO_CHAR);
		raw_kill(victim, ch);
		}		

		 if (ch->pcdata->condition[COND_THIRST] >= bloodpool )
             {
              ch->pcdata->condition[COND_THIRST] = bloodpool;
             }
	if (ch->fighting == NULL) set_fighting(ch,victim);

         return;
        }

	if ( is_garou(ch) && ch->gifts[GETOFFENRIS] >= 4 )
	{
	  stc("Their blood is a deadly venom!\n\r",ch);
	  ch->hit -= number_range(400,500);
	  return;
	}

        if (IS_SET(victim->act, PLR_ACID))
        {
        send_to_char("Their blood is a deadly acid!\n\r", ch);
        ch->hit -= 300;
        victim->pcdata->condition[COND_THIRST] -= 30;
        return;
        }

    if (!IS_NPC(victim)) 
{
victim->pcdata->condition[COND_THIRST] -=number_range(30,40);
}
    if (ch->pcdata->condition[COND_THIRST] >= bloodpool / ch->pcdata->stats[UNI_GEN])
    {
       ch->pcdata->condition[COND_THIRST] = bloodpool/ch->pcdata->stats[UNI_GEN];
    }

   if (victim->pcdata->condition[COND_THIRST] <= 0)
    {
       victim->pcdata->condition[COND_THIRST] = 0; 
    }
	if (ch->fighting == NULL) set_fighting(ch,victim);

   return;
}


void do_diablerise(CHAR_DATA *ch, char *argument  )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
    one_argument( argument,arg);
 
    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch,CLASS_VAMPIRE))
    {
      send_to_char("Huh?\n\r",ch);
      return;
    }

    if ( arg[0] == '\0' && ch->embracing==NULL)
    {
        send_to_char( "Who do you wish to embrace?\n\r", ch );
	  return;
    }

    if (ch->embracing != NULL)
    {
      if ( ( victim = ch->embracing) != NULL)
      {
        send_to_char("You retract your fangs.",ch);
        act("$N retracts his fangs.",ch,NULL,NULL,TO_ROOM);
        stop_embrace(ch,victim);
        return;
      }
    }

    if ((victim = get_char_room( ch, arg)) == NULL && ch->embracing==NULL)
    {
      send_to_char("They arent here.\n\r",ch);
      return;
    }


    if (IS_NPC(victim) || !IS_CLASS(victim,CLASS_VAMPIRE))
    {
      send_to_char("You can only embrace vampires.\n\r",ch);
      return;
    }
  
    if (victim->position != POS_MORTAL)
    {
      send_to_char("You can only embrace mortally wounded vampires.\n\r",ch);
      return;
    }

    sprintf(buf,"%s leaps toward %s baring his fangs.",ch->name,victim->name);
    act(buf,ch,NULL,NULL,TO_ROOM);
    sprintf(buf,"You leap toward %s baring your fangs.\n\r",victim->name);
    send_to_char(buf,ch);
    WAIT_STATE(ch, 15);
    
    sprintf(buf,"You sink your teeth into their throat.\n\r");
    send_to_char(buf,ch);
    sprintf(buf,"%s sinks their teeth into %s's throat.",ch->name,victim->name);
    act(buf,ch,NULL,NULL,TO_ROOM);
    sprintf(buf,"%s sinks their teeth into your throat.\n\r",ch->name);
    send_to_char(buf,victim);
    victim->embraced = ch;
    ch->embracing = victim;
 
    return;
 }


void do_preserve( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    char arg [MAX_INPUT_LENGTH];
    
    argument = one_argument( argument, arg );

    if ( IS_NPC(ch) ) return;

    if ( !IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
      stc("Huh?\n\r",ch);
      return;
    }

    if ( ch->pcdata->powers[VAM_NECR] < 2 )
    {
      stc("You must obtain level 2 Necromancy to use Preserve.\n\r",ch);
      return;
    }

    if ( ( obj = get_obj_carry(ch, arg) ) == NULL )
    {
      stc("You do not have that item.\n\r",ch);
      return;
    }

if (obj->pIndexData->vnum == 12) 
    {
      stc("You cannot preserve that item.\n\r",ch);
      return;
    }

    if ( obj->timer <= 0 )
    {
      stc("That object has no timer.\n\r",ch);
      return;
    }

    obj->timer = -1;
    act("You place your hands on $p and concentrate on it.",ch,obj,NULL,TO_CHAR);
    act("$n places $s hands on $p and it glows brightly.",ch,obj,NULL,TO_ROOM);
    return;
}

void do_spiritguard( CHAR_DATA *ch, char *argument )
{
   
    if (IS_NPC(ch) ) return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE) )
    {
      stc("Huh?\n\r",ch);
      return;
    }

    if ( ch->pcdata->powers[VAM_NECR] < 4 )
    {
      stc("You must obtain level 4 Necromancy to use Spirit Guardian.\n\r",ch);
      return;
    }

    if ( !IS_SET(ch->flag2, AFF2_SPIRITGUARD) )
    {
      stc("You awaken your spirit guardian.\n\r",ch);
      SET_BIT(ch->flag2, AFF2_SPIRITGUARD);
      return;
    }

    else
    {
      stc("You dismiss your spirit guardian.\n\r",ch);
      REMOVE_BIT(ch->flag2, AFF2_SPIRITGUARD);
      return;
    }
  return;
}

void do_spiritgate( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    char arg[MAX_INPUT_LENGTH];
   
    argument = one_argument( argument, arg );
   
    if ( IS_NPC(ch) ) return;
  
    if ( !IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
      stc("Huh?\n\r",ch);
      return;
    }

    if ( ch->pcdata->powers[VAM_NECR] < 3 )
    {
      stc("You must obtain level 3 Necromancy to use SpiritGate.\n\r",ch);
      return;
    }

    if ( ( obj = get_obj_world( ch, arg ) ) == NULL )
    {
      stc("You cannot find that object.\n\r",ch);
      return;
    }

    if ( ch->pcdata->condition[COND_THIRST] < 66 )
    {
      stc("You do not have enough blood.\n\r",ch);
      return;
    }

    if ( obj->in_room == NULL )
    {
      stc("You cannot locate that object.\n\r",ch);
      return;
    }

    if ( obj->carried_by != NULL )
    {
      stc("That corpse is being carried by someone!\n\r",ch);
      return;
    }

    if ( obj->item_type != ITEM_CORPSE_PC && obj->item_type !=
ITEM_CORPSE_NPC )
    {
      stc("That's not even a corpse!\n\r",ch);
      return;
    }

    if ( obj->in_room->vnum == ch->in_room->vnum )
    {
      stc("You're already there!\n\r",ch);
      return;
    }

    act("$n steps into a spirit gate and vanishes.",ch,NULL,NULL,TO_ROOM);
    char_from_room(ch);
    char_to_room(ch, get_room_index( obj->in_room->vnum ));
    act("You step through a spirit gate and appear before $p.",ch,obj,NULL,TO_CHAR);
    act("$n steps out of a spirit gate in front of $p.",ch,obj,NULL,TO_ROOM);
    ch->pcdata->condition[COND_THIRST] -= 65;
    return;
}

void do_scream( CHAR_DATA *ch, char *argument )
{
   CHAR_DATA *vch;
   CHAR_DATA *vch_next;
   CHAR_DATA *mount;
   char arg[MAX_INPUT_LENGTH];

   argument = one_argument( argument, arg );

   if ( IS_NPC(ch) ) return;
 
   if ( !IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
   {
     stc("Huh?\n\r",ch);
     return;
   }

   if ( ch->pcdata->powers[VAM_MELP] < 1 )
   {
     stc("You must obtain level 1 Melpominee to use Scream.\n\r",ch);
     return;
   }

   if ( IS_SET(ch->in_room->room_flags, ROOM_SAFE) )
   {
     stc("Your screams will have no effect here.\n\r",ch);
     return;
   }

   if ( ch->pcdata->condition[COND_THIRST] < 50 )
   {
     stc("You have insufficient blood.\n\r",ch);
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
              if ( number_range( 1, (7 - ch->pcdata->powers[VAM_MELP])) ==
2 )
              {
                act("$n lets out an ear-popping scream!",ch,NULL,vch,TO_ROOM);
                stc("You fall to the ground, clutching your ears.\n\r",vch);
                vch->position = POS_STUNNED;
                act("$n falls to the ground, stunned.",vch,NULL,vch,TO_NOTVICT);
                return;
              }
	      else
	      {
                act("$n lets out an ear-popping scream!",ch,NULL,vch,TO_ROOM);
	        return;
	      }
	    }
	    else continue;

	    return;
        }
    }

  return;
}


void do_zombie(CHAR_DATA *ch, char *argument )
{
    char buf2[MAX_STRING_LENGTH]; 
    char buf [MAX_INPUT_LENGTH];
    char arg [MAX_STRING_LENGTH];
    CHAR_DATA *victim;
    AFFECT_DATA af;
    OBJ_DATA *obj;
    one_argument(argument,arg);
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_CLASS(ch, CLASS_MAGE))
     {
     send_to_char("Huh?\n\r",ch);
     return;
     }
    if (arg[0] == '\0')
    {
    send_to_char("Zombie what corpse?\n\r",ch);
    return;
    }
    if ( IS_CLASS(ch, CLASS_VAMPIRE) && ch->pcdata->powers[VAM_NECR] < 5)
    {
    send_to_char("You require level 5 Necromancy to create a zombie.\n\r",ch);
    return;
    }

    if ( IS_CLASS(ch, CLASS_MAGE) && ch->spheres[MSPI] < 3 )
    {
      stc("You must obtain level 3 Spirit to Awaken the Inanimate.\n\r",ch);
      return;
    } 

    if (ch->pcdata->followers > 5)
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }
    if ((obj = get_obj_carry(ch,arg)) == NULL)
    {
    send_to_char("You dont have that corpse.",ch);
    return;
    }
    if (obj->item_type != ITEM_CORPSE_NPC || IS_SET(obj->quest, QUEST_ZOMBIE))
    {
    send_to_char("You can only Zombie original corpses.\n\r",ch);
    return;
    }
 
 
    ch->pcdata->followers++;
 
    
    victim=create_mobile( get_mob_index( obj->value[2] ) );
    sprintf(buf,"the zombie of %s",victim->short_descr);
    sprintf(buf2,"the zombie of %s is here.\n\r",victim->short_descr);
    free_string(victim->short_descr);
    victim->short_descr = str_dup(buf);
    free_string(victim->name);
    victim->name = str_dup(buf);
    free_string(victim->long_descr);
    victim->long_descr= str_dup(buf2);
    SET_BIT(victim->extra, EXTRA_ZOMBIE);
 	victim->spec_fun = NULL;
    strcpy(buf,"Rise corpse, and bow before me!");
    do_say( ch, buf );
    sprintf(buf, "%s clambers back up to its feet.\n\r",obj->short_descr
);
    act(buf,ch,NULL,NULL,TO_ROOM);
    send_to_char(buf,ch);
 
 
    char_to_room( victim, ch->in_room );
 
 if (victim->level < 100)
{
    add_follower( victim, ch );
    af.duration  = 666;
    af.location  = APPLY_NONE;
    af.modifier  = 0;
    af.bitvector = AFF_CHARM;
    affect_to_char( victim, &af );
}
WAIT_STATE(ch,10);
extract_obj(obj);
    return;
}
/*
void do_fleshcraft( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_INPUT_LENGTH];
 
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
 
    if (ch->pcdata->powers[VAM_VICI] < 2)
    {
	send_to_char("You need Vicissitude 2 to fleshcraft.\n\r",ch);
	return;
    }
 
    if ( arg[0] == '\0' )
    {
	send_to_char( "Change to look like whom?\n\r", ch );
	return;
    }
 
    if (IS_AFFECTED(ch,AFF_POLYMORPH) && !IS_VAMPAFF(ch,VAM_DISGUISED))
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
	return;
    }
 
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
    if ( !IS_NPC(victim) && ch != victim)
    {
	send_to_char( "Not on Players.\n\r", ch );
	return;
    }
 
 
    if ( ch->pcdata->condition[COND_THIRST] < 40 )
    {
	send_to_char("You have insufficient blood.\n\r",ch);
	return;
    }
    ch->pcdata->condition[COND_THIRST] -= number_range(30,40);
 
    if ( ch == victim )
    {
	if (!IS_AFFECTED(ch,AFF_POLYMORPH) &&
!IS_VAMPAFF(ch,VAM_DISGUISED))
	{
	    send_to_char( "You already look like yourself!\n\r", ch );
	    return;
	}
        sprintf(buf,"Your flesh molds and transforms into %s.",ch->name);
	act(buf,ch,NULL,victim,TO_CHAR);
        sprintf(buf,"%s's flesh molds and transforms into
%s.",ch->morph,ch->name);
	act(buf,ch,NULL,victim,TO_ROOM);
	REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
    	free_string( ch->morph );
    	ch->morph = str_dup( "" );
	return;
    }
    if (IS_VAMPAFF(ch,VAM_DISGUISED))
    {
        sprintf(buf,"Your flesh molds and transforms into a clone of
%s.",victim->short_descr);
    	act(buf,ch,NULL,victim,TO_CHAR);
        sprintf(buf,"%s's flesh molds and transforms into a clone of
%s.",ch->morph,victim->short_descr);
    	act(buf,ch,NULL,victim,TO_NOTVICT);
        sprintf(buf,"%s's flesh mols and transforms into a clone of
you!",ch->morph);
    	act(buf,ch,NULL,victim,TO_VICT);
    	free_string( ch->morph );
        ch->morph = str_dup( victim->short_descr );
	return;
    }
    sprintf(buf,"Your flesh molds and transforms into a clone of
%s.",victim->short_descr);
    act(buf,ch,NULL,victim,TO_CHAR);
    sprintf(buf,"%s's flesh molds and transforms into a clone of
%s.",ch->name,victim->short_descr);
    act(buf,ch,NULL,victim,TO_NOTVICT);
    sprintf(buf,"%s's flesh molds and transforms into a clone of
you!",ch->name);
    act(buf,ch,NULL,victim,TO_VICT);
    SET_BIT(ch->affected_by, AFF_POLYMORPH);
    SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
    free_string( ch->morph );
    ch->morph = str_dup( victim->short_descr );
    return;
}
*/

void do_fleshcraft( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
 //   char      arg2 [MAX_INPUT_LENGTH];
//    char      arg3 [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

    one_argument( argument, arg1 );

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch) && !IS_ABOMINATION(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

   
    if (ch->pcdata->powers[VAM_VICI] < 2)
    {
        send_to_char("You need Vicissitude 2 to fleshcraft.\n\r",ch);
        return;
    }

    if ( arg1[0] == '\0' )
    {
	send_to_char( "Change to look like whom?\n\r", ch );
	return;
    }

   

    if (IS_AFFECTED(ch,AFF_POLYMORPH) && !IS_VAMPAFF(ch,VAM_DISGUISED))
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
	return;
    }

    if (IS_POLYAFF(ch,POLY_ZULO))
    {
	send_to_char( "Not while in Zulo Form.\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( IS_IMMORTAL(victim) && victim != ch )
    {
	send_to_char( "You cannot disguise yourself as them.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	if (!IS_AFFECTED(ch,AFF_POLYMORPH) &&
!IS_VAMPAFF(ch,VAM_DISGUISED))
	{
	    send_to_char( "You already look like yourself!\n\r", ch );
	    return;
	}
	if (!IS_POLYAFF(ch, POLY_FLESHCRAFT))
	{
	    send_to_char( "Nothing happens.\n\r", ch );
	    return;
	}
	sprintf(buf,"$n's features twist and distort until $e looks like %s.",ch->name);
	act(buf,ch,NULL,NULL,TO_ROOM);
	REMOVE_BIT(ch->polyaff, POLY_FLESHCRAFT);
	REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
//	REMOVE_BIT(ch->vampaff, VAM_DISGUISED);
	//REMOVE_BIT(ch->extra, EXTRA_VICISSITUDE);
    	free_string( ch->morph );
    	ch->morph = str_dup( "" );
	act("Your features twist and distort until you looks like $n.",ch,NULL,NULL,TO_CHAR);
    	free_string( ch->long_descr );
    	ch->long_descr = str_dup( "" );
	return;
    }
    if (IS_VAMPAFF(ch,VAM_DISGUISED))
    {
	if (!IS_POLYAFF(ch, POLY_FLESHCRAFT))
	{
	    send_to_char( "Nothing happens.\n\r", ch );
	    return;
	}
	act("Your features twist and distort until you looks like $N.",ch,NULL,victim,TO_CHAR);
	act("$n's features twist and distort until $e looks like you.",ch,NULL,victim,TO_VICT);
	act("$n's features twist and distort until $e looks like $N.",ch,NULL,victim,TO_NOTVICT);
    	free_string( ch->morph );
	if (IS_NPC(victim))
	{
	    ch->morph = str_dup( victim->short_descr );
	    free_string( ch->long_descr );
	    ch->long_descr = str_dup( victim->long_descr );
	}
	else
	{
	    ch->morph = str_dup( victim->name );
	    free_string( ch->long_descr );
	    ch->long_descr = str_dup( "" );
	}
	return;
    }
    act("Your features twist and distort until you looks like $N.",ch,NULL,victim,TO_CHAR);
    act("$n's features twist and distort until $e looks like you.",ch,NULL,victim,TO_VICT);
    act("$n's features twist and distort until $e looks like $N.",ch,NULL,victim,TO_NOTVICT);
    SET_BIT(ch->polyaff, POLY_FLESHCRAFT);
    SET_BIT(ch->affected_by, AFF_POLYMORPH);
	SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
//    SET_BIT(ch->vampaff, VAM_DISGUISED);
    //SET_BIT(ch->extra, EXTRA_VICISSITUDE);
    free_string( ch->morph );
    if (IS_NPC(victim))
    {
	ch->morph = str_dup( victim->short_descr );
	free_string( ch->long_descr );
	ch->long_descr = str_dup( victim->long_descr );
    }
    else
    {
	ch->morph = str_dup( victim->name );
	free_string( ch->long_descr );
	ch->long_descr = str_dup( "" );
    }
    return;
}

void do_bonemod( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];

    smash_tilde( argument );
    argument = one_argument( argument, arg1 );


	if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
	{
	   send_to_char("Huh?\n\r",ch);
	   return;
	}
	if (ch->pcdata->powers[VAM_VICI] < 3)
	{
	   send_to_char("You need level 3 Vicissitude to use this power.\n\r",ch);
	   return;
	}

    if ( arg1[0] == '\0')
    {
	send_to_char( "Syntax: bonemod <modification>\n\r",	ch );
	send_to_char( "Horns, Wings, Head, Exoskeleton, Tail\n\r",ch);
        return;
    }


    /*
     * Set something.
     */
    if ( !str_cmp( arg1, "horns" ) )
    {
	
 	if (!IS_VAMPAFF(ch, VAM_HORNS))
	 {
	  SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_HORNS);
	  send_to_char("You pull a set of horns out of your head.\n\r",ch);
	  act("$n pulls a set of horns from his head!\n\r",ch,NULL,NULL,TO_ROOM);
	  return;
       }
	
	if (IS_VAMPAFF(ch, VAM_HORNS))
	 {
	  REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_HORNS);
	  send_to_char("You push your horns back into your head.\n\r",ch);
	  act("$n pushes $n's horns back into $n head.\n\r",ch,NULL,NULL,TO_ROOM); 
	  return;

	 }
    }

    if ( !str_cmp( arg1, "wings" ) )
    {
	
 	if (!IS_VAMPAFF(ch, VAM_WINGS))
	 {
	  SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_WINGS);
	  send_to_char("You pull a pair of leathery wings from your back.\n\r",ch);
	  act("$n pulls a pair of leathery wings from $s back!\n\r",ch,NULL,NULL,TO_ROOM);
	  return;
       }
	
	if (IS_VAMPAFF(ch, VAM_WINGS))
	 {
	  REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_WINGS);
	  send_to_char("You push your wings into your back.\n\r",ch);
	  act("$n pushes $s wings into $s back.\n\r",ch,NULL,NULL,TO_ROOM);
	  return;

	 }
    }    

     if ( !str_cmp( arg1, "exoskeleton" ) )
    {
	
 	if (!IS_VAMPAFF(ch, VAM_EXOSKELETON))
	 {
	  SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_EXOSKELETON);
	  send_to_char("Your skin is covered by a hard exoskeleton.\n\r",ch);
	  act("$n's skin is covered by a hard exoskeleton!\n\r",ch,NULL,NULL,TO_ROOM);
	  return;
       }
	
	if (IS_VAMPAFF(ch, VAM_EXOSKELETON))
	 {
	  REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_EXOSKELETON);
	  send_to_char("Your exoskeleton slowly disappears under your skin.\n\r",ch);
	  act("$n's hard exoskeleton disappears under $s skin.\n\r",ch,NULL,NULL,TO_ROOM);
	  return;

	 }
    }    

     if ( !str_cmp( arg1, "tail" ) )
    {
	
 	if (!IS_VAMPAFF(ch, VAM_TAIL))
	 {
	  SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_TAIL);
	  send_to_char("Your spine extends out into a long, pointed tail.\n\r",ch);
	  act("$n's spine extends to form a long pointed tail!\n\r",ch,NULL,NULL,TO_ROOM);
	  return;
       }
	
	if (IS_VAMPAFF(ch, VAM_TAIL))
	 {
	  REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_TAIL);
	  send_to_char("Your tail slowly retracts into your spine.\n\r",ch);
	  act("$n's tail shrinks and vanishes into $s spine.\n\r",ch,NULL,NULL,TO_ROOM);
	  return;

	 }
    }    

     if ( !str_cmp( arg1, "head" ) )
    {
	
 	if (!IS_VAMPAFF(ch, VAM_HEAD))
	 {
	  SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_HEAD);
	  send_to_char("Your head transforms into that of a fierce lion.\n\r",ch);	  
	  act("$n's head transforms into that of a fierce lion!\n\r",ch,NULL,NULL,TO_ROOM);
	  return;
       }
	
	if (IS_VAMPAFF(ch, VAM_HEAD))
	 {
	  REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_HEAD);
	  send_to_char("Your head slowly resumes it's normal form.\n\r",ch);
	  act("$n's head resumes its normal form.\n\r",ch,NULL,NULL,TO_ROOM);
	  return;

	 }
    }    




    /*
     * Generate usage message.
     */
    do_bonemod( ch, "" );
    return;
}


void do_pigeon( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    CHAR_DATA *victim;
 
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
 
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
    if (ch->pcdata->powers[VAM_ANIM] < 3)
    {
    send_to_char("You require Aimalism level 3 to pigeon.\n\r",ch);
    return;
    }
    if ( arg1[0] == '\0' )
    {
        send_to_char( "Pigeon which object?\n\r", ch );
        return;
    }
 
    if ( arg2[0] == '\0' )
    {
        send_to_char( "Pigeon what to whom?\n\r", ch );
        return;
    }
    if ( ( obj = get_obj_carry( ch, arg1 ) ) == NULL )
    {
	send_to_char( "You are not carrying that item.\n\r", ch );
	return;
    }
    victim = get_char_world(ch,arg2);
    if ( (victim = get_char_world( ch, arg2 ) ) == NULL )
    {
	send_to_char( "They arent here.\n\r", ch );
	return;
    }
 
    if (!IS_NPC(victim) && !IS_IMMUNE(victim, IMM_TRANSPORT))
    {
        send_to_char( "They dont want anything transported to them.\n\r",ch );
	return;
    }
 
    act("You place $p in a pigeon's beak and it flies away.", ch,obj,NULL,TO_CHAR);
    act("$n places $p in a pigeon's beak and it flies away." ,ch,obj,NULL,TO_ROOM);
    obj_from_char(obj);
    obj_to_char(obj,victim);
 act("A pigeon lands on your shoulders and flies away after handing you $p." ,victim,obj,NULL,TO_CHAR);
 act("A pigeon lands on $n's shoulders and flies away after handing him $p." ,victim,obj,NULL,TO_ROOM);
    do_autosave(ch,"");
    do_autosave(victim,"");
    return;
}


void do_beckon(CHAR_DATA *ch, char *argument  )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    one_argument( argument,arg);
 
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch,CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
    if (ch->pcdata->powers[VAM_ANIM] < 1)
    {
    send_to_char("You require level 1 animalism to beckon the wild.\n\r",ch);
    return;
    }
    if ( arg[0] == '\0' )
    {
        send_to_char( "You can beckon a frog, a raven, a cat or a dog.\n\r", ch );
	return;
    }
 
    if (ch->pcdata->followers > 5 )
    {
    send_to_char("Nothing happened.\n\r",ch);
    return;
    }
    
    if ( !str_cmp( argument, "frog" ) )
    {
	victim = create_mobile( get_mob_index( MOB_VNUM_FROG ) );
	if (victim == NULL)
        {send_to_char("Error - please inform Infidel.\n\r",ch); return;}
    }
    else if ( !str_cmp( argument, "raven" ) )
    {
	victim = create_mobile( get_mob_index( MOB_VNUM_RAVEN ) );
	if (victim == NULL)
        {send_to_char("Error - please inform Infidel.\n\r",ch); return;}
    }
    else if ( !str_cmp( argument, "cat" ) )
    {
	victim = create_mobile( get_mob_index( MOB_VNUM_CAT ) );
	if (victim == NULL)
        {send_to_char("Error - please inform Infidel.\n\r",ch); return;}
    }
    else if ( !str_cmp( argument, "dog" ) )
    {
	victim = create_mobile( get_mob_index( MOB_VNUM_DOG ) );
	if (victim == NULL)
        {send_to_char("Error - please inform Infidel.\n\r",ch); return;}
    }
    else 
    {
        send_to_char( "Your can beckon a frog, a raven, a cat or a dog.\n\r", ch );
	return;
    }
 
    act( "You whistle loudly and $N walks in.", ch, NULL, victim,TO_CHAR);
    act( "$n whistles loudly and $N walks in.", ch, NULL, victim,TO_ROOM);
    char_to_room( victim, ch->in_room );
    ch->pcdata->followers += 1;
    SET_BIT(victim->act, ACT_NOEXP);
    return;
}

void do_share( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    CHAR_DATA *familiar;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    one_argument( argument, arg );

    if ( IS_NPC(ch) )
	return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (ch->pcdata->powers[VAM_ANIM] < 4)
    {
        send_to_char("You must obtain at least level 4 in Animalism to use Share Spirits.\n\r",ch);
	return;
    }

    if ( ( familiar = ch->pcdata->familiar ) != NULL)
    {
	sprintf(buf,"You release %s.\n\r",familiar->short_descr);
	send_to_char( buf, ch );
	familiar->wizard = NULL;
	ch->pcdata->familiar = NULL;
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "What do you wish to Share spirits with?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "What an intelligent idea!\n\r", ch );
	return;
    }

    if ( !IS_NPC(victim) )
    {
	send_to_char( "Not on players.\n\r", ch );
	return;
    }

    if (victim->wizard != NULL)
    {
	send_to_char( "You are unable to Share Spirits them.\n\r", ch );
	return;
    }

    if (victim->level > (ch->spl[RED_MAGIC] ))
    {
	send_to_char( "They are too powerful.\n\r", ch );
	return;
    }

    if ( ch->pcdata->condition[COND_THIRST] < 25 )
    {
	send_to_char("You have insufficient blood.\n\r",ch);
	return;
    }

    ch->pcdata->condition[COND_THIRST] -= 25;
    ch->pcdata->familiar = victim;
    victim->wizard = ch;
    act("You share your being with $N.",ch,NULL,victim,TO_CHAR);
    act("$n is staring at you!",ch,NULL,victim,TO_VICT);
    act("$n starts staring at $N",ch,NULL,victim,TO_NOTVICT);
    return;
}

void do_frenzy( CHAR_DATA *ch, char *argument )
{
/*
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    argument = one_argument (argument, arg);
*/

    if ( IS_NPC(ch) )
	return;


    if ( ch->pcdata->powers[VAM_ANIM] < 5 )
    {
	send_to_char("You need level 5 Animalism to use Frenzy.\n\r",ch);
	return;
    }
/*
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        send_to_char( "They aren't here.\n\r", ch );
        return;
    }    

    if ( IS_NPC(victim) )
	{
	  send_to_char("Not on NPC's!\n\r",ch);
	  return;
	}



    if (IS_CLASS(victim, CLASS_VAMPIRE) && arg[0] != '\0')
    {
	if ( victim->rage >= 25 )
	{
	    send_to_char("Their beast is already controlling them!\n\r",ch);
	    return;
	}

      if (number_percent ( )  <= 50)
	{
	    send_to_char("They shake off your attempt.\n\r",ch);
	    act("You shake off $n's attempt to frenzy you.\n\r",ch,NULL,victim,TO_VICT);
	    act("$N shakes off $n's attempt to frenzy $m.\n\r",ch,NULL,victim,TO_ROOM);
          return;
      }

      if (victim->beast == 0 )
	{
	  send_to_char("They are too calm to frenzy!\n\r",ch);
	  return;
	}

	if (!IS_VAMPAFF(victim, VAM_NIGHTSIGHT)) do_nightsight(victim,"");
	if (!IS_VAMPAFF(victim, VAM_FANGS)) do_fangs(victim,"");
	if (!IS_VAMPAFF(victim, VAM_CLAWS)) do_claws(victim,"");
      act("$n sends you into a frenzied rage!",ch,NULL,victim,TO_VICT);
	act("You excite the beast within $n!",victim,NULL,NULL,TO_CHAR);
	act("$n bares $s fangs and growls as $s inner beast consumes $m.",ch,NULL,NULL,TO_ROOM);
	ch->pcdata->stats[UNI_RAGE] += number_range(10,20);
	if (victim->beast > 0) do_beastlike(victim,"");
	WAIT_STATE(ch,12);
	return;
    }
   
    send_to_char("But they are already in a rage!\n\r",ch);
    return;
*/

    if (IS_CLASS(ch, CLASS_VAMPIRE))
    {
      if (ch->beast >= 20)
      {
	if ( ch->pcdata->stats[UNI_RAGE] >= ch->beast )
	{
	    send_to_char("Your beast is already controlling you.\n\r",ch);
	    return;
	}
      }
      if (ch->beast <= 19)
      {
        if ( ch->pcdata->stats[UNI_RAGE] >= 20 )
        {
            send_to_char("Your beast is already controlling you.\n\r",ch);
            return;
        }
      } 

/*
        if (ch->beast == 0)
	{
	   send_to_char("You are too calm to use frenzy.\n\r",ch);
	   return;
	}

*/

	if (!IS_VAMPAFF(ch, VAM_NIGHTSIGHT)) do_nightsight(ch,"");
	if (!IS_VAMPAFF(ch, VAM_FANGS)) do_fangs(ch,"");
	if (!IS_VAMPAFF(ch, VAM_CLAWS)) do_claws(ch,"");
	send_to_char("You bare your fangs and growl as your inner beast consumes you.\n\r",ch);
	act("$n bares $s fangs and growls as $s inner beast consumes $m.",ch,NULL,NULL,TO_ROOM);
	ch->pcdata->stats[UNI_RAGE] += number_range(20,30);
	if (ch->beast > 0) do_beastlike(ch,"");
	WAIT_STATE(ch,12);
	return;
    }
 
    send_to_char("But you are already in a rage!\n\r",ch);
    return;
}

void do_serenity( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC(ch) )
	return;
    if(!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
        send_to_char("huh?.\n\r",ch);
        return;
    }
    if (ch->pcdata->powers[VAM_ANIM] < 2)
    {
        send_to_char("You must obtain at least level 2 in Animalism to use Song of Serenity.\n\r",ch);
	return;
    }

    if (IS_CLASS(ch, CLASS_VAMPIRE) && ch->beast < 1)
    {
	if ( ch->pcdata->stats[UNI_RAGE] < 1 )
	{
	    send_to_char("Your beast doesn't control your actions.\n\r",ch);
	    return;
	}
        send_to_char("You chant a soft tune and pacify your inner beast.\n\r",ch);
        act("$n chants a soft tune and pacifies their inner beast.",ch,NULL,NULL,TO_ROOM);
	ch->pcdata->stats[UNI_RAGE] = 0;
	if (IS_VAMPAFF(ch, VAM_NIGHTSIGHT)) do_nightsight(ch,"");
	if (IS_VAMPAFF(ch, VAM_FANGS)) do_fangs(ch,"");
	if (IS_VAMPAFF(ch, VAM_CLAWS)) do_claws(ch,"");
	WAIT_STATE(ch,12);
	return;
    }
    else 
    {
     send_to_char("Only those who achieve Golconda can sing the Song of Serenity.\n\r",ch);
     return;
    }
}
/*
void do_sharpen(CHAR_DATA *ch, char *argument)
{
  char arg[MAX_STRING_LENGTH];
  OBJ_DATA *obj;
  argument=one_argument(argument,arg);
  if (IS_NPC(ch)) return;
 
  if (!IS_CLASS(ch,CLASS_VAMPIRE))
  {
     send_to_char("Huh?\n\r",ch);
     return;
  }

  if (ch->pcdata->powers[VAM_MELP] < 3)
  {
     send_to_char("You need Melpominee 3 to sharpen.\n\r",ch);
     return;
  }

  if (arg[0] == '\0')
  {
     send_to_char("What do you wish to sharpen?\n\r",ch);
     return;
  }

  if ( ( obj = get_obj_carry(ch,arg) ) == NULL )
  {
     send_to_char("You dont have that weapon.\n\r",ch);
     return;
  }

  if (IS_SET(obj->quest, QUEST_ARTIFACT) || obj->item_type != ITEM_WEAPON)
  {
     send_to_char("You cant sharpen that item.\n\r",ch);
     return;
  }

  if (obj->value[0] == 18000)
  {
     send_to_char("This item is already Sharp!\n\r",ch);
     return;
  }

  if (obj->value[0] != 0)
  {
     send_to_char(" This weapon already has a power.\n\r",ch);
     return;
  }

  obj->value[0] = 18000;
  obj->value[1] = 20;
  obj->value[2] = 30;


  sprintf(arg, "You grind away at %s until it is razor sharp!",
obj->short_descr);
  send_to_char(arg,ch);
  sprintf(arg, "%s grinds away at %s until it is razor sharp!",
ch->name,obj->short_descr);
  act(arg,ch,NULL,NULL,TO_ROOM);
  return;
}
*/

void do_lamprey( CHAR_DATA *ch, char *argument )
{
CHAR_DATA *victim;
 
char buf[MAX_STRING_LENGTH];
 
int dam;
int bloodpool;

    if (ch->pcdata->stats[UNI_GEN] <= 0)
        ch->pcdata->stats[UNI_GEN] = 4;

    {
    if (IS_SET(ch->newbits, NEW_TIDE))
    bloodpool = (3000 / ch->pcdata->stats[UNI_GEN]);
    else bloodpool = (2000 / ch->pcdata->stats[UNI_GEN]);
    } 
if (IS_NPC(ch)) return;
if (!IS_CLASS(ch,CLASS_VAMPIRE))
{
send_to_char("Huh?\n\r",ch);
return;
}
if (ch->pcdata->powers[VAM_OBTE] < 5)
{
send_to_char("You need level 5 Obtenebration to Lamprey.\n\r",ch);
    return;
 
send_to_char("You need level 5 Obtenebration to Lamprey.\n\r",ch);
    return;
    }
 
 
if ( ( victim = ch->fighting ) == NULL )
{
send_to_char( "You aren't fighting anyone.\n\r", ch );
      return;
 
}
WAIT_STATE( ch, 5 );
 
 
if (!IS_NPC(victim))
{
dam = ch->pcdata->powers[VAM_OBTE] * 20;
}
else if (IS_NPC(victim))
{
dam = ch->pcdata->powers[VAM_OBTE] * 100;
}
/*
if ( !IS_NPC(victim) && IS_CLASS(victim, CLASS_WEREWOLF) )
{
    if (victim->power[DISC_WERE_BOAR] > 2 ) dam *= 0.5;
}
*/
if (is_safe(ch,victim) == TRUE) return; 
dam += number_range(1,30);
if ( dam <= 0 )
   dam = 1;
 

sprintf(buf,"Your tendrils of darkness hits $N incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_CHAR);
sprintf(buf,"$n's tendrils of darkness hits you incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_VICT);
sprintf(buf,"$n's tendrils of darkness hits $N incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_NOTVICT);
 
 

send_to_char("\n\r",ch);
victim->hit -= dam;
ch->pcdata->condition[COND_THIRST] += number_range(40,50);
if (ch->pcdata->condition[COND_THIRST]>bloodpool)
{
send_to_char("Your bloodlust is sated.\n\r",ch);
ch->pcdata->condition[COND_THIRST] = bloodpool;
}
return;
}
 
 
 void do_shroud( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC(ch) )
	return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
     {
	  send_to_char("Huh?\n\r",ch);
	  return;
     }

	if (ch->pcdata->powers[VAM_OBTE] <1)
	{
	stc("You need level 1 Obtenebration to use this power.\n\r",ch);
          return; 
	}

    if ( IS_SET(ch->act, PLR_WIZINVIS) )
    {
	REMOVE_BIT(ch->act, PLR_WIZINVIS);
	send_to_char( "You step out from the shadows.\n\r", ch );
	act("$n emerges from the shadows.",ch,NULL,NULL,TO_ROOM);
    }
    else
    {
	send_to_char( "You slowly blend with the shadows.\n\r", ch );
	act("$n blends in with the shadows and disappears.",ch,NULL,NULL,TO_ROOM);
	SET_BIT(ch->act, PLR_WIZINVIS);
    }
    return;
}

void do_shadowstep( CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];

    if ( IS_NPC(ch) )
	return;

    argument = one_argument (argument, arg);

    if (!IS_CLASS(ch, CLASS_VAMPIRE))
	{
         send_to_char("Huh?\n\r",ch);
	   return;
	}

    if (ch->pcdata->powers[VAM_OBTE] < 4)
	{
           send_to_char("You must obtain at least level 4 in Obtenebration to use this power.\n\r",ch);
	   return;
	}


    if ( arg[0] == '\0' )
    {
	send_to_char( "Shadowstep to who?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
    if ( !IS_NPC(victim) && !IS_IMMUNE(victim, IMM_SUMMON)) 
    {
    send_to_char("He doesnt want you near him!\n\r",ch);
    return;
    }

    if (ch == victim)
    {
        send_to_char("But you're already at yourself!\n\r",ch);
	  return;
    }

    if (IS_NPC(victim) && (!room_is_dark(victim->in_room)))
    {
	send_to_char("You can't find a shadow in his room.\n\r",ch);
	return;
    }

    if (victim->in_room == ch->in_room)
    {
	send_to_char("But you're already there!\n\r",ch);
        return;
    }

    char_from_room(ch);
    char_to_room(ch,victim->in_room);
    act("You step into the shadows and appear before $N.", ch, NULL, victim, TO_CHAR);
    act("$n appears out of the shadows before $N.", ch, NULL, victim, TO_NOTVICT);
    act("$n appears from the shadows in front of you.", ch, NULL, victim, TO_VICT);
    do_look(ch,"auto");
    return;
}


void do_cauldron( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];
    int value;
    int dam;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    value = is_number( arg2 ) ? atoi( arg2 ) : -1;

    if ( IS_NPC(ch) )
	return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
     {
	  send_to_char("Huh?\n\r",ch);
	  return;
     }

    if (ch->pcdata->powers[VAM_THAU] < 2)
     {
	send_to_char("You need at least level 2 Thaumaturgy to use this power.\n\r",ch);
	return;
     }


    if ( arg1[0] == '\0' )
    {
	send_to_char( "Whose blood do you wish to boil?\n\r", ch );
	return;
    }
     if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if (arg2[0] == '\0' )
    {
	send_to_char( "How much blood do you want to use?\n\r", ch );
	return;
    }

    if (value > 200)
    {
	stc("You can only use 200 blood on this power.\n\r",ch);
	return;
    }


    if (ch->pcdata->condition[COND_THIRST] < value )
	{
	   send_to_char("You don't have that much blood!\n\r",ch);
	   return;
	}

if (is_safe(ch,victim) == TRUE) return;

    if (IS_NPC(victim))
	{
	dam = (value * 4);
        victim->hit = (victim->hit - dam);
        ch->pcdata->condition[COND_THIRST] =
ch->pcdata->condition[COND_THIRST] - value;
        act("$N screams in agony as $m blood begins to boil.", ch, NULL,
victim, TO_CHAR);
        act("$N screams in agony as $n causes his blood to boil.", ch,
NULL, victim, TO_NOTVICT);
        act("You scream in agony as $n causes your blood to boil.", ch,
NULL, victim, TO_VICT);
        WAIT_STATE(ch,12);
	  return;
      }

    if (!IS_NPC(victim))
	{
	  dam = value * 1.5;
        victim->hit = (victim->hit - dam);
	if (victim->pcdata->condition[COND_THIRST] < value)
	victim->pcdata->condition[COND_THIRST] = 1;
        victim->pcdata->condition[COND_THIRST] =
victim->pcdata->condition[COND_THIRST] - value;
	ch->pcdata->condition[COND_THIRST] =
ch->pcdata->condition[COND_THIRST] - value;
        act("$N screams in agony as $m blood begins to boil.", ch, NULL,
victim, TO_CHAR);
        act("$N screams in agony as $n causes his blood to boil.", ch,
NULL, victim, TO_NOTVICT);
        act("You scream in agony as $n causes your blood to boil.", ch,
NULL, victim, TO_VICT);
        WAIT_STATE(ch,12);
	  return;
      }


}


void do_taste( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      buf [MAX_STRING_LENGTH];
    char      age [MAX_STRING_LENGTH];
    char      lin [MAX_STRING_LENGTH];
    char     lord [MAX_STRING_LENGTH];
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument (argument, arg );

    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
 
    if (ch->pcdata->powers[VAM_THAU] < 1)
    {
        send_to_char("You must obtain at least level 1 in Thaumaturgy to use Taste of Blood.\n\r",ch);
	return;
    }
 
       if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if (!IS_CLASS(victim, CLASS_VAMPIRE))
    {
        send_to_char( "Only useful on vampire targets.\n\r",ch);
        return;
    }

    if (IS_NPC(victim))
    {
        send_to_char( "Only useful on vampire targets.\n\r",ch);
        return;
    }                               

sprintf(buf,"You examine $N's blood carefully.\n\r");
act(buf,ch,NULL,victim,TO_CHAR);
sprintf(buf,"$n examines your blood carefully.\n\r");
act(buf,ch,NULL,victim,TO_VICT);
sprintf(buf,"$n examines $N's blood carefully.\n\r");
act(buf,ch,NULL,victim,TO_NOTVICT);
 

send_to_char("\n\r",ch);
send_to_char("\n\r",victim);


if (victim->pcdata->rank == AGE_ANCILLA)         sprintf( age, "Ancilla");
else if (victim->pcdata->rank == AGE_CHILDE)     sprintf( age, "Childe");
else if (victim->pcdata->rank == AGE_NEONATE)    sprintf( age, "Neonate");
else if (victim->pcdata->rank == AGE_ELDER)      sprintf( age, "Elder");
else if (victim->pcdata->rank == AGE_METHUSELAH) sprintf( age, "Methuselah");
if (victim->lord == NULL) sprintf(lord, "None");
    else sprintf(lord, "%s",victim->lord);
    sprintf( lin,
"---------------------------------------------------------------------------\n\r");
send_to_char( lin,ch);
send_to_char(
"                              Vampire Status\n\r",ch);
send_to_char(lin,ch);
sprintf(buf,
"Generation:%d  Bloodpool:%d  Age:%s  Lord:%s\n\r",
victim->pcdata->stats[UNI_GEN],victim->pcdata->condition[COND_THIRST],
age,lord);
send_to_char(buf,ch);
send_to_char(lin,ch);
send_to_char(
"                              Disciplines\n\r",ch);
send_to_char(lin,ch);
sprintf(buf,
"Animalism:    [%d]             Celerity:   [%d]             Fortitude: [%d]\n\r",
victim->pcdata->powers[VAM_ANIM],
victim->pcdata->powers[VAM_CELE],
victim->pcdata->powers[VAM_FORT]);
send_to_char(buf,ch);
sprintf(buf,
"Obtenebration:[%d]             Presence:   [%d]             Quietus: [%d]\n\r",
victim->pcdata->powers[VAM_OBTE],
victim->pcdata->powers[VAM_PRES],
victim->pcdata->powers[VAM_QUIE]);
send_to_char(buf,ch);
sprintf(buf,
"Thaumaturgy:  [%d]             Auspex:     [%d]             Dominate: [%d]\n\r",
victim->pcdata->powers[VAM_THAU],
victim->pcdata->powers[VAM_AUSP],
victim->pcdata->powers[VAM_DOMI]);
send_to_char(buf,ch);
sprintf(buf,
"Obfuscate:    [%d]             Potence:    [%d]             Protean: [%d]\n\r",
victim->pcdata->powers[VAM_OBFU],
victim->pcdata->powers[VAM_POTE],
victim->pcdata->powers[VAM_PROT]);
send_to_char(buf,ch);
sprintf(buf,
"Serpentis:    [%d]             Vicissitude:[%d]             Daimoinon: [%d]\n\r",
victim->pcdata->powers[VAM_SERP],
victim->pcdata->powers[VAM_VICI],
victim->pcdata->powers[VAM_DAIM]);
send_to_char(buf,ch);
sprintf(buf,
"Chimerstry:   [%d]             Obeah:      [%d]             Melpominee: [%d]\n\r",
victim->pcdata->powers[VAM_CHIM], victim->pcdata->powers[VAM_OBEA],
victim->pcdata->powers[VAM_MELP]);
send_to_char(buf,ch);
sprintf(buf,
"Necromancy:   [%d]                                         Thanatosis: [%d]\n\r",
victim->pcdata->powers[VAM_NECR], victim->pcdata->powers[VAM_THAN] );
stc(buf,ch);
send_to_char(lin,ch);

return;
} 

void do_tide( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
      send_to_char("Huh?\n\r", ch);
      return;
    }
    if (ch->pcdata->powers[VAM_THAU] < 5)
    {
      send_to_char("You require level 5 Thaumaturgy to use Tide of Vitae.\n\r", ch);
      return;
    }

    if (ch->practice < 10)
    {
     send_to_char("You require at least 10 primal to use Tide of Vitae.\n\r",ch);
     return;
    }

    if (IS_SET(ch->newbits, NEW_TIDE))
    {send_to_char("The tide is already with you.\n\r",ch); return;}
    SET_BIT(ch->newbits, NEW_TIDE);
    ch->practice -= 10;
    send_to_char("You feel a tide of vitae rush over you.\n\r",ch);
 
 
}

void do_potency( CHAR_DATA *ch, char *argument )
{

	if (IS_NPC(ch)) return;
        if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
        {
	  send_to_char("Huh?\n\r", ch);
	  return;
        }
     if ( ch->pcdata->stats[UNI_GEN] == 2 )
     {
	send_to_char("you are at your max generation!\n\r", ch);
	return;
}
   if (ch->pcdata->powers[VAM_THAU] < 3)
	{ 
	  send_to_char("You must obtain at least level 3 in Thaumaturgy to use Blood Potency.\n\r", ch);
          return;
        }
        if (IS_EXTRA(ch, EXTRA_POTENCY))
        {
	  send_to_char("Your blood is already potent.\n\r", ch);
          return;
	}
	if (ch->pcdata->condition[COND_THIRST] < 300)
	{
	  send_to_char("You have insufficient blood.\n\r", ch);
	  return;
	}
        if (ch->pcdata->stats[UNI_GEN] == 3)
        {
	  send_to_char("Your blood is as potent as it can get.\n\r", ch);
	  return;
	}	
      
        ch->pcdata->condition[COND_THIRST] = ch->pcdata->condition[COND_THIRST] - 300;
	ch->pcdata->stats[UNI_GEN] = ch->pcdata->stats[UNI_GEN] - 1;
        SET_BIT(ch->extra, EXTRA_POTENCY);
        send_to_char("You feel your blood become more potent.\n\r", ch);
        return;

}

void do_conceal(CHAR_DATA *ch, char *argument)
{
char arg[MAX_STRING_LENGTH];
char buf[MAX_STRING_LENGTH];
OBJ_DATA *obj; 
one_argument(argument,arg);
if (IS_NPC(ch)) return;
if (!IS_CLASS(ch,CLASS_VAMPIRE))
{send_to_char("Huh?\n\r",ch);return;}
if (ch->pcdata->powers[VAM_OBFU] < 5)
{send_to_char("You need obfuscate 5 to conceal items.\n\r",ch);return;}
if (arg[0]== '\0')
{send_to_char("Syntax: Conceal (item).\n\r",ch);return;}
if ((obj=get_obj_carry(ch,arg)) == NULL)
{send_to_char("You dont have that item.\n\r",ch);return;}
if (IS_SET(obj->extra_flags, ITEM_INVIS))
{
sprintf(buf,"%s fades into existance.",obj->short_descr);
send_to_char(buf,ch);act(buf,ch,NULL,NULL,TO_ROOM);
REMOVE_BIT(obj->extra_flags, ITEM_INVIS);
return;
}
if (!IS_SET(obj->extra_flags, ITEM_INVIS))
{
sprintf(buf,"%s fades out of existance.",obj->short_descr);
send_to_char(buf,ch);act(buf,ch,NULL,NULL,TO_ROOM);
SET_BIT(obj->extra_flags, ITEM_INVIS);
return;
}
 
return;
}
/*
void do_tendrils( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg [MAX_INPUT_LENGTH];
    int sn;
    int level;
    int spelltype;
 
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_VAMPIRE)) 
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }
    if (ch->pcdata->powers[VAM_SERP] < 4)
    {
 send_to_char("you need level 4 serpentis to use Arms of the Abyss.\n\r",ch);
 return;
 }
 
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
    if ( ch == victim )
    {
  send_to_char( "You cannot use Arms of the Abyss on yourself.\n\r", ch );
	return;
    }
 
    if ( IS_AFFECTED(victim, AFF_ETHEREAL) )
    {
   send_to_char( "You cannot Arms of Abyss an ethereal person.\n\r", ch );
	return;
    }
 if (is_safe(ch,victim) == TRUE) return;
    if ( ( sn = skill_lookup( "tendrils" ) ) < 0 ) return;
    spelltype = skill_table[sn].target;
    level = ch->spl[spelltype] * 0.25;
    (*skill_table[sn].spell_fun) ( sn, level, ch, victim );
    WAIT_STATE( ch, 12 );
    return;
}

*/

void do_breath( CHAR_DATA *ch, char *argument )
{
    char arg [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *obj_lose;
    OBJ_DATA *obj_next;
    int dam, sn;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if ( ( sn = skill_lookup( "gas breath" ) ) < 0 )
    {
	send_to_char( "Bug...please inform KaVir.\n\r", ch );
	return;
    }

    if (!IS_VAMPIRE(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

  if (ch->pcdata->powers[VAM_SERP] < 4)
    {
 send_to_char("you need level 4 serpentis to use  Breath of the Basilisk.\n\r",ch);
 return;
 }
   if (IS_AFFECTED(ch, AFF_STEELSHIELD)) do_majesty( ch, "");

    if (arg[0] == '\0' && ch->fighting == NULL)
    {
	send_to_char("Who do you wish to use Breath of the Basilisk on?\n\r",ch);
	return;
    }

    if ( ( victim = ch->fighting ) == NULL )
    {
	if ( ( victim = get_char_room( ch, arg ) ) == NULL )
	{
	    send_to_char( "They aren't here.\n\r", ch );
	    return;
	}
    }

    if (is_safe(ch,victim))
    {
	if (!IS_NPC(victim) && ch != victim && IS_MORE(victim,
MORE_GUARDIAN))
	{
	    guardian_message( victim );
	    act("$n just failed to use Breath of the Basilisk on you.",ch,NULL,victim,TO_VICT);
	}
	return;
    }

    dam = number_range(500,1000) * (ch->pcdata->powers[VAM_SERP] *
ch->pcdata->powers[VAM_SERP]);

    if ( !IS_AWAKE(victim) )
	dam *= 2;

    damage( ch, victim, dam, sn + TYPE_ADD_AGG );

    WAIT_STATE( ch, 6 );

    if ( number_percent( ) < (ch->pcdata->powers[VAM_SERP]  << 2) )
    {
	for (obj_lose = victim->carrying; obj_lose != NULL; obj_lose =
obj_next)
	{
	    obj_next = obj_lose->next_content;
	if ( IS_SET( obj_lose->quest, QUEST_RELIC )
	    ||	 IS_SET(obj_lose->quest, QUEST_ARTIFACT ) )
		continue;
	    if ( obj_lose->points > 0 )
		continue;
	    if ( IS_SET( obj_lose->quest, QUEST_SPELLPROOF ) )
	        continue;
	    if (obj_lose->item_type == ITEM_PAGE ||
		 obj_lose->item_type == ITEM_BOOK )
		continue;
            if ( obj_lose->wear_loc == WEAR_NONE )
		continue;

	    if ( number_bits( 2 ) != 0 )
		continue;

	    switch ( obj_lose->item_type )
	    {
	    case ITEM_ARMOR:
		if ( obj_lose->condition > 0 )
		{
		    act( "$p is pitted and etched!",
			victim, obj_lose, NULL, TO_CHAR );
		    obj_lose->condition -= 25;
		    if ( obj_lose->condition < 1 )
			extract_obj( obj_lose );
		}
		break;

	    case ITEM_SCROLL:
	    case ITEM_WAND:
	    case ITEM_STAFF:
	    case ITEM_TRASH:
	    case ITEM_POTION:
	    case ITEM_FURNITURE:
	    case ITEM_FOOD:
	    case ITEM_BOAT:
	    case ITEM_PILL:
	    case ITEM_CORPSE_NPC:
	    case ITEM_DRINK_CON:
	    case ITEM_CONTAINER:
		act( "$p fumes and dissolves!",
		    victim, obj_lose, NULL, TO_CHAR );
		extract_obj( obj_lose );
		break;
	    }
	}
    }
    return;
}
void do_tongue( CHAR_DATA *ch, char *argument )
{
CHAR_DATA *victim;
 
char buf[MAX_STRING_LENGTH];
 
int dam;
if (IS_NPC(ch)) return;
if (!IS_CLASS(ch,CLASS_VAMPIRE))
{
send_to_char("Huh?\n\r",ch);
return;
}
if (ch->pcdata->powers[VAM_SERP] < 5)
{
send_to_char("You need level 5 Serpentis to tongue.\n\r",ch);
    return;
 
send_to_char("You need level 5 Serpentis to tongue.\n\r",ch);
    return;
    }
 
 
if ( ( victim = ch->fighting ) == NULL )
{
send_to_char( "You aren't fighting anyone.\n\r", ch );
      return;
 
}
WAIT_STATE( ch, 5 );
 
if (!IS_NPC(victim))
{
dam = ch->pcdata->powers[VAM_SERP] * 25;
}
else if (IS_NPC(victim))
{
dam = ch->pcdata->powers[VAM_SERP] * 125;
}
/*
if ( !IS_NPC(victim) && IS_CLASS(victim, CLASS_WEREWOLF) )
{
    if (victim->power[DISC_WERE_BOAR] > 2 ) dam *= 0.5;
}
*/
 if (is_safe(ch,victim)== TRUE) return;
dam += number_range(1,30);
if ( dam <= 0 )
   dam = 1;
sprintf(buf,"Your tongue of the serpent hits $N incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_CHAR);
sprintf(buf,"$n's tongue of the serpent hits you incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_VICT);
sprintf(buf,"$n's tongue of the serpent hits $N incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_NOTVICT);
 

send_to_char("\n\r",ch);
victim->hit -= dam;
return;
}
 
 
 void do_poison( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA  *obj;
    char       arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (ch->pcdata->powers[VAM_SERP] < 3)
    {
        send_to_char("You must obtain at least level 3 in Serpentis to use Poison.\n\r",ch);
	return;
    }

    if ( ( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL )
    &&   ( ( obj = get_eq_char( ch, WEAR_HOLD ) ) == NULL ) )
    {
	send_to_char( "You must wield the weapon you wish to poison.\n\r",
ch );
	return;
    }

    if ( obj->value[0] != 0 )
    {
	send_to_char( "This weapon cannot be poisoned.\n\r", ch );
	return;
    }

    if ( ch->pcdata->condition[COND_THIRST] < 15 )
    {
	send_to_char("You have insufficient blood.\n\r",ch);
	return;
    }
    ch->pcdata->condition[COND_THIRST] -= number_range(5,15);
    act("You run your tongue along $p, poisoning it.",ch,obj,NULL,TO_CHAR);
    act("$n runs $s tongue along $p, poisoning it.",ch,obj,NULL,TO_ROOM);
    obj->value[0] = 53;
    obj->timer = number_range(10,20);

    return;
}

void do_objmask( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    char      buf [MAX_STRING_LENGTH];
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if ( !IS_CLASS(ch, CLASS_VAMPIRE) )
    {
      stc("Huh?\n\r",ch);
      return;
    }

    if ( ch->pcdata->powers[VAM_CHIM] < 5 )
    {
      stc("You must obtain level 5 Chimerstry to Mask an Object.\n\r",ch);
      return;
    }
   
        if (IS_VAMPAFF(ch,VAM_CHANGED) )
	{
            send_to_char( "You can't objectmask while changed.\n\r", ch );
            return;
        }
	 if (IS_POLYAFF(ch,POLY_SERPENT))
        {
            send_to_char( "You cannot objectmask from this form.\n\r", ch );
            return;
        }

    if ( IS_SET(ch->flag2, VAMP_OBJMASK ) )
    {
      stc("You return to your normal form.\n\r",ch);
      sprintf(buf, "%s transforms back into %s.\n\r",ch->morph, ch->name
);
      act(buf,ch,NULL,NULL,TO_ROOM);
      ch->morph = str_dup("");
      ch->objdesc = str_dup("");
      ch->long_descr = str_dup("");
      ch->short_descr = str_dup(ch->name);
      REMOVE_BIT(ch->flag2, VAMP_OBJMASK);
      REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
      return;
    }

    if (has_timer(ch)) return;

    if ( ch->pcdata->condition[COND_THIRST] < 50 )
    {
	send_to_char("You have insufficient blood.\n\r",ch);
	return;
    }
    
    ch->pcdata->condition[COND_THIRST] -= number_range(40, 50);

    if ( arg[0] == '\0' )
    {
      stc("What object do you wish to mask yourself as?\n\r",ch);
      return;
    }

    if ( ( obj = get_obj_here( ch, arg ) ) == NULL )
    {
	send_to_char( "That object is not here.\n\r", ch );
	return;
    }

    SET_BIT(ch->flag2, VAMP_OBJMASK );
    SET_BIT(ch->affected_by, AFF_POLYMORPH);
    act("You mask yourself as $p.",ch,obj,NULL,TO_CHAR);
    act("$n masks $mself as $p.",ch,obj,NULL,TO_ROOM);
    free_string(ch->morph);
    ch->morph = str_dup(obj->short_descr);
    free_string(ch->objdesc);
    ch->objdesc = str_dup(obj->description);
    ch->long_descr = str_dup("");
    return;
}

void do_mirror( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char buf[MAX_INPUT_LENGTH];

    if (IS_NPC(ch)) return;

    if ( !IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
      stc("Huh?\n\r",ch);
      return;
    }

    if ( ch->pcdata->powers[VAM_CHIM] < 1 )
    {
      stc("You must obtain level 1 Chimersty to use Mirror Image.\n\r",ch);
      return;
    }

    if ( ch->pcdata->condition[COND_THIRST] < 20 )
    {
      stc("You do not have enough blood to create a Mirror Image of yourself.\n\r",ch);
      return;
    }

    if (ch->pcdata->followers > 4)
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }

    ch->pcdata->followers++;


      victim = create_mobile( get_mob_index( 30000 ) );
      victim->short_descr = str_dup(ch->name);
      sprintf(buf, "%s is hovering here.\n\r",ch->name);
      victim->long_descr = str_dup(buf);
      victim->name = str_dup(ch->name);
      victim->level = 20;
      victim->max_hit = 2000;
      victim->hit = 2000;
      victim->mana = 2000;
      victim->max_mana = 2000;
      victim->max_move = 2000;
      victim->move = 2000;
      SET_BIT(victim->flag2, VAMP_CLONE);
	SET_BIT(victim->act, ACT_NOEXP);
      ch->pcdata->condition[COND_THIRST] -= 20;
	char_to_room( victim, ch->in_room );
	act( "You concentrate your powers and form a mirror image of yourself.", ch, NULL, victim, TO_CHAR );
	act( "$n waves $s hands and a mirror image of $mself appears.",ch, NULL, victim, TO_ROOM );
	return;

}

void do_familiar( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    CHAR_DATA *familiar;
    char arg[MAX_INPUT_LENGTH];

    one_argument( argument, arg );

    return;

    if ( arg[0] == '\0' )
    {
	send_to_char( "What do you wish to make your familiar?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "Become your own familiar?\n\r", ch );
	return;
    }

    if ( !IS_NPC(victim) )
    {
	send_to_char( "Not on players.\n\r", ch );
	return;
    }

    if ( ( familiar = ch->pcdata->familiar ) != NULL ) 
	familiar->wizard = NULL;
    ch->pcdata->familiar = victim;
    victim->wizard = ch;
    send_to_char("Ok.\n\r",ch);

    return;
}

void do_control( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    CHAR_DATA *familiar;
    char arg[MAX_INPUT_LENGTH];

    one_argument( argument, arg );

    if ( !IS_CLASS(ch, CLASS_VAMPIRE) )
    {
//      stc("Huh?\n\r",ch);
do_controlweather(ch,argument);  
    return;
    }

    if ( ch->pcdata->powers[VAM_CHIM] < 4 )
    {
      stc("You must obtain level 4 Chimerstry to use Control the Clone.\n\r",ch);
      return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Which clone do you wish to control?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "Become your own familiar?\n\r", ch );
	return;
    }

    if ( !IS_NPC(victim) )
    {
      stc("Not on players.\n\r",ch);
      return;
    }

    if ( !IS_SET(victim->flag2, VAMP_CLONE) )
    {
      stc("That is not a clone.\n\r",ch);
      return;
    }

    if ( ( familiar = ch->pcdata->familiar ) != NULL ) 
	familiar->wizard = NULL;
    ch->pcdata->familiar = victim;
    victim->wizard = ch;
    act("You take control of $N's mind.",ch,NULL,victim,TO_CHAR);
    act("$n takes control of $N's mind.",ch,NULL,victim,TO_ROOM);

    return;
}


void do_formillusion( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char buf[MAX_INPUT_LENGTH];

    if (IS_NPC(ch)) return;

    if ( !IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
      stc("Huh?\n\r",ch);
      return;
    }

    if ( ch->pcdata->powers[VAM_CHIM] < 2 )
    {
      stc("You must obtain level 3 Chimersty to Form an Illusion of yourself.\n\r",ch);
      return;
    }

    if ( ch->pcdata->condition[COND_THIRST] < 30 )
    {
      stc("You do not have enough blood to Form an Illusion of yourself.\n\r",ch);
      return;
    }

    if (ch->pcdata->followers > 4)
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }

    ch->pcdata->followers++;


	victim = create_mobile( get_mob_index( 30000 ) );
      victim->short_descr = str_dup(ch->name);
      sprintf(buf, "%s is hovering here.\n\r",ch->name);
      victim->long_descr = str_dup(buf);
      victim->name = str_dup(ch->name);
      victim->level = 200;
      victim->max_hit  = ch->max_hit;
      victim->hit      = victim->max_hit;
      victim->max_mana = ch->max_mana;
      victim->mana     = victim->max_mana;
      victim->max_move = ch->max_move;
      victim->move     = victim->max_move;
      victim->hitroll  = ch->hitroll;
      victim->damroll  = ch->damroll;
      victim->sex	= ch->sex;
      SET_BIT(victim->flag2, VAMP_CLONE);
	SET_BIT(victim->act, ACT_NOEXP);
	char_to_room( victim, ch->in_room );
      ch->pcdata->condition[COND_THIRST] -= 30;
	act( "You concentrate your powers and form an illusion of yourself.", ch, NULL, victim, TO_CHAR );
	act( "$n waves $s hands and splits in two.", ch, NULL, victim,
TO_ROOM );
	return;

}

void do_clone( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA *obj;
    OBJ_DATA *obj2;
    AFFECT_DATA *paf;
    AFFECT_DATA *paf2;
 
    argument = one_argument( argument, arg1 );
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
    if (ch->pcdata->powers[VAM_CHIM] < 3)
    {
    send_to_char("You need Chimeristry 3 to clone objects.\n\r",ch);
    return;
    }
 
 
    if ( arg1[0] == '\0' )
    {
        send_to_char( "Make a clone of what object?\n\r", ch );
        return;
    }
 
    if ( ( obj = get_obj_carry( ch, arg1 ) ) == NULL )
    {
        send_to_char( "You dont have that item.\n\r", ch );
	return;
    }
 
   if (obj->points > 0
   || IS_SET(obj->quest, QUEST_ARTIFACT)
   || IS_SET(obj->quest, QUEST_RELIC)
   || IS_SET(obj->quest, ITEM_EQUEST)   
|| (obj->chobj) != NULL
||    obj->item_type == ITEM_QUEST 
||    obj->item_type == ITEM_QUESTCARD)    
   

   {

   send_to_char("You cant clone that object.\n\r",ch);
   return;
   }
 
 
    pObjIndex = get_obj_index( obj->pIndexData->vnum);
    obj2 = create_object( pObjIndex, obj->level );
    /* Copy any changed parts of the object. */
    free_string(obj2->name);
    obj2->name=str_dup(obj->name);
    free_string(obj2->short_descr);
    obj2->short_descr=str_dup(obj->short_descr);
    free_string(obj2->description);
    obj2->description=str_dup(obj->description);
 
    if (obj->questmaker != NULL && strlen(obj->questmaker) > 1)
    {
	free_string(obj2->questmaker);
	obj2->questmaker=str_dup(obj->questmaker);
    }
 
    if (obj->chpoweron != NULL)
    {
    	free_string(obj2->chpoweron);
    	obj2->chpoweron=str_dup(obj->chpoweron);
    }
    if (obj->chpoweroff != NULL)
    {
    	free_string(obj2->chpoweroff);
    	obj2->chpoweroff=str_dup(obj->chpoweroff);
    }
    if (obj->chpoweruse != NULL)
    {
    	free_string(obj2->chpoweruse);
    	obj2->chpoweruse=str_dup(obj->chpoweruse);
    }
    if (obj->victpoweron != NULL)
    {
    	free_string(obj2->victpoweron);
    	obj2->victpoweron=str_dup(obj->victpoweron);
    }
    if (obj->victpoweroff != NULL)
    {
    	free_string(obj2->victpoweroff);
    	obj2->victpoweroff=str_dup(obj->victpoweroff);
    }
    if (obj->victpoweruse != NULL)
    {
    	free_string(obj2->victpoweruse);
    	obj2->victpoweruse=str_dup(obj->victpoweruse);
    }
    obj2->item_type 	= obj->item_type;
    obj2->extra_flags 	= obj->extra_flags;
    obj2->wear_flags 	= obj->wear_flags;
    obj2->weight 	= obj->weight;
    obj2->spectype 	= obj->spectype;
    obj2->specpower 	= obj->specpower;
    obj2->condition 	= obj->condition;
    obj2->toughness 	= obj->toughness;
    obj2->resistance 	= obj->resistance;
    obj2->quest 	= obj->quest;
    obj2->points 	= obj->points;
    obj2->cost 		= obj->cost;
    obj2->value[0] 	= obj->value[0];
    obj2->value[1] 	= obj->value[1];
    obj2->value[2] 	= obj->value[2];
    obj2->value[3] 	= obj->value[3];
    /*****************************************/
    obj_to_char(obj2,ch);
 
    if (obj->affected != NULL)
    {
    	for ( paf = obj->affected; paf != NULL; paf = paf->next )
    	{
	    if (affect_free == NULL)
	        paf2 = alloc_perm( sizeof(*paf) );
	    else
	    {
		paf2 = affect_free;
		affect_free = affect_free->next;
	    }
	    paf2->type  	= 0;
	    paf2->duration	= paf->duration;
	    paf2->location	= paf->location;
	    paf2->modifier	= paf->modifier;
	    paf2->bitvector	= 0;
	    paf2->next  	= obj2->affected;
	    obj2->affected	= paf2;
    	}
    }
    obj2->timer = ch->pcdata->powers[VAM_CHIM] * 2;
SET_BIT(obj2->quest, QUEST_CLONED);    
act( "A clone of $p appears in your hands in a flash of light.", ch, obj,
NULL, TO_CHAR );
    act( "A clone of $p appears in $n's hands in a flash of light.", ch,
obj, NULL, TO_ROOM );
 if (obj->questmaker != NULL) free_string(obj->questmaker);
    obj->questmaker = str_dup(ch->name);	
   WAIT_STATE(ch, 16);
    return;
}

void do_bloodwater( CHAR_DATA *ch, char *argument )
{
CHAR_DATA *victim;
char arg1 [MAX_INPUT_LENGTH];
int dam;
 
argument = one_argument( argument, arg1 );
 
 
if ( IS_NPC(ch) )
    return;
 
 
if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
     {
          send_to_char("Huh?\n\r",ch);
      return;
 }
 
if (ch->pcdata->powers[VAM_NECR] < 1)
 {
send_to_char(
"You need at least level 1 Necromancy to use Blood Water.\n\r",ch);
    return;
 }
 
 
if ( arg1[0] == '\0' )
{
send_to_char( "Whose blood do you wish to turn to water?\n\r", ch );
   return;
}
 if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
{
    send_to_char( "They aren't here.\n\r", ch );
   return;
}

   if ( victim->hit <= -10 )
{
stc("They are already mortally wounded!\n\r", ch );
return;
}
 
 
if (is_safe(ch,victim) == TRUE) return;
if (IS_NPC(victim)) dam=2000;
if (!IS_NPC(victim)) dam=1000;
if (!IS_CLASS(victim,CLASS_VAMPIRE)) victim->hit -= dam;
    act(
    "$N screams in agony as you turn his blood to water.",
   ch, NULL, victim,TO_CHAR);
act("$N screams in agony as $n turns his blood to water.",
 ch, NULL, victim,TO_NOTVICT);
act("You scream in agony as $n turns your blood to water.",
ch, NULL, victim,TO_VICT);
if (!IS_CLASS(victim,CLASS_VAMPIRE))    WAIT_STATE(ch,12);
if (IS_CLASS(victim,CLASS_VAMPIRE))
{
WAIT_STATE(ch,6);
victim->pcdata->condition[COND_THIRST] -= 150;
}
return;
}

void do_mindblast( CHAR_DATA *ch, char *argument )
{
    char arg [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    int dam;
 
    argument = one_argument(argument,arg);
 
    if ( IS_NPC(ch) ) return;
    if (!IS_CLASS(ch,CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
    if (ch->pcdata->powers[VAM_PRES] < 2)
    {
    send_to_char("You require presence 2 to Mindblast.\n\r",ch);
    return;
    }
 
    if (arg[0] == '\0')
    {
    send_to_char("Mindblast Whom?\n\r",ch);
    return;
    }
 
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        send_to_char( "They arent here.\n\r", ch );
	return;
    }
 
    if ( ch == victim )
    {
        send_to_char( "You cannot Mindblast yourself!\n\r", ch );
	return;
    }
    if (IS_SET(victim->in_room->room_flags, ROOM_SAFE))
    {
    send_to_char("You cannot attack them here.\n\r",ch);
    return;
    }
 if (is_safe(ch,victim)== TRUE) return;
    if ( victim->hit < victim->max_hit )
    {
        send_to_char( "They are hurt and alert.\n\r", ch );
	return;
    }
 
 
    act("You close your eyes and concentrate on $N.",ch,NULL,victim,TO_CHAR);
    act("$n closes $s eyes and concentrates on you.",ch,NULL,victim,TO_VICT);
    act("$n closes $s eyes and concentrates on $N.",ch,NULL,victim,TO_NOTVICT);
    WAIT_STATE( ch, 12 );
    if ( number_percent( ) < 50 )
    	dam = number_range(1,4);
    else
    {
    	dam = 0;
        send_to_char("You failed.\n\r",ch);
	return;
    }
 
    dam += char_damroll(ch);
    if (dam == 0) dam = 1;
    if ( !IS_AWAKE(victim) )
	dam *= 2;
 
    if ( dam <= 0 )
	dam = 1;
    victim->hit -= dam;
 
    act("You clutch your head in agony!",victim,NULL,NULL,TO_CHAR);
    act("$n clutches his head in agony!",victim,NULL,NULL,TO_ROOM);
    victim->position = POS_STUNNED;
    if (IS_NPC(victim) && victim->hit < 0) 
    { 
    raw_kill(victim, ch);
    return;
    }
    if (!IS_NPC(victim) && victim->hit < -2) update_pos(ch);
    return;
}


void do_entrance( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg [MAX_INPUT_LENGTH];
    int sn;
    int level;
    int spelltype;
    char buf[MAX_STRING_LENGTH];
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch)) 
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }
    if (ch->pcdata->powers[VAM_PRES] < 3)
    {
 send_to_char("You need presence 3 to entrance.\n\r",ch);
 return;
 }
 
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
    if ( ch == victim )
    {
  send_to_char( "You cannot entrance yourself.\n\r", ch );
	return;
    }
 
    if ( IS_AFFECTED(victim, AFF_ETHEREAL) )
    {
   send_to_char( "You cannot entrance an ethereal person.\n\r", ch );
	return;
    }
if (is_safe(ch,victim) == TRUE) return;
sprintf(buf,"A look of concentration crosses your face.");
act(buf,ch,NULL,NULL,TO_CHAR);
sprintf(buf,"A look of concentration crosses over $n's face.\n\r");
act(buf,ch,NULL,victim,TO_ROOM);
 
    if ( ( sn = skill_lookup( "charm" ) ) < 0 ) return;
    spelltype = skill_table[sn].target;
    level = ch->pcdata->powers[VAM_PRES] * 40;
    (*skill_table[sn].spell_fun) ( sn, level, ch, victim );
    WAIT_STATE( ch, 12 );
    return;
}


void do_summoning(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    CHAR_DATA *mount;
    char arg [MAX_INPUT_LENGTH];

    argument = one_argument (argument,arg);

    if (arg[0] == '\0')
    {
	send_to_char("Summon whom?\n\r",ch);
	return;
    }  

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }


    if   (victim == ch
    ||   victim->in_room == NULL
    ||   IS_SET(victim->in_room->room_flags, ROOM_SAFE)
    ||   IS_SET(victim->in_room->room_flags, ROOM_PRIVATE)
    ||   IS_SET(victim->in_room->room_flags, ROOM_SOLITARY)
    ||   IS_SET(victim->in_room->room_flags, ROOM_NO_RECALL)
    ||   victim->level >= ch->level + 5
    ||   victim->fighting != NULL
    ||   (!IS_NPC(victim) && !IS_IMMUNE(victim, IMM_SUMMON) ))
    
    {
	send_to_char( "You cannot locate them.\n\r", ch );
	return;
    }

    if (ch->pcdata->powers[VAM_PRES] < 4)
    {
	send_to_char("You need level 4 in Presence to use this.\n\r",ch);
	return;
    }
    WAIT_STATE(ch,10);
    act( "$n disappears suddenly.", victim, NULL, NULL, TO_ROOM );
    char_from_room( victim );
    char_to_room( victim, ch->in_room );
    act( "$n arrives suddenly.", victim, NULL, NULL, TO_ROOM );
    act( "$N has summoned you!", victim, NULL, ch,   TO_CHAR );
    do_look( victim, "auto" );
    if ( (mount = victim->mount) == NULL ) return;
    char_from_room( mount );
    char_to_room( mount, get_room_index(victim->in_room->vnum) );
    do_look( mount, "auto" );
    return;
}

void do_awe    ( CHAR_DATA *ch, char *argument )
{
	if (IS_NPC(ch)) return;
        if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_CLASS(ch, CLASS_WEREWOLF) && !IS_ABOMINATION(ch))
	{
	  send_to_char("Huh?\n\r", ch);
          return;
        }
        if ((IS_VAMPIRE(ch) || IS_ABOMINATION(ch)) && ch->pcdata->powers[VAM_PRES] < 1)
	{
	  send_to_char("You must obtain at least level 1 in Presence to you Awe.\n\r", ch);
	  return;
	}
	if (IS_WEREWOLF(ch) && ch->gifts[SILVERFANGS] < 1)
	{
	stc("You need level 1 Silver Fangs to use Mindblock\n\r",ch);
	return;
	}

        if (IS_EXTRA(ch, EXTRA_AWE))
	{
	  REMOVE_BIT(ch->extra, EXTRA_AWE);
	  send_to_char("You are no longer Awe Inspiring.\n\r", ch);
	  act("$n is no longer awe inspiring.", ch, NULL, NULL, TO_ROOM);
	  return;
	}
        SET_BIT(ch->extra, EXTRA_AWE);
	send_to_char("You are now Awe Inspiring.\n\r", ch);
	act("$n is now awe inspiring", ch, NULL, NULL, TO_ROOM);
        return;


}

void do_majesty( CHAR_DATA *ch, char *argument )
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

    if (!IS_CLASS(ch, CLASS_VAMPIRE) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }
    if (ch->pcdata->powers[VAM_PRES] < 5  )
    {
        send_to_char("You must obtain at least level 5 in Presence to use Majesty.\n\r",ch);
	return;
    }

if (ch->majesty_timer > 0)
    {
        if (ch->majesty_timer > 1)
            sprintf(buf,"You may not use majesty for another %d seconds.\n\r",ch->majesty_timer);
        else
            sprintf(buf,"You may not use majesty for another 1 second.\n\r");
        send_to_char(buf,ch);
        return;
    }

    if (has_timer(ch)) return;

    if (IS_AFFECTED(ch, AFF_STEELSHIELD))
    {
        REMOVE_BIT(ch->affected_by, AFF_STEELSHIELD);
        act( "You lower your majesty.",  ch, NULL, NULL, TO_CHAR    );
        act( "$n looks less imposing.",  ch, NULL, NULL, TO_NOTVICT );
        return;
    }
    if ( ch->pcdata->condition[COND_THIRST] < 45 )
    {
	send_to_char( "You have insufficient blood.\n\r", ch );
	return;
    }

    ch->pcdata->condition[COND_THIRST] -= number_range(35,45);
    SET_BIT(ch->affected_by, AFF_STEELSHIELD);
    act( "You raise your majesty.",  ch, NULL, NULL, TO_CHAR    );
    act( "$n suddenly looks very imposing.",  ch, NULL, NULL, TO_NOTVICT);
   ch->majesty_timer = 60;
    return;
}

void do_unveil( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    one_argument( argument, arg );

    if ( !IS_CLASS(ch, CLASS_VAMPIRE) && !IS_CLASS(ch, CLASS_MAGE) && !IS_ABOMINATION(ch))
    {
      stc("Huh?\n\r",ch);
      return;
    }

    if (( IS_CLASS(ch, CLASS_VAMPIRE) || IS_ABOMINATION(ch)) && ch->pcdata->powers[VAM_AUSP] < 3 )
    {
      stc("You must obtain level 3 Auspex to use Unveil the Shrouded Mind.\n\r",ch);
      return;
    }

    if ( IS_CLASS(ch, CLASS_MAGE) && ch->spheres[MMIN] < 3 )
    {
       stc("You must obtain level three Mind to use Probe Thoughts.\n\r",ch);
       return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Whose mind do you wish to Unveil?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( victim == ch )
    {
	stc("Why would you want to unveil your own mind?\n\r",ch);
	return;
    }

    if ( victim->level > ch->level )
    {
      stc("Their mind is far too powerful for you to Unveil.\n\r",ch);
      return;
    }

    if ( victim->spl[BLUE_MAGIC] > ch->spl[BLUE_MAGIC] / 2 )
    {
      stc("Their mind is far too powerful for you to Unveil.\n\r",ch);
      return;
    }

    victim->unveil = ch;
    act("You gaze deeply into $N's eyes.\n\rYou have unveiled $S mind.\n\r", ch,NULL,victim,TO_CHAR );
    return;
}

void do_astralwalk( CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];

    if ( IS_NPC(ch) )
	return;

    argument = one_argument (argument, arg);

    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
       send_to_char("Huh?\n\r",ch);
       return;
    }

    if ( ch->pcdata->powers[VAM_AUSP] < 4 )
    {
        send_to_char("You must obtain level 4 Auspex to use Astral Walk.\n\r",ch);
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Astral Walk to who?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
    if ( !IS_NPC(victim) && !IS_IMMUNE(victim, IMM_SUMMON)) 
    {
      send_to_char("You are unable to locate them.\n\r",ch);
      return;
    }


    if (ch == victim)
    {
        send_to_char("But you're already at yourself!\n\r",ch);
	return;
    }

    if (victim->in_room == ch->in_room)
    {
      send_to_char("But you're already there!\n\r",ch);
      return;
    }

    char_from_room(ch);
// REMOVE_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);
  //          REMOVE_BIT(ch->newbits, NEW_DARKNESS);
    char_to_room(ch,victim->in_room);
 REMOVE_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);
            REMOVE_BIT(ch->newbits, NEW_DARKNESS);
    act("You step through a rift in the Astral plane.\n\rYou leap out of the Astral Plane before $N.", ch, NULL, victim, TO_CHAR);
    act("$n leaps out of a rift in the Astral Plane.", ch, NULL, victim, TO_NOTVICT);
    act("$n leaps out of a rift in the Astral Plane.", ch, NULL, victim, TO_VICT);
    //do_look(ch,"auto");
    REMOVE_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);
            REMOVE_BIT(ch->newbits, NEW_DARKNESS);
	do_look(ch,"auto");  
  return;
}

void do_dragonform( CHAR_DATA *ch, char *argument )
{
char arg [MAX_INPUT_LENGTH];
char buf [MAX_STRING_LENGTH];
argument = one_argument( argument, arg );
 
if (IS_NPC(ch)) return;
 
if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
     send_to_char("Huh?\n\r",ch);
        return;
}
if (ch->pcdata->powers[VAM_VICI] < 4)
{
send_to_char("You must obtain at least level 4 in Vicissitude to use Dragonform\n\r",ch);
return;
}
 
 
if (!IS_POLYAFF(ch, POLY_ZULO))
{
send_to_char("You can only Dragonform while in Zuloform.\n\r",ch);
return;
}
 
if (IS_EXTRA(ch, EXTRA_DRAGON))
{
REMOVE_BIT(ch->extra,EXTRA_DRAGON);
act( "You transform back into zuloform.", ch, NULL, NULL, TO_CHAR );
    act( "$n shrinks back into a big black monster.", ch, NULL, NULL,
TO_ROOM );
    ch->max_hit = ch->max_hit - 500;
ch->hit = ch->hit - 500;
 
if (ch->hit < 1) ch->hit = 1;
    ch->damroll = ch->damroll / 1.2;
ch->hitroll = ch->hitroll / 1.2;
    free_string( ch->morph );
    ch->morph = str_dup( "A big black monster" );
return;
}
 
 
if ( ch->pcdata->condition[COND_THIRST] < 400 )
{
    send_to_char("You have insufficient blood.\n\r",ch);
    return;
}
 
if (ch->mounted == IS_RIDING) do_dismount(ch,"");
ch->pcdata->condition[COND_THIRST] -= number_range(200,400);
    act( "You transform into a large dragon.", ch, NULL, NULL, TO_CHAR );
    act( "$n's body grows and distorts into a large dragon.", ch, NULL,
NULL,TO_ROOM);
SET_BIT(ch->extra,EXTRA_DRAGON);
sprintf(buf, "%s A huge rabid dragon", ch->name);
free_string( ch->morph );
ch->morph = str_dup( buf );
ch->max_hit = ch->max_hit + 500;
ch->hit = ch->hit + 500;
ch->damroll = ch->damroll * 1.2;
ch->hitroll = ch->hitroll * 1.2;
return;
}


void do_plasma( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    
     if ( IS_NPC(ch) )
	return;
 
	if (ch->fight_timer >0) {
        send_to_char("Not until your fight timer expires.\n\r", ch );
        return;}

    if (!IS_CLASS(ch, CLASS_VAMPIRE)) 
    {
	send_to_char("Huh?\n\r", ch);
	return;
    }

    if (ch->pcdata->powers[VAM_VICI] < 5)
    {
       send_to_char("You must obtain at least level 5 in Vicissitude to use Plasma Form.\n\r", ch);
       return;
    }
 
save_char_obj(ch);

  if ((obj = create_object(get_obj_index( 30007),60)) == NULL)
    {
        send_to_char( "Error - Please inform Maser.\n\r", ch);
	return;
    }

    if ( IS_EXTRA(ch, EXTRA_PLASMA) )
    {
      ch->pcdata->obj_vnum = 0;
      REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
      REMOVE_BIT(ch->extra, EXTRA_OSWITCH);
      REMOVE_BIT(ch->extra, EXTRA_PLASMA);
      ch->pcdata->chobj = NULL;
      obj->chobj = NULL;
      free_string(ch->morph);
      ch->morph = str_dup("");
      act("$p transforms into $n.",ch,obj,NULL,TO_ROOM);
      act("Your reform your human body.",ch,obj,NULL,TO_CHAR);
      extract_obj( obj );
      return;
                
    }
    
    if ( IS_AFFECTED(ch, AFF_POLYMORPH) )
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
	return;
    }
    act("$n transforms into $p and splashes to the ground.",ch,obj,NULL,TO_ROOM);
    act("You transform into $p and splashes to the ground.",ch,obj,NULL,TO_CHAR);
    ch->pcdata->obj_vnum = ch->pcdata->powers[VPOWER_OBJ_VNUM];
    obj->chobj = ch;
    ch->pcdata->chobj = obj;
    SET_BIT(ch->affected_by, AFF_POLYMORPH);
    SET_BIT(ch->extra, EXTRA_OSWITCH);
    SET_BIT(ch->extra, EXTRA_PLASMA);
    free_string(ch->morph);
    ch->morph = str_dup("a pool of blood");
    obj_to_room(obj,ch->in_room);
    return;
}
 
void do_bloodagony(CHAR_DATA *ch, char *argument)
{
    char arg[MAX_STRING_LENGTH];
    int value;
    int pcost;
    OBJ_DATA *obj; 
    one_argument( argument,arg);


    value = ch->pcdata->powers[VAM_QUIE];
    pcost = ch->pcdata->powers[VAM_QUIE] * 60;
 
    if ( arg[0] == '\0')
    {
    send_to_char("Bloodagony what?\n\r",ch);
    return;
    }
 
    if (IS_NPC(ch)) return;
    if ((obj= get_obj_carry(ch,arg)) == NULL)
    {
    send_to_char("You dont have that weapon.\n\r",ch);
    return;
    }
 
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
         send_to_char("Huh?\n\r",ch);
         return;
    }
    if (ch->pcdata->powers[VAM_QUIE] < 3 )
    {
         send_to_char("You need level 3 Quietus to use bloodagony.\n\r",ch);
         return;
    }
 
    if ( obj->item_type != ITEM_WEAPON
    ||   IS_SET(obj->quest, QUEST_ARTIFACT)
    ||   obj->chobj != NULL 
    ||  IS_SET(obj->quest, QUEST_BLOODA))
    {
        send_to_char("You are unable to bloodagony this weapon.\n\r",ch);
	return;
    }
    ch->pcdata->quest += pcost;
    oset_affect(ch,obj,value,APPLY_DAMROLL,TRUE);
    oset_affect(ch,obj,value,APPLY_HITROLL,TRUE);
    obj->points -= pcost;
    SET_BIT(obj->quest, QUEST_BLOODA);
 
        act( "You cut your wrist and smear your blood on $p.", ch, obj,
NULL, TO_CHAR );
        act( "$n cuts his wrist and smears blood on $p.", ch, obj, NULL,
TO_ROOM );
    return;
}


void do_spit( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;

    char buf[MAX_STRING_LENGTH];
  
  int dam;
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch,CLASS_VAMPIRE) && !IS_ABOMINATION(ch)) 
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
    if (ch->pcdata->powers[VAM_QUIE] < 1)
    {
    send_to_char("You need level 1 Quietus to spit.\n\r",ch);
    return;
    }
 
 
    if ( ( victim = ch->fighting ) == NULL )
    {
send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;

    }
    if (ch->pcdata->condition[COND_THIRST] < 5)
    {
    send_to_char("You dont have enough blood.\n\r",ch); 
    return; 
    }
    WAIT_STATE( ch, 12 );
    if (!IS_NPC(victim))
    {
    dam = ch->pcdata->powers[VAM_QUIE] * 50;
    } 
    else if (IS_NPC(victim))
    {
    dam = ch->pcdata->powers[VAM_QUIE] * 250;
    }
    ch->pcdata->condition[COND_THIRST] -= 5;
    /*if ( !IS_NPC(victim) && IS_CLASS(victim, CLASS_WEREWOLF) )
    {
	if (victim->power[DISC_WERE_BOAR] > 2 ) dam *= 0.5;
    }
 */
    dam += number_range(1,30);
    if ( dam <= 0 )
       dam = 1;
sprintf(buf,"Your spit of acid hits $N incredibly hard! [%d]",dam);
act(buf,ch,NULL,victim,TO_CHAR);
sprintf(buf,"$n's spit of acid hits you incredibly hard! [%d]",dam);
act(buf,ch,NULL,victim,TO_VICT);
sprintf(buf,"$n's spit of acid hits $N incredibly hard! [%d]",dam);
act(buf,ch,NULL,victim,TO_NOTVICT);
 

    send_to_char("\n\r",ch);
    victim->hit -= dam;
    if (victim->hit <= 10) one_hit(ch,victim,20,gsn_headbutt);
    return;
}

void do_assassinate( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
    int dam;
    argument = one_argument( argument, arg );
 
 
    if(!IS_CLASS(ch,CLASS_VAMPIRE))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
    if (ch->pcdata->powers[VAM_QUIE] < 4)
    {
    send_to_char("You need Quietus level 4 to Assassinate.\n\r",ch);
    return;
    }
    
    if (!IS_NPC(ch) && IS_AFFECTED(ch, AFF_STEELSHIELD) )
    {
        send_to_char( "You cannot attack while in majesty.\n\r", ch );
        return;
    } 

    if ( arg[0] == '\0' )
    {
        send_to_char( "Assassinate whom?\n\r", ch );
	return;
    }
 
 
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
    if ( victim == ch )
    {
        send_to_char( "How can you assassinate yourself?\n\r", ch );
	return;
    }
 
	if (!IS_NPC(victim) && !str_cmp(victim->name,
"SirMog")) 
	return;

    if (is_safe(ch,victim) == TRUE) return;
 
    if ( victim->fighting != NULL )
    {
        send_to_char( "You can't assassinate a fighting person.\n\r", ch
);
	return;
    }
 
    if ( victim->hit < victim->max_hit )
    {
	act( "$N is hurt and suspicious ... you can't sneak up.",
	    ch, NULL, victim, TO_CHAR );
	return;
    }
    if (!IS_AFFECTED(ch, AFF_HIDE))
    {
    send_to_char("You must be hidden to assassinate!\n\r",ch);
    return;
    }
WAIT_STATE(ch,15);
    if (number_percent( ) < 5)
    {
    sprintf(buf,"%s has been assassinated by %s.",victim->name,ch->name);
    do_info(ch,buf);
    victim->hit = 1;
    ch->fighting = victim;
    send_to_char("You spin around and throw a headbutt to finish him.\n\r",ch);
    damage(ch,victim,11,gsn_headbutt);
    return;
    }

    if (!IS_NPC(victim)) dam = ch->pcdata->powers[VAM_QUIE] * 200;
    if (IS_NPC(victim)) dam = ch->pcdata->powers[VAM_QUIE] * 400;
dam += number_range(1,20);
sprintf(buf,"Your assassination hits $N incredibly hard! [%d]",dam);
act(buf,ch,NULL,victim,TO_CHAR);
sprintf(buf,"$n's assassination hits you incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_VICT);
sprintf(buf,"$n's assassination hits $N incredibly hard! [%d]\n\r",dam);
act(buf,ch,NULL,victim,TO_NOTVICT);
 
if (dam > victim->hit) dam = victim->hit-1;
victim->hit -= dam;
ch->fighting = victim;
victim->fighting = ch;
if (victim->hit <= 1)
{
victim->hit = 1;
send_to_char("You spin around and throw a headbutt to finish him.\n\r",ch);
ch->fighting=victim;
damage(ch,victim,11,gsn_headbutt);

}

   return;
}

void do_infirmity( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char  arg[MAX_INPUT_LENGTH];
    char  buf[MAX_INPUT_LENGTH];
    int   sn;
    int   level;
    int   spelltype;
    
    argument = one_argument (argument, arg);

    if ( IS_NPC(ch) )
	return;

	
  	if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
        {
  	send_to_char("Huh?\n\r", ch);
        return;
        }
     	if ( IS_CLASS(ch, CLASS_VAMPIRE) && ch->pcdata->powers[VAM_QUIE] < 2 )
        {
        send_to_char("You need level 2 Quietus to use this power.\n\r",ch);
        return; 
        }
       if (arg[0] == '\0')
	{
	   send_to_char("Who do you wish to use Infirmity on?\n\r",ch);
	   return;
	}
  
  	
      if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
if (is_safe(ch,victim) == TRUE) return;  	
    if ( ( sn = skill_lookup( "infirmity" ) ) < 0 ) 
{
sprintf(buf,"Yep, sn is bieng set to %d.",sn);
send_to_char(buf,ch);
return;

}  

    spelltype = skill_table[sn].target;
    level = ch->pcdata->powers[VAM_QUIE];
    (*skill_table[sn].spell_fun) ( sn, level, ch, victim );
    WAIT_STATE( ch, 12 );
    return; 
}


void do_silencedeath( CHAR_DATA *ch, char *argument )
{
    char buf [MAX_INPUT_LENGTH];

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

if (ch->pcdata->powers[VAM_QUIE] < 5 )
    {
	send_to_char("You require level 5 Quietus to use Silence of Death.\n\r",ch);
	return;
    }

    if (ch->in_room == NULL)
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }

    if (IS_SET(ch->newbits, NEW_SILENCE))
    {
	REMOVE_BIT(ch->newbits, NEW_SILENCE);
	REMOVE_BIT(ch->in_room->added_flags, ROOM2_SILENCE);
	send_to_char("You banish the silence from the room!\n\r", ch);
	act("A look of concentration crosses $n's face.", ch, NULL, NULL,
TO_ROOM );
	act("The room is no longer silent.",ch,NULL,NULL,TO_ROOM);
	ch->silence_timer = 60;
	return;
    }

    if (IS_SET(ch->in_room->added_flags, ROOM2_SILENCE))
    {
	send_to_char("The room is already silent.\n\r", ch);
	return;
    }

    if (ch->silence_timer > 0)
    {
	if (ch->silence_timer > 1)
	    sprintf(buf,"You cannot call upon the Silence of Death for another %d seconds.\n\r",ch->silence_timer);
	else
	    sprintf(buf,"You cannot call upon the Silence of Death for another 1 second.\n\r");
	send_to_char(buf,ch);
	return;
    }

    SET_BIT(ch->in_room->added_flags, ROOM2_SILENCE);
    SET_BIT(ch->newbits, NEW_SILENCE);
    ch->silence_timer = 60;
    send_to_char("You call forth the Silence of Death!\n\r", ch);
    act("A look of concentration crosses $n's face.", ch, NULL, NULL, TO_ROOM );
    act("The room suddenly goes completely silent!",ch,NULL,NULL,TO_ROOM);
    return;
}  


void do_far( CHAR_DATA *ch, char *argument )
{
   CHAR_DATA *victim;
   ROOM_INDEX_DATA *chroom;
   ROOM_INDEX_DATA *victimroom;
   char arg1[MAX_STRING_LENGTH];

   argument = one_argument (argument, arg1);

    if ( IS_NPC(ch) )
	return;

	if (arg1[0] == '\0')
	{
	   send_to_char("Who do you wish to use farcommand on?\n\r",ch);
	   return;
	}
/*  
        if (arg2[0] == '\0')
	{
	   send_to_char("What do you wish to do to them?\n\r",ch);
	   return;
	}

	if (arg3[0] == '\0')
	{
	   send_to_char("Possess or command who?\n\r",ch);
	   return;
	}
*/
  	if (!IS_CLASS(ch, CLASS_VAMPIRE))
  	{
  	send_to_char("Huh?\n\r", ch);
  	return;
  	}
  	/*
  	if ( IS_CLASS(ch, CLASS_VAMPIRE))
)
  	{
  	send_to_char("You need level 9 Presence to use this power.\n\r",
ch);
	return;
	}
*/
      if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
     if ( !IS_NPC(victim) )
	{
	   send_to_char("Their mind is too strong!\n\r",ch);
	   return;
	}
    if ( victim->level > 250)
    {
    send_to_char("They are too big!\n\r",ch);
    return;
    } 
  
    chroom = ch->in_room;
    victimroom = victim->in_room;
    char_from_room(ch);
    char_to_room(ch,victimroom);
    ch->pcdata->familiar = victim;
    victim->wizard = ch;
    send_to_char("You possess their body.\n\r",ch);
    WAIT_STATE(ch, 50);
    char_from_room(ch);
    char_to_room(ch,chroom);  	
    
    return;
}

void do_command( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    char buffy[MAX_STRING_LENGTH];
    CHAR_DATA *victim;
    int awe;
    

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_CLASS(ch, CLASS_MAGE) && !IS_ABOMINATION(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    if (( IS_CLASS(ch, CLASS_VAMPIRE) || IS_ABOMINATION(ch)) && ch->pcdata->powers[VAM_DOMI] < 1 )
    {
        send_to_char( "You must obtain at least level 1 in Dominate to use Command.\n\r", ch );
	return;
    }
    
    if ( IS_CLASS(ch, CLASS_MAGE) && ch->spheres[MMIN] < 2 )
    {
      stc("You must obtain level two Mind to use Control Impulses.\n\r",ch);
      return;
    }

    if (ch->spl[RED_MAGIC] < 1)
    {
	send_to_char( "Your mind is too weak.\n\r", ch );
	return;
    }

    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Command whom to do what?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if (is_safe(ch,victim)) return;

    if ( victim == ch )
    {
	send_to_char( "How can you command yourself??\n\r", ch );
	return;
    }

    if (IS_IMMORTAL(victim))
    {
	stc("I dont think so, do you?\n\r", ch);
        return;
    }
  if ( IS_CLASS(ch, CLASS_VAMPIRE) )
  {
    if (ch->pcdata->powers[VAM_DOMI] > 2)
	awe = 50;
    else if (ch->pcdata->powers[VAM_DOMI] > 3)
	awe = 75;
    else if (ch->pcdata->powers[VAM_DOMI] > 4)
	awe = 100;
    else awe = 25;
  }
  else
   awe = ch->spheres[MMIN] * 20;

    if (IS_EXTRA(ch, EXTRA_AWE))
    {
      awe += 75;
    }

    if ( !IS_NPC(victim) && victim->level != 6 )
    {
	send_to_char( "You can only command other avatars.\n\r", ch );
	return;
    }
  
  if ( ch->pcdata->powers[VAM_DOMI] > 1 )
  {
    sprintf( buffy, "%s %s", arg2, argument );
    if (IS_NPC(victim))
    	sprintf( buf, "I think %s wants to %s",victim->short_descr,buffy);
    else if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_POLYMORPH))
    	sprintf( buf, "I think %s wants to %s", victim->morph,buffy);
    else
    	sprintf( buf, "I think %s wants to %s", victim->name,buffy);
    do_say(ch,buf);
  }
  else
  {
    if (IS_NPC(victim))
        sprintf( buf, "I think %s wants to %s", victim->short_descr, arg2 );
    else if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_POLYMORPH))
        sprintf( buf, "I think %s wants to %s", victim->morph, arg2 );
    else
        sprintf( buf, "I think %s wants to %s", victim->name, arg2 );
    do_say(ch,buf); 
  }

    if ( IS_NPC(victim) && victim->level >= awe )
    {
    	act("You shake off $N's suggestion.",victim,NULL,ch,TO_CHAR);
    	act("$n shakes off $N's suggestion.",victim,NULL,ch,TO_NOTVICT);
    	act("$n shakes off your suggestion.",victim,NULL,ch,TO_VICT);
    	act("$s mind is too strong to overcome.",victim,NULL,ch,TO_VICT);
	return;
    }

    else if ( victim->spl[BLUE_MAGIC] >= (ch->spl[RED_MAGIC]/2) )
    {
    	act("You shake off $N's suggestion.",victim,NULL,ch,TO_CHAR);
    	act("$n shakes off $N's suggestion.",victim,NULL,ch,TO_NOTVICT);
    	act("$n shakes off your suggestion.",victim,NULL,ch,TO_VICT);
    	act("$s mind is too strong to overcome.",victim,NULL,ch,TO_VICT);
	return;
    }

 if (!str_cmp("quit",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }

	if (!str_cmp("give",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("dro",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("drop",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("gif",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("giv",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("gi",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("gift",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("c",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("ca",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("cas",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("cast",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("k",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("ki",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("kil",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }
	if (!str_cmp("kill",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }


 if (!str_cmp("tok",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }

 if (!str_cmp("token",arg2)) {
                send_to_char(" You Failed.\n\r", ch );
                return;
        }

    act("You blink in confusion.",victim,NULL,NULL,TO_CHAR);
    act("$n blinks in confusion.",victim,NULL,NULL,TO_ROOM);
    strcpy(buf,"Yes, you're right, I do...");
    do_say(victim,buf);
    if ( ch->pcdata->powers[VAM_DOMI] > 1 )
      interpret( victim, buffy );
    else interpret( victim, arg2 );
    return;
  
}


void do_mesmerise( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    char buffy[MAX_STRING_LENGTH];
    CHAR_DATA *victim;
    int awe;
    

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

    if (ch->pcdata->powers[VAM_DOMI] < 2)
    {
        send_to_char( "You must obtain at least level 2 in Dominate to use mesmerise.\n\r", ch );
	return;
    }

    if (ch->spl[RED_MAGIC] < 1)
    {
	send_to_char( "Your mind is too weak.\n\r", ch );
	return;
    }

    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Command whom to do what?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if (is_safe(ch, victim)) return;
    if (IS_IMMORTAL(victim))
    {
        stc("I dont think so, do you?\n\r", ch);
        return;
    }
    if ( victim == ch )
    {
	send_to_char( "How can you command yourself??\n\r", ch );
	return;
    }

  {
    if (ch->pcdata->powers[VAM_DOMI] > 2)
	awe = 50;
    else if (ch->pcdata->powers[VAM_DOMI] > 3)
	awe = 75;
    else if (ch->pcdata->powers[VAM_DOMI] > 4)
	awe = 100;
    else awe = 25;
  }

    if (IS_EXTRA(ch, EXTRA_AWE))
    {
      awe += 75;
    }

    if ( !IS_NPC(victim) && victim->level != 6 )
    {
	send_to_char( "You can only command other avatars.\n\r", ch );
	return;
    }

  if ( ch->pcdata->powers[VAM_DOMI] > 1 )
  {
    sprintf( buffy, "%s %s", arg2, argument );
    if (IS_NPC(victim))
    	sprintf( buf, "I think %s wants to %s",victim->short_descr,buffy);
    else if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_POLYMORPH))
    	sprintf( buf, "I think %s wants to %s", victim->morph,buffy);
    else
    	sprintf( buf, "I think %s wants to %s", victim->name,buffy);
    do_say(ch,buf);
  }
  else
  {
    if (IS_NPC(victim))
        sprintf( buf, "I think %s wants to %s", victim->short_descr, arg2
);
    else if (!IS_NPC(victim) && IS_AFFECTED(victim, AFF_POLYMORPH))
        sprintf( buf, "I think %s wants to %s", victim->morph, arg2 );
    else
        sprintf( buf, "I think %s wants to %s", victim->name, arg2 );
    do_say(ch,buf); 
  }

    if ( IS_NPC(victim) && victim->level >= awe )
    {
    	act("You shake off $N's suggestion.",victim,NULL,ch,TO_CHAR);
    	act("$n shakes off $N's suggestion.",victim,NULL,ch,TO_NOTVICT);
    	act("$n shakes off your suggestion.",victim,NULL,ch,TO_VICT);
    	act("$s mind is too strong to overcome.",victim,NULL,ch,TO_VICT);
	return;
    }

    else if ( victim->spl[BLUE_MAGIC] >= (ch->spl[RED_MAGIC]/2) )
    {
    	act("You shake off $N's suggestion.",victim,NULL,ch,TO_CHAR);
    	act("$n shakes off $N's suggestion.",victim,NULL,ch,TO_NOTVICT);
    	act("$n shakes off your suggestion.",victim,NULL,ch,TO_VICT);
    	act("$s mind is too strong to overcome.",victim,NULL,ch,TO_VICT);
	return;
    }

    act("You blink in confusion.",victim,NULL,NULL,TO_CHAR);
    act("$n blinks in confusion.",victim,NULL,NULL,TO_ROOM);
    strcpy(buf,"Yes, you're right, I do...");
    do_say(victim,buf);
    if ( ch->pcdata->powers[VAM_DOMI] > 1 )
      interpret( victim, buffy );
    else interpret( victim, arg2 );
    return;
  
}


void do_acid( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
      send_to_char("Huh?\n\r", ch);
      return;
    }
    if (ch->pcdata->powers[VAM_DOMI] < 4)
    {
      send_to_char("You require level 4 dominate to use Acid Blood.\n\r", ch);
      return;
    }
    if (ch->pcdata->condition[COND_THIRST] < 500)
    {
     send_to_char("You have insufficient blood.\n\r", ch);
     return;
    }
    if (IS_SET(ch->act, PLR_ACID))
    {
     send_to_char("Your blood is already acid.\n\r",ch);
     return;
    }
    SET_BIT(ch->act, PLR_ACID);
    send_to_char("Your blood turns to a potent acid.\n\r", ch);
    return;
}

void do_possession( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    CHAR_DATA *familiar;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    one_argument( argument, arg );

    if ( IS_NPC(ch) )
	return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_CLASS(ch, CLASS_MAGE) && !IS_ABOMINATION(ch) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (( IS_CLASS(ch, CLASS_VAMPIRE) || IS_ABOMINATION(ch)) && ch->pcdata->powers[VAM_DOMI] < 3)
    {
        send_to_char("You must obtain at least level 3 in Dominate to use Possession.\n\r",ch);
	return;
    }
 
    if ( IS_CLASS(ch, CLASS_MAGE) && ch->spheres[MMIN] < 4 )
    {
      stc("You must obtain level four Mind to use Possession.\n\r",ch);
      return;
    }

    if ( ( familiar = ch->pcdata->familiar ) != NULL)
    {
	sprintf(buf,"You break your hold over %s.\n\r",familiar->short_descr);
	send_to_char( buf, ch );
	familiar->wizard = NULL;
	ch->pcdata->familiar = NULL;
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "What do you wish to Possess?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "What an intelligent idea!\n\r", ch );
	return;
    }

    if ( !IS_NPC(victim) )
    {
	send_to_char( "Not on players.\n\r", ch );
	return;
    }

    if (victim->wizard != NULL)
    {
	send_to_char( "You are unable to possess them.\n\r", ch );
	return;
    }

    if (victim->level > (ch->spl[RED_MAGIC] * 0.25))
    {
	send_to_char( "They are too powerful.\n\r", ch );
	return;
    }

    if ( IS_CLASS(ch, CLASS_VAMPIRE) && ch->pcdata->condition[COND_THIRST] < 50 )
    {
	send_to_char("You have insufficient blood.\n\r",ch);
	return;
    }

    if ( IS_CLASS(ch, CLASS_VAMPIRE) )
      ch->pcdata->condition[COND_THIRST] -= 50;
    ch->pcdata->familiar = victim;
    victim->wizard = ch;
    act("You concentrate on $N.",ch,NULL,victim,TO_CHAR);
    act("$n is staring at you!",ch,NULL,victim,TO_VICT);
    act("$n starts staring at $N",ch,NULL,victim,TO_NOTVICT);
    return;
}


void do_coil( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
      send_to_char("Huh?\n\r", ch);
      return;
    }
    if (ch->pcdata->powers[VAM_DOMI] < 5)
    {
      send_to_char("You require level 5 Dominate to use Body Coil.\n\r",
ch);
      return;
    }
    if (!IS_SET(ch->newbits, NEW_COIL))
    {
     send_to_char("You prepare to coil your victims.\n\r", ch);
     SET_BIT(ch->newbits, NEW_COIL);
     return;
    }
    else if (IS_SET(ch->newbits, NEW_COIL))
    {
     send_to_char("You stand down from your coil posture.\n\r", ch);
     REMOVE_BIT(ch->newbits, NEW_COIL);
     return;
    }
 return;
}

void do_earthmeld( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *mount;

    one_argument( argument, arg );
    
    if ( IS_NPC(ch) )
	return;

	if (ch->fight_timer >0) {
        send_to_char("Not until your fight timer expires.\n\r", ch );
        return;}

    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if ( ch->pcdata->powers[VAM_PROT] < 4 )
    {
        send_to_char("You must obtain at least level 4 Protean to use Earthmeld.\n\r",ch);
	return;
    }
    

    if ( IS_AFFECTED(ch, AFF_POLYMORPH) )
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
	return;
    }

	if (has_timer(ch)) return;

    if ( IS_NPC(ch) || IS_EXTRA(ch,EXTRA_EARTHMELD) )
    {
            REMOVE_BIT(ch->affected_by, AFF_SHIFT);
            REMOVE_BIT(ch->extra, EXTRA_EARTHMELD);
            REMOVE_BIT(ch->act, PLR_WIZINVIS);
           if (IS_HEAD(ch,LOST_HEAD)) REMOVE_BIT(ch->loc_hp[0],LOST_HEAD);
            free_string(ch->morph);
            ch->morph = str_dup("");
            ch->level = 3;
            ch->trust = 3; 
           send_to_char( "You rise up from the ground.\n\r", ch );
            sprintf(buf, "%s rises up from the ground",ch->name);
            act(buf,ch,NULL,NULL,TO_ROOM);

            return;

    }

    if ( (mount = ch->mount) != NULL) do_dismount(ch,"");
    SET_BIT(ch->affected_by, AFF_SHIFT);
    SET_BIT(ch->extra, EXTRA_EARTHMELD);
    SET_BIT(ch->act, PLR_WIZINVIS);
    free_string(ch->morph);
    ch->morph = str_dup("Someone");
    ch->level = 4;
    ch->trust = 4;
    send_to_char( "You sink into the ground.\n\r", ch );
    sprintf(buf, "%s sinks into the ground.",ch->name);
    act(buf,ch,NULL,NULL,TO_ROOM);
    return;
}

void do_flamehands( CHAR_DATA *ch, char *argument)
{
    if ( IS_NPC(ch) )
     return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
	  send_to_char("Huh?\n\r",ch);
	  return;
    }

    if (ch->pcdata->powers[VAM_PROT] < 5)
    {
	  send_to_char("You need level 5 Protean to use flaming hands.\n\r",ch);
	  return;
    }

    if (IS_SET(ch->newbits, NEW_MONKFLAME))
    {
	  REMOVE_BIT(ch->newbits, NEW_MONKFLAME);
        send_to_char("Your hands are no longer engulfed by flames.\n\r",ch);
	  act("$n's hands are no longer engulfed by flames.\n\r",ch,NULL,NULL,TO_ROOM);
	  return;
    }
    if (!IS_SET(ch->newbits, NEW_MONKFLAME))
    {
	  SET_BIT(ch->newbits, NEW_MONKFLAME);
	  send_to_char("Your hands are engulfed by flames!\n\r",ch);
	  act("$n's hands are engulfed byflames!\n\r",ch,NULL,NULL,TO_ROOM);
	  return;
    }
}


void do_drain( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg [MAX_INPUT_LENGTH];
    int dam;

    argument = one_argument( argument, arg );

    if ( IS_NPC(ch) )
	return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE))
     {
	  send_to_char("Huh?\n\r",ch);
	  return;
     }

    if (ch->pcdata->powers[VAM_THAN] < 5 )
     {
	send_to_char("You must obtain level 5 Thanatosis to use Drain Life.\n\r",ch);
	return;
     }
     
  
   if ( ( victim = get_char_room( ch, arg ) ) == NULL && (ch->fighting) ==
NULL)
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
   if ((ch->fighting) != NULL)
   {
   victim = ch->fighting;
   }
    
   if ( arg[0] == '\0' && (ch->fighting) == NULL)
    {
	send_to_char( "Whose life do you wish to drain?\n\r", ch );
	return;
    }

    if (victim->hit < 500)
	{
	   send_to_char("They are far to hurt to do that!\n\r",ch);
	   return;
	}

	 if (is_safe(ch, victim))
	 {
       send_to_char("Not while in a safe room!\n\r", ch);
       return;
    }

    if (IS_NPC(victim))
	{
	  dam = ch->pcdata->powers[VAM_THAN] * 10;
        victim->hit = (victim->hit - dam);
        if (dam > 500) dam = number_range( 450, 550 );
        ch->hit = (ch->hit + dam);
	if (ch->hit > ch->max_hit + 1000)
	ch->hit = ch->max_hit + 1000;
        act("You drain the lifeforce out of $N.", ch, NULL, victim,
TO_CHAR);
        act("$n drains the lifeforce out of $N.", ch, NULL, victim,
TO_NOTVICT);
        act("You feel $n draining your lifeforce.", ch, NULL, victim,
TO_VICT);
        WAIT_STATE(ch,12);
	  return;
      }

    if (!IS_NPC(victim))
	{
	  dam = ch->pcdata->powers[VAM_THAN] * 50;
        victim->hit = (victim->hit - dam);
        if (dam > 400) dam = number_range( 350, 450 );
        ch->hit = (ch->hit + dam);
        if (ch->hit > ch->max_hit + 1000)
        ch->hit = ch->max_hit + 1000;      
        act("You drain the lifeforce out of $N.", ch, NULL, victim,
TO_CHAR);
        act("$n drains the lifeforce out of $N.", ch, NULL, victim,
TO_NOTVICT);
        act("You feel $n draining your lifeforce.", ch, NULL, victim,
TO_VICT);
        WAIT_STATE(ch,12);
	  return;
      }


}

void do_ashes( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    
     if ( IS_NPC(ch) )
	return;
 
	if (ch->fight_timer >0) {
        send_to_char("Not until your fight timer expires.\n\r", ch );
        return;}

    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch)) 
    {
	send_to_char("Huh?\n\r", ch);
	return;
    }

    if (ch->pcdata->powers[VAM_THAN] < 3)
    {
       send_to_char("You must obtain at least level 5 in Vicissitude to use Plasma Form.\n\r", ch);
       return;
    }
 
save_char_obj(ch);

  if ((obj = create_object(get_obj_index( 30042),60)) == NULL)
    {
        send_to_char( "Error - Please inform SaGe.\n\r", ch);
	return;
    }

    if ( IS_EXTRA(ch, EXTRA_ASH) )
    {
      ch->pcdata->obj_vnum = 0;
      REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
      REMOVE_BIT(ch->extra, EXTRA_OSWITCH);
      REMOVE_BIT(ch->extra, EXTRA_ASH);
      ch->pcdata->chobj = NULL;
      obj->chobj = NULL;
      free_string(ch->morph);
      ch->morph = str_dup("");
      act("$p transforms into $n.",ch,obj,NULL,TO_ROOM);
      act("Your reform your human body.",ch,obj,NULL,TO_CHAR);
      extract_obj( obj );
      return;
                
    }
    
    if ( IS_AFFECTED(ch, AFF_POLYMORPH) )
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
	return;
    }
    act("$n transforms into $p and falls to the ground.",ch,obj,NULL,TO_ROOM);
    act("You transform into $p and falls to the ground.",ch,obj,NULL,TO_CHAR);
    ch->pcdata->obj_vnum = ch->pcdata->powers[VPOWER_OBJ_VNUM];
    obj->chobj = ch;
    ch->pcdata->chobj = obj;
    SET_BIT(ch->affected_by, AFF_POLYMORPH);
    SET_BIT(ch->extra, EXTRA_OSWITCH);
    SET_BIT(ch->extra, EXTRA_ASH);
    free_string(ch->morph);
    ch->morph = str_dup("a pile of ashes");
    obj_to_room(obj,ch->in_room);
    return;
}

void do_withering (CHAR_DATA *ch,char *argument)
{
    CHAR_DATA *victim;
    OBJ_DATA *obj;
    char arg [MAX_INPUT_LENGTH];
    char buf [MAX_STRING_LENGTH];

    argument = one_argument (argument, arg);
        
    
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }

    if (ch->pcdata->powers[VAM_THAN] < 4 )
    {
    send_to_char("You must obtain level 4 Thanatosis to use Withering.\n\r",ch);
    return;
    }
    if ( arg[0] == '\0' )
    {
    send_to_char("Who do you wish to wither?\n\r",ch);
    return;
    }
    victim = get_char_room(ch, arg);
    if ( ( victim = get_char_room( ch, arg) ) == NULL )
    {
     send_to_char("They arent here.\n\r",ch);
     return;
    }

   if (IS_SET(victim->in_room->room_flags, ROOM_SAFE))
   {
     send_to_char("You cannot attack them here.\n\r",ch);
     return;
   }

   if (is_safe(ch,victim) == TRUE) 
     return;
 
   WAIT_STATE(ch,35);
    sprintf(buf,"A look of concentration crosses over %s's face.",ch->name);
    act(buf,ch,NULL,NULL,TO_ROOM);
    send_to_char("A look of concentration crosses over your face.\n\r",ch);
    if (IS_ARM_R(victim,LOST_ARM) && IS_ARM_L(victim,LOST_ARM) &&
        IS_LEG_R(victim,LOST_LEG) && IS_LEG_L(victim,LOST_LEG))
        {
        send_to_char("All of their limbs are severed already!\n\r",ch);
        return;
        }
       if (number_percent ( ) < 25 )
       {
        if (!IS_ARM_R(victim,LOST_ARM))
        {
        SET_BIT(victim->loc_hp[3],LOST_ARM);
        if ((obj = get_eq_char( victim, WEAR_HOLD )) != NULL )
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_HANDS )) != NULL)
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_WRIST_R )) != NULL)
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_FINGER_R )) != NULL)
           take_item(victim,obj);
        make_part(victim,"arm");
        sprintf(buf,
        "A supernatural force rips %s's arm off!",victim->name);
        act(buf,ch,NULL,NULL,TO_ROOM);
        send_to_char(buf,ch);
        return;
        }
        if (!IS_ARM_L(victim,LOST_ARM))
        {
        SET_BIT(victim->loc_hp[2],LOST_ARM);
        if ((obj = get_eq_char( victim, WEAR_HOLD )) != NULL )
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_HANDS )) != NULL)
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_WRIST_L )) != NULL)
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_FINGER_L )) != NULL)
           take_item(victim,obj);
        make_part(victim,"arm");
        sprintf(buf,
        "A supernatural force rips %s's arm off!",victim->name);
        act(buf,ch,NULL,NULL,TO_ROOM);
        send_to_char(buf,ch);
        return;
        }
        if (!IS_LEG_R(victim,LOST_LEG))
        {
        SET_BIT(victim->loc_hp[5],LOST_LEG);
        if ((obj = get_eq_char( victim, WEAR_FEET )) != NULL )
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_LEGS )) != NULL)
           take_item(victim,obj);
        make_part(victim,"leg");
        sprintf(buf,
        "A supernatural force rips %s's leg off!",victim->name);
        act(buf,ch,NULL,NULL,TO_ROOM);
        send_to_char(buf,ch);
        return;
        }
        if (!IS_LEG_L(victim,LOST_LEG))
        {
        SET_BIT(victim->loc_hp[4],LOST_LEG);
        if ((obj = get_eq_char( victim, WEAR_FEET )) != NULL )
           take_item(victim,obj);
        if ((obj = get_eq_char( victim, WEAR_LEGS )) != NULL)
           take_item(victim,obj);
        make_part(victim,"leg");
        sprintf(buf,
        "A supernatural force rips %s's leg off!",victim->name);
        act(buf,ch,NULL,NULL,TO_ROOM);
        send_to_char(buf,ch);
        return;
        }
        }
send_to_char("You failed.\n\r",ch);
 
return;
}
 
 void do_putrefaction( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
 
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
 
    if (ch->pcdata->powers[VAM_THAN] < 2)
    {
        send_to_char("You must obtain at level 2 in Thanatosis to use Putrefaction.\n\r",ch);
	return;
    }
 
 
    if ( arg[0] == '\0' )
    {
        send_to_char( "Who do you wish to use Putrefaction on?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if (IS_NPC(victim))
    {
        send_to_char("Why use Putrefaction on a mob?\n\r", ch);
        return;
    }

    if ( IS_IMMORTAL(victim) && victim != ch )
    {
        send_to_char( "You can only use Putrefaction on Avatar's or lower.\n\r", ch );
	return;
    }

    if (is_safe(ch,victim) == TRUE) return;

    if (victim->hit < victim->max_hit)
    {
      send_to_char("They are hurt and suspicious.\n\r", ch);
      return;
    }
    act("You close your eyes and concentrate on $N.",ch,NULL,victim,TO_CHAR);
    act("$n closes $s eyes and concentrates on you.",ch,NULL,victim,TO_VICT);
    act("$n closes $s eyes and cencentrates on $N.",ch,NULL,victim,TO_NOTVICT);
    WAIT_STATE(ch, 12);
    if (number_percent( ) < 50)
    {
        send_to_char("You failed.\n\r",ch);
        return;
    }
 
    act("Your flesh begins to rot!", victim,NULL,NULL,TO_CHAR);
    act("$n's flesh begins to rot!", victim,NULL,NULL,TO_ROOM);
    SET_BIT(victim->flag2, AFF2_ROT);
    return;
}
/*
void do_hagswrinkles( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }
    if (ch->pcdata->powers[VAM_THAN] < 1  )
    {
      send_to_char("You must obtain at least level 1 in Thanatosis to use Hagswrinkles.\n\r",ch);
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Change to look like whom?\n\r", ch );
	return;
    }

    if (IS_AFFECTED(ch,AFF_POLYMORPH) && !IS_VAMPAFF(ch,VAM_DISGUISED))
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
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

    if ( IS_IMMORTAL(victim) && victim != ch )
    {
	send_to_char( "You can only use hagswrinkles on Avatars or lower.\n\r", ch );
	return;
    }

    if ( ch->pcdata->condition[COND_THIRST] < 40 )
    {
	send_to_char("You have insufficient blood.\n\r",ch);
	return;
    }
    ch->pcdata->condition[COND_THIRST] -= number_range(30,40);

    if ( ch == victim )
    {
	if (!IS_AFFECTED(ch,AFF_POLYMORPH) &&
!IS_VAMPAFF(ch,VAM_DISGUISED))
	{
	    send_to_char( "You already look like yourself!\n\r", ch );
	    return;
	}
	sprintf(buf,"Your body wrinkles and reshapes as %s.",ch->name);
	act(buf,ch,NULL,victim,TO_CHAR);
	sprintf(buf,"%s's body wrinkles and reshapes as %s.",ch->morph,ch->name);
	act(buf,ch,NULL,victim,TO_ROOM);
	REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
	REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
    	free_string( ch->morph );
    	ch->morph = str_dup( "" );
	return;
    }
    if (IS_VAMPAFF(ch,VAM_DISGUISED))
    {
    	sprintf(buf,"Your body wrinkles and reshapes as
%s.",victim->name);
    	act(buf,ch,NULL,victim,TO_CHAR);
    	sprintf(buf,"%s's body wrinkles and reshapes as
%s.",ch->morph,victim->name);
    	act(buf,ch,NULL,victim,TO_NOTVICT);
    	sprintf(buf,"%s's body wrinkles and reshapes as you!",ch->morph);
    	act(buf,ch,NULL,victim,TO_VICT);
    	free_string( ch->morph );
    	ch->morph = str_dup( victim->name );
	return;
    }
    sprintf(buf,"Your body wrinkles and reshapes as %s.",victim->name);
    act(buf,ch,NULL,victim,TO_CHAR);
    sprintf(buf,"%s's body wrinkles and reforms as
%s.",ch->name,victim->name);
    act(buf,ch,NULL,victim,TO_NOTVICT);
    sprintf(buf,"%s's body wrinkles and reforms as you!",ch->name);
    act(buf,ch,NULL,victim,TO_VICT);
    SET_BIT(ch->affected_by, AFF_POLYMORPH);
    SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
    free_string( ch->morph );
    ch->morph = str_dup( victim->name );
    return;
}
*/

void do_hagswrinkles( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch) && !IS_WEREWOLF(ch) && !IS_ABOMINATION(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

       if ((IS_VAMPIRE(ch) || IS_ABOMINATION(ch)) && ch->pcdata->powers[VAM_THAN] < 1 )
    {
      send_to_char("You must obtain at least level 1 in Thanatosis to use Hagswrinkles.\n\r",ch);
        return;
    }

if (IS_WEREWOLF(ch) && ch->gifts[WENDIGO] < 1)
{
stc("You need level 1 in Wendigo to use Camouflage.\n\r",ch);
return;
}

    if ( arg[0] == '\0' )
    {
	send_to_char( "Change to look like whom?\n\r", ch );
	return;
    }

    if (IS_AFFECTED(ch,AFF_POLYMORPH) && !IS_VAMPAFF(ch,VAM_DISGUISED))
    {
	send_to_char( "Not while polymorphed.\n\r", ch );
	return;
    }

    if (IS_POLYAFF(ch,POLY_ZULO))
    {
if (IS_WEREWOLF(ch))
    {
        send_to_char("Note while using Gift of the Spriggan.\n\r",ch);
    }
else if (!IS_WEREWOLF(ch))
{
	send_to_char( "Not while in Zulo Form.\n\r", ch );
}
        return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( IS_IMMORTAL(victim) && victim != ch )
    {
	send_to_char( "You cannot disguise yourself as them.\n\r", ch );
	return;
    }
    if ( ch == victim )
    {
	if (!IS_AFFECTED(ch,AFF_POLYMORPH) &&
!IS_VAMPAFF(ch,VAM_DISGUISED))
	{
	    send_to_char( "You already look like yourself!\n\r", ch );
	    return;
	}
	if (!IS_POLYAFF(ch, POLY_HAGS))
	{
	    send_to_char( "Nothing happens.\n\r", ch );
	    return;
	}
if (IS_WEREWOLF(ch))
    {
        sprintf(buf,"$n's form shifts and changes until $e looks like %s.",ch->name);
    }
else if (!IS_WEREWOLF(ch))
{
	sprintf(buf,"$n's features twist and distort until $e looks like %s.",ch->name);
}
	act(buf,ch,NULL,NULL,TO_ROOM);
	REMOVE_BIT(ch->polyaff, POLY_HAGS);
	REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
//	REMOVE_BIT(ch, VAM_DISGUISED);
	REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);
	//REMOVE_BIT(ch->extra, EXTRA_VICISSITUDE);
    	free_string( ch->morph );
    	ch->morph = str_dup( "" );
if (IS_WEREWOLF(ch))
{
act("Your form shifts and changes until you looks like $n.",ch,NULL,NULL,TO_CHAR);
}
else if (!IS_WEREWOLF(ch))
{ 
act("Your features twist and distort until you looks like $n.",ch,NULL,NULL,TO_CHAR);  
}
   	free_string( ch->long_descr );
    	ch->long_descr = str_dup( "" );
	return;
    }
    if (IS_VAMPAFF(ch,VAM_DISGUISED))
    {
	if (!IS_POLYAFF(ch, POLY_HAGS))
	{
	    send_to_char( "Nothing happens.\n\r", ch );
	    return;
	}
if (IS_WEREWOLF(ch))
    {
    act("Your form shifts and changes to match that of $N.",ch,NULL,victim,TO_CHAR);
    act("$n's form shifts and changes until $e looks like you.",ch,NULL,victim,TO_VICT);
    act("$n's form shifts and changes until $e looks like $N.",ch,NULL,victim,TO_NOTVICT);
    }
else if (!IS_WEREWOLF(ch))
{

act("Your features twist and distort until you looks like $N.",ch,NULL,victim,TO_CHAR);
act("$n's features twist and distort until $e looks like you.",ch,NULL,victim,TO_VICT);
act("$n's features twist and distort until $e looks like $N.",ch,NULL,victim,TO_NOTVICT);
    	free_string( ch->morph );
}
	if (IS_NPC(victim))
	{
	    ch->morph = str_dup( victim->short_descr );
	    free_string( ch->long_descr );
	    ch->long_descr = str_dup( victim->long_descr );
	}
	else
	{
	    ch->morph = str_dup( victim->name );
	    free_string( ch->long_descr );
	    ch->long_descr = str_dup( "" );
	}
	return;
    }
if (IS_WEREWOLF(ch))
    {
    act("Your form shifts and changes to match that of $N.",ch,NULL,victim,TO_CHAR);
    act("$n's form shifts and changes until $e looks like you.",ch,NULL,victim,TO_VICT);
    act("$n's form shifts and changes until $e looks like $N.",ch,NULL,victim,TO_NOTVICT);
    }
else if (!IS_WEREWOLF(ch))
{
    act("Your features twist and distort until you looks like $N.",ch,NULL,victim,TO_CHAR);
    act("$n's features twist and distort until $e looks like you.",ch,NULL,victim,TO_VICT);
    act("$n's features twist and distort until $e looks like $N.",ch,NULL,victim,TO_NOTVICT);
}
    SET_BIT(ch->polyaff, POLY_HAGS);
    SET_BIT(ch->affected_by, AFF_POLYMORPH);
//    SET_BIT(ch, VAM_DISGUISED);
SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_DISGUISED);  
 // SET_BIT(ch->extra, EXTRA_VICISSITUDE);
    free_string( ch->morph );
    if (IS_NPC(victim))
    {
	ch->morph = str_dup( victim->short_descr );
	free_string( ch->long_descr );
	ch->long_descr = str_dup( victim->long_descr );
    }
    else
    {
	ch->morph = str_dup( victim->name );
	free_string( ch->long_descr );
	ch->long_descr = str_dup( "" );
    }
    return;
}

void do_fear( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    argument = one_argument( argument, arg );

    if ( IS_NPC(ch) ) return;

    if ( !IS_CLASS(ch, CLASS_VAMPIRE) )
    {
	stc("Huh?\n\r",ch);
	return;
    }

    if ( ch->pcdata->powers[VAM_DAIM] < 5 )
    {
      stc("You must obtain level 5 Daimoinon to use Fear.\n\r",ch);
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
      stc("You must be fighting to use Fear.\n\r",ch);
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
      act("You bare your fangs and growl at $N.",ch,NULL,victim,TO_CHAR);
      act("$n bares $s fangs and growls at you.",ch,NULL,victim,TO_VICT);
      act("$n bares $s fangs and growls at $N, and $N flees in terror.",ch,NULL,victim,TO_NOTVICT);
      do_flee( victim, "" );
      return;
    }

    if ( !IS_NPC(victim) )
    {
      if ( ch->pcdata->powers[VAM_DAIM] < 5 )
      {
        if ( number_range( 1, 4 ) != 2 )
        {
          act("You bare your fangs and growl at $N, but nothing happens.",ch,NULL,victim,TO_CHAR);
          act("$n bares $s fangs and growls at you.",ch,NULL,victim,TO_VICT);
          act("$n bares $s fangs and growls at $N, but nothing happens.",ch,NULL,victim,TO_NOTVICT);
	  return;
        }
      }

      act("You bare your fangs and growl at $N.",ch,NULL,victim,TO_CHAR);
      act("$n bares $s fangs and growls at you.",ch,NULL,victim,TO_VICT);
      act("$n bares $s fangs and growls at $N, and $N flees in terror.",ch,NULL,victim,TO_NOTVICT);
      do_flee( victim, "" );
      return;
    }

  return;

}

void do_vtwist(CHAR_DATA *ch, char *argument)
{
  char arg1[MAX_STRING_LENGTH];
  char arg2[MAX_STRING_LENGTH];
  OBJ_DATA *obj; 
 
  argument=one_argument(argument,arg1);
  strcpy(arg2,argument);

  if (IS_NPC(ch)) return;

  if (!IS_CLASS(ch,CLASS_VAMPIRE))
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }

  if (ch->pcdata->powers[VAM_DAIM] < 4)
  {
    send_to_char("You must obtain level 5 Daimoinon to use Twist.\n\r",ch);
    return;
  }

  if (arg1 == NULL || arg2 == NULL)
  {
    send_to_char("Syntax: Dub (item) (description)?\n\r",ch);
    return;
  }

 if( !str_cmp(arg2, "NONAME") || !str_cmp(arg2, "NONAME") ||
!str_cmp(arg2, "NONAME") || !str_cmp(arg2, "NONAME"))
    {
	send_to_char( "You failed!\r\n", ch);
	return;
    }
  if ((obj=get_obj_carry(ch,arg1)) == NULL)
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
    send_to_char("From 3 to 40 characters please.\n\r",ch);
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

void do_gourge(CHAR_DATA *ch, char *argument  )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
   one_argument( argument,arg);
 
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch,CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
   if (ch->pcdata->powers[VAM_MELP] < 2)
   {
   send_to_char("You need Thaumaturgy 8 to Gourge.\n\r",ch);
   return;
   }
    if ( arg[0] == '\0' )
    {
        send_to_char( "Who do you wish to gourge?\n\r", ch );
	return;
    }
    if ((victim = get_char_room( ch, arg)) == NULL)
    {
    send_to_char("They arent here.\n\r",ch);
    return;
    }
	if (IS_NPC(victim) && IS_SET(victim->act, ACT_NOAUTOKILL)) {
	send_to_char("You can't do that to them.\n\r",  ch);
	return;}

    if (!IS_NPC(victim))
    {
    send_to_char("You cannot gourge a person.\n\r",ch);
    return;
    }
    if (victim->level > 30)
    {
    send_to_char(
    "Only small creatures are defenceless enough to be gourged on.\n\r",ch);
    return;
    }
    sprintf(buf,
    "%s leaps toward %s baring his fangs.",ch->name,victim->name);
    act(buf,ch,NULL,NULL,TO_ROOM);
    sprintf(buf,
    "You leap toward %s baring your fangs.\n\r",victim->name);
    send_to_char(buf,ch);
    WAIT_STATE(ch, 15);
    
    send_to_char(
    "You rip their throat out and gourge on the blood.\n\r",ch);
    sprintf(buf,
    "%s rips %s's throat out, gourging on all of their blood."
    ,ch->name,victim->name);
    act(buf,ch,NULL,NULL,TO_ROOM);
    ch->pcdata->condition[COND_THIRST] += number_range(100,200);
    if (ch->pcdata->condition[COND_THIRST] >= 1000 / ch->pcdata->stats[UNI_GEN]);
    {
    send_to_char("Your bloodlust is sated.\n\r",ch);

    ch->pcdata->condition[COND_THIRST] = 1000/ch->pcdata->stats[UNI_GEN];
    }
    sprintf(buf,
    "%s body falls to the ground lifeless.",victim->name);
    send_to_char(buf,ch);
    act(buf,ch,NULL,NULL,TO_ROOM);
    raw_kill( victim, ch );
    return;
}


void do_bloodwall(CHAR_DATA *ch, char *argument)
{
OBJ_DATA *obj = NULL;
OBJ_DATA *objc;
char arg[MAX_STRING_LENGTH];
char arg2[MAX_STRING_LENGTH];
char wall[MAX_STRING_LENGTH];
char buf[MAX_STRING_LENGTH];
sh_int value;

argument=one_argument(argument,arg);
argument=one_argument(argument,arg2);

if (IS_NPC(ch)) return;

if (!IS_CLASS(ch,CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
{
send_to_char("Huh?\n\r",ch);
return;
}
if (ch->pcdata->powers[VAM_DAIM] < 2)
{
send_to_char("You need Daiminion 2 to call Blood Walls.\n\r",ch);
return;
}

if (IS_SET(ch->in_room->room_flags, ROOM_SAFE))
    {
    send_to_char("You are unable to create a Blood wall here.\n\r",
ch);
    return;
    }

if (arg[0] == '\0' || (str_cmp(arg,"n")
                   && str_cmp(arg,"s")
                   && str_cmp(arg,"e")
                   && str_cmp(arg,"w")
                   && str_cmp(arg,"u")
                   && str_cmp(arg,"d")))
{
send_to_char("You may wall n, w, s, e, d or u.\n\r",ch);
return;
}

if (arg2[0] == '\0')
{
send_to_char("Please supply the amount of blood to expend.\n\r",ch);
return;
}


value = is_number( arg2 ) ? atoi( arg2 ) : -1;

if ( ch->pcdata->condition[COND_THIRST] < value )
   {
     stc("You have insufficient blood.\n\r",ch);
     return;
   }

if (value > 200 || value < 1)
{
send_to_char("Please select a value between 1 and 200.\n\r",ch);
return;
}




ch->pcdata->condition[COND_THIRST] -= value;
sprintf(buf,"A look of concentration passes over %s's face.",ch->name);
act(buf,ch,NULL,NULL,TO_ROOM);
send_to_char("A look of concentration passes over your face.\n\r",ch);
if (!str_cmp(arg,"n")) sprintf(wall,"walln");
if (!str_cmp(arg,"w")) sprintf(wall,"wallw");
if (!str_cmp(arg,"s")) sprintf(wall,"walls");
if (!str_cmp(arg,"e")) sprintf(wall,"walle");
if (!str_cmp(arg,"d")) sprintf(wall,"walld");
if (!str_cmp(arg,"u")) sprintf(wall,"wallu");
objc = get_obj_list(ch,wall,ch->in_room->contents);
if ( objc != NULL)
{
send_to_char("There is already a wall blocking that direction.\n\r",ch);
return;
}
WAIT_STATE(ch,25);
sprintf(buf,"A wall of blood pours out of the ground.");
act(buf,ch,NULL,NULL,TO_ROOM);
send_to_char(buf,ch);
if (!str_cmp(arg,"n")) 
{
obj=create_object(get_obj_index(30043),0);
sprintf(buf,"A wall of blood is here, blocking your exit north.");
obj->short_descr = str_dup(buf);
}
if (!str_cmp(arg,"s")) 
{
obj=create_object(get_obj_index(30044),0);
sprintf(buf,"A wall of blood is here, blocking your exit south.");
obj->short_descr = str_dup(buf);
}
if (!str_cmp(arg,"e")) 
{
obj=create_object(get_obj_index(30045),0);
sprintf(buf,"A wall of blood is here, blocking your exit east");
obj->short_descr = str_dup(buf);
}
if (!str_cmp(arg,"w")) 
{
obj=create_object(get_obj_index(30046),0);
sprintf(buf,"A wall of blood is here, blocking your exit west");
obj->short_descr = str_dup(buf);
}
if (!str_cmp(arg,"d")) 
{
obj=create_object(get_obj_index(30047),0);
sprintf(buf,"A wall of blood is here, blocking your exit down");
obj->short_descr = str_dup(buf);
}
if (!str_cmp(arg,"u")) 
{
obj=create_object(get_obj_index(30048),0);
sprintf(buf,"A wall of blood is here, blocking your exit up.");
obj->short_descr = str_dup(buf);
	}

	obj_to_room(obj,ch->in_room);
	obj->timer = (value/8);
	obj->item_type = ITEM_WALL; 
	return;

}


void do_guardian(CHAR_DATA *ch, char *argument )
{
 
    char buf [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    AFFECT_DATA af;
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
     {
     send_to_char("Huh?\n\r",ch);
     return;
     }
    if (ch->pcdata->powers[VAM_DAIM] < 1)
    {
    send_to_char("You require level 1 Daimoinon to create a guardian.\n\r",ch);
    return;
    }
 
    if (ch->pcdata->followers > 5)
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }
    ch->pcdata->followers++;
 
    victim=create_mobile( get_mob_index( MOB_VNUM_GUARDIAN ) );
    victim->level = 200;
    victim->hit = 5000;
    victim->max_hit = 5000;
    victim->hitroll = 50;
    victim->damroll = 50;
    victim->armor = 300;
    SET_BIT(victim->act, ACT_NOEXP); 

    strcpy(buf,"Come forth, creature of darkness, and do my bidding!");
    do_say( ch, buf );
 
    send_to_char( "A demon bursts from the ground and bows before you.\n\r",ch );
    act( "$N bursts from the ground and bows before $n.", ch, NULL,victim, TO_ROOM );
 
    char_to_room( victim, ch->in_room );
 
 
    add_follower( victim, ch );
    af.duration  = 666;
    af.location  = APPLY_NONE;
    af.modifier  = 0;
    af.bitvector = AFF_CHARM;
    affect_to_char( victim, &af );
    return;

}

void do_gate(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    OBJ_DATA  *obj;
    char       arg [MAX_INPUT_LENGTH];
 
    one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_VAMPIRE) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
    if (ch->pcdata->powers[VAM_DAIM] < 3)
    {
    send_to_char("You require Daimoinon level 3 to gate.\n\r",ch);
    return;
    }
    if ( arg[0] == '\0')
    {
        send_to_char( "Who do you wish to gate to?\n\r", ch );
	return;
    }
 
    if ( (victim = get_char_world( ch, arg ) ) == NULL )
    {
    send_to_char("They arent here.\n\r",ch);
    return;
    }
 
 
    if ( (victim == ch) 
    ||   victim->in_room == NULL
    ||   IS_NPC(victim)
    ||   (!IS_NPC(victim) && !IS_IMMUNE(victim, IMM_SUMMON) )
    ||   IS_SET(ch->in_room->room_flags, ROOM_PRIVATE)
    ||   IS_SET(ch->in_room->room_flags, ROOM_SOLITARY)
    ||   IS_SET(ch->in_room->room_flags, ROOM_NO_RECALL)
    ||   IS_SET(victim->in_room->room_flags, ROOM_PRIVATE)
    ||   IS_SET(victim->in_room->room_flags, ROOM_SOLITARY)
    ||   IS_SET(victim->in_room->room_flags, ROOM_NO_RECALL)
    ||   victim->in_room->vnum == ch->in_room->vnum)
    {
	send_to_char( "You failed.\n\r", ch );
	return;
    }
 
 
    obj = create_object( get_obj_index( OBJ_VNUM_GATE ), 0 );
    obj->value[0] = victim->in_room->vnum;
    obj->value[3] = ch->in_room->vnum;
    obj->timer = 5;
    if (IS_AFFECTED(ch,AFF_SHADOWPLANE))
	obj->extra_flags = ITEM_SHADOWPLANE;
    obj_to_room( obj, ch->in_room );
 
    obj = create_object( get_obj_index( OBJ_VNUM_GATE ), 0 );
    obj->value[0] = ch->in_room->vnum;
    obj->value[3] = victim->in_room->vnum;
    obj->timer = 5;
    if (IS_AFFECTED(victim,AFF_SHADOWPLANE))
	obj->extra_flags = ITEM_SHADOWPLANE;
    obj_to_room( obj, victim->in_room );
    act( "A look of concentration passes over $n's face.", ch, NULL,NULL,
TO_ROOM );
    send_to_char("A look of concentration passes over your face.\n\r",ch);
    act( "$p appears in front of $n in a blast of flames.", ch, obj, NULL,
TO_ROOM );
    act( "$p appears in front of you in a blast of flames.", ch, obj,
NULL, TO_CHAR );
    act( "$p appears in front of $n in a blast of flames.", victim, obj,
NULL, TO_ROOM );
    act( "$p appears in front of you in a blast of flames.", ch, obj,
victim, TO_VICT );
    return;
}

void do_obeah(CHAR_DATA *ch, char *argument)
{
    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }

  /*  if (get_disc(ch, DISC_OBEAH) == 0)
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }
*/
 if (ch->pcdata->powers[VAM_OBEA] < 1)
    {
        send_to_char("You must obtain at least level 1 in Obeah to use Obeah.\n\r",ch);
        return;
    }
if (IS_SET(ch->newbits, NEW_OBEAH))   

    {
    if (ch->obeah_timer > 0)
    {
        send_to_char("You cannot close your eye until it stops glowing!\n\r",ch);
        return;
    }
    send_to_char("You close the eye on your forehead.\n\r",ch);
    act("$n closes the eye on $s forehead.", ch, NULL, NULL, TO_ROOM);
    REMOVE_BIT(ch->newbits, NEW_OBEAH);
    return;
    }
    send_to_char("Your third eye opens in your forehead.\n\r",ch);
    act("A third eye opens in $n's forehead.", ch, NULL, NULL, TO_ROOM);
    SET_BIT(ch->newbits, NEW_OBEAH);

    return;
}


void do_panacea(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

    argument = one_argument(argument, arg);

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch) && !IS_ABOMINATION(ch)) 
    {
		send_to_char("Huh?\n\r", ch);
		return;
	}

     if (ch->pcdata->powers[VAM_OBEA] < 2)
    {
        send_to_char("You must obtain at least level 2 in Obeah to use Panacea.\n\r",ch);
	return;
    }


    if (ch->obeah_timer > 0) {
		if (ch->obeah_timer > 1)
			sprintf(buf,"You cannot call upon your Obeah powers for another %d seconds.\n\r",ch->obeah_timer);
		else
			sprintf(buf,"You cannot call upon your Obeah powers for another 1 second.\n\r");
		send_to_char(buf,ch);
		return;
	}

    if (arg[0] == '\0') {
		send_to_char("Who do you want to heal with Panacea?\n\r", ch);
		return;
	}

    if ((victim = get_char_room(ch, arg)) == NULL) {
		send_to_char("They are not here.\n\r", ch);
		return;
	}

    if (!IS_SET(ch->newbits, NEW_OBEAH)) do_obeah(ch,"");

    if (victim->loc_hp[6] > 0) {
		int sn = skill_lookup("clot");
		act("$n's third eye begins to glow with an intense white light.", ch, NULL, NULL, TO_ROOM);
		send_to_char("Your third eye begins to glow with an intense white light.\n\r", ch);
		ch->obeah_timer = 5;
		(*skill_table[sn].spell_fun) (sn,ch->level,ch,victim);
	}
	if ((victim->loc_hp[0] + victim->loc_hp[1] + victim->loc_hp[2] +
	  victim->loc_hp[3] + victim->loc_hp[4] + victim->loc_hp[5]) != 0) {
		act("$n's third eye begins to glow with an intense white light.", ch, NULL, NULL, TO_ROOM);
		send_to_char("Your third eye begins to glow with an intense white light.\n\r", ch);
		ch->obeah_timer = 10;
		reg_mend(victim);
	} else if (victim->hit < victim->max_hit) {
		victim->hit +=  3000;
	if (victim->hit > victim->max_hit) {
	victim->hit = victim->max_hit;
}
		victim->agg -= victim->agg / 3.5;
		if (victim->agg < 0) victim->agg = 0;
		act("$n's third eye begins to glow with an intense white light.", ch, NULL, NULL, TO_ROOM);
		send_to_char("Your third eye begins to glow with an intense white light.\n\r", ch);
		ch->obeah_timer = 30;
		update_pos(victim);
		if (victim->hit >= victim->max_hit) {
			victim->hit = victim->max_hit;
			send_to_char("You have been completely healed!\n\r",victim);
			act("$n's wounds have been completely healed!",victim,NULL,NULL,TO_ROOM);
		} else {
			send_to_char("Your wounds begin to heal!\n\r",victim);
			act("$n's wounds begin to heal!",victim,NULL,NULL,TO_ROOM);
		}
	} else {
		send_to_char("They don't require any healing.\n\r",ch);
		return;
	}

}

void do_anesthetic(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

    argument = one_argument(argument, arg);

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch) && !IS_ABOMINATION(ch))
    {
    send_to_char("Huh?\n\r", ch);
    return;
    }

  if (ch->pcdata->powers[VAM_OBEA] < 3)
    {
        send_to_char("You must obtain at least level 3 in Obeah to use Anesthetic.\n\r",ch);
        return;
    }

    if (ch->obeah_timer > 0)
    {
    if (ch->obeah_timer > 1)
        sprintf(buf,"You cannot call upon your Obeah powers for another %d seconds.\n\r",ch->obeah_timer);
    else
        sprintf(buf,"You cannot call upon your Obeah powers for another 1 second.\n\r");
    send_to_char(buf,ch);
    return;
    }

    if (arg[0] == '\0')
    {
    send_to_char("Who do you want to use Anesthetic Touch on?\n\r", ch);
    return;
    }

    if ((victim = get_char_room(ch, arg)) == NULL)
    {
    send_to_char("They are not here.\n\r", ch);
    return;
    }

    if (!IS_SET(ch->newbits, NEW_OBEAH)) do_obeah(ch,"");

    act("$n's third eye begins to glow with an intense white light.", ch, NULL, NULL, TO_ROOM);
    send_to_char("Your third eye begins to glow with an intense white light.\n\r", ch);
    ch->obeah_timer = 30;

    if (IS_SET(victim->newbits, NEW_CALM))
    {
    send_to_char("You remove their immunity to pain.\n\r",ch);
    send_to_char("You no longer feel so oblivious to pain.\n\r",victim);
    REMOVE_BIT(victim->newbits, NEW_NOPAIN);
   
    send_to_char("You make them immune to pain.\n\r",ch);
    send_to_char("You feel completely oblivious to pain.\n\r",victim);
    SET_BIT(victim->newbits, NEW_NOPAIN);
}
    
    return;
}

void do_neutral(CHAR_DATA *ch, char *argument)
{
    char buf [MAX_INPUT_LENGTH];
    CHAR_DATA *rch;

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch))
    {
    send_to_char("Huh?\n\r", ch);
    return;
    }

    
     if (ch->pcdata->powers[VAM_OBEA] < 4)
    {
        send_to_char("You must obtain at least level 4 in Obeah to create a Neutral Guard\n\r",ch);
        return;
    }


    if (ch->obeah_timer > 0 && !IS_SET(ch->newbits, NEW_NEUTRAL))
    {
    if (ch->obeah_timer > 1)
        sprintf(buf,"You cannot call upon your Obeah powers for another %d seconds.\n\r",ch->obeah_timer);
    else
        sprintf(buf,"You cannot call upon your Obeah powers for another 1 second.\n\r");
    send_to_char(buf,ch);
    return;
    }

    if (ch->in_room == NULL)
    {
    send_to_char("Nothing happens.\n\r",ch);
    return;
    }

    if (IS_SET(ch->newbits, NEW_REINA))
    {
    send_to_char("Nothing happens.\n\r",ch);
    return;
    }

    if (IS_SET(ch->newbits, NEW_NEUTRAL))
    {
    REMOVE_BIT(ch->newbits, NEW_NEUTRAL);
    REMOVE_BIT(ch->in_room->room_flags, ROOM_SAFE);
    act("A look of concentration crosses $n's face.", ch, NULL, NULL, TO_ROOM);
    send_to_char("The peaceful harmony in the air gradually fades away to nothing.\n\r", ch);
    act("The peaceful harmony in the air gradually fades away to nothing.",ch,NULL,NULL,TO_ROOM);
    ch->obeah_timer = 30;
    return;
    }

    if (IS_SET(ch->in_room->room_flags, ROOM_SAFE))
    {
    send_to_char("You are unable to create a Neutral Guard here.\n\r", ch);
    return;
    }

    SET_BIT(ch->in_room->room_flags, ROOM_SAFE);
    SET_BIT(ch->newbits, NEW_NEUTRAL);
    act("$n's third eye begins to glow with an intense white light.", ch, NULL, NULL, TO_ROOM);
    send_to_char("Your third eye begins to glow with an intense white light.\n\r", ch);
    ch->obeah_timer = 30;
    send_to_char("The air is filled with peaceful harmony.\n\r", ch);
    act("The air is filled with peaceful harmony.",ch,NULL,NULL,TO_ROOM);
    for (rch = ch->in_room->people; rch != NULL; rch = rch->next_in_room)
    {
    if (rch->fighting != NULL)
        stop_fighting(rch, TRUE);
    }
    return;
}





void do_renew(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];
    int       sn, check, oldcheck;

    argument = one_argument(argument, arg);

    if (IS_NPC(ch)) return;

     if (!IS_VAMPIRE(ch))
    {
    send_to_char("Huh?\n\r", ch);
    return;
    }

 

if (!IS_NPC(ch) && ch->position == POS_STUNNED)
    {
    send_to_char("Not while you are mortally wounded!.\n\r", ch);
    return;
    }

  if (ch->pcdata->powers[VAM_OBEA] < 5)
    {
        send_to_char("You require level 5 Obeah to use Renewed Vigor.\n\r",ch);
        return;
    }



    if (ch->position == POS_FIGHTING)
    {
    send_to_char("No way!  You are still fighting!\n\r",ch);
    return;
    }

    if (ch->obeah_timer> 0)
    {
    if (ch->obeah_timer > 1)
        sprintf(buf,"You cannot call upon your Obeah powers for another %d seconds.\n\r",ch->obeah_timer);
    else
        sprintf(buf,"You cannot call upon your Obeah powers for another 1 second.\n\r");
    send_to_char(buf,ch);
    return;
    }

    if (arg[0] == '\0')
    {
    send_to_char("Who do you want to use Renewed Vigor on?\n\r", ch);
    return;
    }

    if ((victim = get_char_room(ch, arg)) == NULL)
    {
    send_to_char("They are not here.\n\r", ch);
    return;
    }

    if (!IS_SET(ch->newbits, NEW_OBEAH)) do_obeah(ch,"");

    if ((victim->loc_hp[0] + victim->loc_hp[1] + victim->loc_hp[2] + 
     victim->loc_hp[3] + victim->loc_hp[4] + victim->loc_hp[5] + 
     victim->loc_hp[6]) == 0 && victim->hit == victim->max_hit)
    {
    send_to_char("They don't require any healing.\n\r",ch);
    return;
    }

    act("$n's third eye begins to glow with an intense white light.", ch, NULL, NULL, TO_ROOM);
    send_to_char("Your third eye begins to glow with an intense white light.\n\r", ch);
    ch->obeah_timer = 60;

    if ((check = victim->loc_hp[6]) > 0)
    {
    oldcheck = 0;
    sn = skill_lookup("clot");
    while (oldcheck != (check = victim->loc_hp[6]))
    {
        oldcheck = check;
        (*skill_table[sn].spell_fun) (sn,ch->level,ch,victim);
    }
    }
    if ((check = (victim->loc_hp[0] + victim->loc_hp[1] + victim->loc_hp[2] +
    victim->loc_hp[3] + victim->loc_hp[4] + victim->loc_hp[5])) > 0)
    {
    oldcheck = 0;
    while (oldcheck != (check = victim->loc_hp[0] + victim->loc_hp[1] + 
        victim->loc_hp[2] + victim->loc_hp[3] + victim->loc_hp[4] + 
        victim->loc_hp[5]))
    {
        oldcheck = check;
        reg_mend(victim);
    }
    }
    if (victim->hit < victim->max_hit)
    {
    victim->hit = victim->max_hit;
   // victim->agg = 0;
    send_to_char("You have been completely healed!\n\r",victim);
    act("$n's wounds have been completely healed!",victim,NULL,NULL,TO_ROOM);
    update_pos(victim);
    }
 
    return;
}

void do_willpower( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if ( IS_NPC(ch) )
	return;

    if (arg[0] == '\0')
    {
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	send_to_char("                                -= Will Power =-\n\r",ch);
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	if (IS_WILLPOWER(ch, RES_ANIMALISM))
	    send_to_char("Animalism: You automatically try to resist Beast Within and Song of Serenity.\n\r",ch);
	else
	    send_to_char("Animalism: You don't try to resist Beast Within and Song of Serenity.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_AUSPEX))
	    send_to_char("Auspex: You automatically try to resist Unveil the Shrouded Mind.\n\r",ch);
	else
	    send_to_char("Auspex: You don't try to resist Unveil the Shrouded Mind.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_DOMINATE))
	    send_to_char("Dominate: You automatically try to resist Dominate attempts.\n\r",ch);
	else
	    send_to_char("Dominate: You don't try to resist Dominate attempts.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_PRESENCE))
	    send_to_char("Presence: You automatically try to resist Dread Gaze and Entrancement.\n\r",ch);
	else
	    send_to_char("Presence: You don't try to resist Dread Gaze and Entrancement.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_TOGGLE))
	    send_to_char("Toggle: You automatically keep burning willpower to resist attempts.\n\r",ch);
	else
	    send_to_char("Toggle: You will only burn willpower to resist each first attempt.\n\r",ch);
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	send_to_char("You may change any of the above by typing: willpower <value>\n\r",ch);
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	send_to_char("Remaining resistance in seconds:\n\r", ch );
	sprintf( buf,"Animalism: %d.  Auspex: %d.  Presence: %d.  Dominate: %d.\n\r",
	ch->pcdata->resist[WILL_ANIMALISM], ch->pcdata->resist[WILL_AUSPEX],
	ch->pcdata->resist[WILL_PRESENCE],  ch->pcdata->resist[WILL_DOMINATE]);
	send_to_char( buf, ch );
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	return;
    }

    if (!str_cmp(arg,"animalism"))
    {
	if (IS_WILLPOWER(ch, RES_ANIMALISM))
	{
	    send_to_char("You will no longer try to resist Beast Within and Song of Serenity.\n\r",ch);
	    REMOVE_BIT(ch->pcdata->resist[0], RES_ANIMALISM);
	}
	else
	{
	    send_to_char("You will now automatically try to resist Beast Within and Song of Serenity.\n\r",ch);
	    SET_BIT(ch->pcdata->resist[0], RES_ANIMALISM);
	}
    }
    else if (!str_cmp(arg,"auspex"))
    {
	if (IS_WILLPOWER(ch, RES_AUSPEX))
	{
	    send_to_char("You will no longer try to resist Unveil the Shrouded Mind.\n\r",ch);
	    REMOVE_BIT(ch->pcdata->resist[0], RES_AUSPEX);
	}
	else
	{
	    send_to_char("You will now automatically try to resist Unveil the Shrouded Mind.\n\r",ch);
	    SET_BIT(ch->pcdata->resist[0], RES_AUSPEX);
	}
    }
    else if (!str_cmp(arg,"dominate"))
    {
	if (IS_WILLPOWER(ch, RES_DOMINATE))
	{
	    send_to_char("You will no longer try to resist Domination attempts.\n\r",ch);
	    REMOVE_BIT(ch->pcdata->resist[0], RES_DOMINATE);
	}
	else
	{
	    send_to_char("You will now automatically try to resist Domination attempts.\n\r",ch);
	    SET_BIT(ch->pcdata->resist[0], RES_DOMINATE);
	}
    }
    else if (!str_cmp(arg,"presence"))
    {
	if (IS_WILLPOWER(ch, RES_PRESENCE))
	{
	    send_to_char("You will no longer try to resist Dread Gaze and Entrancement.\n\r",ch);
	    REMOVE_BIT(ch->pcdata->resist[0], RES_PRESENCE);
	}
	else
	{
	    send_to_char("You will now automatically try to resist Dread Gaze and Entrancement.\n\r",ch);
	    SET_BIT(ch->pcdata->resist[0], RES_PRESENCE);
	}
    }
    else if (!str_cmp(arg,"toggle"))
    {
	if (IS_WILLPOWER(ch, RES_TOGGLE))
	{
	    send_to_char("You will now only burn willpower to resist each first attempt.\n\r",ch);
	    REMOVE_BIT(ch->pcdata->resist[0], RES_TOGGLE);
	}
	else
	{
	    send_to_char("You will now automatically keep burning willpower to resist attempts.\n\r",ch);
	    SET_BIT(ch->pcdata->resist[0], RES_TOGGLE);
	}
    }
    else
    {
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	send_to_char("                                -= Will Power =-\n\r",ch);
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	if (IS_WILLPOWER(ch, RES_ANIMALISM))
	    send_to_char("Animalism: You automatically try to resist Beast Within and Song of Serenity.\n\r",ch);
	else
	    send_to_char("Animalism: You don't try to resist Beast Within and Song of Serenity.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_AUSPEX))
	    send_to_char("Auspex: You automatically try to resist Unveil the Shrouded Mind.\n\r",ch);
	else
	    send_to_char("Auspex: You don't try to resist Unveil the Shrouded Mind.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_DOMINATE))
	    send_to_char("Dominate: You automatically try to resist Dominate attempts.\n\r",ch);
	else
	    send_to_char("Dominate: You don't try to resist Dominate attempts.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_PRESENCE))
	    send_to_char("Presence: You automatically try to resist Dread Gaze and Entrancement.\n\r",ch);
	else
	    send_to_char("Presence: You don't try to resist Dread Gaze and Entrancement.\n\r",ch);
	if (IS_WILLPOWER(ch, RES_TOGGLE))
	    send_to_char("Toggle: You automatically keep burning willpower to resist attempts.\n\r",ch);
	else
	    send_to_char("Toggle: You will only burn willpower to resist each first attempt.\n\r",ch);
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	send_to_char("You may change any of the above by typing: willpower <value>\n\r",ch);
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	send_to_char("Remaining resistance in seconds:\n\r", ch );
	sprintf( buf,"Animalism: %d.  Auspex: %d.  Presence: %d.  Dominate: %d.\n\r",
	ch->pcdata->resist[WILL_ANIMALISM], ch->pcdata->resist[WILL_AUSPEX],
	ch->pcdata->resist[WILL_PRESENCE],  ch->pcdata->resist[WILL_DOMINATE]);
	send_to_char( buf, ch );
	send_to_char("--------------------------------------------------------------------------------\n\r",ch);
	return;
    }
    return;
}

void do_love( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch) && !IS_ABOMINATION(ch))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

   if (ch->pcdata->powers[VAM_MELP] < 3)
  {
     send_to_char("You need Melpominee 3 to use the song of love.\n\r",ch);
     return;
  }

    if (ch->reina_timer > 0)
    {
	if (ch->reina_timer > 1)
	    sprintf(buf,"Your voice will not recover for another %d seconds.\n\r",ch->reina_timer);
	else
	    sprintf(buf,"Your voice will not recover for another 1 second.\n\r");
	send_to_char(buf,ch);
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Who do you wish to use the Song of Love on?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "You're already in love with yourself.\n\r", ch );
	return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's\n\r", ch );
	return;
    }

    if (is_safe(ch,victim)) return;

    send_to_char("You sing the Song of Love.\n\r", ch);
    act("$n sings a beautiful, haunting song.", ch, NULL, NULL, TO_ROOM );
    ch->reina_timer = 60;

    if (strlen(victim->pcdata->love) > 2)
    {
	if (!str_cmp(victim->pcdata->love,ch->name))
	{
	    act("You remove $N's love for you!", ch, NULL, victim, TO_CHAR);
	    act("You are no longer in love with $n!", ch, NULL, victim, TO_VICT);
	    free_string(victim->pcdata->love);
	    victim->pcdata->love = str_dup( "" );
 if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
{
		guardian_message( victim );
		act("$n just used Love on you.",ch,NULL,victim,TO_VICT);
	    }
	}
	else
	{
	    send_to_char( "They are already in love with someone else.\n\r", ch );
	    if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
	    {
		guardian_message( victim );
		act("$n just failed to use Love on you.",ch,NULL,victim,TO_VICT);
	    }
	}
	return;
    }

  if (!IS_NPC(victim) && (IS_VAMPIRE(victim)))
// || IS_GHOUL(victim)) &&
//	get_disc(victim,DISC_PRESENCE) >= get_disc(ch,DISC_PRESENCE) )
    {
	send_to_char("They resist you.\n\r",ch);
	if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
	{
	    guardian_message( victim );
	    act("$n just failed to use Love on you.",ch,NULL,victim,TO_VICT);
	}
	return;
    }

    if (!IS_NPC(victim) && victim->pcdata->resist[WILL_PRESENCE] > 0)
    {
	send_to_char("They resist you.\n\r",ch);
	if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
	{
	    guardian_message( victim );
	    act("$n just failed to use Love on you.",ch,NULL,victim,TO_VICT);
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
	send_to_char("You burn some willpower to resist Love.\n\r",victim);
	send_to_char("They resist you.\n\r",ch);
	if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
	{
	    guardian_message( victim );
	    act("$n just failed to use Love on you.",ch,NULL,victim,TO_VICT);
	}
	return;
    }

    act("You make $N fall in love with you!", ch, NULL, victim, TO_CHAR);
    act("You fall in love with $n!", ch, NULL, victim, TO_VICT);
    act("$N gazes lovingly into $n's eyes!", ch, NULL, victim, TO_NOTVICT);

    free_string(victim->pcdata->love);
    victim->pcdata->love = str_dup( ch->name );

    if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
    {
	guardian_message( victim );
	act("$n just used Love on you.",ch,NULL,victim,TO_VICT);
    }
    return;
}
 
void guardian_message( CHAR_DATA *ch )
{
    if ( IS_DEMON(ch) )
    {
	if ( IS_HIGHLANDER(ch) )
	{
	    send_to_char("Your little cherub whispers softly into your ear:\n\r",ch);
	    act( "A little cherub on $n's shoulder whispers something into $n's ear.",ch,NULL,NULL,TO_ROOM);
	}
	else
	{
	    send_to_char("Your pet imp whispers softly into your ear:\n\r",ch);
	    act( "A tiny imp on $n's shoulder whispers something into $n's ear.",ch,NULL,NULL,TO_ROOM);
	}
    }
    else
	send_to_char("Your guardian spirit sends you a telepathic message:\n\r",ch);
    return;
}

void do_reina( CHAR_DATA *ch, char *argument )
{
    char buf [MAX_INPUT_LENGTH];
    CHAR_DATA *rch;

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

   if ( ch->hit <= -10 )
{
stc("Not while mortally wounded!\n\r", ch );
return;
}

    if (ch->fight_timer >0) {
        send_to_char("Not until your fight timer expires.\n\r", ch );
        return;}


   if (ch->pcdata->powers[VAM_MELP] < 4)
  {
     send_to_char("You need Melpominee 4 to use the song of Reina.\n\r",ch);
     return;
  }

    if (ch->in_room == NULL)
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }

    if (IS_SET(ch->newbits, NEW_NEUTRAL))
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }

    if (IS_SET(ch->newbits, NEW_REINA))
    {
	REMOVE_BIT(ch->newbits, NEW_REINA);
	REMOVE_BIT(ch->in_room->room_flags, ROOM_SAFE);
	send_to_char("The peaceful harmony in the air gradually fades away to nothing.\n\r", ch);
	act("A look of concentration crosses $n's face.", ch, NULL, NULL, TO_ROOM );
	act("The peaceful harmony in the air gradually fades away to nothing.",ch,NULL,NULL,TO_ROOM);
	ch->reina_timer = 60;
	return;
    }

    if (IS_SET(ch->in_room->room_flags, ROOM_SAFE))
    {
	send_to_char("You are unable to sing the Song of Reina here.\n\r", ch);
	return;
    }

    if (ch->reina_timer > 0)
    {
	if (ch->reina_timer > 1)
	    sprintf(buf,"Your voice will not recover for another %d seconds.\n\r",ch->reina_timer);
	else
	    sprintf(buf,"Your voice will not recover for another 1 second.\n\r");
	send_to_char(buf,ch);
	return;
    }

    SET_BIT(ch->in_room->room_flags, ROOM_SAFE);
    SET_BIT(ch->newbits, NEW_REINA);
    ch->reina_timer = 60;
    send_to_char("You sing the Song of Reina.\n\r", ch);
    act("$n sings a beautiful, haunting song.", ch, NULL, NULL, TO_ROOM );
    send_to_char("The air is filled with peaceful harmony.\n\r", ch);
    act("The air is filled with peaceful harmony.",ch,NULL,NULL,TO_ROOM);
    for ( rch = ch->in_room->people; rch != NULL; rch = rch->next_in_room )
    {
	if ( rch->fighting != NULL )
	    stop_fighting( rch, TRUE );
    }
    return;
}


void do_courage( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_STRING_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_VAMPIRE(ch))
    {
	send_to_char( "Huh?\n\r", ch );
	return;
    }

       if (ch->pcdata->powers[VAM_MELP] < 5)
  {
     send_to_char("You need Melpominee 5 to use the song of Courage.\n\r",ch);
     return;
  }

    if (ch->reina_timer > 0)
    {
	if (ch->reina_timer > 1)
	    sprintf(buf,"Your voice will not recover for another %d seconds.\n\r",ch->reina_timer);
	else
	    sprintf(buf,"Your voice will not recover for another 1 second.\n\r");
	send_to_char(buf,ch);
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Who do you wish to use Courage on?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They are not here.\n\r", ch );
	return;
    }

    if (IS_NPC(victim))
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    send_to_char("You sing the Song of Courage.\n\r", ch);
    act("$n sings a beautiful, haunting song.", ch, NULL, NULL, TO_ROOM );
    ch->reina_timer = 60;

    if (IS_SET(victim->newbits, NEW_COURAGE))
    {
	if (!IS_NPC(victim) && victim->pcdata->resist[WILL_PRESENCE] > 0 && ch != victim)
	{
	    send_to_char("They resist you.\n\r",ch);
	    if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
	    {
		guardian_message( victim );
		act("$n just failed to remove Courage from you.",ch,NULL,victim,TO_VICT);
	    }
	    return;
	}

	if (!IS_NPC(victim) && IS_WILLPOWER(victim, RES_PRESENCE) && 
	    victim->pcdata->willpower[0] >= 10 && ch != victim)
	{
	    victim->pcdata->willpower[0] -= 10;
	    victim->pcdata->resist[WILL_PRESENCE] = 60;
	    if (!IS_WILLPOWER(victim, RES_TOGGLE))
		REMOVE_BIT(victim->pcdata->resist[0], RES_PRESENCE);
	    send_to_char("You burn some willpower to resist Anger.\n\r",victim);
	    send_to_char("They resist you.\n\r",ch);
	    if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
	    {
		guardian_message( victim );
		act("$n just failed to remove Courage from you.",ch,NULL,victim,TO_VICT);
	    }
	    return;
	}
	if (ch != victim) send_to_char("You remove their Courage.\n\r",ch);
	send_to_char("You no longer feel quite so brave.\n\r",victim);
	WAIT_STATE( ch, 12 );
	return;
    }

    if (ch != victim) send_to_char("You grant them great Courage.\n\r",ch);
    send_to_char("You suddenly feel very brave.\n\r",victim);

    if (!IS_NPC(victim) && ch != victim && IS_MORE(victim, MORE_GUARDIAN))
    {
	guardian_message( victim );
	act("$n just used Courage on you.",ch,NULL,victim,TO_VICT);
    }
    SET_BIT(ch->newbits, NEW_COURAGE);
    WAIT_STATE( ch, 12 );
    return;
}

void do_shroudnight( CHAR_DATA *ch, char *argument )
{
    char buf [MAX_INPUT_LENGTH];

    if (IS_NPC(ch)) return;

if (!IS_CLASS(ch,CLASS_VAMPIRE) && !IS_WEREWOLF(ch) && !IS_ABOMINATION(ch))
{
send_to_char("Huh?\n\r",ch);
return;
}

   if ((IS_VAMPIRE(ch) || IS_ABOMINATION(ch)) && (ch->pcdata->powers[VAM_OBTE] < 2))
{
send_to_char("You need level 2 Obtenebration to use shroud of the night.\n\r",ch);
    return;
}

  if (IS_WEREWOLF(ch) &&  ch->gifts[UKTENA] < 1 )
  {
    stc("You must obtain the first gift of the Uktena to use Dark Shroud.\n\r",ch);
    return;
  }


    if (ch->in_room == NULL)
    {
	send_to_char("Nothing happens.\n\r",ch);
	return;
    }

    if (IS_SET(ch->newbits, NEW_DARKNESS))
    {
	REMOVE_BIT(ch->newbits, NEW_DARKNESS);
	REMOVE_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);
	send_to_char("You banish the darkness from the room!\n\r", ch);
	act("A look of concentration crosses $n's face.", ch, NULL, NULL, TO_ROOM );
	act("$n banishes the darkness from the room!",ch,NULL,NULL,TO_ROOM);
	 ch->darkness_timer = 60;
	return;
    }

    if (IS_SET(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS))
    {
	send_to_char("The room is already in darkness.\n\r", ch);
	return;
    }

    if (ch->darkness_timer > 0)
    {
	if (ch->darkness_timer > 1)
	    sprintf(buf,"You cannot call upon the Shroud of Night for another %d seconds.\n\r",ch->darkness_timer);
	else
	    sprintf(buf,"You cannot call upon the Shroud of Night for another 1 second.\n\r");
	send_to_char(buf,ch);
	return;
    }

    SET_BIT(ch->in_room->room_flags, ROOM_TOTAL_DARKNESS);
    SET_BIT(ch->newbits, NEW_DARKNESS);
    send_to_char("You call forth the Shroud of Night to darken the room!\n\r", ch);
    act("A look of concentration crosses $n's face.", ch, NULL, NULL, TO_ROOM );
    act("The room is filled with darkness!",ch,NULL,NULL,TO_ROOM);
    ch->darkness_timer = 60;   
 return;
} 
