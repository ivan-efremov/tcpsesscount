/**
 * @file tests/test1.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "array_unique.h"


static struct array_unique array;


int initSuite1(void)
{
    return array_unique_init(&array, 4);
}

int cleanSuite1(void)
{
    array_unique_destroy(&array);
    return 0;
}

void testArrayUniquePush(void)
{

}

void testArrayUniqueErase(void)
{

}
