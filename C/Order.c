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

static const char* getOrderId(void* order);
static const char* orderToString(void* order);
static void saveOrderToDatabase(void* order);

struct Order* makeOrder(char* id, time_t date, struct Store* store, struct LinkedList* products)
{
    struct Order* this = (struct Order*)malloc(sizeof(struct Order));
    this->base.getId = getOrderId;
    this->base.toString = orderToString;
    this->base.saveToDatabase = saveOrderToDatabase;
    this->id = id;
    this->date = date;
    this->store = store;
    this->products = products;
    return this;
}

double orderTotalDollars(const struct Order* this)
{
    double dollars = 0.0;
    for (struct LinkedList* node = this->products; node; node = node->next) {
        const struct Product* product = (const struct Product*)node->data;
        const struct Price* price = getProductPrice(product);
        dollars += getPriceAmountInCurrency(price, "USD");
    }
    return dollars;
}

static const char* getOrderId(void* order)
{
    const struct Order* this = (const struct Order*)order;
    return this->id;
}

static const char* orderToString(void* order)
{
    const struct Order* this = (const struct Order*)order;
    char* s = (char*)malloc(sizeof(char[7 + 20 + 1]));
    sprintf(s, "Order{%s}", this->id);
    return s;
}

static void saveOrderToDatabase(void* order)
{
    (void)order; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

time_t getOrderDate(const struct Order* this)
{
    return this->date;
}

const struct LinkedList* getOrderProducts(const struct Order* this)
{
    return this->products;
}

void addOrderProduct(struct Order* this, const struct Product* product)
{
    linkedListInsert(&this->products, (void*)product);
}

void addOrderProducts(struct Order* this, const struct LinkedList* products)
{
    for (const struct LinkedList* node = products; node; node = node->next) {
        const struct Product* product = (const struct Product*)node->data;
        addOrderProduct(this, product);
    }
}
