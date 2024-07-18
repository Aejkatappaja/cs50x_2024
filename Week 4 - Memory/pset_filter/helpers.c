#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int average = round(
                (float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

int set_max_cap(int value)
{

    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int sepiaRed = round((float) .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round((float) .349 * image[i][j].rgbtRed +
                                   .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round((float) .272 * image[i][j].rgbtRed +
                                  .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // Compute sepia values

            image[i][j].rgbtRed = set_max_cap(sepiaRed);
            image[i][j].rgbtGreen = set_max_cap(sepiaGreen);
            image[i][j].rgbtBlue = set_max_cap(sepiaBlue);

            // Update pixel with sepia values
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred_image[height][width];

    for (int col = 0; col < height; col++)
    {
        for (int row = 0; row < width; row++)
        {

            double sumRed = 0;
            double sumGreen = 0;
            double sumBlue = 0;
            double divider = 0;

            for (int y = col - 1; y <= col + 1; y++)
            {
                for (int x = row - 1; x <= row + 1; x++)
                {
                    // If a pixel is within a valid range
                    if ((y >= 0 && y < height) && (x >= 0 && x < width))
                    {
                        sumRed = image[y][x].rgbtRed + sumRed;
                        sumGreen = image[y][x].rgbtGreen + sumGreen;
                        sumBlue = image[y][x].rgbtBlue + sumBlue;
                        divider++;
                    }
                }
            }

            blurred_image[col][row].rgbtRed = round((sumRed / divider));
            blurred_image[col][row].rgbtGreen = round((sumGreen / divider));
            blurred_image[col][row].rgbtBlue = round((sumBlue / divider));
        }
    }

    // Overwrite the orinal image with the blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurred_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurred_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurred_image[i][j].rgbtBlue;
        }
    }

    return;
}
