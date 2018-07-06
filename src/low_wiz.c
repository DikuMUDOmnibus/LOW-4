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
/*
 * This file (C) Tijer
 */

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

#include "merc.h"


/*
 *  Local Functions
 */


char * plr_bit_name( int arg )
{
    static char buf[512];

    buf[0] = '\0';

    if ( arg & PLR_IS_NPC       ) strcat( buf, " npc"           );
    if ( arg & PLR_AUTOEXIT     ) strcat( buf, " autoexit"      );
    if ( arg & PLR_AUTOLOOT     ) strcat( buf, " autoloot"      );
    if ( arg & PLR_AUTOSAC      ) strcat( buf, " autosac"       );
    if ( arg & PLR_BLANK        ) strcat( buf, " blank"         );
    if ( arg & PLR_BRIEF        ) strcat( buf, " brief"         );
    if ( arg & PLR_COMBINE      ) strcat( buf, " combine"       );
    if ( arg & PLR_PROMPT       ) strcat( buf, " prompt"        );
    if ( arg & PLR_TELNET_GA    ) strcat( buf, " telnet_ga"     );
    if ( arg & PLR_HOLYLIGHT    ) strcat( buf, " holylight"     );
    if ( arg & PLR_WIZINVIS     ) strcat( buf, " wizinvis"      );
    if ( arg & PLR_ANSI         ) strcat( buf, " ansi"          );
    if ( arg & PLR_SILENCE      ) strcat( buf, " silenced"      );
    if ( arg & PLR_NO_TELL      ) strcat( buf, " no_tell"       );
    if ( arg & PLR_LOG          ) strcat( buf, " log"           );
    if ( arg & PLR_FREEZE       ) strcat( buf, " freeze"        );
    if ( arg & PLR_GODLESS      ) strcat( buf, " godless"       );

    return ( buf[0] != '\0' ) ? buf+1 : "none";
}

char * extra_plr_bit_name( int arg )
{
    static char buf[512];

    buf[0] = '\0';

    if ( arg & EXTRA_TRUSTED            ) strcat( buf, " q_trusted" );
    if ( arg & EXTRA_NEWPASS            ) strcat( buf, " newpass" );
    if ( arg & EXTRA_OSWITCH            ) strcat( buf, " oswitch" );
    if ( arg & EXTRA_SWITCH             ) strcat( buf, " switch" );
    if ( arg & EXTRA_FAKE_CON           ) strcat( buf, " fake_con" );
    if ( arg & TIED_UP                  ) strcat( buf, " tied_up" );
    if ( arg & GAGGED                   ) strcat( buf, " gagged" );
    if ( arg & BLINDFOLDED              ) strcat( buf, " blindfolded" );
    if ( arg & EXTRA_DONE               ) strcat( buf, " non_virgin" );
    if ( arg & EXTRA_EXP                ) strcat( buf, " got_exp" );
    if ( arg & EXTRA_PREGNANT           ) strcat( buf, " pregnant" );
    if ( arg & EXTRA_LABOUR             ) strcat( buf, " labour" );
    if ( arg & EXTRA_BORN               ) strcat( buf, " born" );
    if ( arg & EXTRA_PROMPT             ) strcat( buf, " prompt" );
    if ( arg & EXTRA_MARRIED            ) strcat( buf, " married" );
    if ( arg & EXTRA_CALL_ALL           ) strcat( buf, " call_all" );


    return ( buf[0] != '\0' ) ? buf+1 : "none";
}

char * get_position_name( int arg )
{
    switch( arg )
    {
        case 0: return "dead";
        case 1: return "mortal";
        case 2: return "incap";
        case 3: return "stunned";
        case 4: return "sleeping";
        case 5: return "meditating";
        case 6: return "sitting";
        case 7: return "resting";
        case 8: return "fighting";
        case 9: return "standing";
    }
    bug( "Get_position_name: unknown type %d.", arg );
    return "(unknown)";
}

/*
 * Itemaffect bit names :)
 */
