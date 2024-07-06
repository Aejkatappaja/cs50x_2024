
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int sentence_length(string sentence);
int letter_count(string sentence, int len);
int word_count(string sentence, int len);
int sentence_count(string sentence, int len);
double coleman_liau_index(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    int length = sentence_length(text);

    int letters = letter_count(text, length);

    int words = word_count(text, length);

    int sentences = sentence_count(text, length);

    double result = coleman_liau_index(letters, words, sentences);

    if (result >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", result);
    }
    return 0;
}

int sentence_length(string sentence)
{
    int n = 0;
    while (sentence[n] != '\0')
    {
        n++;
    }
    return n;
}

int letter_count(string sentence, int len)
{
    int n = 0;
    for (int i = 0; i <= len; i++)
    {
        if (isalpha(sentence[i]) && sentence[i] != ' ')
        {
            n++;
        }
    }
    return n;
}

int word_count(string sentence, int len)
{
    int n = 0;

    for (int i = 0; i <= len; i++)
    {
        if (sentence[i] == ' ')
        {
            n++;
        }
    }

    return n + 1;
}

int sentence_count(string sentence, int len)
{
    int n = 0;

    for (int i = 0; i <= len; i++)
    {
        if (sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?')
        {
            n++;
        }
    }

    return n;
}

double coleman_liau_index(int letters, int words, int sentences)
{
    double L = (double) letters / words * 100;
    double S = (double) sentences / words * 100;

    double index = 0.0588 * L - 0.296 * S - 15.8;

    return round(index);
}
