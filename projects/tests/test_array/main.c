#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <mem.h>
//#include <unistd.h>
#include <windows.h>
#include <string.h>

void takeArray(int (* array)[5]);
void takeArray_1(void *, int, int);
void takeArray_2(int, int (* array)[*]);
bool ff(){ return 1; }
bool f(bool a, bool b){ a = a + b; return a; }
void Ravlyk  (void);
void Ravlyk_1(int N, int *array);
void Ravlyk_2(int N, int *array);
//void Test(){ printf("%d\n", ++aa); };
void printArray(int N, int *array, int cur_position);
void printArray_2(int N, int *array, int cur_position);

int main(void)
{
    //static int aa = 100;
    //Test();
    //Test_1();
    //return 0;

    Ravlyk();
    return 0;

    int a = 100;
    int * ptr = &a;
    //char a : 2;
    puts("\0");

    printf("adr of a: %d, val a: %d, ptr pointed to: %d, adr of ptr: %d\n", (int)&a, a, (int)ptr, (int)&ptr);
    puts("\0");
    //return 0;

    bool (*ptrf)();
    ptrf = ff;
    ptrf();
    ptrf = f;
    ptrf(a, a);
    (*ptrf)(a, a);

    int arr[5][7] = { {200, 2}, {}};
    printf("arr   > %d\n", sizeof arr);
    printf("*arr  > %d\n", sizeof *arr);
    printf("**arr > %d\n", sizeof **arr);
    puts("\0");

    printf("address of arr       > %d, arr points to       > %d\n", ((int)&arr) / 4, (int)arr / 4);
    puts("\0");

    printf("address of arr[1]    > %d, arr[1] points to    > %d\n", ((int)&arr[1]) / 4, (int)arr[1] / 4);
    puts("\0");

    printf("address of arr[1][0] > %d, arr[1][0] has value > %d\n", ((int)&arr[1][0]) / 4, (int)arr[1][0] / 4);
    puts("\0");
    //return 0;

    int i = 0;
    int j = 0;
    int N = 5;
    int M = 7;

    /*int (*pt)[5] = NULL;
    pt = arr;*/

    //typedef int (*arr_type)[];
    //arr_type arr_1 = NULL;

/*    typedef int (*arr_type_N)[N];
    arr_type_N arr_N;

    //arr_1 = arr;
    //printf("%d\n", arr_1[0][1]);
    //takeArray(arr);
    //arr_2 = (arr_type_5)arr_1;
    arr_N = (arr_type_N)malloc(5 * sizeof(int));
    arr_N[4][4] = 12345;
    printf("%d\n", arr_N[4][4]);
    printf("arr_N   > %u\n", sizeof arr);
    printf("*arr_N  > %u\n", sizeof *arr);
    printf("**arr_N > %u\n\n", sizeof **arr);

    takeArray_1(arr, 5, 5);
    printf("%d\n", arr[4][4]);
*/
    takeArray_2(7, arr);
    return 0;


/*--------------------
 *  malloc
 *  realloc
 *  calloc
 *  free
--------------------*/

//  VARIANT 1 ---------------------------------------------
/*  int **array = (int**)malloc(N * sizeof(int*));
    *array = (int*)malloc(N * M * sizeof(int));
    for(i = 1; i < N; i++)
        *(array + i) = *array + (i * M);

//  VARIANT 2 ---------------------------------------------
/*  int **array = (int**)malloc(N * sizeof(int*));
    for(i = 0; i < N; i++)
        array[i] = (int*)malloc(M * sizeof(int));

//  VARIANT 3 ---------------------------------------------
/*  typedef int (*arr_type_M)[M];
    arr_type_M array;
    array = (arr_type_M)malloc(N * M * sizeof(int));*/

//  VARIANT 4 ---------------------------------------------
/*  int (*array)[M];
        array = malloc(N * M * sizeof(int));*/

//  VARIANT 4 ---------------------------------------------
    int (*array)[M];
          array = (int (*)[M])malloc(N * M * sizeof(int));

    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            array[i][j] = i * M + j;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
            printf("%2d:%-2d > %2d  ", i, j, array[i][j]);
        printf("\n");
    }

    puts("\0");

    printf("arr   > %d\n", sizeof array);
    printf("*arr  > %d\n", sizeof *array);
    printf("**arr > %d\n", sizeof **array);
    puts("\0");

    printf("address of arr       > %d, arr points to       > %d\n", ((int)&array) / 4, (int)array / 4);
    puts("\0");

    printf("address of arr[1]    > %d, arr[1] points to    > %d\n", ((int)&array[1]) / 4, (int)array[1] / 4);
    puts("\0");

    printf("address of arr[1][0] > %d, arr[1][0] has value > %d\n", ((int)&array[1][0]) / 4, (int)array[1][0] / 4);
    puts("\0");