char * itemaffect_bit_name( int arg )
{
    static char buf[512];

    buf[0] = '\0';

    if ( arg & ITEMA_SHOCKSHIELD        ) strcat( buf, " Shockshield"  );
    if ( arg & ITEMA_FIRESHIELD         ) strcat( buf, " Fireshield"    );
    if ( arg & ITEMA_ICESHIELD          ) strcat( buf, " Iceshield"     );
    if ( arg & ITEMA_ACIDSHIELD         ) strcat( buf, " Acidshield"    );
    if ( arg & ITEMA_DBPASS             ) strcat( buf, " Pass Door"     );
    if ( arg & ITEMA_CHAOSSHIELD        ) strcat( buf, " Chaoshield"    );
    if ( arg & ITEMA_ARTIFACT           ) strcat( buf, " Artifact"      );
    if ( arg & ITEMA_REGENERATE         ) strcat( buf, " Regeneration"  );
    if ( arg & ITEMA_SPEED              ) strcat( buf, " Speed"         );
    if ( arg & ITEMA_VORPAL             ) strcat( buf, " Vorpal"        );
    if ( arg & ITEMA_PEACE              ) strcat( buf, " Peace"         );
    if ( arg & ITEMA_RIGHT_SILVER       ) strcat( buf, " Right Silver"  );
    if ( arg & ITEMA_LEFT_SILVER        ) strcat( buf, " Left Silver"   );
    if ( arg & ITEMA_REFLECT            ) strcat( buf, " Darkshield"    );
    if ( arg & ITEMA_RESISTANCE         ) strcat( buf, " Resistance"    );
    if ( arg & ITEMA_VISION             ) strcat( buf, " Vision"        );
    if ( arg & ITEMA_STALKER            ) strcat( buf, " Stalker"       );
    if ( arg & ITEMA_VANISH             ) strcat( buf, " Vanish"        );
    if ( arg & ITEMA_RAGER              ) strcat( buf, " Rager"         );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}


