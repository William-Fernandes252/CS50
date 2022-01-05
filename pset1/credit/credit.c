#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGLEN 20

int validateCard(long, int, int);
void catFirstTwoDigits(int*, int*, int number);
int countDigits(int);
long get_long(const char*);

int main(void)
{
    int digitsCount, i, firstDigit, secondDigit, validate;
    long creditCard = get_long("Number: "), aux;

    catFirstTwoDigits(&firstDigit, &secondDigit, creditCard);
    digitsCount = countDigits(creditCard);

    if(digitsCount != 13 && digitsCount != 15 && digitsCount != 16)
    {
        printf("INVALID\ns");
    }
    else
    {
        validate = validateCard(creditCard, firstDigit, secondDigit);
        switch(validate)
        {
            case 0: printf("INVALID\n"); break;
            case 1: printf("AMEX\n"); break;
            case 2: printf("VISA\n"); break;
            case 3: printf("MASTERCARD\n"); break;
        }
    }

    return 0;
}

int validateCard(long number, int firstDigit, int secondDigit)
{
    int pairDigitsSum = 0, checkCardSum = 0, digitPos = 1, validation = 0, aux, digit;

    while(number > 0)
    {
        digit = number % 10;
        if(digitPos % 2 == 0)
        {
            if(digit * 2 < 10)
            {
                pairDigitsSum += digit * 2;
            }
            else
            {
                aux = digit * 2;
                while(aux > 0)
                {
                    pairDigitsSum += aux % 10;
                    aux /= 10;
                }
            }
        }
        else
        {
            checkCardSum += digit;
        }

        digitPos++;
        number /= 10;
    }
    checkCardSum += pairDigitsSum;

    if(checkCardSum % 10 == 0)
    {
        if(firstDigit == 5 && (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5))
        {
            validation = 3;
        }
        else if(firstDigit == 3 && (secondDigit == 4 || secondDigit == 7))
        {
            validation = 1;
        }
        else if(firstDigit == 4)
        {
            validation = 2;
        }
    }

    return validation;
}

long get_long(const char *promptMessage)
{
    long value;
    char input[LONGLEN+1];

    do {
        printf("%s", promptMessage);
        fgets(input, LONGLEN, stdin);
        value = atol(input);
    } while (value == 0 && strcmp(input, "0"));

    return value;
}

void catFirstTwoDigits(int *first, int *second, int number)
{
    while(number > 0)
    {
        number /= 10;
        if(number < 100 && number > 9)
        {
            *secondDigit = number % 10;
        }
        else if(number < 10 && number > 0)
        {
            firstDigit = number;
        }
    }
}

int countDigits(int number)
{
    int count = 0;
    while(number > 0)
    {
        number /= 10;
        count++;
    }
    return count;
}