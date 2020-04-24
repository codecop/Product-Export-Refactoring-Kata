#include <stdlib.h>
#include <stdio.h>
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

char* PriceToString(struct Price* this)
{
    char* buf = (char*)malloc(sizeof(char[7 + 5 + 1]));
    sprintf(buf, "Price{%f}", this->amount);
    return buf;
}

char* PriceGetCurrency(struct Price* this)
{
    return this->currencyCode;
}

double PriceGetAmount(struct Price* this)
{
    return this->amount;
}

double PriceGetAmountInCurrency(struct Price* this, char* currencyCode)
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
