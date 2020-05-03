#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Price {
    double amount;
    const char* currency_code;
};

const struct Price* make_price(double amount, const char* currency_code)
{
    struct Price* this = (struct Price*)malloc(sizeof(struct Price));
    this->amount = amount;
    this->currency_code = currency_code;
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
    return this->currency_code;
}

double get_price_amount(const struct Price* this)
{
    return this->amount;
}

double get_price_amount_in_currency(const struct Price* this, const char* currency_code)
{
    if (strcmp(this->currency_code, currency_code) == 0) {
        return this->amount;
    }
    else {
        printf("Unsupported Operation %s\n",
               "shouldn't call this from a unit test, it will do a slow db "
               "lookup");
        exit(1);
    }
}
