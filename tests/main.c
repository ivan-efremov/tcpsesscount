/**
 * @file tests/main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>


/**
 * @short Тест1
 */
extern int  init_suite1(void);
extern int  cleanup_suite1(void);
extern void test_array_unique_push(void);
extern void test_array_unique_erase(void);



int main()
{
    CU_pSuite pSuite = NULL;

    if(CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("suite1", init_suite1, cleanup_suite1);
    if(pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((CU_add_test(pSuite, "test of array_unique_push()", test_array_unique_push) == NULL) ||
       (CU_add_test(pSuite, "test of array_unique_erase()", test_array_unique_erase) == NULL))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
