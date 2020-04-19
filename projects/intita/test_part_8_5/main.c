/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 8. Типи даних, визначені користувачем (частина 1).
 * Частина 5. Звертання до полів структур.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 04.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Запрограмуй перерахування CLUBS, яке буде містити константи (не менше семи)
   з наступними властивостями:
    - чисельне значення - місце клубу в чемпіонаті;
    - перший синонім - назва клубу;
    - другий синонім - назва міста, яке представляє клуб.
2. Створи структуру Club з такими полями:
   name - назва клубу;
   sity - місто, яке він представляє;
   place - місце в чемпіонаті (ціле число);
3. Запрограмуй цикл, в якому здійснюється оголошення та ініціалізація
   структурних змінних типу Club:
    - кількість змінних дорівнює кількості констант в перерахуванні CLUBS;
    - поля змінних ініціалізуються константами та їх синоніми з перерахування CLUBS:
      place - значення константи; name i sity - синоніми відповідної константи;
    - для вибору змінної використовуй switch(i), де i - значення лічильника циклу
      (змінна типу enum CLUBS);
4. В наступному циклі - організуй виведення на екран у форматі (місце, клуб, місто)
   значення всіх полів кожної структурної змінної. Вибір змінної - через switch(i), аналогічно до п. 4.
*/

#include <stdio.h>
#include <string.h>

enum BULGARCLUBS
{//|     club     |      city       |
 //==================================
    Ludogorec =  1, Razgrad     =  1
   ,Litex     =  3, Lovech      =  3
   ,Beroe     =  5, StaraZagora =  5
   ,Levsky    =  7, Sofia       =  7
   ,ChernoMore    , Varna       =  8
   ,Loko      = 10, Plowdyv     = 10
   ,Marek
 //|---------------|----------------|
 };

struct club
{
    int club_place;
    char club_name[11];
    char club_city[12];
};

void printClub(struct club * club, int list_number);

int main(void)
{
    enum BULGARCLUBS place = 0;
    enum BULGARCLUBS city = 0;
    int list_number = 0;
    struct club clubs[12] = {};
    char * clubs_place[][2] =
    {
       {                           },
       {"Ludogorec" , "Razgrad"    },
       {                           },
       {"Litex"     , "Lovech"     },
       {                           },
       {"Beroe"     , "StaraZagora"},
       {                           },
       {"Levsky"    , "Sofia"      },
       {"ChernoMore", "Varna"      },
       {                           },
       {"Loko"      , "Plowdyv"    },
       {"Marek"     , "Marek"      }
    };
//-----------------------------------------------------------------------------
    for(place = 0; place < 12; place++)
    {
        if( clubs_place[place][0] )
        {
            clubs[place].club_place = place;
            strcpy(clubs[place].club_name, clubs_place[place][0]);
            strcpy(clubs[place].club_city, clubs_place[place][1]);
        }
    }
//-----------------------------------------------------------------------------
    printf(" N| place |    club    |    city    |\n");
    printf("-------------------------------------\n");
    list_number = 1;
    for(city = 0; city < 12; city++)
    {
        switch( city )
        {
            case Razgrad:
                printClub(&clubs[city], list_number++);
                break;
            case Lovech:
                printClub(&clubs[city], list_number++);
                break;
            case StaraZagora:
                printClub(&clubs[city], list_number++);
                break;
            case Sofia:
                printClub(&clubs[city], list_number++);
                break;
            case Varna:
                printClub(&clubs[city], list_number++);
                break;
            case Plowdyv:
                printClub(&clubs[city], list_number++);
                break;
            case Marek:
                printClub(&clubs[city], list_number++);
                break;
        }
    }
    printf("-------------------------------------\n");

    return 0;
}

//-----------------------------------------------------------------------------

void printClub(struct club * club, int list_number)
{
    printf("%2d|%5d  |%-12s|%-12s|\n", list_number,
                                       club->club_place,
                                       club->club_name,
                                       club->club_city);
}
