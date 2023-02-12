#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 4096

int main() {
    char buffer1[BUFF_SIZE];
    char buffer2[BUFF_SIZE];

    FILE *fp;
    fp = fopen("output", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int current_buffer = 1;
    size_t bytes_read = fread(buffer1, sizeof(char), BUFF_SIZE, fp);

    
    while (bytes_read > 0) {
        // Do something with the data in the current buffer
        // For example, print the contents of the buffer:
        printf("%.*s", (int)bytes_read, current_buffer == 1 ? buffer1 : buffer2);

        // Switch to the other buffer and read more data
        current_buffer = current_buffer == 1 ? 2 : 1;
        bytes_read = fread(current_buffer == 1 ? buffer1 : buffer2, sizeof(char), BUFF_SIZE, fp);
    }

    fclose(fp);
    return 0;
}