#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

#define TOLOWER(x) 65 <= (x) && (x) <= 90 ? (x) + 32 : (x)
#define TOUPPER(x) 97 <= (x) && (x) <= 122 ? (x) - 32 : (x)

int checkInput(char*);
char *substitutionEncrypt(char*, char*);

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int error = checkInput(argv[1]);
        if(error == 1)
        {
            fprintf(stderr, "Key must contain 26 characters.\n");
            return 1;
        }
        else if(error == 2)
        {
            fprintf(stderr, "Key has more than one occurence of the same letter.\n");
            return 1;
        }
        else if(error == 3)
        {
            fprintf(stderr, "Key has a non-alphabetic character.\n");
            return 1;
        }
    }

    char *plainText, *cipherText;

    plainText = get_string("plaintext: ");
    cipherText = substitutionEncrypt(plainText, argv[1]);
    printf("ciphertext: %s\n", cipherText);
    free(cipherText);

    return 0;
}

int checkInput(char *input)
{
    int error = 0, n = strlen(input);
    if(strlen(input) != 26)
    {
        error = 1;
    }
    else
    {
        int i, j;

        for(i = 0; i < 26; i++)
        {
            input[i] = TOLOWER(input[i]);
            if(!isalpha(input[i]))
            {
                error = 3;
            }
            for(j = 0; j < i; j++)
            {
                if(input[i] == input[j])
                {
                    error = 2;
                }
            }
        }
    }
    return error;
}

char *substitutionEncrypt(char *text, char *key)
{
    int i, textLen = strlen(text);
    char *cipher = (char*) malloc(textLen + 1);

    for(i = 0; i < textLen; i++)
    {
        if(isalpha(text[i]))
        {
            if('A' <= text[i] && text[i] <= 'Z')
            {
                cipher[i] = TOUPPER(key[text[i] - 'A']);
            }
            else
            {
                cipher[i] = key[text[i] - 'a'];
            }
        }
        else
        {
            cipher[i] = text[i];
        }
    }
    cipher[textLen] = '\0';

    return cipher;
}