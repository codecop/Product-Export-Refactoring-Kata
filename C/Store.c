#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "ModelObject.h"
#include "Product.h"
#include "StoreEvent.h"

/**
 * Represents a physical Store where you can go and buy products and attend
 * events.
 */
struct Store {
    struct ModelObject base;
    /*final Map<String, Product> itemsInStock = new HashMap<String, Product>(); TODO */
    const char* name;
    const char* id;
};

static const char* getStoreId(void* store);
static const char* storeToString(void* store);
static void saveStoreToDatabase(void* store);

void storeAddStockedItems(struct Store* this, const struct LinkedList* products);

struct Store* makeStore(const char* name, const char* id, const struct LinkedList* products)
{
    struct Store* this = (struct Store*)malloc(sizeof(struct Store));
    this->base.getId = getStoreId;
    this->base.toString = storeToString;
    this->base.saveToDatabase = saveStoreToDatabase;
    this->name = name;
    this->id = id;
    storeAddStockedItems(this, products);
    return this;
}

static const char* getStoreId(void* store)
{
    const struct Store* this = (const struct Store*)store;
    return this->id;
}

static const char* storeToString(void* store)
{
    const struct Store* this = (const struct Store*)store;
    char* s = (char*)malloc(sizeof(char[7 + 20 + 1]));
    sprintf(s, "Store{%s}", this->name);
    return s;
}

static void saveStoreToDatabase(void* store)
{
    (void)store; /* unused */
    printf("Unsupported Operation %s\n",
           "missing from this exercise - shouldn't be called from a unit test");
    exit(1);
}

const char* getStoreName(const struct Store* this)
{
    return this->name;
}

void storeAddStockedItems(struct Store* this, const struct LinkedList* products)
{
    for (const struct LinkedList* node = products; node; node = node->next) {
        const struct Product* item = (const struct Product*)node->data;
        /*
        this->itemsInStock.put(getProductName(item), item);
        */
    }
}

void storeAddStoreEvent(struct Store* this, const struct StoreEvent* storeEvent)
{
    /*
    this->itemsInStock.put(getStoreEventName(storeEvent), storeEvent);
    */
}

void storeRemoveStockedItems(struct Store* this, const struct LinkedList* items)
{
    for (const struct LinkedList* node = items; node; node = node->next) {
        const struct Product* item = (const struct Product*)node->data;
        /*
        this->itemsInStock.remove(getProductName(item));
        */
    }
}

bool storeHasItem(const struct Store* this, const struct Product* item)
{
    /*
    return this->itemsInStock.containsKey(getProductName(item));
    */
    return false;
}

const struct Product* storeGetItem(const struct Store* this, const char* name)
{
    /*
    return this->itemsInStock.get(name);
    */
    return NULL;
}

struct LinkedList* getStoreStock(const struct Store* this)
{
    /*
    return Collections.unmodifiableCollection(this->itemsInStock.values());
    */
    return NULL;
}
