/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 2. Основи мови С. Частина 2.
 * Частина 20. Підсумкове завдання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 18.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Складіть програму, яка б виконувала наступні дії:
1) заповнює числами деякий двовимірний масив;
2) приймає з клавіатури номери одного рядка і одного стовпчика;
3) перевіряє, чи кількість рядків і стовпчиків у масиві однакова;
4) якщо кількість однакова - міняє місцями відповідні елементи вибраних рядка і стовпчика;
5) якщо кількість неоднакова - встановлює менше з цих двох величин
(кількість рядків і стовпчиків) і міняє місцями відповідну кількість елементів
у вибраному рядку і стовпчику.
Примітки:
а) елементи, що знаходяться на перетині вибраних рядка і стовпчика,
обміну не підлягають (залишаються на місці);
б) зважаючи на попередню примітку, на місці залишаються також ті елементи,
які після можливого обміну мали б стати на місце перетину рядка і стовпчика.
Наприклад, в масиві arr 4 рядки і 5 стовпчиків; вибрано 2-й рядок і 4-й стовпчик;
оскільки 4 менше 5 – міняємо місцями всі елементи 4-го стовпчика з
першими 4-ма елементами 2-го рядка). При цьому елемент arr[2][4] є "недоторканим",
так само, як елементи arr[2][2] і arr[4][4].
*/

#include <stdio.h>
#define N 5 //row count
#define M 4 //column count

void printArray(int (*array)[M]); //function for printig array
void iptRowColumnNumbers(int *row, int *column); //function for entering row and column numbers

int main(void)
{
    int minNM = 0;
    int i = 0, j = 0;
/*    int array[N][M] = {{ 1,  1,  1,  1,  1},
                       { 1,  1,  1,  2,  1},
                       { 1,  1,  1,  3,  1},
                       {11, 12, 13,  4, 15},
                       { 1,  1,  1,  5,  1}};*/
    int array[N][M] = {{ 1,  1,  1,  1},
                       { 1,  1,  1,  2},
                       {11, 12, 13,  3},
                       { 1,  1,  1,  4},
                       { 1,  1,  1,  5}};
    int tmp = 0;
    int row = 0, column = 0;

    printf("ARRAY BEFORE\n");
    printArray(array);

    iptRowColumnNumbers(&row, &column);

    //user enters row and column numbers that begin from 1,
    //but array indexes begin from 0
    row--;
    column--;

    N <= M ? (minNM = N) : (minNM = M);

    for(i = 0; i < minNM; i++)
    {
            if(row == i || column == i) continue;
            tmp = array[row][i];
            array[row][i] = array[i][column];
            array[i][column] = tmp;
    }

    printf("ARRAY AFTER\n");
    printArray(&array[0]);

    getch();
    return 0;
}

void printArray(int array[][M])
{
    int i = 0, j = 0;

    for(i = 0; i <= M; i++) printf("%3d", i);
    printf("\n");
    for(i = 0; i <= M; i++) printf("---");
    printf("\n");

    for(i = 0; i < N; i++)
    {
        printf("%2d:", i + 1);

        for(j = 0; j < M; j++)
        {
            printf("%3d", array[i][j]);
        }

        printf("\n");
    }
    printf("\n");
}

void iptRowColumnNumbers(int *row, int *column)
{
    while(1)
    {
        printf("ENTER ROW NUMBER FROM 1 TO %d: ", N);
        _flushall();
        *row = 0;
        scanf("%d", row);
        printf("\n");
        if(*row > 0 && *row <= N) break;
        printf("WRONG ROW NUMBER! TRY AGAIN!\n");
    }

    while(1)
    {
        printf("ENTER COLUMN NUMBER FROM 1 TO %d: ", M);
        _flushall();
        *column = 0;
        scanf("%d", column);
        printf("\n");
        if(*column > 0 && *column <= M) break;
        printf("WRONG COLUMN NUMBER! TRY AGAIN!\n");
    }
}
