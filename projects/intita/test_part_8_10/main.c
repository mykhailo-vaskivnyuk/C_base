/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 8. Типи даних, визначені користувачем (частина 1).
 * Частина 10. Динамічні масиви структур.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 10.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Підсумкове завдання до заняття 8.
Реалізуй програму, яка поєднує наступні елементи пройденого заняття:
1) створити структуру Club з полями:
   - name - назва клубу;
   - sity - місто, яке він представляє;
   - score - кількість набраних очок;
2) попередньо створити на диску текстовий файл, в який внести дані -
   майбутні значення полів структури Club :
   - кожне поле - з нового рядка, без пробілів!
   - кількість клубів - не менше 10;
   - розташувати клуби у файлі в довільному порядку, незалежно від кількості очок;
3) ввести з клавіатури число n - кількість клубів, дані про які потрібно прочитати з файлу;
4) виділити динамічно пам’ять для масиву з n структур;
5) прочитати у відповідний масив максимально можливу кількість даних про клуби
   (якщо кількість клубів у файлі менше n);
6) здійснити сортування даного масиву за спаданням кількості очок клубів -
   першим елементом щоб стала структура, клуб якої має максимальну кількість очок, і далі - в порядку зменшення;
   Примітка:
   - з метою обміну структур місцями оголосити додаткову аналогічну структуру,
   в яку тимчасово копіювати ті, що підлягають перестановці;
   - доступ до елементів масиву структур здійснювати за допомогою покажчиків!
7) дані відсортованого масиву вивести до двійкового файлу;
8) ввести з клавіатури число n_club (номер клубу по порядку у файлі),
   прочитати відповідну структуру з двійкового файлу, переконатися в правильності запису в нього даних про клуби.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define STR_MAX_LEN       20
#define STR_CLUB_NAME_LEN 20
#define STR_CLUB_CITY_LEN 20

typedef struct
{
    char club_name[STR_CLUB_NAME_LEN + 1];
    char club_city[STR_CLUB_CITY_LEN + 1];
    int  club_score;
}sClub;

typedef int (*fptr)(sClub **, int *,  FILE *, int);

void addClub       (sClub **, int *,  char *, char *, int);
int  inputClubsKey (sClub **, int *,  FILE *, int);
int  inputClubsTxt (sClub **, int *,  FILE *, int);
int  inputClubsBin (sClub **, int *,  FILE *, int);
int  inputClubBin  (sClub **, int *,  FILE *, int);
int  readClubs     (sClub **, char *, int,    fptr);
int  readClub      (sClub **, char *, int,    fptr);
void printClubs    (sClub *,  int);
void printClub     (sClub *,  int);
void sortClubs     (sClub *,  int);
void freeClubs     (sClub **, int *);

int  inputNumber   (void);
void openFile      (char *,   char *, FILE **);

int main(void)
{
    int           clubs_count      = 0;
    sClub       * clubs            = NULL;
    FILE        * teams            = NULL;
    char        * input_file_name  = "teams.txt";
    char        * file_name        = "teams.dat";
    int           i                = 0;
    size_t        sClub_size       = sizeof(sClub);

//-----------------------------------------------------------------------------
//  input data from txt file
//-----------------------------------------------------------------------------

    clubs_count = readClubs(&clubs, input_file_name, inputNumber(), inputClubsTxt);

//-----------------------------------------------------------------------------
//  print data
//-----------------------------------------------------------------------------

    system("cls");
    puts("\0");
    printClubs(clubs, clubs_count);

//-----------------------------------------------------------------------------
//  sort data
//-----------------------------------------------------------------------------

    sortClubs(clubs, clubs_count);
    puts("\0");
    printClubs(clubs, clubs_count);

//-----------------------------------------------------------------------------
//  write data to file
//-----------------------------------------------------------------------------

    openFile(file_name, "wb", &teams);
    if( !teams ) return 0;
    for(i = 0; i < clubs_count; i++)
    {
        fwrite(&clubs[i], sClub_size, 1, teams);
    }
    fclose(teams);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------
//  read data from file and print
//-----------------------------------------------------------------------------

    if( !(clubs_count = readClub(&clubs, file_name, inputNumber(), inputClubBin)) ) return 0;
    printClubs(clubs, clubs_count);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------

    return 0;
}

