#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_valid_key(const char *key);
void convert_text(const char *key, const char *plaintext);

int main(int argc, const char *argv[])
{

    if (argc != 2)
    {
        return 1;
    }

    const char *key = argv[1];

    if (!is_valid_key(key))
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    convert_text(key, plaintext);

    return 0;
}

bool is_valid_key(const char *key)
{
    if (strlen(key) != 26)
    {
        printf("pas 26 \n");
        return false;
    }

    for (int i = 0; i < strlen(key); i++)

    {
        if (!isalpha(key[i]))
        {
            printf("Key should only contains alpha chars! \n");
            return false;
        }

        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                printf("Yor key should only contains unique characters! \n");
                return false;
            }
        }
    }
    return true;
}

void convert_text(const char *key, const char *plaintext)
{
    char ciphertext[strlen(plaintext) + 1];

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = toupper(key[plaintext[i] - 'A']);
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = tolower(key[plaintext[i] - 'a']);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0';

    printf("ciphertext: %s\n", ciphertext);
}