void do_pstat ( CHAR_DATA *ch, char *argument )
{
    char        arg[MAX_INPUT_LENGTH];
    char        buf[MAX_STRING_LENGTH];
    CHAR_DATA   *victim;

    argument = one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
        send_to_char("Pstat whom?\n\r", ch );
        return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
       send_to_char("They aren't here.\n\r", ch );
        return;
    }

    if ( !IS_NPC( victim ) && IS_SET( victim->act, PLR_GODLESS ) &&
         get_trust( ch ) < NO_GODLESS )
    {
        send_to_char( "You failed.\n\r", ch );
        return;
    }

    sprintf( buf, "Name : %s.\n\r",
        IS_NPC( victim )        ? victim->short_descr : victim->name );
  send_to_char( buf, ch );
    sprintf( buf, "Sex : %s. Room : %d. Align : %d. Primal : %d. Quest : %d.\n\r",
        victim->sex == SEX_MALE         ? "Male"        :
      victim->sex == SEX_FEMALE       ? "Female"      : "None",
        victim->in_room == NULL         ? 0             : victim->in_room->vnum,
        victim->alignment,
        victim->practice,
        IS_NPC( victim )                ? 0             : victim->pcdata->quest
        );
    send_to_char( buf, ch );

    sprintf( buf, "Level : %d.", victim->level);
    send_to_char(buf, ch);
    if (victim->trust > 12) sprintf( buf, " Trust : 12. ");
    else sprintf( buf, " Trust : %d. ", victim->trust);
    send_to_char(buf, ch);

   sprintf( buf, "Gold : %d. Exp : %d.\n\r",
        victim->gold,
        victim->exp );
   send_to_char( buf, ch );

    sprintf( buf, "Hit : %d. Dam : %d. AC : %d. Position : %s\n\r",
       char_hitroll( victim ),
        char_damroll( victim ),
        char_ac( victim ),
        capitalize( get_position_name( victim->position ) ));
    send_to_char( buf, ch );


    sprintf( buf, "HP %ld/%ld. Mana %d/%d. Move %d/%d.\n\r",
        victim->hit, victim->max_hit,
        victim->mana, victim->max_mana,
        victim->move, victim->max_move );
    send_to_char( buf, ch );

    sprintf( buf, "Str: %d.  Int: %d.  Wis: %d.  Dex: %d.  Con: %d.\n\r",
        get_curr_str(victim),
        get_curr_int(victim),
        get_curr_wis(victim),
        get_curr_dex(victim),
        get_curr_con(victim) );
    send_to_char( buf, ch );

    sprintf( buf, "Fighting : %s. (%d)\n\r",
        victim->fighting ? victim->fighting->name  : "(None)",
        victim->fighting ? victim->fighting->level : 0 );
        send_to_char( buf, ch );

    sprintf( buf, "Pkill : %d. Pdeath : %d. Mkill : %d. Mdeath : %d.\n\r",
        IS_NPC( victim ) ? 0 : victim->pkill,
        IS_NPC( victim ) ? 0 : victim->pdeath,
        IS_NPC( victim ) ? 0 : victim->mkill,
       IS_NPC( victim ) ? 0 : victim->mdeath );
    send_to_char( buf, ch );

    sprintf( buf, "TotExp  : %12d. TotMobLev  : %10d. TotQuestPoints : %10d.\n\r",
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_TOTAL_XP],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_TOTAL_LEVEL],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_QUEST] );
    send_to_char( buf, ch );

    sprintf( buf, "HighExp : %12d. HighMobLev : %10d. Tot##Quests     : %10d.\n\r",
      IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_HIGH_XP],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_HIGH_LEVEL],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_NUM_QUEST] );
    send_to_char( buf, ch );

    if ( !IS_NPC( victim ) )
   {
        sprintf( buf, "Unarmed : %4d.", victim->wpn[0] );
        send_to_char( buf, ch );
        sprintf( buf, " Slice   : %4d.", victim->wpn[1] );
        send_to_char( buf, ch );
        sprintf( buf, " Stab    : %4d.", victim->wpn[2] );
        send_to_char( buf, ch );
        sprintf( buf, " Slash   : %4d.", victim->wpn[3] );
        send_to_char( buf, ch );
        sprintf( buf, " Whip    : %4d.\n\r", victim->wpn[4] );
        send_to_char( buf, ch );
        sprintf( buf, "Claw    : %4d.", victim->wpn[5] );
        send_to_char( buf, ch );
        sprintf( buf, " Blast   : %4d.", victim->wpn[6] );
        send_to_char( buf, ch );
        sprintf( buf, " Pound   : %4d.", victim->wpn[7] );
	send_to_char( buf, ch );
        sprintf( buf, " Crush   : %4d.", victim->wpn[8] );
        send_to_char( buf, ch );
        sprintf( buf, " Grep    : %4d.\n\r", victim->wpn[9] );
        send_to_char( buf, ch );
        sprintf( buf, "Bite    : %4d.", victim->wpn[10] );
     	send_to_char( buf, ch );
        sprintf( buf, " Pierce  : %4d.", victim->wpn[11] );
        send_to_char( buf, ch );
        sprintf( buf, " Suck    : %4d.\n\r",victim->wpn[12] );
        send_to_char( buf, ch );

        sprintf( buf, "%-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d.\n\r",
            "Purple",   victim->spl[PURPLE_MAGIC],
            "Red",      victim->spl[RED_MAGIC],
            "Blue",     victim->spl[BLUE_MAGIC],
           "Green",    victim->spl[GREEN_MAGIC],
            "Yellow",   victim->spl[YELLOW_MAGIC] );
        send_to_char( buf, ch );
        sprintf( buf, "%-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d.\n\r",
            "Viper",    victim->stance[STANCE_VIPER],
            "Crane",    victim->stance[STANCE_CRANE],
            "Crab",     victim->stance[STANCE_CRAB],
            "Mongoose", victim->stance[STANCE_MONGOOSE],
            "Bull",     victim->stance[STANCE_BULL] );
        send_to_char( buf, ch );

        sprintf( buf, "%-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %-3d. %-8s : %3d.\n\r",
            "Mantis",   victim->stance[STANCE_MANTIS],
            "Dragon",   victim->stance[STANCE_DRAGON],
            "Tiger",    victim->stance[STANCE_TIGER],
            "Monkey",   victim->stance[STANCE_MONKEY],
           "Swallow",  victim->stance[STANCE_SWALLOW] );
        send_to_char( buf, ch );

        sprintf( buf, "Act         : %s\n\r", plr_bit_name(victim->act ));
    	send_to_char( buf, ch );
	sprintf( buf, "Extra       : %s\n\r",
        victim->extra <= 0 ? "(None)" : extra_plr_bit_name( victim->extra ) );
    	send_to_char( buf, ch );
	sprintf( buf, "ItemAff     : %s\n\r",
        victim->itemaffect <= 0 ? "(None)" : itemaffect_bit_name(victim->itemaffect ) );
    	send_to_char( buf, ch );

              sprintf( buf, "Affected by : %s.\n\r",
        affect_bit_name( victim->affected_by ) );
    	send_to_char( buf, ch );

    return;
}
}


