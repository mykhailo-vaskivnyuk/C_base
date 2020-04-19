#include <stdio.h>
//#include <windows.h>
//#include <locale.h>
#include <string.h>
//STRINGS

int main(void)
{
    f_1();
    return;

    //SetConsoleCP(65001);
    //SetConsoleOutputCP(65001);
    system("chcp 65001 > nul"); // 1251 - windows-1251, 65001 - utf-8
    //char *locale = setlocale(LC_ALL, "Russian");
    printf("ПРИВІТ");
    return;

    //int *p1; // = {1, 2, 3};

    //p1 = "Klingon";
    //p1[0] = 5;

    char ch = '\0';
    while(scanf("%c", &ch))
    {
        ch = getchar();
        //_flushall();
        //printf("%c\n", ch);
        printf("%c - %d\n", ch, ch);
    }

    //printf("Hello World!\n");
    return 0;
}

void f_1(void)
{
    //strlen();
    //strcat();
    //strncat();
    //strcmp();
    //strncmp();
}
