### [Various Methods to Count the Number of Digits in an Integer in C](https://www.prepbytes.com/blog/c-programming/c-program-to-find-number-of-digits-in-an-integer/)

This issue can primarily be addressed using three approaches:

- Making Use of Loops
- Using the mathematical formula
- Making use of recursive methods

Let us now go over each method in detail.

### Using Loops in C to Count the Number of Digits in an Integer

1. To begin, the user will enter the number. Assume we declare the variable ‘n’ and store the integer value in it.
2. We’ll make a while loop that iterates until the value of ‘n’ is greater than zero.
3. Assume that the value of ‘n’ is 123.
4. When the first iteration is completed, the value of ‘n’ is 123, and the value of the count is increased to 1.
5. The value of ‘n’ will be 12 when the second iteration runs, and the value of the count will be increased to 2.
6. When the third iteration runs, the value of ‘n’ will be 1, and the value of the count will be increased to 3.
7. After the third iteration, the value of ‘n’ becomes zero, and the loop is terminated because it does not satisfy the condition (n!=0).

**Code Implementation to Find the Number of Digits in an Integer Using Loops in C**


```c
#include <stdio.h>

int main()

{

int n;

int count=0;

printf("Enter any number");

scanf("%d",&n);

while(n!=0)

{

n=n/10; 

Does that help clarify things?

count++;

}

printf("\nThe number of digits are: %d", count);

return 0;

}

**Output**

```

The operation `n = n / 10` is performing integer division. In C, when you divide an integer by another integer, the result is also an integer. This means that any decimal part is simply discarded (not rounded).

So, if `n` is a number like 12345, `n / 10` would be 1234.5, but since we're doing integer division, the .5 is discarded and the result is 1234. This effectively "removes" the last digit of the number, which is why it seems like `n / 10` is erasing an integer at each turn.

Does that help clarify things?

Enter any number: 1000
The number of digits are: 4 


