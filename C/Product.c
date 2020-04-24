#include "ModelObject.h"
#include "Price.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Product {
    struct ModelObject base;
    char* name;
    char* id;
    long weight;
    struct Price* price;
};

struct Product* makeProduct(char* name, char* id, long weight, struct Price* price)
{
    struct Product* this = (struct Product*)malloc(sizeof(struct Product));
    this->name = name;
    this->id = id;
    this->weight = weight;
    this->price = price;
    return this;
}

void ProductSaveToDatabase(struct Product* this)
{
    (void) this; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

char* ProductGetName(struct Product* this)
{
    return this->name;
}

char* ProductGetId(struct Product* this)
{
    return this->id;
}

char* ProductToString(struct Product* this)
{
    char* buf = (char*)malloc(sizeof(char[8 + 20 + 1]));
    sprintf(buf, "Product{%s}", this->name);
    return buf;
}

long ProductGetWeight(struct Product* this)
{
    return this->weight;
}

struct Price* ProductGetPrice(struct Product* this)
{
    return this->price;
}

bool ProductIsEvent(struct Product* this)
{
    (void) this; /* unused */
    return false;
}
