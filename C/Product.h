#include <stdbool.h>

#include "Price.h"

struct Product;

extern const struct Product* makeProduct(char* name, char* id, long weight, struct Price* price);
extern const char* getProductName(const struct Product* this);
extern long getProductWeight(const struct Product* this);
extern const struct Price* getProductPrice(const struct Product* this);
extern bool isProductEvent(const struct Product* this);
