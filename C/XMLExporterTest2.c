#include <setjmp.h> /* used by mocka */
#include <stdarg.h> /* used by mocka */
#include <stddef.h> /* used by mocka */

#include "LinkedList.h"
#include "SampleModelObjects2.h"
#include "XMLExporter.h"
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>
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

#define READ_BUFFER 1000
static char __readBuffer[READ_BUFFER];

static const char* get_approved(const char* filename)
{
    memset(__readBuffer, 0, READ_BUFFER);
    FILE* file;
    file = fopen(filename, "r");
    fread(__readBuffer, sizeof(char), READ_BUFFER, file);
    fclose(file);
    return __readBuffer;
}

static void save(const char* filename, const char* data)
{
    printf("saving");
    FILE* file;
    file = fopen(filename, "w");
    fwrite(data, sizeof(char), strlen(data), file);
    fflush(file);
    fclose(file);
}

#define verify_xml(xml, file_name) \
    if (strcmp(get_approved((file_name)), (xml)) != 0) { \
        save("foo.xml", (xml)); \
    } \
    assert_string_equal(get_approved((file_name)), xml);

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
        cmocka_unit_test(test_export_full), /* */
        // cmocka_unit_test(test_export_tax_details), /* */
        // cmocka_unit_test(test_export_store),       /* */
        // cmocka_unit_test(test_export_history),     /* */
    };

    return cmocka_run_group_tests(test_suite, setup_sample_model_objects, NULL);
}
