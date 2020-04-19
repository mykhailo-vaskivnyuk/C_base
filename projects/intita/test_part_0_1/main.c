/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Підсумкове тестове завдання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 14.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/*
Завдання.
If-Else.
  Хмарочос має N поверхів і один під'їзд. На кожному поверсі - по 3 квартири. Ліфт може зупинятися тільки на
  непарних поверхах. Написати програму, яка визначає номер поверху, на якому повинен зупинитися ліфт, якщо
  пасажир при посадці набирає номер потрібної йому квартири M.
  Вхідні дані: кількість поверхів; номер поверху, на якому сідає пасажир; номер потрібної квартири.
  Вихідний результат - номер поверху зупинки ліфта.
  Примітка. Якщо квартира знаходиться на парному поверсі - ліфт повинен зупинитися на сусідньому непарному,
  який відповідає коротшому пройденому шляху (залежно від того, з якого поверху почався рух, і від напрямку руху -
  вверх чи вниз).
  Кількість поверхів N можна вводити з клавіатури або задавати як константу (через директиву #define).

Switch-Case.
  Маємо рівнобедрений прямокутний трикутник з наступними елементами: 1 - катет a, 2 - гіпотенуза b,
  3 - висота h, що виходить з прямого кута, 4 - площа S. Написати програму, яка:
  - приймає з клавіатури номер потрібного елемента;
  - приймає з клавіатури значення потрібного елемента;
  - на основі введеного значення - розраховує значення всіх інших елементів трикутника.

Наступні дві задачі - можна на вибір взяти лише одну.
Цикли1.
  Фермеру потрібно на 100 тис. грн. придбати 100 голів скота. Оптова тваринницька агрофірма пропонує
  поголів'я за наступними цінами: за бика - 10 тис. грн., за корову - 5 тис. грн., за теля - 500 грн. Написати
  програму, яка на основі вказаних вхідних даних обрахує кількість різних видів поголів'я, придбаного
  фермером.

Цикли2.
  Написати програму, яка в зростаючому порядку виводить на екран всі тризначні числа, які не
  містять однакових цифр. Операції ділення і знаходження остачі від ділення не використовувати!
*/

#include <stdio.h>
#include <math.h>
#include <conio.h>

#define TEST_1 //TEST_1, TEST_2, TEST_3

#define FLOOR_COUNT         30
#define APARTMENTS_ON_FLOOR  3

void fTriangle(void);
void fLift(void);
void fThreeNumbers(void);

int main(void)
{

    while( 1 )
    {
#ifdef TEST_1
        fTriangle();
#endif

#ifdef TEST_2
        fLift();
#endif

#ifdef TEST_3
        fThreeNumbers();
#endif
        puts("\0");
        puts("TO TRY AGAIN PRESS ANY KEY. TO EXIT - PRESS 'q'.");
        if( 'q' == getch() ) break;
    }

    return 0;
}

void fTriangle(void)
{
    typedef struct
    {
        float katet;
        float gipotenusa;
        float height;
        float square;
    } sTriangle;

    typedef enum
    {
        KATET      = 1
       ,GIPOTENUSA
       ,HEIGHT
       ,SQUARE
    } eTriangleElement;

    eTriangleElement triangle_element = 0;
    sTriangle triangle = {0, 0, 0, 0};
    float triangle_element_value = 0;
//-----------------------------------------------------------------------------
//  Вводимо ЕЛЕМЕНТ трикутника
//-----------------------------------------------------------------------------
    puts("\0");
    while( 1 )
    {
        puts("INPUT TRIANGLE ELEMENT: 1 - KATET, 2 - GIPOTENUSA, 3 - HEIGHT, 4 - SQUARE");
        fflush(stdin);
        triangle_element = 0;
        scanf("%u", &triangle_element);
        if( triangle_element > 0 && triangle_element <= 4) break;
        puts("\0");
        puts("WRON TRIANGLE ELEMENT. TRY AGAIN!");
    }
//-----------------------------------------------------------------------------
//  Ввводимо ЗНАЧЕННЯ елемента трикутника
//-----------------------------------------------------------------------------
    while( 1 )
    {
        puts("INPUT TRIANGLE ELEMENT VALUE:");
        fflush(stdin);
        triangle_element_value = 0;
        scanf("%f", &triangle_element_value);
        if( triangle_element_value > 0) break;
        puts("WRON TRIANGLE ELEMENT VALUE. TRY AGAIN.");
    }
    puts("\0");
//-----------------------------------------------------------------------------
//  В залежності від введенного елемента визначаємо значення РЕШТИ елементів
//-----------------------------------------------------------------------------
    switch( triangle_element )
    {
        case KATET:
            triangle.katet = triangle_element_value;
            triangle.square = pow(triangle.katet, 2) / 2;
            triangle.gipotenusa = sqrt(2 * 2 * triangle.square);
            triangle.height = triangle.gipotenusa / 2;
            printf("YOU'V INPUT KATET = %.2f\n", triangle.katet);
            break;
        case GIPOTENUSA:
            triangle.gipotenusa = triangle_element_value;
            triangle.height = triangle.gipotenusa / 2;
            triangle.katet = sqrt(pow(2 * triangle.height, 2) / 2);
            triangle.square = pow(triangle.katet, 2) / 2;
            printf("YOU'V INPUT GIPOTENUSA = %.2f\n", triangle.gipotenusa);
            break;
        case HEIGHT:
            triangle.height = triangle_element_value;
            triangle.gipotenusa = triangle.height * 2;
            triangle.katet = sqrt(pow(triangle.gipotenusa, 2) / 2);
            triangle.square = pow(triangle.katet, 2) / 2;
            printf("YOU'V INPUT HEIGHT = %.2f\n", triangle.height);
            break;
        case SQUARE:
            triangle.square = triangle_element_value;
            triangle.katet = sqrt(2 * triangle.square);
            triangle.gipotenusa = sqrt(2 * pow(triangle.katet, 2));
            triangle.height = triangle.gipotenusa / 2;
            printf("YOU'V INPUT SQUARE = %.2f\n", triangle.square);
            break;
    }
//-----------------------------------------------------------------------------
//  Виводимо РЕЗУЛЬТАТ на екран
//-----------------------------------------------------------------------------
    puts("\0");
    puts("TRIANGLE ELEMENTS VALUES:\n");
    printf(" - KATET:      %7.2f\n", triangle.katet);
    printf(" - GIPOTENUSA: %7.2f\n", triangle.gipotenusa);
    printf(" - HIGHT:      %7.2f\n", triangle.height);
    printf(" - SQUARE:     %7.2f\n", triangle.square);
}

