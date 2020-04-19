/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 8. Типи даних, визначені користувачем (частина 1).
 * Частина 3. Довільне нумерування синонімів перерахування.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 04.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Запрограмуй перерахування BULGARCLUBS (перелік окремих клубів
   болгарської футбольної Прем’єр-ліги) з наступними константами:
   Ludogorec = 1, Litex = 3, Beroe = 5, Levsky - 7, ChernoMore = 8, Loko = 10, Marek = 11.
2. Долучи до вказаних констант альтернативні синоніми - назви міст:
   Razgrad = 1, Lovech = 3, StaraZagora = 5, Sofia - 7, Varna = 8, Plowdyv = 10, Marek = 11.
3. Запрограмуй цикл, в якому:
   - по черзі (в різних рядках) будуть виводитися на екран вказані значення
     і синоніми констант у форматі (номер, клуб, місто) відповідно до значення
     лічильника ітерацій циклу;
   - вибір реалізуй за допомогою оператора switch(f), де f -
     змінна типу перерахування BULGARCLUBS;
   - параметр вибору - назва міста (вказується після case).
*/

#include <stdio.h>

enum BULGARCLUBS
{
    Ludogorec =  1, Razgrad     =  1
   ,Litex     =  3, Lovech      =  3
   ,Beroe     =  5, StaraZagora =  5
   ,Levsky    =  7, Sofia       =  7
   ,ChernoMore    , Varna       =  8
   ,Loko      = 10, Plowdyv     = 10
   ,Marek
 };

int main(void)
{   
    char * cities[] =
    {
        [Ludogorec] = "Razgrad",
        [Litex]     = "Lovech",
        [Beroe]     = "StaraZagora",
        [Levsky]    = "Sofia",
        [ChernoMore]= "Varna",
        [Loko]      = "Plowdyv",
        [Marek]     = "Marek"
    };

    char * clubs[] =
    {
        [Razgrad]     = "Ludogorec",
        [Lovech]      = "Litex",
        [StaraZagora] = "Beroe",
        [Sofia]       = "Levsky",
        [Varna]       = "ChernoMore",
        [Plowdyv]     = "Loko",
        [Marek]       = "Marek"
    };

    enum BULGARCLUBS city;
    int i = 0;
    int list_number = 1;

//-----------------------------------------------------------------------------

    printf(" N|    club    |    city    |\n");
    printf("-----------------------------\n");
    for(i = 0; i < 12; i++)
    {
        if( cities[i] )
            printf("%2d|%-12s|%-12s|\n", list_number++, clubs[i], cities[i]);
    }

//-----------------------------------------------------------------------------

    list_number = 1;
    printf("-----------------------------\n");
    for(city = 0; city < 12; city++)
    {
        switch( city )
        {
            case Razgrad:
                printf("%2d|%-12s|%-12s|\n", list_number++, clubs[city], "Razgrad");
                break;
            case Lovech:
                printf("%2d|%-12s|%-12s|\n", list_number++, clubs[city], "Lovech");
                break;
            case StaraZagora:
                printf("%2d|%-12s|%-12s|\n", list_number++, clubs[city], "StaraZagora");
                break;
            case Sofia:
                printf("%2d|%-12s|%-12s|\n", list_number++, clubs[city], "Sofia");
                break;
            case Varna:
                printf("%2d|%-12s|%-12s|\n", list_number++, clubs[city], "Varna");
                break;
            case Plowdyv:
                printf("%2d|%-12s|%-12s|\n", list_number++, clubs[city], "Plowdyv");
                break;
            case Marek:
                printf("%2d|%-12s|%-12s|\n", list_number++, clubs[city], "Marek");
                break;
        }
    }

//-----------------------------------------------------------------------------

    puts("\0");
    return 0;
}
