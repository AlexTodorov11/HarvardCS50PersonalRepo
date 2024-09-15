#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to validate the key
bool is_valid_key(string key)
{
    int n = strlen(key);
    if (n != 26)
    {
        return false;
    }

    bool seen[26] = {false};

    for (int i = 0; i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
        int index = tolower(key[i]) - 'a';
        if (seen[index])
        {
            return false;
        }
        seen[index] = true;
    }
    return true;
}

// Function to encrypt the plaintext
string encrypt(string plaintext, string key)
{
    int n = strlen(plaintext);
    char *ciphertext = malloc(n + 1); // +1 for the null terminator

    for (int i = 0; i < n; i++)
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
    ciphertext[n] = '\0'; // Null-terminate the ciphertext
    return ciphertext;
}

int main(int argc, string argv[])
{
    // Check for valid number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // Validate the key
    if (!is_valid_key(key))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Encrypt the plaintext
    string ciphertext = encrypt(plaintext, key);

    // Output the ciphertext
    printf("ciphertext: %s\n", ciphertext);

    // Free the allocated memory
    free(ciphertext);

    return 0;
}
