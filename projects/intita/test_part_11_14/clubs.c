#include "clubs.h"

static void openFile(char * file_name, char * file_mode, FILE ** file_ptr_addr);
static void addClub(sClub * clubs, int * clubs_count, char * club_name, ...);

sClub cls_new_club(char * club_name, ...)
{
    sClub club = NULL;
    char * par_ptr = (char *)&club_name;
    club = (sClub)malloc(sizeof(struct club));

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
    else
    {
        club->club_name[0] = '\0';
        club->club_city[0] = '\0';
        club->club_country[0] = '\0';
        club->club_place = 0;
        club->club_revenue = 0;
    }

    return club;
}

int readClubs(sClub * clubs, char * file_name, int elements_count, in_func_ptr input_function)
{
    FILE        * teams        = NULL;
    int           clubs_count  = 0;

    if( file_name )
    {
        openFile(file_name, "r", &teams);
        if( !teams ) exit(0);
    }
    else
        teams = stdin;

    input_function(clubs, &clubs_count, teams, elements_count);
    fclose(teams);
    return clubs_count;
}

int  inputNumber(void)
{
    int clubs_count = 0;
    while(1)
    {
        if( clubs_count < 0 )
        {
            puts("\nWRONG NUMBER! TRY AGAIN!");
        }
        printf("\nINPUT CLUBS COUNT/NUMBER TO READ: ");
        fflush(stdin);
        clubs_count = 0;
        scanf("%d", &clubs_count);
        if( clubs_count > 0 ) break;
        clubs_count = -1;
    }

    return clubs_count;
}

int inputClubsTxt(sClub * clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char   club_name[CLUB_NAME_MAX_LEN + 1] = "";
    char   club_city[CLUB_CITY_MAX_LEN + 1] = "";
    int    club_place                       = 0;
    int    club_score                       = 0;
    char   tmp_str[STR_MAX_LEN + 1]         = "";
    int    i                                = 1;
    char * new_line_position                = 0;

    while( fgets(tmp_str, STR_MAX_LEN + 1, input_file)
           && (*clubs_count < elements_count || !elements_count))
    {
        if( (new_line_position = strchr(tmp_str, '\n')) != NULL )
            *new_line_position = '\0';

        switch( i )
        {
            case 1:
                strncpy(club_name, tmp_str, CLUB_NAME_MAX_LEN);
                break;
            case 2:
                strncpy(club_city, tmp_str, CLUB_CITY_MAX_LEN);
                break;
            case 3:
                sscanf(tmp_str, "%d", &club_place);
                break;
            case 4:
                sscanf(tmp_str, "%d", &club_score);
                break;
        }
        if( i++ == 4 )
        {
            addClub(clubs, clubs_count, club_name, club_city, club_place);
            i = 1;
        }
    }

    return 0;
}

void addClub(sClub * clubs, int * clubs_count, char * club_name, ...)
{
    sClub     club_ptr   = NULL;
    size_t    sClub_size = sizeof(struct club);

    *clubs_count += 1;
    *clubs = (sClub)realloc(*clubs, sClub_size * (*clubs_count));
    if( !*clubs ) exit(0);

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    char * par_ptr = (char *)&club_name;

    if( *(char *)par_ptr )
    {
        strcpy(club_ptr->club_name, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        strcpy(club_ptr->club_city, *(char **)par_ptr);
        par_ptr += sizeof(char *);
        //strcpy(club->club_country, *(char **)par_ptr);
        //par_ptr += sizeof(char *);
        //club->club_revenue = *(double *)(par_ptr);
        //par_ptr += sizeof(double);
        club_ptr->club_place = *(int *)par_ptr;
    }
    else
    {
        club_ptr->club_name[0] = '\0';
        club_ptr->club_city[0] = '\0';
        club_ptr->club_country[0] = '\0';
        club_ptr->club_place = 0;
        //club_ptr->club_revenue = 0;
    }
}
//*****************************************************************************
//  OTHER FUNCTIONS
//*****************************************************************************
void openFile(char * file_name, char * file_mode, FILE ** file_ptr_addr)
{
    *file_ptr_addr = fopen(file_name, file_mode);

    if( *file_ptr_addr )
    {
        rewind(*file_ptr_addr);
        return;
    }

    switch( *file_mode )
    {
        case 'r':
            printf("FILE %s DOES NOT EXIST!\n", file_name);
            break;
        case 'a':
        case 'w':
            printf("CAN NOT OPEN OR CREATE FILE %s !\n", file_name);
            break;
    }
}

void printClubs(sClub clubs, int clubs_count)
{
    int i = 0;

    puts("\0");
    puts("     ----------------------------------------------");
    puts("     | N| place | score |    club    |    city    |");
    puts("     ----------------------------------------------");

    for(i = 0; i < clubs_count; i++)
    {
        printf("     ");
        printClub(&clubs[i], i + 1);
    }
    puts("     ----------------------------------------------");
    puts("\0");
}

void printClub(sClub club, int list_number)
{
    if( club == NULL )
        printf("|  |       |       |            |            |\n");
    else
    {
        printf("|%2d| %5d | %5d |%-12s|%-12s|\n",
                 list_number,
                 club->club_place,
                 0,
                 club->club_name,
                 club->club_city);
    }
}

void freeClubs(sClub * clubs, int * clubs_count)
{
    free(clubs);
    *clubs = NULL;
    *clubs_count = 0;
}
//*****************************************************************************
//  END OTHER FUNCTIONS
//*****************************************************************************
/*
int inputClubsKey(sClub_ptr * clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_place                       = 0;
    int    club_score                       = 0;

    while( elements_count-- || !elements_count )
    {
         system("cls");
         printClubs(*clubs, *clubs_count);

         fflush(input_file);

         printf("ENTER CLUB NAME: ");
         gets(club_name);
         printf("ENTER CLUB CITY: ");
         gets(club_city);
         printf("ENTER CLUB PLACE: ");
         club_place = 0;
         scanf("%d", &club_place);
         printf("ENTER CLUB SCORE: ");
         fflush(input_file);
         club_score = 0;
         scanf("%d", &club_score);

         addClub(clubs, clubs_count, club_name, club_city, club_place, club_score);

         system("cls");
         printClubs(*clubs, *clubs_count);
         printf("ENTER 'q' TO EXIT OR PRESS ANY KEY TO INPUT NEW RECORD");
         if( 'q' == getch() ) break;
     }

    return 0;
}
*/
