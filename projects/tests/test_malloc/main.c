#include <stdio.h>
#include <stdlib.h>

#define COUNT 20

int main(void)
{
    int * int_ptr_first = NULL;
    int * int_ptr_second = NULL;
    int i = 0;

    int_ptr_first = (int *)malloc(COUNT * sizeof(int));
    for(i = 0; i < COUNT; i++)
        int_ptr_first[i] = i;

    int_ptr_second = int_ptr_first;

    int_ptr_first += COUNT/2;
    free(int_ptr_first);

    int_ptr_second = (int *)realloc(int_ptr_second, COUNT * sizeof(int));

    for(i = 0 + COUNT / 2; i < COUNT; i++)
        int_ptr_second[i] = i * 10;

    for(i = 0; i < COUNT; i++)
        printf("%d\n", int_ptr_second[i]);

    return 0;
}
