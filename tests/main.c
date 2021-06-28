/**
 * @file tests/main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>


/**
 * @short Тест1
 */
extern int  initSuite1(void);
extern int  cleanSuite1(void);
extern void testArrayUniquePush(void);
extern void testArrayUniqueErase(void);



int main()
{
    CU_pSuite pSuite = NULL;

    if(CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("suite1", initSuite1, cleanSuite1);
    if(pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((CU_add_test(pSuite, "test of array_unique_push()", testArrayUniquePush) == NULL) ||
       (CU_add_test(pSuite, "test of array_unique_erase()", testArrayUniqueErase) == NULL))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