void do_waitplayer(CHAR_DATA *ch, char *argument)

{
    CHAR_DATA           *victim;
    DESCRIPTOR_DATA     *d;
    char                arg1[MAX_STRING_LENGTH];
    char                arg2[MAX_STRING_LENGTH];
    sh_int              value;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( IS_NPC( ch ) ) return;
/*
    if ( arg1[0] == '\0' || arg2 == '\0' )
    {
        send_to_char( "Syntax: waitplayer [victim] [seconds]\n\r", ch );
        return;
    }
*/
    if ( !str_cmp( arg1, "all" ) )
    {
        if ( !is_number( arg2 ) )
        {
            send_to_char( "Number of seconds must be a numeric.\n\r", ch );
            return;
        }

        value = atoi( arg2 );

        if ( value < 1 || value > 30 )
        {
            send_to_char( "Range must be 1 to 30 seconds.\n\r", ch );
            return;
        }

        for ( d = descriptor_list ; d != NULL ; d = d->next )
        {
            if ( d->connected < CON_PLAYING ) continue;
            if ( d->connected > CON_PLAYING ) continue;
            if ( ( victim = d->character ) == NULL ) continue;
            if ( victim == ch ) continue;
            if ( IS_NPC( victim ) ) continue;
            if ( get_trust( ch ) <= get_trust( victim ) ) continue;
            if ( !can_see( ch, victim ) ) continue;
            if ( IS_SET( ch->act, PLR_GODLESS )
            &&  get_trust( ch ) < NO_GODLESS ) continue;

            WAIT_STATE( victim, value * 4 );
       }
        return;
    }

    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
        send_to_char( "They are not here.\n\r", ch );
        return;
    }

    if ( IS_NPC( victim ) )
    {
        send_to_char( "Not on NPC's.\n\r", ch );
        return;
    }

    if ( !IS_NPC( victim ) && IS_SET( victim->act, PLR_GODLESS )
    &&   get_trust( ch ) < NO_GODLESS )
    {
        send_to_char( "You failed.\n\r", ch );
        return;
    }

    if ( get_trust( victim ) >= get_trust( ch ) )
    {
        send_to_char( "You failed.\n\r", ch );
        return;
    }

    if ( !is_number( arg2 ) )
    {
        send_to_char( "Number of seconds must be numeric.\n\r", ch );
       return;
    }

    value = atoi( arg2 );

    if ( value < 1 || value > 30 )
    {
        send_to_char( "Value range is 1 to 30 seconds.\n\r", ch );
        return;
    }

    WAIT_STATE( victim, value * 4 );
    send_to_char( "Ok.\n\r", ch );
    return;
}
void do_pshow(CHAR_DATA *ch, char *argument)
{
	char buf[MAX_STRING_LENGTH];
	char arg[MAX_STRING_LENGTH];
	DESCRIPTOR_DATA *d;

if (IS_NPC(ch)) return;
sprintf(buf, "[Name        ][Class        ][Gen][ Hit ][Mana ][Move ][HR  ][DR  ][AC   ][Exp       ]\n\r");
send_to_char(buf, ch);
	for (d = descriptor_list; d != NULL; d = d->next)
	{
		CHAR_DATA *wch;
		if (d->connected != CON_PLAYING) continue;
		wch = (d->original != NULL) ? d->original : d->character;

           if ( wch->class == CLASS_VAMPIRE )
                        strcpy( arg, "Vampire" );
                    else if ( wch->class == CLASS_WEREWOLF )
                        strcpy( arg, "Werewolf" );
                    else if ( wch->class == CLASS_MAGE )
                        strcpy( arg, "Mage" );
                    else if ( wch->class == CLASS_DEMON )
                        strcpy( arg, "Demon" );
                    else if ( wch->class == CLASS_NINJA )
                        strcpy( arg, "Ninja" );
                    else if ( wch->class == CLASS_MONK )
                        strcpy( arg, "Monk" );
                    else if ( wch->class == CLASS_DROW )
                        strcpy( arg, "Drow" );
                    else if ( wch->class == CLASS_HIGHLANDER )
                        strcpy( arg, "Highlander" );
                    else
                        strcpy( arg, "None");


sprintf(buf,"[%-12s][%-13s][%3d][%5ld][%5d][%5d][%4d][%4d][%5d][%10d]\n\r",
		wch->name,
		arg,
		wch->pcdata->stats[UNI_GEN],
		wch->max_hit,
		wch->max_mana,
		wch->max_move,
		char_hitroll(wch),
		char_damroll(wch),
		char_ac(wch),
                wch->exp );
		send_to_char(buf,ch);
	}
    return;
}
void do_makepreg ( CHAR_DATA *ch, char *argument )
{
           CHAR_DATA   *mother;
	   CHAR_DATA   *father;
           char        arg1[MAX_INPUT_LENGTH];
           char        arg2[MAX_INPUT_LENGTH];

         if (IS_NPC( ch ) ) return;
         argument = one_argument( argument, arg1 );
         argument = one_argument(argument, arg2 );

         if ( arg1[0] == '\0' || arg2[0] == '\0' )
         {
        	send_to_char( "Syntax: makepreg [mother] [father]\n\r", ch );
        	return;
         }
         if (( mother = get_char_world( ch, arg1 ) ) == NULL )
         {
        	send_to_char( "Mother is not here.\n\r", ch );
        	return;
         }

         if ( ( father = get_char_world( ch, arg2 ) ) == NULL )
         {
	         send_to_char( "Father is not here.\n\r", ch );
                 return;
         }

         if ( IS_NPC( mother ) || IS_NPC( father ) )
         {
                 send_to_char( "Not on NPC's.\n\r", ch );
                 return;
         }

         if ( mother->sex == father->sex )
         {
                send_to_char("Cant make same sex babies\n\r", ch);
                return;
         }

         if ( mother->sex == SEX_MALE )
         {
                send_to_char(" Only women can be mothers.\n\r", ch);
                return;
         }

         if ( father->sex == SEX_FEMALE )
         {
                send_to_char("Only men can be fathers.\n\r", ch);
                return;
         }

         if ( mother == father )
         {
                send_to_char("You like asexual reprodcution?\n\r", ch);
                return;
         }

         if ( IS_EXTRA( mother, EXTRA_PREGNANT ) )
         {
                send_to_char( "They are already pregnant.\n\r", ch );
                return;
         }

          make_preg( mother, father );
          send_to_char( "You are now pregnant.\n\r", mother );
          send_to_char( "You are going to be a father.\n\r", father );

          if ( ch != mother && ch != father )
              send_to_char( "Done.\n\r", ch );
              return;
}
void do_topxp(CHAR_DATA *ch, char *argument)
{
    char buf[MAX_STRING_LENGTH];
	CHAR_DATA *vch;
	CHAR_DATA *top[5];
    DESCRIPTOR_DATA *d;
	int i;
	bool showme;
	int players = 0;

	if (IS_NPC(ch)) return;
	send_to_char("Counting only online players:\n\r", ch);
	for (i = 0; i < 5; i++) top[i] = NULL;
	for (i = 0; i < 5; i++) {
		for (d = descriptor_list; d != NULL; d = d->next) {
			if (d->connected != CON_PLAYING) continue;
			if ((vch = d->character) == NULL) continue;
			if (IS_IMMORTAL(vch)) continue;
			if (!strcmp(vch->name, "SuoMarte")) continue;
			players++;
			if (top[i] == NULL || vch->pcdata->score[SCORE_TOTAL_XP] >
top[i]->pcdata->score[SCORE_TOTAL_XP]) {
				if (top[0] == vch) continue;
				if (top[1] == vch) continue;
				if (top[2] == vch) continue;
				if (top[3] == vch) continue;
				top[i] = vch;
			}
		}
	}
	players = UMIN(players, 5);
	for (i = 0; i < players; i++)
		if (top[i] == NULL) top[i] = ch;
	for (i = 0; i < players; i++) {
		sprintf(buf, "  %d: #r%-12s#n with #w%d#n XP and #w%d#n earnt QP.\n\r", i+1,
top[i]->name, top[i]->pcdata->score[SCORE_TOTAL_XP], top[i]->pcdata->score[SCORE_QUEST]);
		send_to_char(buf, ch);
	}
	showme = TRUE;
	for (i = 0; i < players; i++)
		if (top[i] == ch) showme = FALSE;
	if (showme) {
		sprintf(buf, "You: #r%-12s#n with #w%d#n XP and #w%d#n earnt QP.\n\r", ch->name,
ch->pcdata->score[SCORE_TOTAL_XP], ch->pcdata->score[SCORE_QUEST]);
		send_to_char(buf, ch);
	}
}

