#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;
    for (int i = 0; i < height; i++)
        for (int ii = 0; ii < width; ii++) 
        {
            gray = (image[i][ii].rgbtBlue + image[i][ii].rgbtGreen + image[i][ii].rgbtRed) / 3;
            image[i][ii].rgbtBlue = gray;
            image[i][ii].rgbtGreen = gray;
            image[i][ii].rgbtRed = gray;
        }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepia_blue, sepia_green, sepia_red;
    int original_blue, original_green, original_red;
    for (int i = 0; i < height; i++)
        for (int ii = 0; ii < width; ii++) 
        {
            original_blue = image[i][ii].rgbtBlue;
            original_green = image[i][ii].rgbtGreen;
            original_red = image[i][ii].rgbtRed;
            sepia_blue = .272 * original_red + .534 * original_green + .131 * original_blue;
            sepia_green = .349 * original_red + .686 * original_green + .168 * original_blue;
            sepia_red = .393 * original_red + .769 * original_green + .189 * original_blue;
            image[i][ii].rgbtBlue = sepia_blue > 255 ? 255 : sepia_blue;
            image[i][ii].rgbtGreen = sepia_green > 255 ? 255 : sepia_green;
            image[i][ii].rgbtRed = sepia_red > 255 ? 255 : sepia_red;
        }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
        for (int ii = 0; ii < width; ii++) 
        {
            copy[i][ii].rgbtBlue = image[i][ii].rgbtBlue;
            copy[i][ii].rgbtGreen = image[i][ii].rgbtGreen;
            copy[i][ii].rgbtRed = image[i][ii].rgbtRed;
        }

    int image_width;
    for (int i = 0; i < height; i++) 
    {
        image_width = 0;
        for (int ii = width; ii >= 0; ii--)
            image[i][image_width++] = copy[i][ii];
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
        for (int ii = 0; ii < width; ii++) 
        {
            copy[i][ii].rgbtBlue = image[i][ii].rgbtBlue;
            copy[i][ii].rgbtGreen = image[i][ii].rgbtGreen;
            copy[i][ii].rgbtRed = image[i][ii].rgbtRed;
        }

    const int MIN_WIDTH_HEIGHT = 0;
    const int MAX_HEIGHT = height - 1;
    const int MAX_WIDTH = width - 1;
    int neighbour_height, neighbour_width;
    int blue_sum, green_sum, red_sum;
    int neighbours;

    for (int i = 0; i < height; i++) {
        for (int ii = 0; ii < width; ii++) {
            neighbour_height = neighbour_width = blue_sum = green_sum = red_sum = neighbours = 0;
            for (int h = -1; h < 2; h++) {
                for (int w = -1; w < 2; w++) {
                    neighbour_height = i + h;
                    neighbour_width = ii + w;
                    if (neighbour_height >= MIN_WIDTH_HEIGHT && neighbour_height < MAX_HEIGHT 
                    && neighbour_width >= MIN_WIDTH_HEIGHT && neighbour_width < MAX_WIDTH) {
                        blue_sum += copy[neighbour_height][neighbour_width].rgbtBlue;
                        green_sum += copy[neighbour_height][neighbour_width].rgbtGreen;
                        red_sum += copy[neighbour_height][neighbour_width].rgbtRed;
                        neighbours++;
                    }
                }
            }
            image[i][ii].rgbtBlue = blue_sum / neighbours;
            image[i][ii].rgbtGreen = green_sum / neighbours;
            image[i][ii].rgbtRed = red_sum / neighbours;
        }
    }
}
