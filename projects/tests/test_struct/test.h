#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct test
{
    int    id;
    int    data;
    void (*data_change)(void);
} sTest;

void test_init       (sTest *);
void test_set_current(sTest *);

#endif // TEST_H
