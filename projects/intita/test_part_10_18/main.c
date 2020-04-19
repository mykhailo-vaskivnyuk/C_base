/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 10. Динамічні структури даних (частина 1).
 * Частина 18. Створення циклічного списку.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 22.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Перепишіть процедуру Circled(), використовуючи виключно синтаксис С.
В списку вхідних параметрів тип змінних Head i Tail встановіть
як покажчик на покажчик, і в потрібних місцях тіла процедури
забезпечте його розіменування.
*/

#include "clubs.h"
#include "clubs_circled.h"

/*
typedef struct club  * sClubNode;
typedef struct clubs * sClubs;

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
void      cls_delete_list (sClubs *);              //bool //перевірка чи вузол з цього списку

sClubNode findClub        (sClubs,          const char *,    bool (*)(const sClubNode, const char *));
bool      ifClubCountry   (const sClubNode, const char *);

void      printClubs      (sClubs);
void      printClub       (const sClubNode, int);
*/

/*
bool clsd_init_list (sClubsCld *);
bool clsd_from_cls  (sClubsCld, sClubs *);
bool cls_from_clsd  (sClubs,   sClubsCld *);
*/

int main(void)
{
    sClubs    clubs     = NULL;
    sClubNode club      = NULL;
    sClubNode club_2    = NULL;
    sClubsCld clubs_cld = NULL;

    puts("\0");
//---------------------------- cls_init_list -----------------------------------
    cls_init_list(&clubs);
//---------------------------- cls_add_to_end ----------------------------------
    club = cls_new("Super Club 2", "Club City 2", "Club Country 2", 200.5, 228);
    cls_add_to_end(clubs, club);
    puts("add_to_end:   Club 2");
    printClubs(clubs);
//---------------------------- cls_add_to_begin --------------------------------
    club = cls_new("Super Club 1", "Club City 1", "Club Country 1", 100.5, 128);
    cls_add_to_begin(clubs, club);
    puts("add_to_begin: Club 1");
    printClubs(clubs);
//---------------------------- cls_add_before ----------------------------------
    puts("add_before:   Club 3 before Club 1");
    club_2 = cls_new("Super Club 3", "Club City 3", "Club Country 3", 300.5, 328);
    cls_add_before(clubs, club, club_2);
    printClubs(clubs);
//---------------------------- cls_add_after -----------------------------------
    puts("add_after:    Club 4 after Club 1");
    club_2 = cls_new("Super Club 4", "Club City 4", "Club Country 4", 400.5, 428);
    cls_add_after(clubs, club, club_2);
    printClubs(clubs);
//---------------------------- findClub ----------------------------------------
    puts("findClub:   \"Club Country 2\"");
    puts("\0");
    if( (club = findClub(clubs, "Club Country 2", ifClubCountry)) )
            printClub(club, 1);
    else
    {
        printf("CAN NOT FIND CLUB BY COUNTRY\n");
        club = cls_get_head(clubs);
    }
    puts("\0");
//--------------------- clsd_from_cls / cls_from_clsd ---------------------------

    clsd_init_list(&clubs_cld);
    clsd_from_cls(clubs_cld, &clubs);

    cls_init_list(&clubs);
    cls_from_clsd(clubs, &clubs_cld);

//---------------------------- cls_delete_node ---------------------------------
    printf("delete_node: %s\n", club->club_name);
    cls_delete_node(clubs, &club);
    printClubs(clubs);

    cls_delete_node(clubs, &club_2);
    puts("delete_node:  Club 4");
    printClubs(clubs);

    club = cls_get_head(clubs);
    cls_delete_node(clubs, &club);
    puts("delete_node:  Head");
    printClubs(clubs);

    club = cls_get_tail(clubs);
    cls_delete_node(clubs, &club);
    puts("delete_node:  Tail");
    printClubs(clubs);
//---------------------------- cls_delete_list ---------------------------------
    cls_delete_list(&clubs);
//------------------------------------------------------------------------------
    puts("\0");
    return 0;
}
