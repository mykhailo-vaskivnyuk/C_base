#ifndef CLUBS_H
#define CLUBS_H

#include <stdlib.h>
#include <string.h>

#define CLUB_NAME_MAX_LEN    20
#define CLUB_CITY_MAX_LEN    20
#define CLUB_COUNTRY_MAX_LEN 20

typedef struct club
{
    char  club_name   [CLUB_NAME_MAX_LEN    + 1];
    char  club_city   [CLUB_CITY_MAX_LEN    + 1];
    char  club_country[CLUB_COUNTRY_MAX_LEN + 1];
    float club_revenue;
    int   club_place;

} * sClub;

sClub cls_new_club(char *, ...);

#endif // CLUBS_H
