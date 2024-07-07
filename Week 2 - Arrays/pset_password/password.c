// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and "
               "symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{

    int len = strlen(password);
    bool has_lower = false;
    bool has_upper = false;
    bool has_digit = false;
    bool has_symbol = false;

    for (int i = 0; i < len; i++)
    {
        if (islower(password[i]))
        {
            has_lower = true;
        }
        else if (isupper(password[i]))
        {
            has_upper = true;
        }
        else if (isdigit(password[i]))
        {
            has_digit = true;
        }
        else if (ispunct(password[i]))
        {
            has_symbol = true;
        }
    }

    return has_lower && has_upper && has_digit && has_symbol;
}
