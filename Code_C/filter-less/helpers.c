#include "helpers.h"

int custom_round(float num)
{
    if (num >= 0)
    {
        return (int) (num + 0.5);
    }
    else
    {
        return (int) (num - 0.5);
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get RGB values
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Calculate average and round it
            int average = custom_round((red + green + blue) / 3.0);

            // Set all RGB components to the average (gray color)
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get original RGB values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Calculate sepia values, rounding and clamping
            int sepiaRed =
                custom_round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen =
                custom_round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue =
                custom_round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Cap the values to max of 255
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Swap pixels from left to right
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixel j with pixel (width - 1 - j)
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image
    RGBTRIPLE copy[height][width];

    // Copy the original image into the temporary one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0, greenSum = 0, blueSum = 0;
            int count = 0;

            // Loop over the neighboring pixels including the current one
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighboring pixel is within the image boundaries
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        redSum += copy[ni][nj].rgbtRed;
                        greenSum += copy[ni][nj].rgbtGreen;
                        blueSum += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute the average and round
            image[i][j].rgbtRed = custom_round((float) redSum / count);
            image[i][j].rgbtGreen = custom_round((float) greenSum / count);
            image[i][j].rgbtBlue = custom_round((float) blueSum / count);
        }
    }
}
