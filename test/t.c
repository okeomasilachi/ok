#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void readFromFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
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
        printf("%s", line);
        printf("1\n");
    }

    free(line);
    fclose(file);
}

int main() {
    const char* filename = "../oki.txt";  // Replace with your file name
    readFromFile(filename);

    return 0;
}
