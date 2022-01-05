#include "helpers.h"
#include <math.h>
#include <stdio.h>

#define ROUND(x) (x) - (BYTE)(x) >= 0.5 ? (BYTE)(x) + 1 : (BYTE)(x)
#define CAP(x, cap) (x) < cap ? (x) : cap
#define SQUARE(x) (x)*(x)

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float mean;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            mean = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3.0f;
            mean = ROUND(mean);
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtRed = mean;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k;
    RGBTRIPLE aux[width];

    for(i = 0; i < height; i++)
    {
        for(j = width - 1, k = 0; j >= 0; j--, k++)
        {
            aux[k] = image[i][j];
        }
        for(j = 0; j < width; j++)
        {
            image[i][j] = aux[j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blured[height][width];
    int i, j, k, l;
    float bSum, gSum, rSum, surrPixelsCount;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            bSum = 0;
            gSum = 0;
            rSum = 0;
            surrPixelsCount = 0;

            for(k = i - 1; k <= i + 1; k++)
            {
                for(l = j - 1; l <= j + 1; l++)
                {
                    if(k >= 0 && k < height && l >= 0 && l < width)
                    {
                        bSum += image[k][l].rgbtBlue;
                        gSum += image[k][l].rgbtGreen;
                        rSum += image[k][l].rgbtRed;
                        surrPixelsCount++;
                    }
                }
            }

            blured[i][j].rgbtBlue = ROUND(bSum/surrPixelsCount);
            blured[i][j].rgbtGreen = ROUND(gSum/surrPixelsCount);
            blured[i][j].rgbtRed = ROUND(rSum/surrPixelsCount);
        }
    }

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blured[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blured[i][j].rgbtGreen;
            image[i][j].rgbtRed = blured[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edges[height][width];
    int i, j, k, l, m, n;
    int xSobelOp[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}},
        ySobelOp[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    double  gxBlue, gxGreen, gxRed,
            gyBlue, gyGreen, gyRed,
            gBlue, gGreen, gRed;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            gxBlue = 0, gxGreen = 0, gxRed = 0;
            gyBlue = 0, gyGreen = 0, gyRed = 0;

            for(k = i - 1, m = 0; k <= i + 1; k++, m++)
            {
                for(l = j - 1, n = 0; l <= j + 1; l++, n++)
                {
                    if(k >= 0 && k < height && l >= 0 && l < width)
                    {
                        gxBlue += image[k][l].rgbtBlue * xSobelOp[m][n];
                        gyBlue += image[k][l].rgbtBlue * ySobelOp[m][n];
                        gxGreen += image[k][l].rgbtGreen * xSobelOp[m][n];
                        gyGreen += image[k][l].rgbtGreen * ySobelOp[m][n];
                        gxRed += image[k][l].rgbtRed * xSobelOp[m][n];
                        gyRed += image[k][l].rgbtRed * ySobelOp[m][n];
                    }
                }
            }

            gBlue = CAP(sqrt(SQUARE(gxBlue) + SQUARE(gyBlue)), 255.0);
            gGreen = CAP(sqrt(SQUARE(gxGreen) + SQUARE(gyGreen)), 255.0);
            gRed = CAP(sqrt(SQUARE(gxRed) + SQUARE(gyRed)), 255.0);

            edges[i][j].rgbtBlue = ROUND(gBlue);
            edges[i][j].rgbtGreen = ROUND(gGreen);
            edges[i][j].rgbtRed = ROUND(gRed);
        }
    }

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = edges[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edges[i][j].rgbtGreen;
            image[i][j].rgbtRed = edges[i][j].rgbtRed;
        }
    }

    return;
}
