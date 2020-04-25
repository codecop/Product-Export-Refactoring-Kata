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
};

static const char* getProductId(void* product);
static const char* productToString(void* product);
static void saveProductToDatabase(void* product);

const struct Product* makeProduct(char* name, char* id, long weight, struct Price* price)
{
    struct Product* this = (struct Product*)malloc(sizeof(struct Product));
    this->base.getId = getProductId;
    this->base.toString = productToString;
    this->base.saveToDatabase = saveProductToDatabase;
    this->id = id;
    this->name = name;
    this->weight = weight;
    this->price = price;
    return this;
}

static const char* getProductId(void* product)
{
    const struct Product* this = (const struct Product*)product;
    return this->id;
}

static const char* productToString(void* product)
{
    const struct Product* this = (const struct Product*)product;
    char* s = (char*)malloc(sizeof(char[9 + 20 + 1]));
    sprintf(s, "Product{%s}", this->name);
    return s;
}

static void saveProductToDatabase(void* product)
{
    (void)product; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

const char* getProductName(const struct Product* this)
{
    return this->name;
}

long getProductWeight(const struct Product* this)
{
    return this->weight;
}

const struct Price* getProductPrice(const struct Product* this)
{
    return this->price;
}

bool isProductEvent(const struct Product* this)
{
    (void)this; /* unused */
    return false;
}
