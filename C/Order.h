#include <time.h>

#include "Product.h"
#include "Store.h"

extern struct Order* makeOrder(char* id, time_t date, struct Store* store, struct LinkedList* products);
extern double orderTotalDollars(const struct Order* this);
extern time_t getOrderDate(const struct Order* this);
extern const struct LinkedList* getOrderProducts(const struct Order* this);
extern void addOrderProduct(struct Order* this, const struct Product* product);
extern void addOrderProducts(struct Order* this, const struct LinkedList* products);
