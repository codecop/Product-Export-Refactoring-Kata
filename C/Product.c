#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ModelObject.h"
#include "Price.h"

struct Product {
    struct ModelObject base;
    const char* id;
    const char* name;
    long weight;
    const struct Price* price;
    bool isEvent;
};

static const char* get_product_id(void* product);
static const char* product_to_string(void* product);
static void save_product_to_database(void* product);

const struct Product* make_product(char* name, char* id, long weight, struct Price* price)
{
    struct Product* this = (struct Product*)malloc(sizeof(struct Product));
    this->base.getId = get_product_id;
    this->base.toString = product_to_string;
    this->base.saveToDatabase = save_product_to_database;
    this->id = id;
    this->name = name;
    this->weight = weight;
    this->price = price;
    this->isEvent = false;
    return this;
}

static const char* get_product_id(void* product)
{
    const struct Product* this = (const struct Product*)product;
    return this->id;
}

static const char* product_to_string(void* product)
{
    const struct Product* this = (const struct Product*)product;
    char* s = (char*)malloc(sizeof(char[9 + 20 + 1]));
    sprintf(s, "Product{%s}", this->name);
    return s;
}

static void save_product_to_database(void* product)
{
    (void)product; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

const char* get_product_name(const struct Product* this)
{
    return this->name;
}

long get_product_weight(const struct Product* this)
{
    return this->weight;
}

const struct Price* get_product_price(const struct Product* this)
{
    return this->price;
}

bool is_product_event(const struct Product* this)
{
    return this->isEvent;
}
