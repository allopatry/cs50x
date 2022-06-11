#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Prototypes
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Tally and report the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    else
    {
        printf("Tie!\n");
        return 0;
    }
}

// Calculates the Scrabble score of a word. Skips non-alphabetical characters
int compute_score(string word)
{
    // Points assigned to each letter of the alphabet
    int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;

    // Iterates through each character in the input string
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char c = word[i];
        // Checks if the characters are alphabetical. Otherwise, effectively skips them.
        if isalpha(c)
        {
            // Offsets ascii if the character is uppercase
            if isupper(c)
            {
                int j = c - 65;
                int k = points[j];
                score = score + k;
            }
            // Offsets ascii if the character is lowercase
            else
            {
                int j = c - 97;
                int k = points[j];
                score += k;
            }
        }
    }
    return score;
}