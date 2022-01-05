#include <stdio.h>
#include <cs50.h>

int get_positive_integer(void);
int computeYearsToFinalPop(int, int);

int main(void)
{
    int startSize, finalSize;

    do
    {
        startSize = get_int("Start size: ");
    } while(startSize < 9);
    do
    {
        finalSize = get_int("End size: ");
    } while(finalSize < startSize);

    printf("Years: %d\n", computeYearsToFinalPop(startSize, finalSize));

    return 0;
}

int computeYearsToFinalPop(int start, int final)
{
    int years = 0;
    while(start < final)
    {
        start = start + start/3 - start/4;
        years++;
    }
    return years;
}