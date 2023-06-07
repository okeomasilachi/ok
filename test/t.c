#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void signal_handler(int signum) {
    printf("\nShell> "); // Display the shell prompt after receiving the signal
    fflush(stdout); // Flush the output buffer
}

int main() {
    signal(SIGINT, signal_handler);

    while (1) {
        printf("Shell> ");

        char input[100];
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        printf("You entered: %s\n", input);
    }

    return 0;
}
