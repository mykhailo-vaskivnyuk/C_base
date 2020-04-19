#include "clubs.h"

#ifndef CLUBS_CIRCLED_H
#define CLUBS_CIRCLED_H

//#include <stdbool.h>

typedef struct clubs_cld
{
    sClubNode clubs_cld_head;
    int       clubs_cld_count;
} * sClubsCld;

bool clsd_init_list (sClubsCld *);
bool clsd_from_cls  (sClubsCld, sClubs *);
bool cls_from_clsd  (sClubs,   sClubsCld *);

#endif // CLUBS_CIRCLED_H
