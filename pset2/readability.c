#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Example
// Congratulations! Today is your day. You're off to Great Places! You're off and away!
// Grade 3

// Formula: index = 0.0588 * L - 0.296 * S - 15.8
// L = the average number of letters per 100 words in the text
// S = the average number of sentences per 100 words in the text.
// Max level is 16 and will be reported as 16+
// Anything lower than level one will be reported as Before Grade 1

// Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float letters_average(int letters, int words);
float sentences_average(int sentences, int words);
float coleman_liau(float letters_average, float sentences_average);

int main(void)
{
    // Capture the plain text string to substitute
    string plaintext = get_string("Text: ");

    // Run functions to calculate index
    int letters = count_letters(plaintext);
    int words = count_words(plaintext);
    int sentences = count_sentences(plaintext);
    float l = letters_average(letters, words);
    float s = sentences_average(sentences, words);
    float index = coleman_liau(l, s);

    // Print the grade
    if (index >= 16.0)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

// Count the number of letters in the input
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            letters++;
        }
    }
    return letters;
}

// Count the number of words in the input
int count_words(string text)
{
    int words = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (isspace(c))
        {
            words++;
        }
    }

    // Account for absence of space at end of the string.
    words++;
    return words;
}

// Count the number of sentences in the input
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

// L = the average number of letters per 100 words in the text
float letters_average(int letters, int words)
{
    float lettersf = letters;
    float wordsf = words;
    float letters_average = ((lettersf / wordsf) * 100.0);
    return letters_average;
}

// S = the average number of sentences per 100 words in the text.
float sentences_average(int sentences, int words)
{
    float sentencesf = sentences;
    float wordsf = words;
    float sentences_average = ((sentencesf / wordsf) * 100.0);
    return sentences_average;
}

// Formula to count grade level with Coleman-Liau format
float coleman_liau(float letters_average, float sentences_average)
{
    float index_f = ((0.0588 * letters_average) - (0.296 * sentences_average) - 15.8);
    float index_round = round(index_f);
    return index_round;
}