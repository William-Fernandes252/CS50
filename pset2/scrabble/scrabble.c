#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int computeScore(char*);

int main(void)
{
    char *word1, *word2;
    int score1, score2;

    word1 = get_string("Player 1: ");
    word2 = get_string("Player 2: ");

    score1 = computeScore(word1);
    score2 = computeScore(word2);

    if(score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if(score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int computeScore(char *word)
{
    int wordScore = 0, punctTable[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        if('a' <= word[i] && word[i] <= 'z')
        {
            wordScore += punctTable[word[i]-'a'];
        }
        else if('A' <= word[i] && word[i] <= 'Z')
        {
            wordScore += punctTable[word[i]-'A'];
        }
    }
    return wordScore;
}