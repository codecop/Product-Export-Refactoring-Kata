#include <stdbool.h>

#include "LinkedList.h"
#include "Product.h"
#include "StoreEvent.h"

struct Store;

extern struct Store* makeStore(const char* name, const char* id, const struct LinkedList* products);
extern const char* getStoreName(const struct Store* this);
extern void storeAddStockedItems(struct Store* this, const struct LinkedList* products);
extern void storeAddStoreEvent(struct Store* this, const struct StoreEvent* storeEvent);
extern bool storeHasItem(const struct Store* this, const struct Product* item);
extern const struct Product* storeGetItem(const struct Store* this, const char* name);
extern const struct LinkedList* getStoreStock(const struct Store* this);
