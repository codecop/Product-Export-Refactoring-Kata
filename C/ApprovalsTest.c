#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>

#include "Approvals.c"

static void test_approvals_name(void** state)
{
    (void)state; /* unused */

    assert_string_equal("ApprovalsTest.foo.approved.txt",
                        approvals_file_name_for(__FILE__, "foo", true, "txt"));
}

static void test_save_load(void** state)
{
    (void)state; /* unused */

    const char* s = "abc123";
    approvals_save("foo", s);
    const char* r = approvals_load("foo");
    assert_string_equal(s, r);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_approvals_name), /* */
        cmocka_unit_test(test_save_load),      /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