void fLift(void)
{
    int passenger_floor = 0;
    int apartment = 0;
    int floor_to_go = 0;

//-----------------------------------------------------------------------------
//  Вводимо номер ПОВЕРХУ, на якому знаходиться пасажир
//-----------------------------------------------------------------------------
    puts("\0");
    while( 1 )
    {
        printf("INPUT PASSENGER FLOOR (1 TO %d): ", FLOOR_COUNT);
        fflush(stdin);
        passenger_floor = 0;
        scanf("%d", &passenger_floor);
        if( passenger_floor > 0 && passenger_floor <= FLOOR_COUNT) break;
        puts("\0");
        puts("WRON PASSENGER FLOOR. TRY AGAIN!");
    }
//-----------------------------------------------------------------------------
//  Вводимо номер КВАРТИРИ, в яку направляється пасажир
//-----------------------------------------------------------------------------
    while( 1 )
    {
        printf("INPUT APARTMENT (1 TO %d): ", FLOOR_COUNT * APARTMENTS_ON_FLOOR);
        fflush(stdin);
        apartment = 0;
        scanf("%d", &apartment);
        if( apartment > 0 && apartment <= FLOOR_COUNT * APARTMENTS_ON_FLOOR) break;
        puts("\0");
        puts("WRON APARTMENT. TRY AGAIN!");
    }
//-----------------------------------------------------------------------------
//  Визначаємо ПОВЕРХ, на який напрявляється пасажир
//-----------------------------------------------------------------------------
    floor_to_go = (int)(apartment / APARTMENTS_ON_FLOOR);
    if( apartment % APARTMENTS_ON_FLOOR != 0 ) floor_to_go++;
    puts("\0");
    printf("APARTMENT:    %d\n", apartment);
    printf("FLOOR TO GO:  %d", floor_to_go);
//-----------------------------------------------------------------------------
//  Визначаємо ПОВЕРХ, на якому зупиниться ліфт
//-----------------------------------------------------------------------------
    if( (floor_to_go & 1) == 0 )
    {
        if(floor_to_go > passenger_floor)
            floor_to_go = floor_to_go - 1;
        else if(floor_to_go < passenger_floor)
            floor_to_go = floor_to_go + 1;
    }
//-----------------------------------------------------------------------------
//  Виводимо РЕЗУЛЬТАТ на екран
//-----------------------------------------------------------------------------
    puts("\0");
    printf("RESULT FLOOR: %d\n", floor_to_go);
}

void fThreeNumbers()
{
    static int i = 1, j = 0;
           int k = 0;
//-----------------------------------------------------------------------------
/*  При кожному виклику функції будемо виводи максимум по 10 чисел.
    Для цього об'являємо лічильники циклів (сотні та десятки) як static,
      щоб вони зберігали свої значення між викликами функції.
    Відповідно організовуємо прирощення та скидання лічильників. */
//-----------------------------------------------------------------------------
    for( ; i <= 9; i++ ){
        for( ; j <= 9; ){
            if( j == i ){
                j++;
                continue;
            }
            for( k = 0; k <= 9; k++ ){
                if( k == i || k == j ) continue;
                printf("%d\n", i * 100 + j * 10 + k);
            }
            j++;
            return;
        }j = 0;
    }i = 1;
}
