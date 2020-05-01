#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>

#include "LinkedList.h"
#include "Price.h"
#include "SampleModelObjects.h"
#include "Util.h"

static void test_util_from_iso8601_utc(void** state)
{
    (void)state; /* unused */

    assert_int_equal(1514764800L, from_iso8601_utc("2018-01-01T00:00Z"));
}

static void test_price_functions(void** state)
{
    (void)state; /* unused */

    const struct Price* price = make_price(1.2, "USD");
    assert_string_equal("USD", get_price_currency(price));
    assert_float_equal(1.2, get_price_amount(price), 0.001);
    assert_float_equal(1.2, get_price_amount_in_currency(price, "USD"), 0.001);
    assert_string_equal("Price{1.200000}", price_to_string(price));
}

static void test_linked_list_append(void** state)
{
    (void)state; /* unused */

    struct LinkedList* ll = make_linked_list();
    int a = 1;
    int b = 2;
    int c = 3;
    linked_list_append(&ll, (void*)&a);
    linked_list_append(&ll, (void*)&b);
    linked_list_append(&ll, (void*)&c);

    int sum = 0;
    for (struct LinkedList* node = ll; node; node = node->next) {
        int* i = (int*)node->data;
        sum += *i;
    }
    assert_int_equal(6, sum);
}

static void test_sample_product(void** state)
{
    (void)state; /* unused */
    make_sample_model_objects();

    assert_string_equal("Cherry Bloom", get_product_name(CherryBloom));
    assert_string_equal("LIPSTICK01", get_product_id(CherryBloom));
    assert_string_equal("Product{Cherry Bloom}", product_to_string(CherryBloom));
    assert_int_equal(30, get_product_weight(CherryBloom));
    assert_int_equal(0, is_product_event(CherryBloom));
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_util_from_iso8601_utc), /* */
        cmocka_unit_test(test_price_functions),       /* */
        cmocka_unit_test(test_linked_list_append),    /* */
        cmocka_unit_test(test_sample_product),        /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
