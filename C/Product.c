#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Price.h"

struct Product {
    const char* name;
    const char* id;
    long weight;
    const struct Price* price;
    bool isEvent;
};

const struct Product* make_product(char* name, char* id, long weight, struct Price* price)
{
    struct Product* this = (struct Product*)malloc(sizeof(struct Product));
    this->name = name;
    this->id = id;
    this->weight = weight;
    this->price = price;
    this->isEvent = false;
    return this;
}

void save_product_to_database(const struct Product* this)
{
    (void)this; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

const char* get_product_name(const struct Product* this)
{
    return this->name;
}

const char* get_product_id(const struct Product* this)
{
    return this->id;
}

const char* product_to_string(const struct Product* this)
{
    char* s = (char*)malloc(sizeof(char[9 + 20 + 1]));
    sprintf(s, "Product{%s}", this->name);
    return s;
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
