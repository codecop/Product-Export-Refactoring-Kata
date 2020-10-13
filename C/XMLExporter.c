#include "LinkedList.h"
#include "Order.h"
#include "Price.h"
#include "Product.h"
#include "Store.h"
#include "StringBuilder.h"
#include "TaxCalculator.h"
#include "XmlBuilder.h"
#include "Util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char* stylist_for(const struct Product*);
static const char* make_formatted_double(double);

#define PRODUCT_DETAIL_NONE 0
#define PRODUCT_DETAIL_STYLIST 1
#define PRODUCT_DETAIL_WEIGHT 2
#define PRODUCT_DETAIL_PRICE 4
#define PRODUCT_DETAIL_LOCATION 8

void xml_product(struct StringBuilder* xml, const struct Product* product, struct Store* store,
        unsigned int details)
{
    xml_open(xml, "product");

    xml_attribute(xml, "id", get_product_id(product));

    if (details & PRODUCT_DETAIL_STYLIST) {
        if (is_product_event(product)) {
            xml_attribute(xml, "stylist", stylist_for(product));
        }
    }

    if (details & PRODUCT_DETAIL_LOCATION) {
        if (is_product_event(product)) {
            xml_attribute(xml, "location", get_store_name(store));
        }
    }

    if (details & PRODUCT_DETAIL_WEIGHT) {
        if (get_product_weight(product) > 0) {
            sb_append(xml, " weight='");
            sb_append_long(xml, get_product_weight(product));
            sb_append(xml, "'");
        }
    }

    if (details & PRODUCT_DETAIL_PRICE) {
        xml_open(xml, "price");
        xml_attribute(xml, "currency", get_price_currency(get_product_price(product)));

        const char* formatted = make_formatted_double(get_price_amount(get_product_price(product)));
        xml_text(xml, formatted);
        free((void*)formatted);

        xml_close(xml, "price");
    }

    xml_text(xml, get_product_name(product));
    xml_close(xml, "product");
}

const char* xml_export_full(const struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    xml_open(xml, "orders");
    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;
        xml_open(xml, "order");
        xml_attribute(xml, "id", get_order_id(order));
        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            xml_product(xml, product, NULL, PRODUCT_DETAIL_STYLIST | PRODUCT_DETAIL_WEIGHT | PRODUCT_DETAIL_PRICE);
        }

        xml_close(xml, "order");
    }

    xml_close(xml, "orders");
    return xml_string(xml);
}

const char* xml_export_tax_details(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    xml_open(xml, "orderTax");
    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;
        xml_open(xml, "order");
        const char* formatted = make_iso_date_str(get_order_date(order));
        xml_attribute(xml, "date", formatted);
        double tax = 0.0;
        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            xml_product(xml, product, NULL, PRODUCT_DETAIL_NONE);
            if (is_product_event(product))
                tax += get_price_amount_in_currency(get_product_price(product), "USD") * 0.25;
            else
                tax += get_price_amount_in_currency(get_product_price(product), "USD") * 0.175;

        }

        xml_open(xml, "orderTax");
        xml_attribute(xml, "currency", "USD");
        if (get_order_date(order) < from_iso_date("2018-01-01T00:00Z"))
            tax += 10;
        else
            tax += 20;
        const char* formatted_tax = make_formatted_double(tax);
        xml_text(xml, formatted_tax);
        free((void*)formatted_tax);
        xml_close(xml, "orderTax");
        xml_close(xml, "order");
    }

    double total_tax = calculate_added_tax(orders);
    const char* formatted_total_tax = make_formatted_double(total_tax);
    xml_text(xml, formatted_total_tax);
    free((void*)formatted_total_tax);
    xml_close(xml, "orderTax");
    return xml_string(xml);
}

static const char* make_formatted_double(double d)
{
    char* s = (char*)malloc(sizeof(char[24 + 1]));
    sprintf(s, "%03.2f", d);
    return s;
}

const char* xml_export_store(struct Store* store)
{
    struct StringBuilder* xml = make_xml();
    xml_open(xml, "store");
    xml_attribute(xml, "name", get_store_name(store));
    const struct LinkedList* products = get_store_stock(store);
    for (const struct LinkedList* node = products; node; node = node->next) {
        const struct Product* product = (const struct Product*)node->data;
        xml_product(xml, product, store, PRODUCT_DETAIL_LOCATION | PRODUCT_DETAIL_WEIGHT | PRODUCT_DETAIL_PRICE);
    }

    xml_close(xml, "store");

    return xml_string(xml);
}

const char* xml_export_history(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    xml_open(xml, "orderHistory");
    time_t now = time(NULL);
    const char* formatted_now = make_iso_date_str(now);
    xml_attribute(xml, "createdAt", formatted_now);
    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;
        xml_open(xml, "order");
        const char* formatted_date = make_iso_date_str(get_order_date(order));
        xml_attribute(xml, "date", formatted_date);
        free((void*)formatted_date);
        const char* formatted_total = make_formatted_double(order_total_dollars(order));
        xml_attribute(xml, "totalDollars", formatted_total);
        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            xml_open(xml, "product");
            xml_attribute(xml, "id", get_product_id(product));
            xml_text(xml, get_product_name(product));
            xml_close(xml, "product");
        }

        xml_close(xml, "order");
    }

    xml_close(xml, "orderHistory");
    return xml_string(xml);
}

static const char* stylist_for(const struct Product* product)
{
    (void)product; /* unused */

    return "Celeste Pulchritudo"; /* in future we will look up the name of the stylist from the database */
}
