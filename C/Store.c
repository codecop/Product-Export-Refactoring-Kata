#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "LinkedMap.h"
#include "ModelObject.h"
#include "Product.h"

/**
 * Represents a physical Store where you can go and buy products and attend
 * events.
 */
struct Store {
    struct ModelObject base;
    struct LinkedMap* itemsInStock; /* Map<String, Product> */
    const char* name;
    const char* id;
};

static const char* get_store_id(void* store);
static const char* store_to_string(void* store);
static void save_store_to_database(void* store);

void store_add_stocked_items(struct Store* this, const struct LinkedList* products);

struct Store* make_store(const char* name, const char* id, const struct LinkedList* products)
{
    struct Store* this = (struct Store*)malloc(sizeof(struct Store));
    this->base.getId = get_store_id;
    this->base.toString = store_to_string;
    this->base.saveToDatabase = save_store_to_database;
    this->name = name;
    this->id = id;
    this->itemsInStock = NULL;
    store_add_stocked_items(this, products);
    return this;
}

static const char* get_store_id(void* store)
{
    const struct Store* this = (const struct Store*)store;
    return this->id;
}

static const char* store_to_string(void* store)
{
    const struct Store* this = (const struct Store*)store;
    char* s = (char*)malloc(sizeof(char[7 + 20 + 1]));
    sprintf(s, "Store{%s}", this->name);
    return s;
}

static void save_store_to_database(void* store)
{
    (void)store; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

const char* get_store_name(const struct Store* this)
{
    return this->name;
}

void store_add_stocked_items(struct Store* this, const struct LinkedList* items)
{
    for (const struct LinkedList* node = items; node; node = node->next) {
        const struct Product* item = (const struct Product*)node->data;
        const char* productName = get_product_name(item);
        linked_map_put(&this->itemsInStock, productName, item);
    }
}

void store_add_store_event(struct Store* this, const struct Product* storeEvent)
{
    const char* storeEventName = get_product_name(storeEvent);
    linked_map_put(&this->itemsInStock, storeEventName, storeEvent);
}

bool store_has_item(const struct Store* this, const struct Product* item)
{
    const char* productName = get_product_name(item);
    return linked_map_contains(this->itemsInStock, productName);
}

const struct Product* store_get_item(const struct Store* this, const char* name)
{
    return (const struct Product*)linked_map_get(this->itemsInStock, name);
}

const struct LinkedList* get_store_stock(const struct Store* this)
{
    return linked_map_values(this->itemsInStock);
}
