#include <cs50.h>
#include <stdio.h>

int main(void)
{
int counter = 0;

string answer = get_string("What's your name? ");
int age = get_int("How old are you? ");

counter++;

printf("Hello, %s\nYou are %i year old %i", answer, age, counter);


}
