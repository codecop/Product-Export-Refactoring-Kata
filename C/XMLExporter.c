#include "LinkedList.h"
#include "Order.h"
#include "Price.h"
#include "Product.h"
#include "Store.h"
#include "StringBuilder.h"
#include "TaxCalculator.h"
#include "Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char* stylist_for(const struct Product*);

const char* export_full(const struct LinkedList* orders)
{
    struct StringBuilder* xml = make_sb();
    sb_append(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    sb_append(xml, "<orders>");
    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;
        sb_append(xml, "<order");
        sb_append(xml, " id='");
        sb_append(xml, get_order_id(order));
        sb_append(xml, "'>");
        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            sb_append(xml, "<product");
            sb_append(xml, " id='");
            sb_append(xml, get_product_id(product));
            sb_append(xml, "'");
            if (is_product_event(product)) {
                sb_append(xml, " stylist='");
                sb_append(xml, stylist_for(product));
                sb_append(xml, "'");
            }
            if (get_product_weight(product) > 0) {
                sb_append(xml, " weight='");
                sb_append_long(xml, get_product_weight(product));
                sb_append(xml, "'");
            }
            sb_append(xml, ">");
            sb_append(xml, "<price");
            sb_append(xml, " currency='");
            sb_append(xml, get_price_currency(get_product_price(product)));
            sb_append(xml, "'>");
            sb_append_double(xml, get_price_amount(get_product_price(product)));
            sb_append(xml, "</price>");
            sb_append(xml, get_product_name(product));
            sb_append(xml, "</product>");
        }
        sb_append(xml, "</order>");
    }
    sb_append(xml, "</orders>");
    return sb_string(xml);
}

static const char* iso_date(time_t);
static const char* format(double);

const char* export_tax_details(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_sb();
    sb_append(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    sb_append(xml, "<orderTax>");
    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;
        sb_append(xml, "<order");
        sb_append(xml, " date='");
        sb_append(xml, iso_date(get_order_date(order)));
        sb_append(xml, "'");
        sb_append(xml, ">");
        double tax = 0.0;
        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            sb_append(xml, "<product");
            sb_append(xml, " id='");
            sb_append(xml, get_product_id(product));
            sb_append(xml, "'");
            sb_append(xml, ">");
            sb_append(xml, get_product_name(product));
            sb_append(xml, "</product>");
            if (is_product_event(product)) {
                tax += get_price_amount_in_currency(get_product_price(product), "USD") * 0.25;
            }
            else {
                tax += get_price_amount_in_currency(get_product_price(product), "USD") * 0.175;
            }
        }
        sb_append(xml, "<orderTax currency='USD'>");
        if (get_order_date(order) < from_iso8601_utc("2018-01-01T00:00Z")) {
            tax += 10;
        }
        else {
            tax += 20;
        }
        sb_append(xml, format(tax));
        sb_append(xml, "</orderTax>");
        sb_append(xml, "</order>");
    }
    double totalTax = calculate_added_tax(orders);
    sb_append(xml, format(totalTax));
    sb_append(xml, "\n");
    sb_append(xml, "</orderTax>");
    return sb_string(xml);
}

static const char* format(double d)
{
    char* s = (char*)malloc(sizeof(char[24 + 1]));
    sprintf(s, "%03.2f", d);
    return s;
}

const char* ExportStore(struct Store* store)
{
    struct StringBuilder* xml = make_sb();
    sb_append(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    sb_append(xml, "<store");
    sb_append(xml, " name='");
    sb_append(xml, get_store_name(store));
    sb_append(xml, "'");
    sb_append(xml, ">");
    const struct LinkedList* products = get_store_stock(store);
    for (const struct LinkedList* node = products; node; node = node->next) {
        const struct Product* product = (const struct Product*)node->data;
        sb_append(xml, "<product");
        sb_append(xml, " id='");
        sb_append(xml, get_product_id(product));
        sb_append(xml, "'");
        if (is_product_event(product)) {
            sb_append(xml, " location='");
            sb_append(xml, get_store_name(store));
            sb_append(xml, "'");
        }
        else {
            sb_append(xml, " weight='");
            sb_append_long(xml, get_product_weight(product));
            sb_append(xml, "'");
        }
        sb_append(xml, ">");
        sb_append(xml, "<price");
        sb_append(xml, " currency='");
        sb_append(xml, get_price_currency(get_product_price(product)));
        sb_append(xml, "'>");
        sb_append_double(xml, get_price_amount(get_product_price(product)));
        sb_append(xml, "</price>");
        sb_append(xml, get_product_name(product));
        sb_append(xml, "</product>");
    }
    sb_append(xml, "</store>");
    return sb_string(xml);
}

const char* export_history(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_sb();
    sb_append(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    sb_append(xml, "<orderHistory");
    sb_append(xml, " createdAt='");
    time_t now = time(NULL);
    sb_append(xml, iso_date(now));
    sb_append(xml, "'");
    sb_append(xml, ">");
    for (const struct LinkedList* node = orders; node; node = node->next) {
        const struct Order* order = (const struct Order*)node->data;
        sb_append(xml, "<order");
        sb_append(xml, " date='");
        sb_append(xml, iso_date(get_order_date(order)));
        sb_append(xml, "'");
        sb_append(xml, " totalDollars='");
        sb_append_double(xml, order_total_dollars(order));
        sb_append(xml, "'>");
        const struct LinkedList* products = get_order_products(order);
        for (const struct LinkedList* node = products; node; node = node->next) {
            const struct Product* product = (const struct Product*)node->data;
            sb_append(xml, "<product");
            sb_append(xml, " id='");
            sb_append(xml, get_product_id(product));
            sb_append(xml, "'");
            sb_append(xml, ">");
            sb_append(xml, get_product_name(product));
            sb_append(xml, "</product>");
        }
        sb_append(xml, "</order>");
    }
    sb_append(xml, "</orderHistory>");
    return sb_string(xml);
}

static const char* iso_date(const time_t date)
{
    struct tm* utc = gmtime(&date);
    /* compensate expected ranges */
    utc->tm_year = utc->tm_year + 1900;
    utc->tm_mon = utc->tm_mon + 1;

    char* s = (char*)malloc(sizeof(char[17 + 1]));
    sprintf(s, "%04d-%02d-%02dT%02d:%02dZ", /* */
               utc->tm_year, utc->tm_mon, utc->tm_mday, utc->tm_hour, utc->tm_min);
	free(utc);
    return s;
}

static const char* stylist_for(const struct Product* product)
{
    (void)product; /* unused */

    return "Celeste Pulchritudo";
    /* in future we will look up the name of */
    /* the stylist from the database */
}