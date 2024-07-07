### Code Explanation

#### Header Includes

c

Copier le code

`#include <cs50.h> #include <ctype.h> #include <stdio.h> #include <string.h>`

- These are header files included at the beginning of the code. They provide various functionalities:
    - `cs50.h`: Includes functions like `get_string()` for input handling.
    - `ctype.h`: Includes functions like `isalpha()` and `toupper()` for character operations.
    - `stdio.h`: Standard input-output functions like `printf()`.
    - `string.h`: String handling functions like `strlen()` and `strcpy()`.

#### Function Prototypes

c

Copier le code

`bool is_valid_key(const char *key); void convert_text(const char *key, const char *plaintext);`

- These are function prototypes. They declare the existence of two functions (`is_valid_key` and `convert_text`) before they are defined later in the code. This allows the `main` function to call them.

#### Main Function

c

Copier le code

`int main(int argc, const char *argv[]) {     if (argc != 2)     {         return 1;     }      const char *key = argv[1];      if (!is_valid_key(key))     {         return 1;     }      string plaintext = get_string("plaintext: ");      convert_text(key, plaintext);      return 0; }`

- `int main(int argc, const char *argv[])`: This is the entry point of the program. `argc` is the number of arguments passed to the program, and `argv[]` is an array of strings containing these arguments.
    
- `if (argc != 2) { return 1; }`: Checks if exactly one command-line argument (besides the program name itself) is provided. If not, the program exits with a return value of 1, indicating an error.
    
- `const char *key = argv[1];`: Declares `key` as a pointer to a constant character string (`const char *`). It assigns `key` to point to the first command-line argument (`argv[1]`), which is expected to be the encryption key.
    
- `if (!is_valid_key(key)) { return 1; }`: Calls the `is_valid_key` function to validate the encryption key. If the key is invalid (not 26 characters, contains non-alphabetic characters, or has duplicates), the program exits with a return value of 1.
    
- `string plaintext = get_string("plaintext: ");`: Uses `get_string` (likely from `cs50.h`) to prompt the user for input and store it in `plaintext`. The user input is expected to be the plaintext message to be encrypted.
    
- `convert_text(key, plaintext);`: Calls the `convert_text` function, passing the validated key and the plaintext as arguments to perform the encryption.
    
- `return 0;`: Indicates successful execution of the program.
    

#### is_valid_key Function

c

Copier le code

`bool is_valid_key(const char *key) {     if (strlen(key) != 26)     {         printf("pas 26 \n");         return false;     }      for (int i = 0; i < strlen(key); i++)     {         if (!isalpha(key[i]))         {             printf("Key should only contains alpha chars! \n");             return false;         }          for (int j = i + 1; j < strlen(key); j++)         {             if (key[i] == key[j])             {                 printf("Your key should only contains unique characters! \n");                 return false;             }         }     }     return true; }`

- `bool is_valid_key(const char *key)`: Defines a function that takes a pointer to a constant character string (`const char *key`) and returns a boolean (`true` if the key is valid, `false` otherwise).
    
- `if (strlen(key) != 26) { printf("pas 26 \n"); return false; }`: Checks if the length of `key` is not 26. If not, it prints an error message and returns `false`.
    
- `for (int i = 0; i < strlen(key); i++)`: Iterates through each character of `key` to perform additional checks.
    
- `if (!isalpha(key[i])) { printf("Key should only contains alpha chars! \n"); return false; }`: Checks if the current character `key[i]` is not alphabetic. If true, it prints an error message and returns `false`.
    
- Nested Loop: Checks for duplicate characters in `key`. If any duplicates are found, it prints an error message and returns `false`.
    
- `return true;`: If all checks pass, the function returns `true`, indicating the key is valid.
    

#### convert_text Function

c

Copier le code

`void convert_text(const char *key, const char *plaintext) {     char ciphertext[strlen(plaintext) + 1];      for (int i = 0, n = strlen(plaintext); i < n; i++)     {         if (isupper(plaintext[i]))         {             ciphertext[i] = toupper(key[plaintext[i] - 'A']);         }         else if (islower(plaintext[i]))         {             ciphertext[i] = tolower(key[plaintext[i] - 'a']);         }         else         {             ciphertext[i] = plaintext[i];         }     }      ciphertext[strlen(plaintext)] = '\0';      printf("ciphertext: %s\n", ciphertext); }`

- `void convert_text(const char *key, const char *plaintext)`: Defines a function that takes two arguments: `key` (a pointer to a constant character string) and `plaintext` (a pointer to a constant character string).
    
- `char ciphertext[strlen(plaintext) + 1];`: Declares `ciphertext` as a character array with a size equal to the length of `plaintext` plus one (for the null terminator).
    
- `for (int i = 0, n = strlen(plaintext); i < n; i++) { ... }`: Iterates through each character of `plaintext` to convert it into ciphertext using the provided `key`.
    
- `if (isupper(plaintext[i])) { ciphertext[i] = toupper(key[plaintext[i] - 'A']); }`: If the current character in `plaintext` is uppercase, it uses the corresponding character from `key` after adjusting for uppercase letters ('A').
    
- `else if (islower(plaintext[i])) { ciphertext[i] = tolower(key[plaintext[i] - 'a']); }`: If the current character in `plaintext` is lowercase, it uses the corresponding character from `key` after adjusting for lowercase letters ('a').
    
- `else { ciphertext[i] = plaintext[i]; }`: Copies non-alphabetic characters (like spaces or punctuation) directly to `ciphertext`.
    
- `ciphertext[strlen(plaintext)] = '\0';`: Adds the null terminator to `ciphertext` to properly terminate the string.
    
- `printf("ciphertext: %s\n", ciphertext);`: Prints the encrypted ciphertext to the console.