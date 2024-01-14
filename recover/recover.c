#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // checks if only 1 argument is entered
    if (argc != 2)
    {
        printf("usage: ./recover 'file name'.raw \n");
        return 1;
    }
    char* infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    // checks if there is a problem with file
    if (inptr == NULL)
    {
        printf("Not able to open file \n");
        return 1;
    }
    typedef uint8_t BYTE;
    BYTE buffer[512];
    FILE* jpegout;
    int c = 0;
    bool jpegfound = false;
    //looping on memory card
    while (fread(buffer, 1, 512, inptr) == 512)
    {
        char outfile[9];
        //check for first jpeg file
        if ((buffer[0] == 255) && (buffer[1] == 216) && (buffer[2] == 255) && ((buffer[3] & 0xf0) == 0xe0) && (c == 0))
        {
            jpegfound = true;
            sprintf(outfile, "%03i.jpg", c);
            jpegout = fopen(outfile, "w");
            c++;
        }
        //handling new jpeg files
        else if ((buffer[0] == 255) && (buffer[1] == 216) && (buffer[2] == 255) && ((buffer[3] & 0xf0) == 0xe0) && (c > 0))
        {
            jpegfound = true;
            fclose(jpegout);
            sprintf(outfile, "%03i.jpg", c);
            jpegout = fopen(outfile, "w");
            c++;
        }
        //reading jpeg filles
        if (jpegfound)
        {
            fwrite(buffer, 1, 512, jpegout);
        }
    }
    //closeing files before terminating
    fclose(jpegout);
    fclose(inptr);
    return 0;
}