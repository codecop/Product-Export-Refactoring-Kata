#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Price {
    double amount;
    const char* currencyCode;
};

const struct Price* make_price(double amount, const char* currencyCode)
{
    struct Price* this = (struct Price*)malloc(sizeof(struct Price));
    this->amount = amount;
    this->currencyCode = currencyCode;
    return this;
}

const char* price_to_string(const struct Price* this)
{
    char* s = (char*)malloc(sizeof(char[7 + 9 + 1]));
    sprintf(s, "Price{%f}", this->amount);
    return s;
}

const char* get_price_currency(const struct Price* this)
{
    return this->currencyCode;
}

double get_price_amount(const struct Price* this)
{
    return this->amount;
}

double get_price_amount_in_currency(const struct Price* this, const char* currencyCode)
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
