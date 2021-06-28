/**
 * @file tests/test1.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "array_unique.h"


static struct array_unique array;


int init_suite1(void)
{
    return array_unique_init(&array, 4);
}

int cleanup_suite1(void)
{
    array_unique_destroy(&array);
    return 0;
}

void test_array_unique_push(void)
{
    uint64_t key = 0ul;
    for(key = 0ul; key < 20ul; key += 2) {
        CU_ASSERT(array_unique_push(&array, key) == 1);
    }
    CU_ASSERT(array_unique_size(&array) == 10);
    CU_ASSERT(array_unique_push(&array, 2ul) == 0);
    CU_ASSERT(array_unique_push(&array, 4ul) == 0);
    CU_ASSERT(array_unique_push(&array, 6ul) == 0);
    array_unique_print(&array);
}

void test_array_unique_erase(void)
{
    CU_ASSERT(array_unique_size(&array) == 10);
}
