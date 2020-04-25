#include <time.h>

#include "LinkedList.h"
#include "Product.h"
#include "Store.h"

struct Order;

extern struct Order* makeOrder(char* id, time_t date, struct Store* store, struct LinkedList* products);
extern double orderTotalDollars(const struct Order* this);
extern time_t getOrderDate(const struct Order* this);
extern const struct LinkedList* getOrderProducts(const struct Order* this);
extern void addOrderProduct(struct Order* this, const struct Product* product);
extern void addOrderProducts(struct Order* this, const struct LinkedList* products);
