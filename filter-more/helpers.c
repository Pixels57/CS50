#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            int green = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            int blue = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int w = width;
        for(int j = 0; j < (width / 2); j++)
        {
            int tempr = image[i][j].rgbtRed;
            int tempb = image[i][j].rgbtBlue;
            int tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtRed = image[i][w - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][w - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][w - 1].rgbtBlue;
            image[i][w - 1].rgbtRed = tempr;
            image[i][w - 1].rgbtBlue = tempb;
            image[i][w - 1].rgbtGreen = tempg;
            w--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
        RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((j == 0) && (i == 0))
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0);
            }
            else if ((j == (width - 1)) && (i == 0))
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 4.0);
            }
            else if ((j == 0) && (i == (height - 1)))
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 4.0);
            }
            else if ((j == (width - 1)) && (i == (height - 1)))
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 4.0);
            }
            else if (i == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
            }
            else if (i == (height - 1))
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0);
            }
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
            }
            else if (j == (width - 1))
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);
            }
            else
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxr, gxb, gxg, gyr, gyb, gyg;
            if ((j == 0) && (i == 0))
            {
                // calc. the Gx and Gy for each color of top left pixel
                gxr = (copy[i][j + 1].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed * 1);
                gxb = (copy[i][j + 1].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue * 1);
                gxg = (copy[i][j + 1].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen * 1);
                gyr = (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed * 1);
                gyb = (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue * 1);
                gyg = (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen * 1);
            }
            else if ((j == (width - 1)) && (i == 0))
            {
                // calc. the Gx and Gy for each color of top right pixel
                gxr = (copy[i][j - 1].rgbtRed * -2) + (copy[i + 1][j - 1].rgbtRed * -1);
                gxb = (copy[i][j - 1].rgbtBlue * -2) + (copy[i + 1][j - 1].rgbtBlue * -1);
                gxg = (copy[i][j - 1].rgbtGreen * -2) + (copy[i + 1][j - 1].rgbtGreen * -1);
                gyr = (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j - 1].rgbtRed * 1);
                gyb = (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j - 1].rgbtBlue * 1);
                gyg = (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j - 1].rgbtGreen * 1);
            }
            else if ((j == 0) && (i == (height - 1)))
            {
                // calc. the Gx and Gy for each color of bottom left pixel
                gxr = (copy[i][j + 1].rgbtRed * 2) + (copy[i - 1][j + 1].rgbtRed * 1);
                gxb = (copy[i][j + 1].rgbtBlue * 2) + (copy[i - 1][j + 1].rgbtBlue * 1);
                gxg = (copy[i][j + 1].rgbtGreen * 2) + (copy[i - 1][j + 1].rgbtGreen * 1);
                gyr = (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1);
                gyb = (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1);
                gyg = (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1);
            }
            else if ((j == (width - 1)) && (i == (height - 1)))
            {
                // calc. the Gx and Gy for each color of bottom right pixel
                gxr = (copy[i][j - 1].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1);
                gxb = (copy[i][j - 1].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1);
                gxg = (copy[i][j - 1].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1);
                gyr = (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j].rgbtRed * -2);
                gyb = (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j].rgbtBlue * -2);
                gyg = (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j].rgbtGreen * -2);
            }
            else if (i == 0)
            {
                // calc. the Gx and Gy for each color of a top edge pixel
                gxr = (copy[i][j - 1].rgbtRed * -2) + (copy[i + 1][j - 1].rgbtRed* -1) + (copy[i][j + 1].rgbtRed * 2) +
                      (copy[i + 1][j + 1].rgbtRed * 1);
                gxb = (copy[i][j - 1].rgbtBlue * -2) + (copy[i + 1][j - 1].rgbtBlue * -1) + (copy[i][j + 1].rgbtBlue * 2) +
                      (copy[i + 1][j + 1].rgbtBlue * 1);
                gxg = (copy[i][j - 1].rgbtGreen * -2) + (copy[i + 1][j - 1].rgbtGreen * -1) + (copy[i][j + 1].rgbtGreen * 2) +
                      (copy[i + 1][j + 1].rgbtGreen * 1);
                gyr = (copy[i + 1][j - 1].rgbtRed * 1) + (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed * 1);
                gyb = (copy[i + 1][j - 1].rgbtBlue * 1) + (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue * 1);
                gyg = (copy[i + 1][j - 1].rgbtGreen * 1) + (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (i == (height - 1))
            {
                // calc. the Gx and Gy for each color of a bottom edge pixel
                gxr = (copy[i][j - 1].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i][j + 1].rgbtRed * 2) +
                      (copy[i - 1][j + 1].rgbtRed * 1);
                gxb = (copy[i][j - 1].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i][j + 1].rgbtBlue * 2) +
                      (copy[i - 1][j + 1].rgbtBlue * 1);
                gxg = (copy[i][j - 1].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i][j + 1].rgbtGreen * 2) +
                      (copy[i - 1][j + 1].rgbtGreen * 1);
                gyr = (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1);
                gyb = (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1);
                gyg = (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1);
            }
            else if (j == 0)
            {
                // calc. the Gx and Gy for each color of a left edge pixel
                gxr = (copy[i + 1][j + 1].rgbtRed * 1) + (copy[i][j + 1].rgbtRed * 2) + (copy[i - 1][j + 1].rgbtRed * 1);
                gxb = (copy[i + 1][j + 1].rgbtBlue * 1) + (copy[i][j + 1].rgbtBlue * 2) + (copy[i - 1][j + 1].rgbtBlue * 1);
                gxg = (copy[i + 1][j + 1].rgbtGreen * 1) + (copy[i][j + 1].rgbtGreen * 2) + (copy[i - 1][j + 1].rgbtGreen * 1);
                gyr = (copy[i + 1][j + 1].rgbtRed * 1) + (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1) +
                      (copy[i + 1][j].rgbtRed * 2);
                gyb = (copy[i + 1][j + 1].rgbtBlue * 1) + (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1) +
                      (copy[i + 1][j].rgbtBlue * 2);
                gyg = (copy[i + 1][j + 1].rgbtGreen * 1) + (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1) +
                      (copy[i + 1][j].rgbtGreen * 2);
            }
            else if (j == (width - 1))
            {
                // calc. the Gx and Gy for each color of a right edge pixel
                gxr = (copy[i + 1][j - 1].rgbtRed * -1) + (copy[i][j - 1].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1);
                gxb = (copy[i + 1][j - 1].rgbtBlue * -1) + (copy[i][j - 1].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1);
                gxg = (copy[i + 1][j - 1].rgbtGreen * -1) + (copy[i][j - 1].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1);
                gyr = (copy[i + 1][j - 1].rgbtRed * 1) + (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1) +
                      (copy[i + 1][j].rgbtRed * 2);
                gyb = (copy[i + 1][j - 1].rgbtBlue * 1) + (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1) +
                      (copy[i + 1][j].rgbtBlue * 2);
                gyg = (copy[i + 1][j - 1].rgbtGreen * 1) + (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1) +
                      (copy[i + 1][j].rgbtGreen * 2);
            }
            else
            {
                // calc. the Gx and Gy for each color of a non special case default pixel in the middle
                gxr = (copy[i + 1][j - 1].rgbtRed * -1.0) + (copy[i][j - 1].rgbtRed * -2.0) + (copy[i - 1][j - 1].rgbtRed * -1.0) + (copy[i - 1][j + 1].rgbtRed * 1.0) +
                      (copy[i][j + 1].rgbtRed * 2.0) + (copy[i + 1][j + 1].rgbtRed * 1.0);
                gxb = (copy[i + 1][j - 1].rgbtBlue * -1.0) + (copy[i][j - 1].rgbtBlue * -2.0) + (copy[i - 1][j - 1].rgbtBlue * -1.0) + (copy[i - 1][j + 1].rgbtBlue * 1.0) +
                      (copy[i][j + 1].rgbtBlue * 2.0) + (copy[i + 1][j + 1].rgbtBlue * 1.0);
                gxg = (copy[i + 1][j - 1].rgbtGreen * -1.0) + (copy[i][j - 1].rgbtGreen * -2.0) + (copy[i - 1][j - 1].rgbtGreen * -1.0) + (copy[i - 1][j + 1].rgbtGreen * 1.0) +
                      (copy[i][j + 1].rgbtGreen * 2.0) + (copy[i + 1][j + 1].rgbtGreen * 1.0);
                gyr = (copy[i + 1][j - 1].rgbtRed * 1.0) + (copy[i - 1][j].rgbtRed * -2.0) + (copy[i - 1][j - 1].rgbtRed * -1.0) + (copy[i + 1][j].rgbtRed * 2.0) +
                      (copy[i - 1][j + 1].rgbtRed * -1.0) + (copy[i + 1][j + 1].rgbtRed * 1.0);
                gyb = (copy[i + 1][j - 1].rgbtBlue * 1.0) + (copy[i - 1][j].rgbtBlue * -2.0) + (copy[i - 1][j - 1].rgbtBlue * -1.0) + (copy[i + 1][j].rgbtBlue * 2.0) +
                      (copy[i - 1][j + 1].rgbtBlue * -1.0) + (copy[i + 1][j + 1].rgbtBlue * 1.0);
                gyg = (copy[i + 1][j - 1].rgbtGreen * 1.0) + (copy[i - 1][j].rgbtGreen * -2.0) + (copy[i - 1][j - 1].rgbtGreen * -1.0) +
                      (copy[i + 1][j].rgbtGreen * 2.0) + (copy[i - 1][j + 1].rgbtGreen * -1.0) + (copy[i + 1][j + 1].rgbtGreen * 1.0);
            }
            // calc. the Gx and Gy for each color
            int nr = round(sqrt(((gxr) * (gxr)) + ((gyr) * (gyr))));
            int ng = round(sqrt(((gxg) * (gxg)) + ((gyg) * (gyg))));
            int nb = round(sqrt(((gxb) * (gxb)) + ((gyb) * (gyb))));
            if (nr > 255)
            {
                nr = 255;
            }
            else if (nr < 0)
            {
                nr = nr * -1;
            }
            if (nb > 255)
            {
                nb = 255;
            }
            else if (nb < 0)
            {
                nb = nb * -1;
            }
            if (ng > 255)
            {
                ng = 255;
            }
            else if (ng < 0)
            {
                ng = ng * -1;
            }
            image[i][j].rgbtRed = nr;
            image[i][j].rgbtBlue = nb;
            image[i][j].rgbtGreen = ng;
        }
    }
    return;
}
