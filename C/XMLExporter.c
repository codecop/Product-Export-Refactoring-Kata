#include "LinkedList.h"
#include "Order.h"
#include "Price.h"
#include "Product.h"
#include "Store.h"
#include "TaxCalculator.h"
#include "XmlBuilder.h"
#include <stdlib.h>

static const char* stylist_for(const struct Product*);

#define PRODUCT_DETAIL_WEIGHT 2
#define PRODUCT_DETAIL_PRICE 4

void xml_product(struct StringBuilder* xml, const struct Product* product, unsigned int details)
{
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

    linked_list_each(const struct Order*, order, orders,

        xml_open(xml, "order");
        xml_attribute_s(xml, "id", get_order_id(order));

        linked_list_each(const struct Product*, product, get_order_products(order),

            xml_open(xml, "product");
            xml_attribute_s(xml, "id", get_product_id(product));
            if (is_product_event(product)) {
                xml_attribute_s(xml, "stylist", stylist_for(product));
            }

            xml_product(xml, product, PRODUCT_DETAIL_WEIGHT | PRODUCT_DETAIL_PRICE);

            xml_text_s(xml, get_product_name(product));
            xml_close(xml, "product");
        )

        xml_close(xml, "order");
    )

    xml_close(xml, "orders");

    return xml_string(xml);
}

const char* xml_export_tax_details(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();

    xml_open(xml, "orderTax");

    linked_list_each(const struct Order*, order, orders,
        xml_open(xml, "order");
        xml_attribute_date(xml, "date", get_order_date(order));

        linked_list_each(const struct Product*, product, get_order_products(order),
            xml_open(xml, "product");
            xml_attribute_s(xml, "id", get_product_id(product));
            xml_text_s(xml, get_product_name(product));
            xml_close(xml, "product");
        )

        xml_open(xml, "orderTax");
        xml_attribute_s(xml, "currency", "USD");

        double tax = order_tax(order);
        xml_text_d(xml, tax);

        xml_close(xml, "orderTax");

        xml_close(xml, "order");
    )

    xml_text_d(xml, calculate_added_tax(orders));
    xml_close(xml, "orderTax");

    return xml_string(xml);
}

const char* xml_export_store(struct Store* store)
{
    struct StringBuilder* xml = make_xml();

    xml_open(xml, "store");
    xml_attribute_s(xml, "name", get_store_name(store));

    linked_list_each(const struct Product*, product, get_store_stock(store),
        xml_open(xml, "product");
        xml_attribute_s(xml, "id", get_product_id(product));
        if (is_product_event(product)) {
            xml_attribute_s(xml, "location", get_store_name(store));
        }
        xml_product(xml, product, PRODUCT_DETAIL_WEIGHT | PRODUCT_DETAIL_PRICE);
        xml_text_s(xml, get_product_name(product));
        xml_close(xml, "product");
    )

    xml_close(xml, "store");

    return xml_string(xml);
}

const char* xml_export_history(struct LinkedList* orders)
{
    struct StringBuilder* xml = make_xml();

    xml_open(xml, "orderHistory");
    xml_attribute_date(xml, "createdAt", time(NULL));

    linked_list_each(const struct Order*, order, orders,

        xml_open(xml, "order");
        xml_attribute_date(xml, "date", get_order_date(order));
        xml_attribute_d(xml, "totalDollars", order_total_dollars(order));

        linked_list_each(const struct Product*, product, get_order_products(order),
            xml_open(xml, "product");
            xml_attribute_s(xml, "id", get_product_id(product));
            xml_text_s(xml, get_product_name(product));
            xml_close(xml, "product");
        )

        xml_close(xml, "order");
    )

    xml_close(xml, "orderHistory");

    return xml_string(xml);
}

static const char* stylist_for(const struct Product* product)
{
    (void)product; /* unused */

    return "Celeste Pulchritudo"; /* in future we will look up the name of the stylist from the database */
}
