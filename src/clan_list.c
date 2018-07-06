/***************************************************************************
 *  God Wars Mud originally written by KaVir aka Richard Woolcock.         *
 *  Changes done to the code done by Sage aka Walter Howard, this mud is   *
 *  for the public, however if you run this code it means you agree        *
 *  to the license.low, license.gw, and license.merc have fun. :)          *
***************************************************************************/
/*This code was written by KaVir and he is to be given full credit for it*/
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

#define FILE_CLAN      "../area/clan.txt"

CLAN_DATA         *     clans_data       [MAX_CLAN]; 

/*
 * Clan table.
 */
char *	const	clan_table	[] =
{
    "None",
    "None",
    "None",
    "None",
    "None",
    "None",
    "None",
    "None",
    "None",
    "None",
    "None",
    "None"
};

bool clan_exist( )
{
    FILE *fp;
    char buf [MAX_STRING_LENGTH];
    bool found = FALSE;

    fclose( fpReserve );
    sprintf( buf, "%s", FILE_CLAN );
    if ( ( fp = fopen( buf, "r" ) ) != NULL )
    {
        found = TRUE;
        fclose( fp );
    }
    fpReserve = fopen( NULL_FILE, "r" );
    return found;
}


void do_clanlist( CHAR_DATA *ch, char *argument )
{
    char       buf[MAX_STRING_LENGTH];
    int i;

    send_to_char("--------------------"
	"-------------- CLAN "
	"LIST ---------------"
	"--------------------\n\r", ch );
    for ( i = 0; i < MAX_CLAN; i++ )
    {
        sprintf( buf, "%-15s Leader:%-16s Prince:%-16s Members:%-3d\n\r",
            clan_table[i], clans_data[i]->clan_head, clans_data[i]->primogen,
            clans_data[i]->members );
        send_to_char( buf, ch );
    }
    send_to_char("--------------------"
	"--------------------"
	"--------------------"
	"--------------------\n\r", ch );

    return;
}


void clan_write( )
{
    FILE *fp;
    int i;

    fflush( fpReserve );
    fclose( fpReserve );

    if ( ( fp = fopen( CLAN_DIR, "w" ) ) == NULL )
	bug("Cannot Open clan data file.", 0);
    else
    {
	for ( i = 0; i < MAX_CLAN; i++ )
	{
	    fprintf( fp, "%s %d %s %s\n", 
		clan_table[i], clans_data[i]->members, 
		clans_data[i]->clan_head, clans_data[i]->primogen );
	}
    }

    fflush( fp );
    fclose( fp );
    fpReserve = fopen( NULL_FILE, "r" );
    return;
}

void clan_read( )
{
    FILE *fp;
    int i;

    if ( !clan_exist() )
    {
	for ( i = 0; i < MAX_CLAN; i++ )
	{
	    clans_data[i] = alloc_perm( sizeof(CLAN_DATA) );
	    clans_data[i]->members = 0;
	    clans_data[i]->clan_head = str_dup( "None" );
	    clans_data[i]->primogen = str_dup( "None" );
	}
	clan_write();
	return;
    }

    fflush( fpReserve );
    fclose( fpReserve );

    if ( ( fp = fopen( CLAN_DIR, "r" ) ) != NULL )
    {
	if ( fread_letter( fp ) == EOF )
	{
	    bug( "clan_read: blank file.", 0 );
	    for ( i = 0; i < MAX_CLAN; i++ )
	    {
		clans_data[i] = alloc_perm( sizeof(CLAN_DATA) );
		clans_data[i]->members = 0;
		clans_data[i]->clan_head = str_dup( "None" );
		clans_data[i]->primogen = str_dup( "None" );
	    }
	    clan_write();
	    return;
	}
	for ( i = 0; i < MAX_CLAN; i++ )
	{
	    fread_word( fp );
	    clans_data[i] = alloc_perm( sizeof(CLAN_DATA) );
	    clans_data[i]->members = fread_number( fp );
	    clans_data[i]->clan_head = str_dup( fread_word( fp ) );
	    clans_data[i]->primogen = str_dup( fread_word( fp ) );
	}
    }
    else
    {
	bug( "clan_read: fopen", 0 );
	perror( CLAN_DIR );
    }

    fflush( fp );
    fclose( fp );
    fpReserve = fopen( NULL_FILE, "r" );
    return;
}

void update_clanlist( CHAR_DATA *ch, bool add_char )
{
    int clan = find_clanname( ch );

    if ( clan < 0 ) return;

    if ( add_char )
	clans_data[clan]->members++;
    else
    {
	clans_data[clan]->members--;
	if ( !str_cmp( ch->name, clans_data[clan]->clan_head ) )
	{
	    free_string( clans_data[clan]->clan_head );
	    clans_data[clan]->clan_head = str_dup( "None" );
	}
	if ( !str_cmp( ch->name, clans_data[clan]->primogen ) )
	{
	    free_string( clans_data[clan]->primogen );
	    clans_data[clan]->primogen = str_dup( "None" );
	}
    }
    clan_write();
    return;
}

int find_clanname( CHAR_DATA *ch )
{
    int clan;

    if ( strlen( ch->clan ) < 2 || !str_cmp( ch->clan, "None" ) ) clan = 0;
    else if ( !str_cmp( ch->clan, "None" ) )	clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )	clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )		clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )		clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )		clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )	clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )	clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )	clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )	clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )	clan = CLAN_NONE;
    else if ( !str_cmp( ch->clan, "None" ) )		clan = CLAN_NONE;
    else return -1;
    return clan;
}

