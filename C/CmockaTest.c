#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>

static void int_equal(void** state)
{
    (void)state; /* unused */

    assert_int_equal(0, 0);
}

static void stringt_equal(void** state)
{
    (void)state; /* unused */

    assert_string_equal("foo", "foo");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(int_equal),     /* */
        cmocka_unit_test(stringt_equal), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
