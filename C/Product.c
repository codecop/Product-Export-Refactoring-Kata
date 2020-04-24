#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ModelObject.h"
#include "Price.h"

struct Product {
    struct ModelObject base;
    char* name;
    long weight;
    struct Price* price;
};

static char* productToString(void* product);
static void saveProductToDatabase(void* product);

struct Product* makeProduct(char* name, char* id, long weight, struct Price* price)
{
    struct Product* this = (struct Product*)malloc(sizeof(struct Product));
    this->base.id = id;
    this->base.toString = productToString;
    this->base.saveToDatabase = saveProductToDatabase;
    this->name = name;
    this->weight = weight;
    this->price = price;
    return this;
}

static char* productToString(void* product)
{
    struct Product* this = (struct Product*)product;
    char* buf = (char*)malloc(sizeof(char[8 + 20 + 1]));
    sprintf(buf, "Product{%s}", this->name);
    return buf;
}

static void saveProductToDatabase(void* product)
{
    (void)product; /* unused, would cast to struct Product* */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

char* getProductName(struct Product* this)
{
    return this->name;
}

long getProductWeight(struct Product* this)
{
    return this->weight;
}

struct Price* getProductPrice(struct Product* this)
{
    return this->price;
}

bool isProductEvent(struct Product* this)
{
    (void)this; /* unused */
    return false;
}