//  VARIANT 6 ---------------------------------------------
/*    printf("\n");

    int *ptr = (int*)malloc(N * M * sizeof(int));

    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            ptr[i * M + j] = i * M + j;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
            printf("%2d:%-2d > %2d  ", i, j, ptr[i * M + j]);
        printf("\n");
    }*/

//    printf("\nHello World!\n");

    return 0;
}

void takeArray(int (* array)[5])
{
    printf("%d\n", array[0][0]);
}

void takeArray_1(void * array, int N, int M)
{
    typedef int (*arr_type_M)[M];
    arr_type_M arr;
    arr = (arr_type_M)array;
    arr[N - 1][M - 1] = 100;
    printf("%d\n", arr[N - 1][M - 1]);
}

void takeArray_2(int M, int (* array)[M])
{
    printf("%d %s\n", array[0][0], __FUNCTION__);

}

void Ravlyk()
{
    int array[5][5] = { { 1,  2,  3,  4,  5},
                        { 6,  7,  8,  9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}
                     };

    Ravlyk_1(5, *array);
    puts("\0");
}

void Ravlyk_1(int N, int *array)
{
   int step[4] = {1, N, -1, -N};
   int cur_position = -1;
   int i = 0, k = 0;
   int array_size = N;
   while( N )
   {
       for(i = 0; i < N; i++)
       {
           cur_position += step[k];
           //printf("pos %d > %d\n", cur_position, array[cur_position]);
           printArray(array_size, array, cur_position);
       }
       k  = (k + 1) & 3;
       N -=  k      & 1;
   }
}

void Ravlyk_2(int N, int *array)
{
   int step[4] = {1, N, -1, -N};
   int cur_position = -1;
   int i = 0;
   struct
   {
       unsigned char k : 2;
       unsigned char l : 1;
   } trigger = {0, 0};

   while( N )
   {
       for(i = 0; i < N; i++)
       {
           cur_position += step[trigger.k];
           printf("pos %d > %d\n", cur_position + 1, array[cur_position]);
       }
       trigger.k++;
       N -= ++trigger.l;
   }
}

void printArray(int N, int *array, int cur_position)
{
    static char * screen_area = NULL;
    int i = 0;
    char tmp_str[4] = "";

    if( !screen_area )
    {
        screen_area = malloc(N * N * 3 + N * (1 + 10));
        memset(screen_area, ' ', N * N * 3 + N * (1 + 10));
        for(i = 0; i < N; i++)
            screen_area[(i + 1) * (N * 3 + 10) + i] = '\n';
        screen_area[N * N * 3 + N * (1 + 10) - 1] = '\0';
    }

    sprintf(tmp_str, "%3d", array[cur_position]);
    memcpy(&screen_area[cur_position * 3 + (int)(cur_position / N) + ((int)(cur_position / N) + 1) * 10], tmp_str, 3);
    system("cls");
    puts("\n\n\n\n\n\n");
    puts(screen_area);
    Sleep(200);
    //exit(0);
}

void printArray_2(int N, int *array, int cur_position)
{
    static char * tmp_array = NULL;
    int i = 0, j = 0;

    if( !tmp_array )
    {
        tmp_array = malloc(N * N);
        memset(tmp_array, 0, N * N);
    }

    tmp_array[cur_position] = 1;

    system("cls");
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(tmp_array[i * N + j])
                printf("%3d", array[i * N + j]);
            else
                printf("   ");
        }
        puts("\0");
    }
    //Sleep(100000);
}
