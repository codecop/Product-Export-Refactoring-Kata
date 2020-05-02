#include <setjmp.h> /* for mocka */
#include <stdarg.h> /* for mocka */
#include <stddef.h> /* for mocka */

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
    approvals_delete("foo");
}

static void test_approval(void** state)
{
    (void)state; /* unused */

    approvals_verify("abc123", __FILE__, "test_approval", "txt");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_approvals_name), /* */
        cmocka_unit_test(test_save_load),      /* */
        cmocka_unit_test(test_approval),       /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
