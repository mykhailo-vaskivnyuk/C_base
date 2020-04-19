#include "clubs.h"

sClub cls_new_club(char * club_name, ...)
{
    sClub club = NULL;
    char * par_ptr = (char *)&club_name;
    club = (sClub)malloc(sizeof(struct club));

    if( club == NULL ) return club;

    if( *(char *)par_ptr )
    {
        strcpy(club->club_name, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        strcpy(club->club_city, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        strcpy(club->club_country, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        club->club_revenue = *(double *)(par_ptr);
        par_ptr += sizeof(double);
        club->club_place = *(int *)par_ptr;
    }
    else
    {
        club->club_name[0] = '\0';
        club->club_city[0] = '\0';
        club->club_country[0] = '\0';
        club->club_place = 0;
        club->club_revenue = 0;
    }

    return club;
}
