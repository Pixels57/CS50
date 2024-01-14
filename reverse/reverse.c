#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse 'filename'.wav \n");
        return 1;
    }

    // Open input file for reading
    char* input = argv[1];
    FILE* infile = fopen(input, "r");
    if (infile == NULL)
    {
        printf("Cannot open file \n");
        return 1;
    }

    // Read header
    WAVHEADER wav;
    fread(&wav, sizeof(WAVHEADER), 1, infile);

    // Use check_format to ensure WAV format
    int check = check_format(wav);
    bool isWav = false;
    if (check == 0)
    {
        isWav = true;
    }
    else
    {
        printf("File is not WAV. \n");
        return 1;
    }

    // Open output file for writing
    char* output = argv[2];
    FILE* outfile = fopen(output, "w");
    if (outfile == NULL)
    {
        printf("Cannot create file \n");
        return 1;
    }

    // Write header to file
    fwrite(&wav, sizeof(WAVHEADER), 1, outfile);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(wav);

    // Write reversed audio to file
    BYTE buffer[block_size];
    fseek(infile, 0, SEEK_END);
    while (ftell(infile) > sizeof(WAVHEADER))
    {
        fseek(infile, -1 * block_size, SEEK_CUR);
        fread(&buffer, block_size, 1, infile);
        fwrite(&buffer, block_size, 1, outfile);
        fseek(infile, -1 * block_size, SEEK_CUR);
    }


    fclose(outfile);
    fclose(infile);
}

int check_format(WAVHEADER header)
{
    if ((header.format[0] == 'W') && (header.format[1] == 'A') && (header.format[2] == 'V') && (header.format[3] == 'E'))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    int channel_num = header.numChannels;
    int bitsample = header.bitsPerSample;
    return (channel_num * bitsample) / 8;
}