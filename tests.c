#define _GNU_SOURCE
#include <sys/types.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "data_structure.h"
#include "tcalc.h"

#define PREC 0.001
#define calcul(x) main_calcul((char*)(x))

START_TEST(example_test) {
    ck_assert_double_eq_tol(calcul("--1"),1,PREC);
    ck_assert_double_eq_tol(calcul("-(-1)"),1,PREC);
    ck_assert_double_eq_tol(calcul("9"),9,PREC);
    ck_assert_double_eq_tol(calcul("(3+2)"), 5,PREC);
    ck_assert_double_eq_tol(calcul("(3+2)-1"),4,PREC);
    ck_assert_double_eq_tol(calcul("5--2"),7,PREC);
}
END_TEST


int main()
{
    Suite* s = suite_create("Week 01 tests");
    TCase *tc1 = tcase_create("basic tests");
    suite_add_tcase(s, tc1);

    /* Add your own tests here */
    tcase_add_test(tc1, example_test);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);

    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

