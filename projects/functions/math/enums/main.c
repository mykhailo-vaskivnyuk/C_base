#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int checkSubEnum(int * enum_1, int enaum_size_1, int * enum_2, int enum_size_2);
int * createEnum(int enaum_size);
void fillEnum(int * array, int array_size);
int checkUnic(int * array, int array_size, int number);
void printArray(int * array, int array_size);

int main(void)
{
    int enum_size_1 = 10;
    int enum_size_2 = 5;
    int * enum_1 = NULL;
    int * enum_2 = NULL;

//-------------------------------------------

    enum_1 = createEnum(enum_size_1);
    enum_2 = createEnum(enum_size_2);

//-------------------------------------------

    fillEnum(enum_1, enum_size_1);
    fillEnum(enum_2, enum_size_2);

//-------------------------------------------

    checkSubEnum(enum_1, enum_size_1, enum_2, enum_size_2);

    return 0;
}

int checkSubEnum(int * enum_1, int enaum_size_1, int * enum_2, int enum_size_2)
{
    return 0;
}

int * createEnum(int array_size)
{
    int * array = (int*)malloc(array_size * sizeof(int));
    return array;
}

void fillEnum(int * array, int array_size)
{
    int i = 0;
    int number = 0;

    while(i < array_size)
    {
        while(1)
        {
            system("cls");
            printArray(array, i);
            printf("INPUT %d/%d INTEGER NUMBERS: ", i + 1, array_size);
            fflush(stdin);
            number = 0;
            scanf("%d", &number);
            if( checkUnic(array, i, number) ) break;
        }
        array[i++] = number;
    }

}

int checkUnic(int * array, int array_size, int number)
{
    int i = 0;

    if( !array_size ) return 1;
    for(i = 0; i < array_size; i++)
        if( array[i] == number )
        {
            printf("NUMBER %d ALREADY EXISTS!", number);
            getch();
            return 0;
        }
    return 1;
}

void printArray(int * array, int array_size)
{
    int i = 0;

    printf("ENUM: ");
    if( array_size )
        for(i = 0; i < array_size; i++)
            printf("%d ", array[i]);
    printf("\n");
}