void do_reimb(CHAR_DATA *ch, char *argument)
{
	CHAR_DATA	*vch;
	char		arg[MAX_INPUT_LENGTH];
	char		arg2[MAX_INPUT_LENGTH];
	int v;

	argument = one_argument(argument, arg);
	if (arg[0] == '\0') {
		send_to_char("Reimburse <target> <xp|qp> <amount>\n\r", ch);
		return;
	}
	if ((vch = get_char_world(ch, arg)) == NULL) {
		send_to_char("They aren't logged on.\n\r", ch);
		return;
	}
	if (IS_NPC(vch)) {
		send_to_char("That is a mob.\n\r", ch);
		return;
	}
	argument = one_argument(argument, arg);
	argument = one_argument(argument, arg2);
	v = atoi(arg2);
	if (arg[0] == '\0' || arg2[0] == '\0'
	  || (!is_number(arg2) && v >= 0)) {
		do_reimb(ch, "");
		return;
	}
	if (!str_cmp(arg, "xp")) {
		vch->exp += v;
		vch->pcdata->score[SCORE_TOTAL_XP] += v;
	} else if (!str_cmp(arg, "qp")) {
		vch->pcdata->quest += v;
		vch->pcdata->score[SCORE_QUEST] += v;
	} else {
		send_to_char("Please specify XP or QP.\n\r", ch);
		return;
	}
	if (vch->mkill < 5) {
		vch->mkill = 5;
		do_autosave(ch, "");
	}
	sprintf(arg2, "%s reimbursed %d %s.\n\r", vch->name, v, arg);
	send_to_char(arg2, ch);
	sprintf(arg2, "%s has reimbursed you %d %s.\n\r", ch->name, v, arg);
	send_to_char(arg2, vch);
}

