#include <cs50.h>
#include <stdio.h>


int main(void)
{
int x = get_int("What's x? ");
int y = get_int("What's y? ");


(x < y) ? printf("x is lesser than y\n") : (x > y) ? printf("x is greater than y\n") : printf("x equal y");

// if (x < y) {
//     printf("x is lesser than y\n");
// } else if (y < x){
//      printf("x is greater than y\n");
// } else {
//     printf("x equal y");
// }
return 0;
}
