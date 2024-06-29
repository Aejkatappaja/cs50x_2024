#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define AMEX "AMEX"
#define MASTERCARD "MASTERCARD"
#define VISA "VISA"
#define INVALID "INVALID"

int get_card_length(long n);
string verify_card_type(long n, int len);
bool amex_matching_pattern(long x);
bool mastercard_matching_pattern(long x);
bool visa_matching_pattern(long x);

int main(void)
{

    long card_numbers = get_long("Number: ");

    long len = get_card_length(card_numbers);

    verify_card_type(card_numbers, len);
}

int get_card_length(long n)
{
    int count = 0;

    while (n != 0)
    {
        n = n / 10;
        count++;
        printf("n: %li\n", n);
    }

    if (count != 13 && count != 15 && count != 16)
    {
        printf("%s\n", INVALID);
        return 0;
    }
    else
    {
        printf("count: %i\n", count);
    }
    return count;
}

string verify_card_type(long n, int len)
{
    long x = n;

    while (x >= 100)
    {
        x /= 10;
    }
    printf("%li\n", x);

    if (len == 15 && amex_matching_pattern(x))
    {
        printf("%s\n", AMEX);
    }
    else if (len == 16 && mastercard_matching_pattern(x))
    {
        printf("%s\n", MASTERCARD);
    }
    else if ((len == 13 || len == 16) && visa_matching_pattern(x))
    {
        printf("%s\n", VISA);
    }
    return "hello";
}

bool amex_matching_pattern(long x)
{
    return x == 34 || x == 37;
}

bool mastercard_matching_pattern(long x)
{
    return x == 51 || x == 52 || x == 53 || x == 54 || x == 55;
}

bool visa_matching_pattern(long x)
{
    return (x / 10) == 4;
}
