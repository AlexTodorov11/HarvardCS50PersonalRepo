#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

// Define a type for a byte, which is 8 bits recover
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Open the forensic image (memory card file)
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];  // Buffer to store a block of data
    FILE *output_file = NULL; // Pointer for the output JPEG file
    char filename[8];         // Buffer to store the filename (###.jpg)
    int file_count = 0;       // Count of the recovered JPEGs
    int jpeg_found = 0;       // Flag to track if we're in the middle of a JPEG

    // Read through the entire input file block by block
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input_file) == BLOCK_SIZE)
    {
        // Check if the first four bytes match JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If we're already writing to a JPEG file, close it before starting a new one
            if (jpeg_found == 1)
            {
                fclose(output_file);
            }

            // Create a new filename for the new JPEG
            sprintf(filename, "%03i.jpg", file_count);
            output_file = fopen(filename, "w");
            if (output_file == NULL)
            {
                printf("Could not create output file.\n");
                return 1;
            }

            // Start writing to the new JPEG file
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);
            file_count++;   // Increment file counter
            jpeg_found = 1; // Indicate we're now writing a JPEG
        }
        else
        {
            // If already found a JPEG, keep writing blocks until a new JPEG is found
            if (jpeg_found == 1)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);
            }
        }
    }

    // Close any remaining open files
    if (output_file != NULL)
    {
        fclose(output_file);
    }

    // Close the input file
    fclose(input_file);

    return 0;
}
