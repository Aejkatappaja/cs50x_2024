#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int CARD_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    uint8_t buffer[CARD_SIZE];
    char *filename = malloc(8);
    int file_number = 0;
    FILE *img = NULL;
    bool writing = false;
    bool file_is_jpeg = (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        ((buffer[3] & 0xf0) == 0xe0));

    while (fread(buffer, 1, CARD_SIZE, card) == CARD_SIZE)
    {
        // Vérifier si un nouveau JPEG commence au début du bloc
        if (file_is_jpeg)
        {
            // Si un fichier est déjà ouvert, le fermer
            if (writing)
            {
                fclose(img);
            }

            // Créer un nouveau fichier JPEG
            sprintf(filename, "%03i.jpg", file_number);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create output file %s\n", filename);
                return 1;
            }
            file_number++;
            writing = true;
        }

        // Si un fichier est ouvert pour écrire, écrire le buffer
        if (writing)
        {
            fwrite(buffer, 1, CARD_SIZE, img);
        }
    }

    // Fermer le dernier fichier ouvert
    if (writing)
    {
        fclose(img);
    }

    free(filename);
    fclose(card);

    return 0;
}
