#include "clubs.h"

static sClubNode cls_create    (void);
static void      cls_free_node (sClubNode *);

bool cls_init_list(sClubs * ptr_clubs)
{
    sClubs clubs = NULL;

    clubs = (sClubs)malloc(sizeof(struct clubs));

    if( clubs == NULL ) return false;

    clubs->clubs_head = NULL;
    clubs->clubs_tail = NULL;
    clubs->clubs_count = 0;

    *ptr_clubs = clubs;

    return true;
}

bool cls_is_empty(sClubs clubs)
{ return clubs->clubs_head == NULL; }

sClubNode cls_get_head(sClubs clubs)
{ return clubs->clubs_head; }

sClubNode cls_get_tail(sClubs clubs)
{ return clubs->clubs_tail; }

bool cls_is_head(sClubs clubs, const sClubNode club)
{ return clubs->clubs_head == club; }

bool cls_is_tail(sClubs clubs, const sClubNode club)
{ return clubs->clubs_tail == club; }

sClubNode cls_create(void)
{
    sClubNode club;
    club = (sClubNode)malloc(sizeof(struct club));

    if( club == NULL) return club;

    club->club_name[0] = '\0';
    club->club_city[0] = '\0';
    club->club_country[0] = '\0';
    club->club_place = 0;
    club->club_revenue = 0;

    club->club_next = NULL;
    club->club_prev = NULL;
    return club;
}

sClubNode cls_new(char * club_name, ...)
{
    sClubNode club = NULL;
    char * par_ptr = (char *)&club_name;
    club = cls_create();

    if( club == NULL ) return club;

    if( *(char *)par_ptr )
    {
        strcpy(club->club_name, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        strcpy(club->club_city, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        strcpy(club->club_country, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        club->club_revenue = *(double *)(par_ptr);
        par_ptr += sizeof(double);
        club->club_place = *(int *)par_ptr;
    }

    return club;
}

sClubNode cls_add_to_end(sClubs clubs, const sClubNode club_to_add)
{
    if( cls_is_empty(clubs) )
    {
        clubs->clubs_head = club_to_add;
        clubs->clubs_tail = club_to_add;
        clubs->clubs_count = 1;
        return club_to_add;
    }

    sClubNode club_tail = cls_get_tail(clubs);

    club_to_add->club_prev = club_tail;
    club_tail->club_next = club_to_add;
    clubs->clubs_tail = club_to_add;
    clubs->clubs_count++;

    return club_to_add;
}

sClubNode cls_add_to_begin(sClubs clubs, const sClubNode club_to_add)
{
    if( cls_is_empty(clubs) )
    {
        cls_add_to_end(clubs, club_to_add);
        return club_to_add;
    }

    sClubNode club_head = cls_get_head(clubs);

    club_to_add->club_next = club_head;
    club_head->club_prev = club_to_add;
    clubs->clubs_head = club_to_add;
    clubs->clubs_count++;

    return club_to_add;
}

sClubNode cls_add_after(sClubs clubs, const sClubNode club_current, const sClubNode club_to_add)
{
    if( cls_is_tail(clubs, club_current) )
        return cls_add_to_end(clubs, club_to_add);

    club_to_add->club_next = club_current->club_next;
    club_current->club_next->club_prev = club_to_add;
    club_to_add->club_prev = club_current;
    club_current->club_next = club_to_add;
    clubs->clubs_count++;
    return club_to_add;
}

sClubNode cls_add_before(sClubs clubs, sClubNode const club_current, const sClubNode club_to_add)
{
    if( cls_is_head(clubs, club_current) )
        return cls_add_to_begin(clubs, club_to_add);

    return cls_add_after(clubs, club_current->club_prev, club_to_add);
}

void cls_delete_node(sClubs * ptr_clubs, sClubNode * ptr_club_to_delete)
{
    sClubs      clubs = *ptr_clubs;
    sClubNode club_to_delete  = *ptr_club_to_delete;

    if( cls_is_head(clubs, club_to_delete) )
    {
        if( cls_is_tail(clubs, club_to_delete) )
        {
            clubs->clubs_head = NULL;
            clubs->clubs_tail = NULL;
            clubs->clubs_count = 0;
            cls_free_node(ptr_club_to_delete);
            return;
        }

        clubs->clubs_head = club_to_delete->club_next;
        club_to_delete->club_next->club_prev = NULL;
        clubs->clubs_count--;
        cls_free_node(ptr_club_to_delete);
        return;
    }

    club_to_delete->club_prev->club_next = club_to_delete->club_next;
    if( cls_is_tail(clubs, club_to_delete) )
        clubs->clubs_tail = club_to_delete->club_prev;
    else
        club_to_delete->club_next->club_prev = club_to_delete->club_prev;

    cls_free_node(ptr_club_to_delete);
    clubs->clubs_count--;
}

void cls_delete_list(sClubs * ptr_clubs)
{
    sClubNode club_current = cls_get_head(*ptr_clubs);
    sClubNode club_to_delete = NULL;

    while( club_current )
    {
        club_to_delete = club_current;
        club_current = club_to_delete->club_next;
        cls_free_node(&club_to_delete);
    }

    free(*ptr_clubs);
    *ptr_clubs = NULL;
}

void cls_free_node(sClubNode * ptr_club)
{
    free(*ptr_club);
    *ptr_club = NULL;
}

void printClubs(sClubs clubs)
{
    if( clubs == NULL ) return;

    int i = 0;
    sClubNode club = cls_get_head(clubs);

    puts("\0");
    puts("  ----------------------------------------------------------------------------------------------------");
    puts("  | N| place |     club     |     city     |     country     | revenue |   club next  |   club prev  |");
    puts("  ----------------------------------------------------------------------------------------------------");

    for(i = 0; i < clubs->clubs_count; i++)
    {
        printClub(club, i + 1);
        club = club->club_next;
    }
    puts("  ----------------------------------------------------------------------------------------------------");
    printf("  |                                                                    ");
    printf("|     count    |    %4d      |\n", clubs->clubs_count);
    puts("  ----------------------------------------------------------------------------------------------------");
    puts("\0");
}

void printClub(const sClubNode club, int list_number)
{
    printf("  |%2d|%5d  |%-14s|%-14s|%-17s| %7.2f |%-14s|%-14s|",

                                       list_number,
                                       club->club_place,
                                       club->club_name,
                                       club->club_city,
                                       club->club_country,
                                       club->club_revenue,

                                       club->club_next->club_name,
                                       club->club_prev->club_name);
    puts("\0");

}
