#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ASCII_RANGE 256

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <output_frequency_file>\n", argv[0]);
        return 1;
    }

    const char *inputFile = "large_text_file.txt";

    FILE *fp = fopen(inputFile, "rb");
    if (!fp)
    {
        perror("Error opening large_text_file.txt");
        return 1;
    }

    uint64_t freq[ASCII_RANGE] = {0};

    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        freq[(unsigned char)ch]++;
    }

    fclose(fp);

    FILE *out = fopen(argv[1], "w");
    if (!out)
    {
        perror("Error opening output file");
        return 1;
    }

    for (int i = 0; i < ASCII_RANGE; i++)
    {
        if (freq[i] > 0)
        {
            fprintf(out, "%c,%llu;", (char)i, (unsigned long long)freq[i]);
        }
    }

    fprintf(out, "\n");
    fclose(out);

    printf("Frequency file written to %s\n", argv[1]);
    return 0;
}
