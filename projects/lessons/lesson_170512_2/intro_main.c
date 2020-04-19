#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
bool  - 1 byte
char  - 1 byte
short - 2 byte
int - 4 byte
long - 4/8 byte
long long - 8 byte
float - 4 byte
double - 8 byte

*/

/*

+
-
/
*
%

*/

int global_counter = 0;
void change_value(int* value);

void test_func(void)
{	
	global_counter++;
}

int add(int a, int b);
int divide(int a, int b);

int main(int argc, char *argv[]) 
{	
	/*test_func();
	
	int res_of_adding = add(10, 20);
	printf("res_of_adding - %i\n", add(10, 20));
	
	int my_value = 4;
	char symbol = 77;
	char symbol2 = 'i';
	char* str = "my string";	
	
	printf("my_value - %i\n", my_value);	
	
	printf("symbol (code 77) - %i\n", symbol);
	printf("symbol (code 77) - %c\n", symbol);
	printf("symbol2 (i) - %i\n", symbol2);
	printf("symbol2 (i) - %c\n", symbol2);
	
	printf("symbol (code 77) - %s\n", str);	
	
	printf("-------------------\n");	
	
	printf("size of int - %i\n", sizeof(int));
	printf("size of short - %i\n", sizeof(short));
	int value = 236;
	
	int decreasing = value - add(10, 20);
	//decreasing--;
	//decreasing = decreasing - 1;
	
	decreasing = (5688 - decreasing);
	decreasing /= 6;
	
	float div_res = ((float)value)/5;
	
	printf("236 - add(10, 20) = %i\n", decreasing);
	
	printf("value/5;= %f\n", div_res);
	
	int from_console = 0;
	scanf("%i", &from_console);	
	printf("from_console = %i\n", from_console);
	*/
	int a = 9;
	printf("a - %i\n", a);
	printf("addr a (operator &)- %p\n", &a);	
	int *p_a = &a;	
	
	printf("p_a - %p\n", p_a);
	printf("p_a - %i\n", p_a);
		
	printf("value a (*p_a) - %i\n", *p_a);
	
	int res_of_adding = add(a, 20);
	
	int test_value = 82;
	printf("1. test_value - %i\n", test_value);
	printf("1. test_value addr - %p\n", &test_value);
	//int result = change_value(&test_value);
	change_value(&test_value);
	printf("2. test_value - %i\n", test_value);
	//printf("2. result - %i\n", result);
	return 0;
}

void change_value(int* p_value)
{
	printf("1. value - %i\n", *p_value);
	printf("1. value addr - %p\n", p_value);
	
	*p_value = -1;
	
	printf("2. value - %i\n", *p_value);
	
	//return *p_value;
}

int add(int a, int b)
{
	
	int div_res = divide(a, b);
	//int res = a+b;
	//	return res;
	a = 83477;
	global_counter++;
	return a+b;
}

int divide(int a, int b)
{
	//int res = a+b;
	//	return res;
	return a/b;
}

