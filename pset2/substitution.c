#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Intended usage is to provide a 26 character cipher
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Define variables
    int n = strlen(argv[1]);
    string cipher = argv[1];

    // Cipher must be 26 characters
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Iterates through each character in cipher
    for (int i = 0; i < n; i++)
    {
        // Cast to character
        char j = cipher[i];
        bool k = isalpha(j);

        // Must be alphabetical character
        if (k != 1)
        {
            printf("Key must contain 26 alpha characters.\n");
            return 1;
        }
    }

    // Capture the plain text string to substitute
    string plaintext = get_string("plaintext: ");
    int n2 = strlen(plaintext);

    printf("ciphertext: ");

    // Iterate through each character in the input string
    for (int i = 0; i < n2; i++)
    {
        // Temporary variable to store the plaintext string character at position i
        char j = (plaintext[i]);

        // Only use cipher on alphabetical characters
        if isalpha(j)
        {
            // Use this operation for uppercase characters in the plaintext string
            if islower(j)
            {
                int offset = (j - 97);
                // printf("%d/n", offset);
                char cipher_char = cipher[offset];
                char cipher_lower = tolower(cipher_char);
                printf("%c", cipher_lower);
            }

            // ASCII offset to account for case change
            else
            {
                int offset = j - 65;
                char cipher_char = cipher[offset];
                char cipher_upper = toupper(cipher_char);
                printf("%c", cipher_upper);
            }
        }
        else
        {
            printf("%c", j);
        }
    }
    printf("\n");
}