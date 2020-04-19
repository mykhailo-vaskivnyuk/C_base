#include <stdio.h>
#include "first.h"
#define BIT_1 0x01

//как поменять два числа xor-ом?
//xor шифрование

int main(void)
{
    int i = 0;
    char a = 5;

    f();

    printf("\n");
    for(i = 7; i >= 0; i--)   
    {
        printf("%d", ((a >> i) & BIT_1) ? 1 : 0);
    }
    printf("\n");

    return 0;
}
