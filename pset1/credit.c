#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Checks that a credit card number is likely valid and for valid cards
//      returns the card manufacturer as a string to the terminal.

// Luhn's Algorithm for checksum:
// 1. Multiply every other digit by 2, starting with the number’s
//     second-to-last digit, and then add those products’ digits together.
// 2. Add the sum to the sum of the digits that weren’t multiplied by 2.
// 3. If the total’s last digit is 0 (or, put more formally,
//      if the total modulo 10 is congruent to 0), the number is valid!

// Card definitions:
// AMEX: 15-digit number. Starts with 34 or 37.
// MASTERCARD: 16-digit number. Starts with 51, 52, 53, 54, or 55.
// VISA: 13- or 16-digit number. Starts with 4.

// Prototypes
int extractor(long card_num, int length, int n);

int main(void)
{
    // get_long will only accept integers
    long card_num = get_long("Number: ");

    int length, d1, d2;
    long card_temp = card_num;

    // Calculates the number of digits in the input number
    length = floor(log10(labs(card_num))) + 1;

    int arr[length - 1];
    int total = 0;

    // Captures the first and first-two digits, respectively
    d1 = extractor(card_num, length, 1);
    d2 = extractor(card_num, length, 2);

    // Checks that the passed long integer is a valid length
    if ((length != 13) && (length != 15) && (length != 16))
    {
        printf("INVALID\n");
        return 0;
    }
    else
    {
        // Captures each digit in the card number and stores in an array
        for (int i = 0; i < length; i++)
        {
            int r = card_temp % 10;
            // Cursed empty printf command needed to avoid segfault with some VISA cards?
            printf("");
            arr[i] = r;
            card_temp = (card_temp - r);
            card_temp = card_temp / 10;
        }

        // Set up for a checksum
        for (int i = 0; i < length; i++)
        {
            // Even numbers
            if (i % 2 == 0)
            {
                int j = arr[i];
                total = total + j;
            }

            // Odd numbers
            else
            {
                int j = arr[i];
                int k = j * 2;

                // Add digits comprising two-digit numbers, rather than the actual number
                if (k > 9)
                {
                    int v = (k % 10);
                    int w = ((k - v) / 10) % 10;
                    total = total + w + v;
                }

                else
                {
                    total = total + k;
                }
            }
        }

        // If last digit of total is a zero, checksum passes
        int mod = total % 10;
        if (mod != 0)
        {
            printf("INVALID\n");
            return 0;
        }

        // Report the actual card type, if the conditions are correct
        else
        {
            // Checks if American Express
            if (length == 15)
            {
                if ((d2 == 34) || (d2 == 37))
                {
                    printf("AMEX\n");
                    return 0;
                }
                else
                {
                    printf("INVALID\n");
                    return 0;
                }
            }
            else if ((length == 16) || (length == 13))
            {
                // Checks if Mastercard
                if ((d2 == 51) || (d2 == 52) || (d2 == 53) || (d2 == 54) || (d2 == 55))
                {
                    printf("MASTERCARD\n");
                    return 0;
                }
                // Checks if Visa
                else if (d1 == 4)
                {
                    printf("VISA\n");
                    return 0;
                }
                else
                {
                    printf("INVALID\n");
                    return 0;
                }
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
    }
}


// Returns numbers from the given card number beginning with first number
int extractor(long card_num, int length, int n)
{
    int d;
    d = (int)(card_num / pow(10, length - n));
    return d;
}
