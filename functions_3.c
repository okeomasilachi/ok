#include "main.h"


char *read_in() {
    char* input = (char*)malloc(BUFFER_SIZE * sizeof(char));
    ssize_t read_bytes;
    int input_length, write_index = 0, space_count = 0, i, newline_count;

    if (input == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    read_bytes = read(STDIN_FILENO, input, BUFFER_SIZE);
    if (read_bytes == -1) {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }

    input_length = read_bytes;
    write_index = 0;
    space_count = 0;
    for (i = 0; i < input_length; i++) {
        if (isspace(input[i])) {
            space_count++;
        } else {
            space_count = 0;
        }

        if (space_count <= 1) {
            input[write_index++] = input[i];
        }
    }

    newline_count = 0;
    for (i = 0; i < write_index; i++) {
        if (input[i] == '\n') {
            newline_count++;
        } else {
            if (newline_count > 1) {
                input[i - newline_count + 1] = ';';
                write_index = write_index - (newline_count - 1);
            }
            newline_count = 0;
        }
    }

    if (newline_count > 1) {
        input[write_index - newline_count + 1] = ';';
        write_index = write_index - (newline_count - 1);
    }

    input[write_index] = '\0';

    input = (char*)realloc(input, (write_index + 1) * sizeof(char));

    return input;
}