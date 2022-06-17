#include "helpers.h"
#include <math.h>

// Uses some logic from https://github.com/melvinkokxw/cs50-pset/blob/master/pset4/filter/more/helpers.c

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over scanlines
    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels within scanline
        for (int j = 0; j < width; j++)
        {
            // Rounded average converts to grayscale
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Instantiates a temporary array to store reflection
    RGBTRIPLE tmpimage[height][width];

    // Iterate over scanlines
    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels within scanline
        for (int j = 0; j < width; j++)
        {
            // Reflects the image left-right and stores in tmpimage
            tmpimage[i][j] = image[i][width - j - 1];
        }
    }

    // Set the input equal to the temporary array
    // Iterate over scanlines
    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels within scanline
        for (int j = 0; j < width; j++)
        {
            // Reflect original image left-right
            image[i][j] = tmpimage[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Instantiates a temporary array to store blurred data
    RGBTRIPLE tmpimage[height][width];

    // Box averaging filter with some treatment of edge cases
    // Iterate over scanlines
    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels within scanline
        for (int j = 0; j < width; j++)
        {
            // Initialize some storage variables
            int red = 0, green = 0, blue = 0, num_pixels = 0;

            // Iterate over rows above, equal to, and below kernel
            for (int row = i - 1; row <= i + 1; row++)
            {
                // Iterate over columns left, equal to, and right of kernel
                for (int col = j - 1; col <= j + 1; col++)
                {
                    // Edge cases to skip
                    if (row == -1 || row == height || col == -1 || col == width)
                    {
                        // Don't break - just keep going
                        continue;
                    }
                    // Accumulates values to later average
                    red += image[row][col].rgbtRed;
                    green += image[row][col].rgbtGreen;
                    blue += image[row][col].rgbtBlue;
                    num_pixels++;
                }
            }

            tmpimage[i][j].rgbtRed = round(red / (float)num_pixels);
            tmpimage[i][j].rgbtGreen = round(green / (float)num_pixels);
            tmpimage[i][j].rgbtBlue = round(blue / (float)num_pixels);
        }
    }

    // Set the input equal to the temporary array
    // Iterate over scanlines
    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels within scanline
        for (int j = 0; j < width; j++)
        {
            // Blur original image
            image[i][j] = tmpimage[i][j];
        }
    }

    return;
}

// Detect edges
// https://en.wikipedia.org/wiki/Sobel_operator

// "treat the image as if there was a 1 pixel solid black border around
//   the edge of the image: therefore, trying to access a pixel past the
//   edge of the image should be treated as a solid black pixel
//   (values of 0 for each of red, green, and blue)."
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Instantiates a temporary array to store edge-enhanced data
    RGBTRIPLE tmpimage[height][width];

    // Sobel convolutions in X and Y directions
    int gx_conv[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_conv[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Sobel filter with some treatment of edge cases
    // Iterate over scanlines
    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels within scanline
        for (int j = 0; j < width; j++)
        {
            // Initialize some storage variables
            float gx_red = 0, gx_green = 0, gx_blue = 0;
            float gy_red = 0, gy_green = 0, gy_blue = 0;

            // Iterate over rows above, equal to, and below kernel
            for (int row = i - 1; row <= i + 1; row++)
            {
                // Iterate over columns left, equal to, and right of kernel
                for (int col = j - 1; col <= j + 1; col++)
                {
                    // Edge cases to skip
                    if (row == -1 || row == height || col == -1 || col == width)
                    {
                        // Don't break - just keep going
                        continue;
                    }

                    // Accumulates values to later average
                    gx_red += image[row][col].rgbtRed * gx_conv[row - (i - 1)][col - (j - 1)];
                    gx_green += image[row][col].rgbtGreen * gx_conv[row - (i - 1)][col - (j - 1)];
                    gx_blue += image[row][col].rgbtBlue * gx_conv[row - (i - 1)][col - (j - 1)];
                    gy_red += image[row][col].rgbtRed * gy_conv[row - (i - 1)][col - (j - 1)];
                    gy_green += image[row][col].rgbtGreen * gy_conv[row - (i - 1)][col - (j - 1)];
                    gy_blue += image[row][col].rgbtBlue * gy_conv[row - (i - 1)][col - (j - 1)];
                }
            }

            // Gx^2 + Gy^2
            int g_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int g_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int g_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            // result%255
            if (g_red > 255)
            {
                g_red = 255;
            }
            if (g_green > 255)
            {
                g_green = 255;
            }
            if (g_blue > 255)
            {
                g_blue = 255;
            }

            // set this portion of the temp image to the computed values
            tmpimage[i][j].rgbtRed = g_red;
            tmpimage[i][j].rgbtGreen = g_green;
            tmpimage[i][j].rgbtBlue = g_blue;
        }
    }


    // Set the input equal to the temporary array
    // Iterate over scanlines
    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels within scanline
        for (int j = 0; j < width; j++)
        {
            // Return sobel-filtered image to original image array
            image[i][j] = tmpimage[i][j];
        }
    }

    return;
}
