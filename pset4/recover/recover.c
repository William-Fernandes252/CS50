#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FILENAMELEN 7
#define BLOCKSIZE 512

typedef uint8_t BYTE;

uint8_t recover(FILE*);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *card = fopen("card.raw", "r");
    if(card == NULL)
    {
        fprintf(stderr ,"Couldn't open the input file.\n");
        return 1;
    }

    if(recover(card) == 0)
    {
        fprintf(stderr, "Some error occurred in recovering.\n");
        return 1;
    }

    if(fclose(card) != 0)
    {
        fprintf(stderr, "Failed to close the input file. Data may be lost.\n");
        return 1;
    }
    return 0;
}

uint8_t recover(FILE *memory)
{
    uint16_t bytesRead;
    BYTE recovered = 0, first = 1, size = 0, *buffer;
    char filename[FILENAMELEN+1];
    FILE *img;

    buffer = (BYTE*) malloc(BLOCKSIZE);
    while((bytesRead = fread(buffer, sizeof(BYTE), BLOCKSIZE, memory)) == BLOCKSIZE)
    {
        size = 1;
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if(first == 1)
            {
                sprintf(filename, "%03d.jpg", recovered);
                img = fopen(filename, "w");
                fwrite(buffer, 1, bytesRead, img);
                first = 0;
            }
            else
            {
                if(fclose(img) != 0)
                {
                    return 0;
                }
                recovered++;
                sprintf(filename, "%03d.jpg", recovered);
                img = fopen(filename, "w");
                fwrite(buffer, 1, bytesRead, img);
            }
        }
        else if(first == 0)
        {
            fwrite(buffer, 1, bytesRead, img);
        }
    }

    free(buffer);
    if(fclose(img) != 0)
    {
        return 0;
    }

    return recovered;
}