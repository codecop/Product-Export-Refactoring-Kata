#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Price.h"

struct Product {
    const char* name;
    const char* id;
    long weight;
    const struct Price* price;
    void* location; /* struct Store* */
};

struct Product* make_product(const char* name, const char* id, long weight, const struct Price* price)
{
    struct Product* this = (struct Product*)malloc(sizeof(struct Product));
    this->name = name;
    this->id = id;
    this->weight = weight;
    this->price = price;
    this->location = NULL;
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
    bool is_product_event(const struct Product*);

    if (is_product_event(this)) {
        char* s = (char*)malloc(sizeof(char[12 + 20 + 1]));
        sprintf(s, "StoreEvent{%s}", this->name);
        return s;
    }
    else {
        char* s = (char*)malloc(sizeof(char[9 + 20 + 1]));
        sprintf(s, "Product{%s}", this->name);
        return s;
    }
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
    return this->location != NULL;
}

void product_set_location(struct Product* this, void* locationStore)
{
    this->location = locationStore;
}
