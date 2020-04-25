#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Price {
    double amount;
    char* currencyCode;
};

const struct Price* makePrice(double amount, char* currencyCode)
{
    struct Price* this = (struct Price*)malloc(sizeof(struct Price));
    this->amount = amount;
    this->currencyCode = currencyCode;
    return this;
}

const char* priceToString(const struct Price* this)
{
    char* s = (char*)malloc(sizeof(char[7 + 9 + 1]));
    sprintf(s, "Price{%f}", this->amount);
    return s;
}

double getPriceAmount(const struct Price* this)
{
    return this->amount;
}

const char* getPriceCurrency(const struct Price* this)
{
    return this->currencyCode;
}

double getPriceAmountInCurrency(const struct Price* this, char* currencyCode)
{
    if (strcmp(this->currencyCode, currencyCode) == 0) {
        return this->amount;
    }
    else {
        printf("Unsupported Operation %s\n",
               "shouldn't call this from a unit test, it will do a slow db "
               "lookup");
        exit(1);
    }
}
