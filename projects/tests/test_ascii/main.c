#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    unsigned int symbol = '\0';
    unsigned int symbol_max_value = 255;
    int i = 0;
    int j = 0;
/*    if( isupper('f') )
        printf("%s\n\n", "done");
    else
        printf("%c\n\n", toupper('f'));

    return 0;
    //system("chcp 1251");
    //printf("%d :: %c :: |", 'Б', 'Б');
    //return 0;
*/
/*    while( 1 )
    {
        printf("> ");
        scanf("%d", &symbol);
        printf("%d :: %c :: !\n", symbol, symbol);
        if( getch() == 'q') break;
    }
*/
    for(i = 0; i <= (int)symbol_max_value/10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if( !(symbol <= symbol_max_value) ) break;
            printf("%0x :: %c :: !\n", symbol, symbol);
            symbol++;
        }
        puts("=============");
        getch();
    }

    return 0;
}

