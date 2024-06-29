#include <cs50.h>
#include <stdio.h>

#define PYRAMID_MAX_HEIGHT 8
#define BLOCK '#'
#define SPACING " "

void blocks_separator(void);
void construct_mario_blocks(int n);

int main(void)
{
    int n;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > PYRAMID_MAX_HEIGHT);

    construct_mario_blocks(n);
}

void construct_mario_blocks(int n)
{

    for (int i = 0; i < n; i++)

    {
        for (int j = 1; j < n - i; j++)
        {
            printf("%s", SPACING);
        }

        for (int k = 0; k <= i; k++)
        {
            printf("%c", BLOCK);
        }

        blocks_separator();

        for (int l = 0; l <= i; l++)
        {
            printf("%c", BLOCK);
        }

        printf("\n");
    }
}

void blocks_separator(void)
{
    printf("%s", SPACING);
    printf("%s", SPACING);
}