void do_resetpassword( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *victim;
    char *pwdnew;

    if ( IS_NPC(ch) )
    return;

    argument=one_argument( argument, arg1 );
    argument=one_argument( argument, arg2 );

    victim = get_char_world(ch, arg1);


    if (  ( ch->pcdata->pwd != '\0' )
    && ( arg1[0] == '\0' || arg2[0] == '\0')  )
    {
        send_to_char( "Syntax: password <char> <new>.\n\r", ch );
        return;
    }
    if( victim == '\0' )
    {
                send_to_char( "That person isn't here, they have to be here to reset pwd's.\n\r", ch);
                return;
    }
    if ( IS_NPC( victim ) )
    {
                send_to_char( "You cannot change the password of NPCs!\n\r",ch);
                return;
    }

    if (( victim->level > LEVEL_IMMORTAL ) || ( get_trust(victim) > LEVEL_IMMORTAL ))

        {
                send_to_char( "You can't change the password of that player.\n\r",ch);
                return;
    }

    if ( strlen(arg2) < 5 )
    {
        send_to_char( "New password must be at least five characters long.\n\r", ch );
        return;
    }

    pwdnew = crypt( arg2, victim->name );
    free_string( victim->pcdata->pwd );
    victim->pcdata->pwd = str_dup( pwdnew );
    save_char_obj( victim );
    send_to_char( "Ok.\n\r", ch );
    sprintf( buf, "Your password has been changed to %s.", arg2 );
    send_to_char( buf, victim);
    return;
}

