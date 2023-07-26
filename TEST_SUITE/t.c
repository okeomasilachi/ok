#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        // Process each line here
        printf("Read: %s", line);
    }

    free(line);
    return 0;
}
