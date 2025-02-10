#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void substitute(string plaintext, string key); // Function for swapping characters later on

int main(int argc, char *argv[]) // takes arguments
{
    if (argc == 1 || argc > 2) // Checks if user provided an argument with the program running, or provided more than one argument
    {
        printf("No key provided. Please use './substitution [KEY]'\n");
        exit(1);

    }
    string key = argv[1];  // assign the key to a string
    int check[26] = {0};    // arrray to check against
    int keylength  = strlen(key);

    for (int i = 0; i < keylength; i++)
    {
        key[i] = tolower(key[i]);   // converts the key to lower case, so that unique test can test one type
    }

    if (keylength == 26)
    {
        for (int i = 0; i < 26; i++) // check if 26 characters long
        {
            char cha = key[i];
            if (cha < 'a' || cha > 'z') // checks if alphabetical
            {
                printf("Invalid character detected. Please only use A-Z, not case-sensitive.\n");
                exit(1);
            }
            if (check[cha - 'a']) // checks if already seen
            {
                printf("Please use each character only once. 26 unique letters.\n");
                exit(1);
            }
            check[cha - 'a'] = 1; // lists the character as seen
        }
    }
    else
    {
        printf("Invalid length of key. Please use 26 letters.\n");  // not 26 long
        exit(1);
    }

    string plaintext = get_string("Plain text: ");
    substitute(plaintext, key);

}

void substitute(string plaintext, string key)
{
    int length = strlen(plaintext); // length of text for loop later
    char lookup[2][26]; // Alphabet on 0, Key on 1
    // char ptarray[length];
    char answer[length]; // define the variable to be written to for encryption

    for (int i = 0; i < 26; i++)
    {
        lookup[0][i] = 'A' + i; // Assigning alphabet to lookup row 0
    }

    for (int i = 0; i < 26; i++)
    {
        lookup[1][i] = key[i]; // Assigning Key to lookup row 1
    }

    // for (int i = 0; i < length; i++)  feel like I don't need this but keeping in case I do
    // {
    //     ptarray[i] = plaintext[];
    // }

    for (int i = 0; i < length; i++) // Cycle through each letter in the given text
    {
        for (int j = 0; j < 26; j++) // Cycle through the default alphabet
        {
            if (isalpha(plaintext[i])) // checks if alphabetical, a different method to ealier
            {
                if (plaintext[i] == lookup[0][j] || plaintext[i] == tolower(lookup[0][j])) // if the given character = the default alphabet (or lowercase)
                {
                    if (isupper(plaintext[i]))
                    {
                        answer[i] = toupper(lookup[1][j]);   // assign the key-character to the given character, capital
                    }
                    else
                    {
                        answer[i] = tolower(lookup[1][j]);  // assign the key-character to the given character, lower
                    }
                }

            }
            else
            {
                answer[i] = plaintext[i]; // catches spaces and numbers
            }
        }


    }
    answer[length] = '\0';  // add null term

    printf("ciphertext: %s\n", answer);
    exit(0);
}
