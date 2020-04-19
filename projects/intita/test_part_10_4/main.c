/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 10. Типи даних, визначені користувачем (частина 2).
 * Частина 4. Додавання нового вузла в початок списку.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 17.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Перепишіть наведену процедуру, користуючись виключно синтаксисом мови С.
Процедура повинна мати наступні особливості:
- покажчик Head передається в неї по значенню;
- змінене значення Head повертається в місце виклику.
*/

#include <stdio.h>
#include "clubs.h"

int main(void)
{
    sClubs    * clubs_ptr = NULL;
    sClubNode * club_ptr  = NULL;

    cls_init(&clubs_ptr);
    club_ptr = cls_new("Super Club", "Club City", "Club Country", 100.5, 128);
    cls_add_to_end(clubs_ptr, club_ptr);

    puts("\0");
    printf("Club Name:    %20s\n",   club_ptr->club_name);
    printf("Club City:    %20s\n",   club_ptr->club_city);
    printf("Club Country: %20s\n",   club_ptr->club_country);
    printf("Club Revenue: %20.2f\n", club_ptr->club_revenue);
    printf("Club Place:   %17d\n",   club_ptr->club_place);

    club_ptr = cls_new("Super Club 2", "Club City 2", "Club Country 2", 200.5, 228);
    cls_add_to_begin(clubs_ptr, club_ptr);

    puts("\0");
    printf("Club Name:    %20s\n",   club_ptr->club_name);
    printf("Club City:    %20s\n",   club_ptr->club_city);
    printf("Club Country: %20s\n",   club_ptr->club_country);
    printf("Club Revenue: %20.2f\n", club_ptr->club_revenue);
    printf("Club Place:   %17d\n",   club_ptr->club_place);

    puts("\0");
    return 0;
}
