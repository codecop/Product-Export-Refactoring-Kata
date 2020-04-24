#include <stdbool.h>

#include "ModelObject.h"
#include "Price.h"

struct Product {
    struct ModelObject base;
    char* name;
    long weight;
    struct Price* price;
};

extern struct Product* makeProduct(char* name, char* id, long weight, struct Price* price);
extern char* getProductName(struct Product* this);
extern char* getProductId(struct Product* this);
extern long getProductWeight(struct Product* this);
extern struct Price* getProductPrice(struct Product* this);
extern bool isProductEvent(struct Product* this);
