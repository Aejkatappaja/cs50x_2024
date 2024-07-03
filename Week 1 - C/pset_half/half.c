#include <cs50.h>
#include <stdio.h>

int main(void)
{

    float bill = get_float("Bill before tax and tip: ");
    float tax = get_float("Sale Tax Percent: ");
    float result = bill + ((tax / 100) * bill);
    float tip = get_float("Tip percent: ");
    float total = (result / 2) + (((tip / 100) * result) / 2);
    printf("You will owe $%.2f each!\n", total);
}
