#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a string is a valid integer
bool is_valid_key(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

// Function to encrypt a character
char encrypt_char(char c, int key)
{
    if (isupper(c))
    {
        return 'A' + (c - 'A' + key) % 26;
    }
    else if (islower(c))
    {
        return 'a' + (c - 'a' + key) % 26;
    }
    return c; // Non-alphabetic characters remain unchanged
}

int main(int argc, string argv[])
{
    // Check for valid number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validate the key
    if (!is_valid_key(argv[1]))
    {
        printf("Key must be a positive integer.\n");
        return 1;
    }

    // Convert the key from string to integer
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Encrypt the plaintext
    int n = strlen(plaintext);
    char ciphertext[n + 1]; // +1 for the null terminator

    for (int i = 0; i < n; i++)
    {
        ciphertext[i] = encrypt_char(plaintext[i], key);
    }

    // Add null terminator to the end of the ciphertext
    ciphertext[n] = '\0';

    // Output the ciphertext
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}
