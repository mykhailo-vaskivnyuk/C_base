#include <stdio.h>
#include <strings.h>
#include <stdbool.h>

#define ST "world world"

int f1(int a);
int f2(int b);

int main(void)
{
    int k = -4, l = 3;
    //k -= (2*l++)/4 + 5%(--l);
    k -= 5%(--l) + (2*l++)/4;
    printf("%d", k);
    return 0;

    char str[20] = "world";
    //str = ;
    printf("Hello World!\n");

    //scanf("%s", str);
    printf("%s\n", str);

    printf("len: %d, size: %d\n", strlen(str), sizeof str);
    //printf("%s\n", ST);

    5 > 4 ? 1 : 0; //тернарний оператор Прата 285
    //прочитать функции по строкам
    //10 - масиви
    //11 - по строкам
    //зробити калькулятор
    //тімус погуглити
    printf("%d", f2(5));

    return 0;
}

int f1(int a)
{
    a += 10;
    return a;
}

int f2(int b)
{
    b = f1(b);
    return b;
}

