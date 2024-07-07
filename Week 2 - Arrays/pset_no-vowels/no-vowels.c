// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string letter);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You should provide an argument vector!\n ");
        return 1;
    }

    string result = replace(argv[1]);
    printf("%s\n", result);
}

string replace(string word)
{

    string converted_word = word;

    for (int i = 0; i < strlen(word); i++)
    {
        switch (word[i])
        {
            case 'a':
                converted_word[i] = '6';
                break;

            case 'e':
                converted_word[i] = '3';
                break;
            case 'i':
                converted_word[i] = '1';
                break;
            case 'o':
                converted_word[i] = '0';
                break;
        }
    }
    return converted_word;
}
