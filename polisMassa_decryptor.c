#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char *filename = "sshd.sync";  
    char *filename_out = "sshd_decrypted.sync";
    fp = fopen(filename, "rb");   

    if (fp == NULL) {
        perror("[FILE ERROR] Can not found /var/run/sshd.sync");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char*)malloc(filesize);
    if (buffer == NULL) {
        perror("[MEMORY ERROR] Memory allocation error");
        fclose(fp);
        return 1;
    }

    fread(buffer, 1, filesize, fp);
    fclose(fp);

    for (long i = 0; i < filesize; i++) {
        buffer[i] = ~buffer[i];
    }

    fp = fopen(filename_out, "wb");
    if (fp == NULL) {
        perror("[FILE ERROR] Can not open output file!");
        free(buffer);
        return 1;
    }
    fwrite(buffer, 1, filesize, fp);

    fclose(fp);
    free(buffer);

    printf("Decrypt Completed!\n");
    return 0;
}
//ocxh
