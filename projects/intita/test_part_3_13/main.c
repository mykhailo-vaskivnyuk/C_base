/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 3. Процедури і функції.
 * Частина 13. Підсумкове завдання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 19.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму, що виконує наступні дії:
1) приймає з клавіатури деяке N-цифрове додатне ціле число (з перевіркою на додатність і на кількість цифр за допомогою циклу do-while);
2) за допомогою процедури Div() розбиває його на окремі цифри (справа наліво), які записує в масив;
3) приймає з клавіатури число K- номер деякої цифри, починаючи з 1;
4) за допомогою функції NSymbol() знаходить і повертає K-ту цифру в числі, рахуючи зліва направо (функцію викликати, якщо K<=N, інакше вивести повідомлення про помилку).
*/

#include <stdio.h>
#define FIGURES_COUNT 3

void iptIntNumber(int *number); //function to enter number
int cntFigures(int number); //function to count figures in number
void Div(int number, int array[]); //function divides number into figures
int NSymbol(int position, int array[], int *error); //function gets figure by its position

int main(void)
{
    int number = 0;
    int array[FIGURES_COUNT] = {};
    int k = 0; //figure position
    int figure = 0;
    int error = 0;

    iptIntNumber(&number);
    printf("YOU ENTERED NUMBER %d\n\n", number);

    Div(number, array);

    printf("ENTER FIGURE POSITION FROM 1 TO %d: ", FIGURES_COUNT);
    _flushall();
    scanf("%d", &k);
    printf("\n");

    figure = NSymbol(k, array, &error);

    if(!error)
        printf("THE FIGURE POSITION IS %d\nTHE FIGURE IS %d\n", k, figure);

    return 0;
}

void iptIntNumber(int *number)
{
    do
    {
        printf("ENTER 3-FIGURES NUMBER: ");
        _flushall();
        *number = 0;
        scanf("%d", number);
        printf("\n");
        if(*number > 0 && cntFigures(*number) == FIGURES_COUNT) break;
        printf("WRONG NUMBER! TRY AGAIN!\n");
    }
    while(1);
}

int cntFigures(int number)
{
    int figures_count = 0;

    do
    {
        number /= 10;
        figures_count++;
    }
    while(number);

    return figures_count;
}

void Div(int number, int array[])
{
    int i = 0;

    do
    {
       array[i++] = number % 10;
       number /= 10;
    }
    while(number && i < FIGURES_COUNT);
}

int NSymbol(int position, int array[], int *error)
{
    if(position < 1 || position > FIGURES_COUNT)
    {
        printf("FIGURE POSITION IS TO BE FROM 1 TO %d, BUT NOT %d\n", FIGURES_COUNT, position);
        printf("THE FIGURE CAN NOT BE SHOWN!\n");
        *error = 1;
        return 0;
    }
    return array[FIGURES_COUNT - position];
}
