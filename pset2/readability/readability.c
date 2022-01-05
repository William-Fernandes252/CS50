#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int countWords(char*);
int countSentences(char*);
int countLetters(char*);
double computeLiauIndex(int, int, int);

int main(void)
{
    char *text;
    int nSentences, nWords, nLetters;
    double gradeLevel;

    text = get_string("Text: ");

    nSentences = countSentences(text);
    nWords = countWords(text);
    nLetters = countLetters(text);
    gradeLevel = computeLiauIndex(nLetters, nWords, nSentences);

    if(gradeLevel - (int)gradeLevel > 0.5)
    {
        gradeLevel = ceil(gradeLevel);
    }
    else
    {
        gradeLevel = floor(gradeLevel);
    }

    if(gradeLevel < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(gradeLevel > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int)gradeLevel);
    }

    return 0;
}

int countWords(char *text)
{
    int counter = 1, i, len;
    for(i = 0, len = strlen(text); i < len; i++)
    {
        if(text[i] == ' ')
        {
            counter++;
        }
    }
    return counter;
}

int countSentences(char *text)
{
    int counter = 0, i, len;
    for(i = 0, len = strlen(text); i < len; i++)
    {
        if(text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}

int countLetters(char *text)
{
    int counter = 0, i, len;
    for(i = 0, len = strlen(text); i < len; i++)
    {
        if(isalpha(text[i]))
        {
            counter++;
        }
    }
    return counter;
}

double computeLiauIndex(int nLetters, int nWords, int nSentences)
{
    return 0.0588 * (nLetters * 100.0 / nWords) - 0.296 * (nSentences * 100.0 / nWords) - 15.8;
}