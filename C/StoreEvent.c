#include <stdbool.h>
#include <stdlib.h>

#include "Product.h"
/*#include "Store.h"*/
#include "Price.h"
#include "StoreEvent.h"

/**
 * Ticket to In-store event, eg. makeover, eyeshadow masterclass
 * or beauty product launch evening reception
 */
struct StoreEvent {
    struct Product* base;
    /* struct Store* location; */
};

const struct StoreEvent* makeStoreEvent(const char* name,
                                        const char* id,
                                        /*struct Store* location,*/
                                        const struct Price* price)
{
    struct StoreEvent* this = (struct StoreEvent*)malloc(sizeof(struct StoreEvent));
    /*
    this->base.getId = getProductId;
    this->base.toString = productToString;
    this->base.saveToDatabase = saveProductToDatabase;
    this->id = id;
    this->name = name;
    this->weight = 0;
    this->price = price;
    storeEventSetLocation(this, location);
    */
    return this;
}

/*
void storeEventSetLocation(struct StoreEvent* this, struct Store* locationStore)
{
    this->location = locationStore;
    storeAddStoreEvent(locationStore, this);
}
*/

static const char* storeEventToString(void* storeEvent)
{
    const struct StoreEvent* this = (const struct StoreEvent*)storeEvent;
    char* s = (char*)malloc(sizeof(char[12 + 20 + 1]));
    /*sprintf(s, "StoreEvent{%s}", this->name);*/
    return s;
}

const char* getStoreEventName(const struct StoreEvent* storeEvent)
{
    return "";
}

bool storeEventIsEvent(const struct StoreEvent* this)
{
    (void)this;
    return true;
}
