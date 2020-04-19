#ifndef CLUBS_H
#define CLUBS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CLUB_NAME_MAX_LEN    20
#define CLUB_CITY_MAX_LEN    20
#define CLUB_COUNTRY_MAX_LEN 20

struct club
{
    char  club_name   [CLUB_NAME_MAX_LEN    + 1];
    char  club_city   [CLUB_CITY_MAX_LEN    + 1];
    char  club_country[CLUB_COUNTRY_MAX_LEN + 1];
    float club_revenue;
    int   club_place;

    struct club * club_next;
    struct club * club_prev;
};

typedef struct club * sClubNode;

typedef struct clubs
{
    sClubNode clubs_head;
    sClubNode clubs_tail;
    int       clubs_count;
} * sClubs;

bool      cls_init_list   (sClubs *);
bool      cls_is_empty    (sClubs);
bool      cls_is_head     (sClubs,   const sClubNode);
bool      cls_is_tail     (sClubs,   const sClubNode);
sClubNode cls_get_head    (sClubs);
sClubNode cls_get_tail    (sClubs);

sClubNode cls_new         (char *, ...);
sClubNode cls_add_to_end  (sClubs,   const sClubNode);
sClubNode cls_add_to_begin(sClubs,   const sClubNode);
sClubNode cls_add_after   (sClubs,   const sClubNode, const sClubNode);
sClubNode cls_add_before  (sClubs,   const sClubNode, const sClubNode);
void      cls_delete_node (sClubs,         sClubNode *); //bool //перевірка чи вузол з цього списку
void      cls_delete_list (sClubs *);

sClubNode findClub        (sClubs,          const char *,    bool (*)(const sClubNode, const char *));
bool      ifClubCountry   (const sClubNode, const char *);

void      printClubs      (sClubs);
void      printClub       (const sClubNode, int);

#endif // CLUBS_H
