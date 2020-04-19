/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 10. Типи даних, визначені користувачем (частина 2).
 * Частина 14. Додавання вузла в двозв’язний список після заданого.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 22.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Перепишіть процедуру AddAfter(), використовуючи виключно синтаксис С.
В списку вхідних параметрів тип змінних Head i Tail встановіть
як покажчик на покажчик, і в потрібних місцях тіла процедури
забезпечте його розіменування.
*/

#include "clubs.h"

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
void      cls_delete_node (sClubs *, sClubNode *); //bool //перевірка чи вузол з цього списку
void      cls_delete_list (sClubs *);              //bool //перевірка чи вузол з цього списку

void      printClubs      (sClubs);
void      printClub       (const sClubNode, int);
*/

int main(void)
{
    sClubs    clubs      = NULL;
    sClubNode club_ptr   = NULL;
    sClubNode club_ptr_2 = NULL;

    puts("\0");
//------------------------------------------------------------------------------
    cls_init_list(&clubs);
//------------------------------------------------------------------------------
    club_ptr = cls_new("Super Club 2", "Club City 2", "Club Country 2", 200.5, 228);
    cls_add_to_end(clubs, club_ptr);
    puts("add_to_end:   Club 2");
    printClubs(clubs);
//------------------------------------------------------------------------------
    club_ptr = cls_new("Super Club 1", "Club City 1", "Club Country 1", 100.5, 128);
    cls_add_to_begin(clubs, club_ptr);
    puts("add_to_begin: Club 1");
    printClubs(clubs);
//------------------------------------------------------------------------------
    puts("add_before:   Club 3 before Club 1");
    club_ptr_2 = cls_new("Super Club 3", "Club City 3", "Club Country 3", 300.5, 328);
    cls_add_before(clubs, club_ptr, club_ptr_2);
    printClubs(clubs);
//------------------------------------------------------------------------------
    puts("add_after:    Club 4 after Club 1");
    club_ptr_2 = cls_new("Super Club 4", "Club City 4", "Club Country 4", 400.5, 428);
    cls_add_after(clubs, club_ptr, club_ptr_2);
    printClubs(clubs);
//------------------------------------------------------------------------------
    cls_delete_node(&clubs, &club_ptr);
    puts("delete_node:  Club 1");
    printClubs(clubs);

    cls_delete_node(&clubs, &club_ptr_2);
    puts("delete_node:  Club 4");
    printClubs(clubs);

    club_ptr = cls_get_head(clubs);
    cls_delete_node(&clubs, &club_ptr);
    puts("delete_node:  Head");
    printClubs(clubs);

    club_ptr = cls_get_tail(clubs);
    cls_delete_node(&clubs, &club_ptr);
    puts("delete_node:  Tail");
    printClubs(clubs);

    cls_delete_list(&clubs);
//------------------------------------------------------------------------------
    puts("\0");
    return 0;
}
