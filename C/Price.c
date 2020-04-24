#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Price {
    double amount;
    char* currencyCode;
};

struct Price* makePrice(double amount, char* currencyCode)
{
    struct Price* this = (struct Price*)malloc(sizeof(struct Price));
    this->amount = amount;
    this->currencyCode = currencyCode;
    return this;
}

char* priceToString(struct Price* this)
{
    char* buf = (char*)malloc(sizeof(char[7 + 5 + 1]));
    sprintf(buf, "Price{%f}", this->amount);
    return buf;
}

double getPriceAmount(struct Price* this)
{
    return this->amount;
}

char* getPriceCurrency(struct Price* this)
{
    return this->currencyCode;
}

double getPriceAmountInCurrency(struct Price* this, char* currencyCode)
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
