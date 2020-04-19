#include "test.h"
#include <conio.h>

int main(void)
{
    sTest test_1;
    sTest test_2;

    puts("\0");

    test_init(&test_1);
    test_1.data = 10;
    test_1.data_change();
    printf("test.data   = %d\n", test_1.data);

    getch();
    test_init(&test_2);
    test_2.data = 5;
    test_2.data_change();
    printf("test.data   = %d\n", test_2.data);

    getch();
    test_set_current(&test_1);

    puts("\0");
    printf("test.data   = %d\n", test_1.data);
    getch();
    test_1.data -= 98;
    printf("test.data   = %d\n", test_1.data);
    getch();
    test_1.data_change();
    printf("test.data   = %d\n", test_1.data);
    getch();
    test_1.data_change();
    printf("test.data   = %d\n", test_1.data);

    puts("\0");
    getch();
    return 0;
}
