#include "clubs_circled.h"

bool clsd_init_list(sClubsCld * ptr_clubs_cld)
{
    sClubsCld clubs_cld = NULL;

    clubs_cld = (sClubsCld)malloc(sizeof(struct clubs_cld));

    if( clubs_cld == NULL ) return false;

    clubs_cld->clubs_cld_head = NULL;
    clubs_cld->clubs_cld_count = 0;

    *ptr_clubs_cld = clubs_cld;

    return true;
}

bool clsd_from_cls(sClubsCld clubs_cld, sClubs * ptr_clubs)
{
    if( cls_is_empty(*ptr_clubs) ) return false;

    sClubNode club_head = cls_get_head(*ptr_clubs);
    sClubNode club_tail = cls_get_tail(*ptr_clubs);

    club_head->club_prev = club_tail;
    club_tail->club_next = club_head;
    clubs_cld->clubs_cld_head = club_head;
    clubs_cld->clubs_cld_count = (*ptr_clubs)->clubs_count;

    *ptr_clubs = NULL;

    return true;
}

bool cls_from_clsd(sClubs clubs, sClubsCld * ptr_clubs_cld)
{
    if( *ptr_clubs_cld == NULL || (*ptr_clubs_cld)->clubs_cld_head == NULL) return false;

    sClubNode club_head = (*ptr_clubs_cld)->clubs_cld_head;
    sClubNode club_tail = club_head->club_prev;

    club_head->club_prev = NULL;
    club_tail->club_next = NULL;
    clubs->clubs_head = club_head;
    clubs->clubs_tail = club_tail;
    clubs->clubs_count = (*ptr_clubs_cld)->clubs_cld_count;

    *ptr_clubs_cld = NULL;

    return true;
}
