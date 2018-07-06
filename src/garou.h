/******************************************************************************
 *                                                                            *
 *                 This is the file that has the ww powers            *
 *                                                                            *
 ******************************************************************************/
 /***************************************************************************
 *  God Wars Mud originally written by KaVir aka Richard Woolcock.         *
 *  Changes done to the code done by Sage aka Walter Howard, this mud is   *
 *  for the public, however if you run this code it means you agree        *
 *  to the license.low, license.gw, and license.merc have fun. :)          *
***************************************************************************/

/* 
The Breed, Auspice and Tribe defines are for ch->gifts[ ], replacing Totems.
*/

#define MAX_GIFTS	20

/* Breed */
#define HOMID     	0
#define METIS     	1
#define LUPUS		2

/* Auspice */
#define RAGABASH	3
#define THEURGE		4
#define PHILODOX	5
#define GALLIARD	6
#define AHROUN		7

/* Tribe */
#define BLACKFURIES	8
#define BONEGNAWERS	9
#define CHILDREN	10
#define CHILDRENOFGAIA  10
#define FIANNA		11
#define GETOFFENRIS	12
#define GLASSWALKERS	13
#define REDTALONS	14
#define SHADOWLORDS	15
#define SILENTSTRIDERS	16
#define SILVERFANGS	17
#define STARGAZERS	18
#define UKTENA		19
#define WENDIGO		20

/* Garou Macros */
#define IS_GAR1(ch, gift)	(IS_SET((ch)->garou1, (gift)))

/* Gnosis */
#define GCURRENT		0
#define GMAXIMUM		1

/* Garou 1 Flags */
#define WOLF_RAZORCLAWS			1
#define WOLF_COCOON			2
#define GAROU_BLISSFUL		      (C)
#define GAROU_WHELP2		      (D)
#define GAROU_WHELP1		      (E)
#define WW_GRANITE		      (F)
#define GAROU_CLENCHED		      (G)
#define GAROU_AVENGER		      (H)
#define GAROU_PAWS		      (I)
#define WOLF_VISCERAL		      (J)
#define WOLF_QUICKSAND		      (K)


//Area Affects
