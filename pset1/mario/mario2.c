#include <stdio.h>
#include <cs50.h>

void printPyramid(int);

int main(void)
{
    int height, spaces, blocks, i, j;
    do
    {
        height = get_int("Height: ");
    } while(height < 1 || height > 8);

    spaces = height - 1;
    blocks = 1;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        for(j = 0; j < blocks; j++)
        {
            printf("#");
        }
        printf("  ");
        for(j = 0; j < blocks; j++)
        {
            printf("#");
        }
        printf("\n");

        blocks++;
        spaces--;
    }

    return 0;
}