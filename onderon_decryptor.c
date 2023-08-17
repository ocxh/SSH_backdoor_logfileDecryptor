#include <stdio.h>
#include <stdlib.h>

#define DECRYPTION_OFFSET 25
#define TEMP_FILE "/tmp/.tempZz"

void executeCommand(const char *cmd);
int decrypt(const char *sourceFile, const char *destFile);

int main(int argc, char **argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Error: Missing input file argument.\n");
        exit(EXIT_FAILURE);
    }

    if (decrypt(argv[1], TEMP_FILE) == 0) {
        executeCommand("cat " TEMP_FILE);
    } else {
        fprintf(stderr, "Error: Decryption failed.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void executeCommand(const char *cmd)
{
    system(cmd);
}

int decrypt(const char *sourceFile, const char *destFile)
{
    FILE *inFile = fopen(sourceFile, "rb");
    FILE *outFile = fopen(destFile, "w");

    if (!inFile || !outFile) {
        perror("Error opening file");
        return 1;
    }

    char ch;
    while ((ch = fgetc(inFile)) != EOF) {
        fputc(ch - DECRYPTION_OFFSET, outFile);
    }

    fclose(inFile);
    fclose(outFile);

    return 0;
}
