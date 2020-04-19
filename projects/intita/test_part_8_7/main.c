/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 8. Типи даних, визначені користувачем (частина 1).
 * Частина 7. Запис і читання структур з двійкових файлів.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 06.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму для виконання наступних дій:
1) описати структуру Club з такими полями:
   name - назва клубу;
   sity - місто, яке він представляє;
   place - місце в чемпіонаті (ціле число);
2) оголосити одну змінну типу Club, покажчик на відповідну структуру,
   а також покажчик на двійковий файл;
3) відкрити двійковий файл teams.dat в режимі "ab" (дозапис в кінець);
4) створити цикл, в якому по черзі (не менше 7-ми разів!):
   - ввести з клавіатури значення полів змінної типу Club;
   - записати введену структуру (дані про клуб) у файл teams.dat ;
5) після закриття файлу – відкрити його в режимі читання
   і прочитати з нього перші 3 структури ;
6) прочитані дані записати у новий двійковий файл (наприклад, teams1.dat);
7) новостворений файл відкрити в режимі читання, вміст його вивести на екран,
   переконатися в коректності перенесення даних з іншого файлу.
В пп. 4-7 операції читання-запису в двійкові файли реалізовувати за одну команду!
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define STR_MAX_LEN       43
#define STR_CLUB_NAME_LEN 20
#define STR_CLUB_CITY_LEN 20

struct club
{
    char club_name[STR_CLUB_NAME_LEN + 1];
    char club_city[STR_CLUB_CITY_LEN + 1];
    int  club_place;
};

int  inputClubs(struct club **, int *,  FILE *, int);
void addClub   (struct club **, int *,  char *, char *, int);
int  readClubs (struct club **,  int,    char *);
void printClubs(struct club *,  int);
void printClub (struct club *,  int);
void freeClubs (struct club **, int *);
void openFile  (char *,         char *, FILE **);

int main(void)
{
    int           clubs_count      = 0;
    struct club * clubs            = NULL;
    FILE        * teams            = NULL;
    char        * file_name        = "teams.dat";
    char        * file_name_new    = "teams_new.dat";
    int           i                = 0;
    size_t        struct_club_size = sizeof(struct club);

//-----------------------------------------------------------------------------
//  input data
//-----------------------------------------------------------------------------

    inputClubs(&clubs, &clubs_count, NULL, 0);

//-----------------------------------------------------------------------------
//  write data to file
//-----------------------------------------------------------------------------

    openFile(file_name, "ab", &teams);
    if( !teams ) return 0;
    for(i = 0; i < clubs_count; i++)
    {
        //fprintf(teams, "%s %s %d\n", clubs[i].club_name,
        //                             clubs[i].club_city,
        //                             clubs[i].club_place);
        fwrite(&clubs[i], struct_club_size, 1, teams);
    }
    fclose(teams);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------
//  read data from file and print
//-----------------------------------------------------------------------------

    system("cls");
    if( !(clubs_count = readClubs(&clubs, 0, file_name)) ) return 0;
    printClubs(clubs, clubs_count);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------
//  write data to a new file
//-----------------------------------------------------------------------------

    if( !(clubs_count = readClubs(&clubs, 3, file_name)) ) return 0;
    openFile(file_name_new, "wb", &teams);
    if( !teams ) return 0;
    for(i = 0; i < clubs_count; i++)
    {
        //fprintf(teams, "%s %s %d\n", clubs[i].club_name,
        //                             clubs[i].club_city,
        //                             clubs[i].club_place);
        fwrite(&clubs[i], struct_club_size, 1, teams);
    }
    fclose(teams);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------
//  read data from the new file and print
//-----------------------------------------------------------------------------

    if( !(clubs_count = readClubs(&clubs, 0, file_name_new)) ) return 0;
    printClubs(clubs, clubs_count);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------

    return 0;
}



//*****************************************************************************
//  OTHER FUNCTIONS
//*****************************************************************************
int inputClubs(struct club ** clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    //char   tmp_str[STR_MAX_LEN + 1]         = "";
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_place                       = 0;
    struct club tmp_club                    = {"", "", 0};
    size_t struct_club_size                 = sizeof(struct club);

    if( input_file )
    {
//        while( fgets(tmp_str, STR_MAX_LEN + 1, input_file) )
//        {
//            sscanf(tmp_str, "%20s%20s%d", club_name, club_city, &club_place);
//            addClub(clubs, clubs_count, club_name, club_city, club_place);
//        }
        while( fread(&tmp_club, struct_club_size, 1, input_file) && (*clubs_count < elements_count || !elements_count) )
        {
            //addClub(clubs, clubs_count, tmp_club.club_name, tmp_club.club_city, tmp_club.club_place);
            addClub(clubs, clubs_count, "", "", 0);
            (*clubs)[*clubs_count - 1] = tmp_club;
        }
    }
    else
    {
        while( 1 )
        {
            system("cls");
            printClubs(*clubs, *clubs_count);
            printf("\nENTER CLUB SITY PLACE: ");

            fflush(stdin);
            club_place = 0;
            scanf("%20s%20s%d", club_name, club_city, &club_place);

            addClub(clubs, clubs_count, club_name, club_city, club_place);

            system("cls");
            printClubs(*clubs, *clubs_count);
            printf("\nENTER 'q' TO EXIT OR PRESS ANY KEY TO INPUT NEW RECORD");
            if( 'q' == getch() ) break;
        }
     }

    return 0;
}

void addClub(struct club ** clubs, int * clubs_count, char * club_name, char * club_city, int club_place)
{
    struct club * club_ptr         = NULL;
    size_t        struct_club_size = sizeof(struct club);
    //size_t        char_size        = sizeof(char);

    *clubs_count += 1;
    *clubs = (struct club *)realloc(*clubs, struct_club_size * (*clubs_count));

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    //club_ptr->club_name = (char *)malloc(char_size * (strlen(club_name) + 1));
    strcpy(club_ptr->club_name, club_name);
    //club_ptr->club_city = (char *)malloc(char_size * (strlen(club_city) + 1));
    strcpy(club_ptr->club_city, club_city);
    club_ptr->club_place = club_place;
}

void printClubs(struct club * clubs, int clubs_count)
{
    int i = 0;

    puts("\0");
    puts("     --------------------------------------");
    puts("     | N| place |    club    |    city    |");
    puts("     --------------------------------------");

    for(i = 0; i < clubs_count; i++)
    {
        printClub(&clubs[i], i + 1);
    }
    puts("     --------------------------------------");
}

void printClub(struct club * club, int list_number)
{
    printf("     |%2d|%5d  |%-12s|%-12s|\n", list_number,
                                       club->club_place,
                                       club->club_name,
                                       club->club_city);
}

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

void freeClubs(struct club ** clubs, int * clubs_count)
{
    //int i = 0;

    //for(i = 0; i < *clubs_count; i++)
    //{
    //    free((*clubs)[i].club_name);
    //    free((*clubs)[i].club_city);
    //}
    free(clubs);
    *clubs = NULL;
    *clubs_count = 0;
}

int readClubs(struct club ** clubs, int elements_count, char * file_name)
{
    FILE        * teams       = NULL;
    //struct club * clubs       = NULL;
    int           clubs_count = 0;

    openFile(file_name, "rb", &teams);
    if( !teams ) return 0;

    inputClubs(clubs, &clubs_count, teams, elements_count);
    //printClubs(clubs, clubs_count);
    fclose(teams);
    //freeClubs(&clubs, &clubs_count);
    return clubs_count;
}
