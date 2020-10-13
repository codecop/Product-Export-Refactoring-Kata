#include "LinkedList.h"
#include "Order.h"
#include "Price.h"
#include "Product.h"
#include "Store.h"
#include "StringBuilder.h"
#include "TaxCalculator.h"
#include "Util.h"
#include "XmlBuilder.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char* stylist_for(const struct Product*);

#define PRODUCT_DETAIL_NONE 0
#define PRODUCT_DETAIL_STYLIST 1
#define PRODUCT_DETAIL_WEIGHT 2
#define PRODUCT_DETAIL_PRICE 4
#define PRODUCT_DETAIL_LOCATION 8

void xml_product(struct StringBuilder* xml, const struct Product* product, struct Store* store,
        unsigned int details)
{
    if (details & PRODUCT_DETAIL_STYLIST) {
        if (is_product_event(product)) {
            xml_attribute_s(xml, "stylist", stylist_for(product));
        }
    }

    if (details & PRODUCT_DETAIL_LOCATION) {
        if (is_product_event(product)) {
            xml_attribute_s(xml, "location", get_store_name(store));
        }
    }

    if (details & PRODUCT_DETAIL_WEIGHT) {
        if (get_product_weight(product) > 0) {
            xml_attribute_l(xml, "weight", get_product_weight(product));
        }
    }

    if (details & PRODUCT_DETAIL_PRICE) {
        xml_open(xml, "price");
        xml_attribute_s(xml, "currency", get_price_currency(get_product_price(product)));
        xml_text_d(xml, get_price_amount(get_product_price(product)));
        xml_close(xml, "price");
    }

}

const char* xml_export_full(const struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    xml_open(xml, "orders");
    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;
        xml_open(xml, "order");
        xml_attribute_s(xml, "id", get_order_id(order));
        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            xml_open(xml, "product");
            xml_attribute_s(xml, "id", get_product_id(product));

            xml_product(xml, product, NULL, PRODUCT_DETAIL_STYLIST | PRODUCT_DETAIL_WEIGHT | PRODUCT_DETAIL_PRICE);

            xml_text_s(xml, get_product_name(product));
            xml_close(xml, "product");
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

        xml_attribute_date(xml, "date", get_order_date(order));

        double tax = 0.0;

        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            xml_open(xml, "product");
            xml_attribute_s(xml, "id", get_product_id(product));
            xml_text_s(xml, get_product_name(product));
            xml_close(xml, "product");

            if (is_product_event(product))
                tax += get_price_amount_in_currency(get_product_price(product), "USD") * 0.25;
            else
                tax += get_price_amount_in_currency(get_product_price(product), "USD") * 0.175;

        }

        xml_open(xml, "orderTax");
        xml_attribute_s(xml, "currency", "USD");

        if (get_order_date(order) < from_iso_date("2018-01-01T00:00Z"))
            tax += 10;
        else
            tax += 20;

        xml_text_d(xml, tax);

        xml_close(xml, "orderTax");

        xml_close(xml, "order");
    }

    double total_tax = calculate_added_tax(orders);
    xml_text_d(xml, total_tax);

    xml_close(xml, "orderTax");
    return xml_string(xml);
}

const char* xml_export_store(struct Store* store)
{
    struct StringBuilder* xml = make_xml();
    xml_open(xml, "store");
    xml_attribute_s(xml, "name", get_store_name(store));

    const struct LinkedList* products = get_store_stock(store);
    for (const struct LinkedList* node = products; node; node = node->next) {
        const struct Product* product = (const struct Product*)node->data;
        xml_open(xml, "product");
        xml_attribute_s(xml, "id", get_product_id(product));

        xml_product(xml, product, store, PRODUCT_DETAIL_LOCATION | PRODUCT_DETAIL_WEIGHT | PRODUCT_DETAIL_PRICE);

        xml_text_s(xml, get_product_name(product));
        xml_close(xml, "product");
    }

    xml_close(xml, "store");

    return xml_string(xml);
}

const char* xml_export_history(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    xml_open(xml, "orderHistory");

    time_t now = time(NULL);
    xml_attribute_date(xml, "createdAt", now);

    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;

        xml_open(xml, "order");

        xml_attribute_date(xml, "date", get_order_date(order));

        xml_attribute_d(xml, "totalDollars", order_total_dollars(order));

        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;

            xml_open(xml, "product");
            xml_attribute_s(xml, "id", get_product_id(product));
            xml_text_s(xml, get_product_name(product));
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
