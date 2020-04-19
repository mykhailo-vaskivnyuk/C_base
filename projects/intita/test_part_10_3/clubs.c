#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clubs.h"

void cls_init(sClubs ** clubs)
{
    *clubs = (sClubs *)malloc(sizeof(sClubs));
    (*clubs)->clubs_head = NULL;
    (*clubs)->clubs_count = 0;
}

sClubNode * cls_new(char * club_name, ...)
{
    sClubNode * club_ptr = NULL;
    char * par_ptr = (char *)&club_name;
    club_ptr = cls_create();
    if( *(char *)par_ptr )
    {
        strcpy(club_ptr->club_name, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        strcpy(club_ptr->club_city, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        strcpy(club_ptr->club_country, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        club_ptr->club_revenue = *(double *)(par_ptr);
        par_ptr += sizeof(double);
        club_ptr->club_place = *(int *)par_ptr;
    }

    return club_ptr;
}

sClubNode * cls_create(void)
{
    sClubNode * club;
    club = (sClubNode * )malloc(sizeof(sClubNode));
    club->club_name[0] = '\0';
    club->club_city[0] = '\0';
    club->club_country[0] = '\0';
    club->club_place = 0;
    club->club_revenue = 0;

    club->club_next = NULL;
    return club;
}

sClubNode * cls_add_to_end(sClubs * clubs, sClubNode * club_to_add)
{
    if( clubs->clubs_head == NULL)
    {
        clubs->clubs_head = club_to_add;
        clubs->clubs_count = 1;
        return club_to_add;
    }

    sClubNode * club_current = clubs->clubs_head;
    while( club_current->club_next != NULL)
        club_current = club_current->club_next;

    club_current->club_next = club_to_add;
    clubs->clubs_count++;

    return club_to_add;
}
