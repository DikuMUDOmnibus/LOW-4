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

/* Special Bits */

#define SPC_CHAMPION	1 /* PLR_CHAMPION 4 */
#define SPC_DEMON_LORD	2 /* OLD_DEMON Flag */
#define SPC_WOLFMAN	4 /* old PLR_WOLFMAN */
#define SPC_PRINCE      8 /* old EXTRA_PRINCE */
#define SPC_SIRE	16 /* Old EXTRA_SIRE */
#define SPC_ANARCH      32 /* old extra_anarch */
#define SPC_INCONNU     64 /* old extra_inconnu */
#define SPC_DROW_WAR	128
#define SPC_DROW_MAG	256
#define SPC_DROW_CLE	512
#define SPC_ROGUE      1024
#define SPC_NOFIND     2048

/* Class Bits */
#define CLASS_NONE	 0
#define CLASS_DEMON	 1 /* PLR_DEMON 2 */
#define CLASS_ABOMINATION 3 /* CLASS_VAMPIRE  + CLASS_WEREWOLF */
#define CLASS_MAGE	 2 
#define CLASS_WEREWOLF	 4 /* PLR_WEREWOLF */
#define CLASS_VAMPIRE	 8 
#define CLASS_BLACK_SPIRAL_DANCER 10 /* CLASS_WEREWOLF + CLASS_DEMON */
#define CLASS_HIGHLANDER 16 /* EXTRA_HIGHLANDER */
#define CLASS_DROW	 32
#define CLASS_MOOGLE	 64
#define CLASS_NINJA     128
#define CLASS_PALADIN   256
#define CLASS_MONK      512
#define CLASS_DRAGON   1024
#define CLASS_ELADRIN  2048

/* Power Bits for Monks */
#define MPOWER_POWER              2 /* Monk Power */
#define PMONK     0

/* Powers/Principles for Ninjas */
#define NPOWER_SORA	      0
#define NPOWER_CHIKYU	      1
#define NPOWER_NINGENNO	      2
#define BLACK_BELT 	      4
#define HARA_KIRI	      5
#define NINJAKI		      6

/* Paladin Bits */
/* Stats */
#define PALADIN_CURRENT		      8	/* POWER_CURRENT 0*/
#define PALADIN_TOTAL		      9	/* POWER_TOTAL   1*/
#define PALADIN_POWER		     10 /* TOTAL ARMOUR BOUNS */

/* Powers */
#define PPOWER_FLAGS		      0 /* C_POWERS  1 */
#define PPOWER_CURRENT		      1 /* C_CURRENT 2 */

#define PALADIN_SCRY              1
#define PALADIN_CHARGE            2
#define PALADIN_SPEED             4
#define PALADIN_TOUGHNESS         8
#define PALADIN_HOLYBLESS        16
#define PALADIN_JOUST            32
#define PALADIN_HEAL             64

/* 
 * Bits For Highlanders
 */
#define HPOWER_WPNSKILL 0

/* 
 * Bits For Mages
 */
#define MPOWER_RUNE0	0
#define MPOWER_RUNE1	1
#define MPOWER_RUNE2	2
#define MPOWER_RUNE3	3
#define MPOWER_RUNE4	4

/*
 * Bits for Werewolves 
 */
/* Stats */

#define UNI_GEN        	0 /* vampgen */
#define UNI_AFF		1 /* vampaff */
#define UNI_CURRENT	2 /* vamppass */
#define UNI_RAGE	3 /* ch->wolf = how big rage they are in*/
#define UNI_FORM0      	4/* wolfform[0] */
#define UNI_FORM1      	5 /* wolfform[1] */

#define	WOLF_POLYAFF	6

/*new vamp powers*/
#define		VAM_HORNS			1
#define		VAM_WINGS			2
#define		VAM_EXOSKELETON		        3
#define		VAM_TAIL			4
#define		VAM_HEAD			5

/* 
 * Powers 
 * Totems for werewolves.
 */

#define WPOWER_TIGER	      11	
#define WPOWER_MANTIS	      0
#define WPOWER_BEAR	      1
#define WPOWER_LYNX	      2
#define WPOWER_GAIA	      12
#define WPOWER_BOAR	      3
#define WPOWER_OWL	      4
#define WPOWER_SPIDER	      5
#define WPOWER_WOLF	      6
#define WPOWER_HAWK	      7
#define WPOWER_SILVER	     10

