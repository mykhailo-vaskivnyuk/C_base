#include <stdio.h>

void sortArray(int * array, int array_size);
void printArrayInt(int * array, int array_size_N, int array_size_M, int array_type, int array_ptr);

int main(void)
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sortArray(array, 10);
    printArrayInt(array, 1, 10, 0, 0);

    printf("Hello World!\n");
    return 0;
}

void sortArray(int * array, int array_size)
{
    int i   = 0;
    int j   = 0;
    int tmp = 0;

    for( i = 1; i < array_size; i++ )
    {
        for( j = i; j > 0; j--)
        {
            if( array[j] < array[j - 1] ) break;

            tmp          = array[j];
            array[j]     = array[j - 1];
            array[j - 1] = tmp;
        }
    }
}

void printArrayInt(int * array, int array_size_N, int array_size_M, int array_type, int array_ptr)
{
    int i     = 0;
    int j     = 0;
    int index = 0;
    int value = 0;

    puts("\0");
    for(i = 0; i < array_size_M; i++)
        printf("%4d ", i + 1);
    puts("\0");

    puts("\0");
    for(i = 0; i < array_size_N; i++)
    {
        for(j = 0; j < array_size_M; j++)
        {
            index = array_type ? (j * array_size_N + i) : (i * array_size_M + j);
            value = array_ptr  ? **((int **)array + index) : *(array + index);
            printf("%4d ", value);
        }
        puts("\0");
    }
    puts("\0");
}