void do_lord( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );
    if ( IS_NPC(ch) ) return;

    if ( arg[0] == '\0' )
    {
    send_to_char( "Who's lord(s) do you wish to change or set?\n\r", ch );
        return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        send_to_char( "They aren't here.\n\r", ch );
        return;
    }
    if ( IS_NPC(victim) ) return;

    smash_tilde( argument );
    if ( strlen(argument) < 0 || strlen(argument) > 70 )
    {
        send_to_char( "Clan name should be between 0 and 70 characters long.\n\r", ch);
        send_to_char( "Leave a blank to remove lord(s).\n\r", ch);
        return;
    }
    free_string( victim->lord );
    victim->lord = str_dup( argument );
        send_to_char("Lord set.\n\r", ch);
    return;
}

void do_numlock( CHAR_DATA *ch, char *argument )
{
           char       buf  [ MAX_STRING_LENGTH ];
           char       arg1 [ MAX_INPUT_LENGTH  ];
    extern int        numlock;
           int        temp;



    one_argument( argument, arg1 );

    temp = atoi( arg1 );

    if ( arg1[0] == '\0' )
    {
        sprintf( buf, "Current numlock setting is:  %d.\n\r", numlock );
       send_to_char( buf, ch );
        return;
    }

    if ( ( temp < 0 ) || ( temp > 11 ) )
    {
        sprintf( buf, "Level must be between 0 and 11.\n\r" );
        send_to_char( buf, ch );
        return;
    }

    numlock = temp;

    if ( numlock != 0 )
    {
        sprintf( buf, "Game numlocked to levels %d and below.\n\r", numlock );
       send_to_char( buf, ch );
    }
    else

        send_to_char( "Game now open to all levels.\n\r", ch );

    return;

}

void do_newlock( CHAR_DATA *ch, char *argument )
{
           extern int        numlock;
           char       buf [ MAX_STRING_LENGTH ];


    if ( numlock != 0 && get_trust( ch ) < MAX_LEVEL )
    {
        send_to_char( "You may not change the current numlock setting\n\r",
                     ch );
        sprintf( buf, "Game numlocked to levels %d and below.\n\r", numlock );
        send_to_char( buf, ch );
        return;
    }

    if ( numlock != 0 )
    {
        sprintf( buf, "Game numlocked to levels %d and below.\n\r", numlock );
        send_to_char( buf, ch );
        send_to_char( "Changing to: ", ch );
    }

    numlock = 1;
    send_to_char( "Game locked to new characters.\n\r", ch );
    return;

}
void do_renamep( CHAR_DATA *ch, char *argument )
{
    char                arg[MAX_INPUT_LENGTH];
    char                buf[MAX_STRING_LENGTH];
    char                new_name[MAX_INPUT_LENGTH];
    DESCRIPTOR_DATA     *d;
    CHAR_DATA           *victim;
    OBJ_DATA            *obj;

    argument = one_argument( argument, arg );
    argument = one_argument( argument, new_name );

    if ( IS_NPC( ch ) ) return;

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
       send_to_char( "Rename who?\n\r", ch );   
        return;
    }
    
    if ( new_name[0] == '\0' )
    {
        send_to_char( "Rename them to what?\n\r", ch );
        return;
    }
    
    if ( IS_NPC( victim ) )
    {
        send_to_char( "Use mset instead.\n\r", ch );
        return;
    }
     
    if ( victim->desc == NULL || victim->desc->connected != CON_PLAYING )
    {
        send_to_char( "They are not available for a rename at the moment.\n\r", ch );
        return;
    }
    if ( IS_IMMORTAL( victim ) && victim != ch)
    {
        send_to_char( "You are unable to rename Gods!\n\r",ch);
        return;
    }
    
    if ( char_exists(FALSE,new_name) )
    {
        send_to_char( "There is already a player saved by that name.\n\r", ch );
        return;
    }

   
    for ( d = descriptor_list ; d != NULL ; d = d->next )
    {
        if ( d->character != NULL && victim->desc != d )
        {
            if ( !IS_NPC( d->character )
            &&   strlen( d->character->name ) > 0
            &&  !str_cmp( d->character->name, new_name ) )
            {  
                send_to_char( "There is already a player with that name.\n\r", ch );
                return;
            }
        }
    }
    if ( !check_parse_name( new_name ) )
    {
       send_to_char( "That is an illegal new name!\n\r", ch );
       return;
    }
    for ( obj = object_list ; obj != NULL ; obj = obj->next )
    {
        if ( strlen( obj->questowner ) < 3 ) continue;
        if ( str_cmp( victim->name, obj->questowner ) ) continue;
        free_string(obj->questowner);
        obj->questowner = str_dup(capitalize(new_name)); 
    }
    sprintf( buf, "%s%s", PLAYER_DIR, capitalize( victim->name ) );
    free_string( victim->name );
    victim->name = str_dup( capitalize( new_name ) );
    unlink( buf );
    do_autosave( victim, "" );
    sprintf( buf, "You have been renamed to %s.\n\r", capitalize( new_name ) );
    send_to_char( buf, victim);
    send_to_char( "Rename complete.\n\r", ch );
   return;
}
    
