#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ModelObject.h"
#include "Product.h"
#include "Store.h"

#define MAX_ORDER 10

struct Order {
    struct ModelObject base;
    char* id;
    time_t date;
    struct Store* store;
    struct Product* products[MAX_ORDER + 1]; /* NULL terminated */
};

static const char* getOrderId(void* order);
static const char* orderToString(void* order);
static void saveOrderToDatabase(void* order);

void addOrderProducts(struct Order* this, struct Product* products[]);

struct Order* makeOrder(char* id, time_t date, struct Store* store, struct Product* products[])
{
    struct Order* this = (struct Order*)malloc(sizeof(struct Order));
    this->base.getId = getOrderId;
    this->base.toString = orderToString;
    this->base.saveToDatabase = saveOrderToDatabase;
    this->id = id;
    this->date = date;
    this->store = store;
    for (unsigned int i = 0; i <= MAX_ORDER; i++) {
        this->products[i] = NULL;
    }
    addOrderProducts(this, products);
    return this;
}

double orderTotalDollars(const struct Order* this)
{
    double dollars = 0.0;
    for (unsigned int i = 0; this->products[i] != NULL; i++) {
        const struct Price* price = getProductPrice(this->products[i]);
        dollars += getPriceAmountInCurrency(price, "USD");
    }
    return dollars;
}

static const char* getOrderId(void* order)
{
    struct Order* this = (struct Order*)order;
    return this->id;
}

static const char* orderToString(void* order)
{
    struct Order* this = (struct Order*)order;
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

const struct Product** getOrderProducts(const struct Order* this)
{
    return this->products;
}

void addOrderProduct(struct Order* this, struct Product* product)
{
    unsigned int i = 0;
    while (this->products[i] != NULL) {
        i += 1;
    }
    if (i < MAX_ORDER) {
        this->products[i] = product;
    }
    /* ignored error handling :-( */
}

void addOrderProducts(struct Order* this, struct Product* products[])
{
    unsigned int i = 0;
    while (products[i] != NULL) {
        addOrderProduct(this, products[i]);
        i += 1;
    }
}
