#include "test.h"

static int     test_current_id;
static int     test_count     ;
static sTest * test_current   ;

static void    test_data_change(void);

void test_init(sTest * test)
{
    test->id          = test_count++;
    test->data        = 0;
    test->data_change = test_data_change;
    test_current_id   = test->id;
    test_current      = test;
}

void test_data_change(void)
{
    sTest * self = test_current;

    self->data = self->data * self->data;
}

void test_set_current(sTest * test)
{
    test_current    = test;
    test_current_id = test->id;
}
