#include <stdio.h>

int myfunc(int *arg1, int *arg2);
int myfunc2(int arg1, int arg2);

int global = 0;

int main(int argc, char *argv[])
{
//    int myfunc(int *arg1, int *arg2);
/*
    int
    char
*/
    int a = 5;
    --a;
    char ch = 'm';
    int *adr;

    {
        printf("value: %i, size: %i\n", a, sizeof(a));
        a++;
//        int a = 15;
//        printf("value: %i, size: %i\n", a, sizeof(a));
    }
//    getchar();
//    scanf("%i", &a);
//    printf("value: %i, size: %i\n", a, sizeof(a));
//    printf("Hello World!\nNew string\n");
//    printf("value: %d\n", ch);
    printf("sum: %i\n", myfunc2(a, 2));
//    printf("%i:%c",argc, *argv[0]);
//    adr = &a;
//    a = *adr + 10;
//    printf("value: %i, size: %i, adr: %i\n", a, sizeof(a), adr);

    return 0;
}

myfunc2(int arg1, int arg2)
{
    int res = 0;
//    printf("%i\n", arg1);
    res = myfunc(&arg1, &arg2) + 10;
//    printf("%i\n", arg1);
    return res;
}

myfunc(int *arg1, int *arg2)
{
    int res = 0;
    res = *arg1 + *arg2 + global;
    *arg1 = 100;
    return *arg1 + *arg2; //++res;
}
