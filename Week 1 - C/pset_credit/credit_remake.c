#include <cs50.h>
#include <stdio.h>

#define AMEX "AMEX"
#define MASTERCARD "MASTERCARD"
#define VISA "VISA"
#define INVALID "INVALID"

int credit_card_input_length(long credit_card);
string get_credit_card_type(int length, long n, bool check);
int luhn_check(long card_number);

int main(void)
{

    long credit_card_input = get_long("Number :");
    int length = credit_card_input_length(credit_card_input);
    bool check = luhn_check(credit_card_input);
    string result = get_credit_card_type(length, credit_card_input, check);
    printf("%s\n", result);
}

int credit_card_input_length(long credit_card)
{
    int count = 0;
    while (credit_card >= 1)
    {
        count++;
        credit_card /= 10;
    }
    return count;
}

string get_credit_card_type(int length, long n, bool check)
{
    int amex_match_length = length == 15;
    int mastercard_match_length = length == 16;
    int visa_match_length = length == 13 || length == 16;

    long prefix = n;
    while (prefix >= 100)
    {
        prefix /= 10;
    }

    if (check && amex_match_length && (prefix == 34 || prefix == 37))
    {
        return AMEX;
    }
    else if (check && mastercard_match_length && (prefix >= 51 && prefix <= 55))
    {
        return MASTERCARD;
    }
    else if (check && visa_match_length && (prefix / 10 == 4))
    {
        return VISA;
    }
    return INVALID;
}

int luhn_check(long card_number)
{
    int sum = 0;
    bool alternate = false;

    while (card_number > 0)
    {
        int digit = card_number % 10;

        if (alternate)
        {
            digit *= 2;
            if (digit > 9)
            {
                sum -= 9;
            }
        }

        sum += digit;
        card_number /= 10;
        alternate = !alternate;
    }

    return (sum % 10) == 0;
}
