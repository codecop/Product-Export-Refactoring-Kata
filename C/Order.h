#include <time.h>

#include "Product.h"
#include "Store.h"

extern struct Order* makeOrder(char* id, time_t date, struct Store* store, struct Product* products[]);
extern time_t getOrderDate(struct Order* this);
extern struct Product** getOrderProducts(struct Order* this);
extern void addOrderProduct(struct Order* this, struct Product* product);
extern void addOrderProducts(struct Order* this, struct Product* products[]);
extern double orderTotalDollars(struct Order* this);
