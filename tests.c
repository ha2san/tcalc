#define _GNU_SOURCE
#include <sys/types.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "data_structure.h"
#include "tcalc.h"

#define PREC 0.001
#define calcul(x,y) ck_assert_double_eq_tol(main_calcul((char*)(x),(&ret)),(y),(PREC))

START_TEST(example_test)
{
    int ret;
    calcul("--1",1);
    calcul("-(-1)",1);
    calcul("9",9);
    calcul("(3+2)", 5);
    calcul("(3+2)-1",4);
    calcul("5--2",7);
    calcul("0.32",0.32);
    calcul("0.32+0.68",1);
    calcul("((3))",3);
    calcul("10%2",0);
    calcul("10*2",20);
    calcul("10/2",5);
    calcul("2^8",256);
    calcul("2^8*2",512);
    calcul("1*2+3/2",3.5);
    calcul("1*2%4/2",0);
    calcul("3.4%6",3);

    double value = run_argument("1+1");
    ck_assert_double_eq_tol((int)value,2,PREC);

    value = run_argument("--help");
    ck_assert_int_eq((int)value,EXIT_SUCCESS);

    value = run_stdin();
    ck_assert_int_eq((int)value,EXIT_SUCCESS);

    value = run_stdin();
    ck_assert_int_eq((int)value,EXIT_SUCCESS);

    value = run_stdin();
    ck_assert_int_eq((int)value,EXIT_SUCCESS);

    value = run_stdin();
    ck_assert_int_eq((int)value,EXIT_SUCCESS);
}
END_TEST

START_TEST(error_test)
{
    int ret;

    main_calcul((char*)"+",&ret);
    ck_assert_int_eq(ret,EXIT_FAILURE);
    main_calcul((char*)"((1+1)",&ret);
    ck_assert_int_eq(ret,EXIT_FAILURE);
    main_calcul((char*)"(3)1+2",&ret);
    ck_assert_int_eq(ret,EXIT_FAILURE);
    main_calcul((char*)"((3))",&ret);
    ck_assert_int_eq(ret,EXIT_SUCCESS);
    main_calcul((char*)"%1+1",&ret);
    ck_assert_int_eq(ret,EXIT_FAILURE);
    main_calcul((char*)"1&1",&ret);
    ck_assert_int_eq(ret,EXIT_FAILURE);
    main_calcul((char*)"()+1",&ret);
    ck_assert_int_eq(ret,EXIT_FAILURE);
}
END_TEST

int main()
{
    Suite* s = suite_create("tests");
    TCase *tc1 = tcase_create("basic tests");
    suite_add_tcase(s, tc1);

    /* Add your own tests here */
    tcase_add_test(tc1, example_test);
    tcase_add_test(tc1, error_test);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);

    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

