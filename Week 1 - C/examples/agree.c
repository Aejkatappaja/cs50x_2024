
#include <cs50.h>
#include <stdio.h>

int main(void)
{

    char c = get_char("Do you agree? ");

    int userAgreed = (c == 'y' || c == 'Y');
    int userDisagree = (c == 'n' || c == 'N');

    if (userAgreed)
    {
        printf("Agreed.\n");
    }

    else if (userDisagree)
    {
        printf("Not agreed.\n");
    }
}