//*****************************************************************************
//  OTHER FUNCTIONS
//*****************************************************************************
int inputClubsKey(sClub ** clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_score                       = 0;

    while( elements_count-- || !elements_count )
    {
         system("cls");
         printClubs(*clubs, *clubs_count);
         printf("ENTER CLUB CITY SCORE: ");

         fflush(input_file);
         club_score = 0;
         scanf("%20s%20s%d", club_name, club_city, &club_score);

         addClub(clubs, clubs_count, club_name, club_city, club_score);

         system("cls");
         printClubs(*clubs, *clubs_count);
         printf("ENTER 'q' TO EXIT OR PRESS ANY KEY TO INPUT NEW RECORD");
         if( 'q' == getch() ) break;
     }

    return 0;
}

int inputClubsTxt(sClub ** clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_score                       = 0;
    char   tmp_str[STR_MAX_LEN + 1]         = "";
    int    i                                = 1;

    while( fgets(tmp_str, STR_MAX_LEN + 1, input_file)
           && (*clubs_count < elements_count || !elements_count))
    {
        switch( i )
        {
            case 1:
                sscanf(tmp_str, "%20s", club_name);
                break;
            case 2:
                sscanf(tmp_str, "%20s", club_city);
                break;
            case 3:
                sscanf(tmp_str, "%d", &club_score);
                break;
        }
        if( i++ == 3 )
        {
            addClub(clubs, clubs_count, club_name, club_city, club_score);
            i = 1;
        }
    }

    return 0;
}

int inputClubsBin(sClub ** clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    sClub  tmp_club                         = {"", "", 0};
    size_t sClub_size                       = sizeof(sClub);

    while( fread(&tmp_club, sClub_size, 1, input_file) &&
           (*clubs_count < elements_count || !elements_count) )
    addClub(clubs, clubs_count, tmp_club.club_name, tmp_club.club_city, tmp_club.club_score);

    return 0;
}

int inputClubBin(sClub ** clubs, int * clubs_count, FILE * input_file, int element_number)
{
    sClub  tmp_club                         = {"", "", 0};
    size_t sClub_size                       = sizeof(sClub);

    fseek(input_file, sClub_size * (element_number - 1), SEEK_SET);
    if( fread(&tmp_club, sClub_size, 1, input_file) )
        addClub(clubs, clubs_count, tmp_club.club_name, tmp_club.club_city, tmp_club.club_score);

    return 0;
}

void addClub(sClub ** clubs, int * clubs_count, char * club_name, char * club_city, int club_score)
{
    sClub  * club_ptr   = NULL;
    size_t   sClub_size = sizeof(sClub);

    *clubs_count += 1;
    *clubs = (sClub *)realloc(*clubs, sClub_size * (*clubs_count));
    if( !*clubs ) exit(0);

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    strcpy(club_ptr->club_name, club_name);
    strcpy(club_ptr->club_city, club_city);
    club_ptr->club_score = club_score;
}

void printClubs(sClub * clubs, int clubs_count)
{
    int i = 0;

    puts("\0");
    puts("     --------------------------------------");
    puts("     | N| score |    club    |    city    |");
    puts("     --------------------------------------");

    for(i = 0; i < clubs_count; i++)
    {
        printClub(&clubs[i], i + 1);
    }
    puts("     --------------------------------------");
    puts("\0");
}

void printClub(sClub * club, int list_number)
{
    printf("     |%2d|%5d  |%-12s|%-12s|\n", list_number,
                                       club->club_score,
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

void freeClubs(sClub ** clubs, int * clubs_count)
{
    free(clubs);
    *clubs = NULL;
    *clubs_count = 0;
}

int readClubs(sClub ** clubs, char * file_name, int elements_count, fptr input_function)
{
    FILE        * teams        = NULL;
    int           clubs_count  = 0;

    openFile(file_name, "r", &teams);
    if( !teams ) return 0;

    input_function(clubs, &clubs_count, teams, elements_count);
    fclose(teams);
    return clubs_count;
}

int readClub(sClub ** clubs, char * file_name, int element_number, fptr input_function)
{
    FILE        * teams        = NULL;
    int           clubs_count  = 0;

    openFile(file_name, "r", &teams);
    if( !teams ) return 0;

    input_function(clubs, &clubs_count, teams, element_number);
    fclose(teams);
    return clubs_count;
}

void sortClubs(sClub * clubs,  int clubs_count)
{
   int i = 0;
   int j = 0;
   sClub tmp_club;

   clubs_count--;

   for(i = 0; i < clubs_count; i++)
   {
       for(j = 0; j < clubs_count - i; j++)
       {
           if(clubs[j].club_score < clubs[j + 1].club_score)
           {
               tmp_club = clubs[j];
               clubs[j] = clubs[j + 1];
               clubs[j + 1] = tmp_club;
           }
       }
   }
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
