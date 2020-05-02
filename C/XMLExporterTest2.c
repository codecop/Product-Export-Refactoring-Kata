#include <setjmp.h> /* used by mocka */
#include <stdarg.h> /* used by mocka */
#include <stddef.h> /* used by mocka */

#include "LinkedList.h"
#include "SampleModelObjects2.h"
#include "XMLExporter.h"
#include <cmocka.h>
#include <stdio.h>

struct LinkedList* orders;

static int setup_sample_model_objects(void** state)
{
    (void)state; /* unused */
    make_sample_model_objects();
    orders = make_linked_list();
    linked_list_append(&orders, RecentOrder);
    linked_list_append(&orders, OldOrder);
    return 0;
}

#define verify_xml(xml, file_name) \
 printf("%s\n", (xml)); \
 printf("%s\n", (file_name));

static void test_export_full(void** state)
{
    (void)state; /* unused */

    const char* xml = xml_export_full(orders);

    verify_xml(xml, "XMLExporterTest.exportFull.approved.xml");
}

static void test_export_tax_details(void** state)
{
    (void)state; /* unused */

    const char* xml = xml_export_tax_details(orders);

    verify_xml(xml, "XMLExporterTest.exportTaxDetails.approved.xml");
}

static void test_export_store(void** state)
{
    (void)state; /* unused */
    struct Store* store = FlagshipStore;

    const char* xml = xml_export_store(store);

    verify_xml(xml, "XMLExporterTest.exportStore.approved.xml");
}

static void test_export_history(void** state)
{
    (void)state; /* unused */

    const char* xml = xml_export_history(orders);

    /*
    const char* regex = "createdAt='[^']+'";
    xml = xmlreplace_first(regex, "createdAt='2018-09-20T00:00Z'");
    */
    verify_xml(xml, "XMLExporterTest.exportHistory.approved.xml");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_export_full),        /* */
        cmocka_unit_test(test_export_tax_details), /* */
        cmocka_unit_test(test_export_store),       /* */
        cmocka_unit_test(test_export_history),     /* */
    };

    return cmocka_run_group_tests(test_suite, setup_sample_model_objects, NULL);
}
