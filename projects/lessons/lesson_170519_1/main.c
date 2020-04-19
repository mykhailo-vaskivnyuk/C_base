#include <stdio.h>

void factorial(int a, int *result);

int main(void)
{
    int a = 5;
    int result = 0;
    factorial(a, &result);
    printf("FACTORIAL %d is %d\n", a, result);
    return 0;
}

/*
int factorial(int a)
{
   printf("%d\n", a);
   if(a <= 0)
       return 0;
   if(a == 1)
       return 1;
   return a-- * factorial(a);
}
*/

void factorial(int a, int *result)
{
   printf("%d\n", a);
   if(a <= 0)
       *result = 0;
   else if(a == 1)
       *result = 1;
   else
   {
       factorial(a - 1, result);
       *result *= a;
   }
}
