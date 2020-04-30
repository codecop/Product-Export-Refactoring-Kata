#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LinkedList.h"
#include "ModelObject.h"
#include "Product.h"
#include "Store.h"

struct Order {
    struct ModelObject base;
    const char* id;
    time_t date;
    struct Store* store;
    struct LinkedList* products;
};

static const char* get_order_id(void* order);
static const char* order_to_string(void* order);
static void save_order_to_database(void* order);

struct Order* make_order(char* id, time_t date, struct Store* store, struct LinkedList* products)
{
    struct Order* this = (struct Order*)malloc(sizeof(struct Order));
    this->base.getId = get_order_id;
    this->base.toString = order_to_string;
    this->base.saveToDatabase = save_order_to_database;
    this->id = id;
    this->date = date;
    this->store = store;
    this->products = products;
    return this;
}

double order_total_dollars(const struct Order* this)
{
    double dollars = 0.0;
    for (struct LinkedList* node = this->products; node; node = node->next) {
        const struct Product* product = (const struct Product*)node->data;
        const struct Price* price = get_product_price(product);
        dollars += get_price_amount_in_currency(price, "USD");
    }
    return dollars;
}

static const char* get_order_id(void* order)
{
    const struct Order* this = (const struct Order*)order;
    return this->id;
}

static const char* order_to_string(void* order)
{
    const struct Order* this = (const struct Order*)order;
    char* s = (char*)malloc(sizeof(char[7 + 20 + 1]));
    sprintf(s, "Order{%s}", this->id);
    return s;
}

static void save_order_to_database(void* order)
{
    (void)order; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

time_t get_order_date(const struct Order* this)
{
    return this->date;
}

const struct LinkedList* get_order_products(const struct Order* this)
{
    return this->products;
}

void add_order_product(struct Order* this, const struct Product* product)
{
    linked_list_append(&this->products, (void*)product);
}

void add_order_products(struct Order* this, const struct LinkedList* products)
{
    for (const struct LinkedList* node = products; node; node = node->next) {
        const struct Product* product = (const struct Product*)node->data;
        add_order_product(this, product);
    }
}
