#include <setjmp.h> /* for mocka */
#include <stdarg.h> /* for mocka */
#include <stddef.h> /* for mocka */

#include <cmocka.h>

#include "Approvals.c"
#include "Approvals.h"

static void test_approvals_name(void** state)
{
    (void)state; /* unused */

    assert_string_equal("ApprovalsTest.foo.approved.txt",
                        approvals_file_name_for(__FILE__, "foo", true, "txt"));
}

static void test_approvals_save_load(void** state)
{
    (void)state; /* unused */

    const char* s = "abc123";
    approvals_save("foo", s);
    const char* r = approvals_load("foo");
    assert_string_equal(s, r);
    approvals_delete("foo");
}

static void test_approvals_verify(void** state)
{
    (void)state; /* unused */

    const char* approved =
        approvals_verify("abc123", __FILE__, "test_approval", "txt");
    assert_string_equal(approved, "abc123");
}

static void test_verify(void** state)
{
    (void)state; /* unused */

    verify_xml("<nope />", "test_verify");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_approvals_name),      /* */
        cmocka_unit_test(test_approvals_save_load), /* */
        cmocka_unit_test(test_approvals_verify),    /* */
        cmocka_unit_test(test_verify),              /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
