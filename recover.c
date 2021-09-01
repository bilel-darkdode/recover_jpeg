
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#define Array 512

int main(void)
{
    // open memory card file
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open the memory.\n");
        return 2;
    }


    unsigned char buffer[Array];


    int filecounter = 0;

    FILE* picture = NULL;


    int jpeg_found = 0; //false


    while (fread(buffer, Array, 1, file) == 1)
    {
        // read first 4 bytes of buffer and see if jpg signature using bitwise on last byte
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (jpeg_found == 1)
            {

                fclose(picture);
            }
            else
            {

                jpeg_found = 1;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", filecounter);
            picture = fopen(filename, "a");
            filecounter++;
        }

        if (jpeg_found == 1)
        {

            fwrite(&buffer, Array, 1, picture);
        }

    }


    fclose(file);
    fclose(picture);

    return 0;
}