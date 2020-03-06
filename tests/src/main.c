#include <ztest.h>

extern void test_suit_placeholder(void);

/* test case main entry */
void test_main(void)
{
    ztest_test_suite(suit_tests,
        ztest_unit_test(test_suit_placeholder));
    ztest_run_test_suite(suit_tests);
}
