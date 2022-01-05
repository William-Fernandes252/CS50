#include <stdio.h>
#include <cs50.h>

void printStairs(int);

int main(void)
{
    int height, spaces, blocks, i, j;
    do
    {
        height = get_int("Height: ");
    } while(height < 1 || height > 8);

    printStairs(height);

    return 0;
}

void printStairs(int height)
{
    if(height == 0)
    {
        return;
    }
    else
    {
        printStairs(height - 1);
        for(int i = 0; i < height; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}