#include <setjmp.h> /* used by mocka */
#include <stdarg.h> /* used by mocka */
#include <stddef.h> /* used by mocka */

#include <cmocka.h>

static void test_foo(void** state)
{
    (void)state; /* unused */

    /* TODO: implement this test */
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_foo), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
