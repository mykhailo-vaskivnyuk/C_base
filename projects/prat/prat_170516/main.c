#include <stdio.h>
//#include <math.h>
#include <conio.h>

void f_1(void);

int main(void)
{
    f_1();
    return;

    printf("12345\n");
    printf("12345\b\b\b\b\b\b");
    int c = 0;
    c = getch();
    c = getch();
    //c = getch();
    printf("%i %c", c, c);
    return 0;

    //int mass[5] = {0, 1, 2, 3, 10};
    int mass[6] = {0};
    int cr = 0;
    //int msz = 5;
    //int mass2[msz];
    int mas_1[][2] = {{1, 2}, {3, 4}};
    int (*mas_2)[2]; // = {{11, 12}, {13, 14}};

    mas_2 = mas_1;
    printf("%d\n", mas_2[0]);

    mas_1[1][1] = 100;
    for(cr; cr < 4; cr++)
        printf("%2d\n", mas_2[0][cr]);
    return 0;

    for(cr; cr < 6; cr++)
        printf("%2d\n", mass[cr]);

    printf("Hello World!\n");
    return 0;
}

void f_1(void)
{

}