void do_dele( CHAR_DATA *ch, char *argument )
{
    send_to_char( "If you want to DELETE yourself, you have to spell it out.\n\r", ch );
    return;
}
void do_delete( CHAR_DATA *ch, char *argument)
{
    char strsave[MAX_INPUT_LENGTH];
    char        arg[MAX_INPUT_LENGTH];
    char        buf[MAX_STRING_LENGTH];
    char *pArg;


    if ( IS_NPC( ch ) ) return;
       {
		pArg = arg;
		while (*argument == ' ') argument++;
		while (*argument != '\0') {
			if (*argument == ' ') {
				argument++;
				break;
			}
			*pArg++ = *argument++;
		}
		*pArg = '\0';
	}

/*
    argument = one_argument( argument, arg );
*/
    if (IS_IMMORTAL(ch) )
    {
        stc("You are an imm... you cant delete yourself.\n\r",ch);
        return;
    }

    if ( arg[0] == '\0' )
    {
        send_to_char( "Syntax: delete [password]\n\r", ch );
        send_to_char( "   If you self delete, you will #rNOT#n get a reimburse\n\r", ch);
        send_to_char( "   Use this command very carefully.\n\r", ch);
        sprintf(buf, "%s is contemplating deletion.", ch->name);
        log_string(buf);
        return;
    }
    if ( strcmp( crypt( arg, ch->pcdata->pwd ), ch->pcdata->pwd ) )
    {
        send_to_char("Wrong Password, wait 10 seconds.\n\r", ch );
        WAIT_STATE( ch, 40 );
	sprintf(buf, "%s tried to delete with the wrong pwd.", ch->name);
        log_string(buf);     
        return;
    }
    sprintf( strsave, "%s%s", PLAYER_DIR, capitalize( ch->name ) );
    sprintf(buf, "%s turns themself into line noise.", ch->name );
    log_string(buf);
    stop_fighting(ch,TRUE);
    do_quit(ch,"");
    unlink(strsave);
    return;
}

void do_katana( CHAR_DATA *ch, char *argument )

{
     OBJ_DATA *obj;

     if (IS_NPC(ch)) return;

     if (!IS_CLASS(ch, CLASS_HIGHLANDER))
     {
         stc("Huh?\n\r", ch);
        return;
     }

     if ( ch->practice < 60 )
     {
        send_to_char("It costs 60 points of primal to create a katana.\n\r",ch);
        return;
     }
     ch->practice   -= 60;
     obj = create_object(get_obj_index(29695)  ,0 );
     if (IS_SET(obj->quest, QUEST_ARTIFACT))
        REMOVE_BIT(obj->quest, QUEST_ARTIFACT);
     obj_to_char(obj, ch);  
     act("A katana appears in your hands in a flash of light.",ch,NULL,NULL,TO_CHAR);
     act("A katana appears in $n's hands in a flash of light.",ch,NULL,NULL,TO_ROOM);

     return;
}
 
