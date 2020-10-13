#include "LinkedList.h"
#include "Order.h"
#include "Price.h"
#include "Product.h"
#include "StoreEvent.h"
#include "Store.h"
#include "TaxCalculator.h"
#include "XmlBuilder.h"
#include <stdlib.h>

static const char* stylist_for(const struct Product*);

/* ****************************************
 * Generic export product
 * ****************************************
 */

#define PRODUCT_DETAIL_NONE 0
#define PRODUCT_WITH_LOCATION 1
#define PRODUCT_WITH_STYLIST 2
#define PRODUCT_WITH_WEIGHT 4
#define PRODUCT_WITH_PRICE 8

static void export_product_price(struct StringBuilder* xml, const struct Product* product)
{
    xml_open(xml, "price");
    xml_attribute_s(xml, "currency", get_price_currency(get_product_price(product)));
    xml_text_d(xml, get_price_amount(get_product_price(product)));
    xml_close(xml, "price");
}

static void export_product(struct StringBuilder* xml, const struct Product* product, unsigned int details)
{
    xml_open(xml, "product");
    xml_attribute_s(xml, "id", get_product_id(product));

    if (details & PRODUCT_WITH_LOCATION) {
        if (is_product_event(product)) {
            xml_attribute_s(xml, "location", get_store_name(get_store_event_location(product)));
        }
    }

    if (details & PRODUCT_WITH_STYLIST) {
        if (is_product_event(product)) {
            xml_attribute_s(xml, "stylist", stylist_for(product));
        }
    }

    if (details & PRODUCT_WITH_WEIGHT) {
        if (get_product_weight(product) > 0) {
            xml_attribute_l(xml, "weight", get_product_weight(product));
        }
    }

    if (details & PRODUCT_WITH_PRICE) {
        export_product_price(xml, product);
    }

    xml_text_s(xml, get_product_name(product));
    xml_close(xml, "product");
}

/* ****************************************
 * Generic export order
 * ****************************************
 */

#define ORDER_DETAIL_NONE 0
#define ORDER_WITH_ID 16
#define ORDER_WITH_DATE 32
#define ORDER_WITH_DOLLAR 64
#define ORDER_WITH_TAX 128

static void export_order_tax(struct StringBuilder* xml, const struct Order* order)
{
    xml_open(xml, "orderTax");
    xml_attribute_s(xml, "currency", "USD");
    xml_text_d(xml, order_tax(order));
    xml_close(xml, "orderTax");
}

static void export_order(struct StringBuilder* xml, const struct Order* order, unsigned int details, void export_p(struct StringBuilder*, const struct Product*))
{
    xml_open(xml, "order");

    if (details & ORDER_WITH_ID) {
        xml_attribute_s(xml, "id", get_order_id(order));
    }
    if (details & ORDER_WITH_DATE) {
        xml_attribute_date(xml, "date", get_order_date(order));
    }
    if (details & ORDER_WITH_DOLLAR) {
        xml_attribute_d(xml, "totalDollars", order_total_dollars(order));
    }

    linked_list_each(const struct Product*, product, get_order_products(order),
        export_p(xml, product);
    )

    if (details & ORDER_WITH_TAX) {
        export_order_tax(xml, order);
    }

    xml_close(xml, "order");
}

/* ****************************************
 * Specific methods
 * ****************************************
 */

static void export_full_order(struct StringBuilder* xml, const struct Order* order);
static void export_full_orders(struct StringBuilder* xml, const struct LinkedList* orders);
static void export_full_product(struct StringBuilder* xml, const struct Product* product);

const char* xml_export_full(const struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    export_full_orders(xml, orders);
    return xml_string(xml);
}

static void export_full_orders(struct StringBuilder* xml, const struct LinkedList* orders)
{
    xml_open(xml, "orders");
    linked_list_each(const struct Order*, order, orders,
        export_full_order(xml, order);
    )
    xml_close(xml, "orders");
}

static void export_full_order(struct StringBuilder* xml, const struct Order* order)
{
    export_order(xml, order, ORDER_WITH_ID, export_full_product);
}

static void export_full_product(struct StringBuilder* xml, const struct Product* product)
{
    export_product(xml, product, PRODUCT_WITH_STYLIST | PRODUCT_WITH_WEIGHT | PRODUCT_WITH_PRICE);
}

static void export_tax_detail_orders(struct StringBuilder* xml, struct LinkedList* orders);
static void export_tax_detail_order(struct StringBuilder* xml, const struct Order* order);
static void export_order_tax(struct StringBuilder* xml, const struct Order* order);
static void export_plain_product(struct StringBuilder* xml, const struct Product* product);

const char* xml_export_tax_details(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    export_tax_detail_orders(xml, orders);
    return xml_string(xml);
}

static void export_tax_detail_orders(struct StringBuilder* xml, struct LinkedList* orders)
{
    xml_open(xml, "orderTax");

    linked_list_each(const struct Order*, order, orders,
        export_tax_detail_order(xml, order);
    )

    xml_text_d(xml, calculate_added_tax(orders));
    xml_close(xml, "orderTax");
}

static void export_tax_detail_order(struct StringBuilder* xml, const struct Order* order)
{
    export_order(xml, order, ORDER_WITH_DATE | ORDER_WITH_TAX, export_plain_product);
}

static void export_plain_product(struct StringBuilder* xml, const struct Product* product)
{
    export_product(xml, product, PRODUCT_DETAIL_NONE);
}

static void export_store(struct StringBuilder* xml, struct Store* store);
static void export_store_product(struct StringBuilder* xml, const struct Product* product);

const char* xml_export_store(struct Store* store)
{
    struct StringBuilder* xml = make_xml();
    export_store(xml, store);
    return xml_string(xml);
}

static void export_store(struct StringBuilder* xml, struct Store* store)
{
    xml_open(xml, "store");
    xml_attribute_s(xml, "name", get_store_name(store));
    linked_list_each(const struct Product*, product, get_store_stock(store),
         export_store_product(xml, product);
    )
    xml_close(xml, "store");
}

static void export_store_product(struct StringBuilder* xml, const struct Product* product)
{
    export_product(xml, product, PRODUCT_WITH_LOCATION | PRODUCT_WITH_WEIGHT | PRODUCT_WITH_PRICE);
}

static void export_order_history(struct StringBuilder* xml, struct LinkedList* orders);
static void export_order_history_order(struct StringBuilder* xml, const struct Order* order);

const char* xml_export_history(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();
    export_order_history(xml, orders);
    return xml_string(xml);
}

static void export_order_history(struct StringBuilder* xml, struct LinkedList* orders)
{
    xml_open(xml, "orderHistory");
    xml_attribute_date(xml, "createdAt", time(NULL));
    linked_list_each(const struct Order*, order, orders,
        export_order_history_order(xml, order);
    )
    xml_close(xml, "orderHistory");
}

static void export_order_history_order(struct StringBuilder* xml, const struct Order* order)
{
    export_order(xml, order, ORDER_WITH_DATE | ORDER_WITH_DOLLAR, export_plain_product);
}

static const char* stylist_for(const struct Product* product)
{
    (void)product; /* unused */

    return "Celeste Pulchritudo"; /* in future we will look up the name of the stylist from the database */
}
