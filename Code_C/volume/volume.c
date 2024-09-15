// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        fclose(input); // Ensure input file is closed
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        // Multiply sample by factor and ensure it's within valid range
        int32_t new_sample = sample * factor;

        // Clamp the result to the range of 16-bit signed int
        if (new_sample > 32767)
        {
            new_sample = 32767;
        }
        else if (new_sample < -32768)
        {
            new_sample = -32768;
        }

        // Write updated sample to output file
        int16_t output_sample = (int16_t) new_sample;
        fwrite(&output_sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    // Added a value
    return 0;
}
