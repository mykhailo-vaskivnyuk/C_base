#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main(void)
{
    printf("Hello World!\n");
    printf("------------\n");

/*  ÍÅ ÏÐÀÖÞª
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("ïðèâ³ò");
*/

/*
    if(5 > 10)
        printf("YES\n");
    else
        printf("NO\n");
*/

/*
    int c = 0;
    for(c; c <= 10; c++)
        printf("%d\n", c);
*/

/*
    float a, b;
    scanf("%f%f", &a, &b);
    printf("%f\n%f\n", a, b);
*/

/*
    char l = 'b';
    int n = 1;
    switch(n)
    {
        case 1:
            printf("a");
            break;
        case 2:
            printf("b");
            break;
        case 3:
            printf("c");
            break;
        default:
            printf("d");
    }
*/

/*
    int n;
    while(1)
    {
        scanf("%d", &n);
        printf(">%d\n", n);
        getchar();
    }
*/
    getch(); //#include <conio.h>
    return 0;
}