#define VPOWER_OBJ_VNUM		1

#define DROW_POWER	8
#define DROW_TOTAL	9
#define DROW_MAGIC	11

#define MOOGLE_DANCES 8
/*
 * Bits for Demonic Champions.
 */

/*Stats*/

#define DEMON_CURRENT		      8	/* POWER_CURRENT 0*/
#define DEMON_TOTAL		      9	/* POWER_TOTAL   1*/
#define DEMON_POWER		     10 /* TOTAL ARMOUR BOUNS */
#define NINJA_KI               8   /* Ninja Ki is 8 */

/*Powers*/
#define DPOWER_FLAGS		      0 /* C_POWERS  1 */
#define DPOWER_CURRENT		      1 /* C_CURRENT 2 */
#define DPOWER_HEAD		      2 /* C_HEAD    3 */
#define DPOWER_TAIL		      3 /* C_TAIL    4 */
#define DPOWER_OBJ_VNUM		      4 /* DISC[10]  5 */

#define DEM_UNFOLDED		      1

#define DEM_FANGS		      1
#define DEM_CLAWS		      2
#define DEM_HORNS		      4
#define DEM_TAIL		      8
#define DEM_HOOVES		     16
#define DEM_EYES		     32
#define DEM_WINGS		     64
#define DEM_MIGHT		    128
#define DEM_TOUGH		    256
#define DEM_SPEED		    512
#define DEM_TRAVEL		   1024
#define DEM_SCRY		   2048
#define DEM_SHADOWSIGHT		   4096
/* Object Powers */
#define DEM_MOVE		   8192   /* 1 Can roll as an object */
#define DEM_LEAP		   16384   /* 2 Can leap out of someone's hands */
#define DEM_MAGIC		   32768   /* 4 Can cast spells as an object */
#define DEM_LIFESPAN		  65536   /* 8 Can change lifespan */
#define DEM_GRAFT		  131072  
#define DEM_IMMOLATE		  262144
#define DEM_INFERNO		  524288
#define DEM_CAUST	         1048576 
#define DEM_ENTOMB	         2097152
#define DEM_FREEZEWEAPON         4194304
#define DEM_UNNERVE	         8388608
#define DEM_LEECH	        16777216
#define DEM_TRUESIGHT		33554432
#define DEM_BLINK		67108864
#define DEM_FORM	       134217728	
#define DEM_SHIELD 	       268435456
 

#define HEAD_NORMAL		      0
#define HEAD_WOLF		      1
#define HEAD_EAGLE		      2
#define HEAD_LION		      4
#define HEAD_SNAKE		      8

#define TAIL_NONE		      0
#define TAIL_POISONOUS		      1
#define TAIL_SCORPION		      2

/* Drow Powers */
/*
#define DPOWER_DROWFIRE		1
#define DPOWER_DARKNESS		2
#define DPOWER_LIGHTS		4
#define DPOWER_DROWSIGHT	8
#define DPOWER_LEVITATION	16
#define DPOWER_DROWSHIELD	32
#define DPOWER_DROWPOISON	64
#define DPOWER_FANGS           128
*/
#define DPOWER_DROWFIRE         1
#define DPOWER_DARKNESS         2
#define DPOWER_LIGHTS           4
#define DPOWER_DROWSIGHT        8
#define DPOWER_LEVITATION       16
#define DPOWER_DROWSHIELD       32
#define DPOWER_DROWPOISON       64
#define DPOWER_SHADOWWALK       128
#define DPOWER_GAROTTE          256
#define DPOWER_ARMS             512
#define DPOWER_DROWHATE         1024
#define DPOWER_SPIDERFORM       2048
#define DPOWER_WEB              4096
#define DPOWER_DGAROTTE         8192
#define DPOWER_CONFUSE          16384
#define DPOWER_GLAMOUR          32768
#define DPOWER_EARTHSHATTER     65536
#define DPOWER_SPEED            131072
#define DPOWER_TOUGHSKIN        262144
#define DPOWER_REGEN		524288

/* Moogle Dances */

#define DANCE_SONG 	1
#define DANCE_SUITE	2
#define DANCE_ARIA	4
#define DANCE_SONATA	8
#define DANCE_BLUES	16
#define DANCE_RONDO	32
#define DANCE_REQUIEM	64
#define DANCE_JAZZ	128


