#ifndef CLUBS_H
#define CLUBS_H

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

};

typedef struct club sClubNode;

typedef struct
{
    sClubNode * clubs_head;
    int         clubs_count;
} sClubs;

void        cls_init        (sClubs **);
sClubNode * cls_create      (void);
sClubNode * cls_new         (char *, ...);
sClubNode * cls_add_to_end  (sClubs *,  sClubNode *);
sClubNode * cls_add_to_begin(sClubs *,  sClubNode *);
sClubNode * cls_add_after   (sClubs *,  sClubNode *, sClubNode *);
sClubNode * cls_add_before  (sClubs *,  sClubNode *, sClubNode *);
void        cls_delete_node (sClubs **, sClubNode **);
void        cls_delete_list (sClubs **);
void        cls_free_node   (sClubNode **);

void printClubs(sClubs * clubs);

#endif // CLUBS_H

