#ifndef CLUBS_H
#define CLUBS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#define CLUB_NAME_MAX_LEN    20
#define CLUB_CITY_MAX_LEN    20
#define CLUB_COUNTRY_MAX_LEN 20
#define STR_MAX_LEN          20

typedef struct club
{
    char  club_name   [CLUB_NAME_MAX_LEN    + 1];
    char  club_city   [CLUB_CITY_MAX_LEN    + 1];
    //кількість забитих м'ячів;     club_goals_conceded
    //кількість пропущених м'ячів;  club_goals_scored
    //кількість набраних очок.      club_score
    char  club_country[CLUB_COUNTRY_MAX_LEN + 1];
    float club_revenue;             //поле не потрібно
    int   club_place;

} * sClub;

typedef int (*in_func_ptr)(sClub *, int *,  FILE *, int);

sClub cls_new_club (char *, ...);

int   readClubs    (sClub *, char *, int,    in_func_ptr);
int   inputNumber  (void);
int   inputClubsTxt(sClub *, int *,  FILE *, int);
void  printClubs   (sClub,   int);
void  printClub    (sClub,   int);
void  freeClubs    (sClub *, int*);

#endif // CLUBS_H
