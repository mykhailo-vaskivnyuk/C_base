#include <stdio.h>
#include <windows.h>
//#include <wincon.h>

int main(void)
{
    //SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE );
    //SetConsoleCP(1251);

    COORD crd = {10, 10};
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), crd );
    printf("Hello World!\n");

    crd.X = 1;
    crd.Y = 1;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), crd );
    printf("Hello World!\n");

    crd.X = 10;
    crd.Y = 1;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), crd );
    printf("!!!!! World!\n");

    return 0;
}
