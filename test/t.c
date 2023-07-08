#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void remov(char *str) {
    int i, j;
    char *src, *dst; 
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != '\t' && str[i] != '\n') {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
    src = str;
    dst = str;
    while (*src) {
        if (*src != '"') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int isStringEmpty(const char *str) {
    while (*str) {
        if (!isspace(*str))
            return 0; // String is not empty
        str++;
    }
    return 1; // String is empty
}

void readFromFile(const char* filename) {
    int i = 1, fd = open(filename, O_RDONLY);

    (void) i;
    if (fd == -1) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* file = fdopen(fd, "r");
    if (file == NULL) {
        printf("Failed to open the file with file stream.\n");
        close(fd);
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        remov(line);
        if (isStringEmpty(line))
        {
            i++;
            continue;
        }
        printf("%s\t%d\n", line, i);
        i++;
    }

    free(line);
    fclose(file);
}


int main() {
    const char* filename = "../oki.txt";  // Replace with your file name
    readFromFile(filename);

    return 0;
}
 