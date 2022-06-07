#include <cs50.h>
#include <stdio.h>

// Prototype "breadcrumbs"
void left_spaces(int n);
void blocks(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    // Checks user input is between 1 and 8
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        int j, k;

        // Variable to keep track of number of spaces
        j = (n - i) - 1;

        // Variable to keep track of number of blocks
        k = i + 1;

        left_spaces(j);
        blocks(k);
        printf("  ");
        blocks(k);
        printf("\n");
    }
}

// Will print left-aligned spaces
void left_spaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// Will print blocks as '#' character
void blocks(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}