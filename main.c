#include "shell.h"

/*
 * main .c file that creates a simple shell
 * @av - argument vector
 * @ac - argument count
 * On success, return 0
 */

int main(int ac, char **av, char **env) {
    (void) av;
    (void) ac;

    char *line = NULL;
    size_t n = 0;

    while (1) {
        printf("Shell Prompt> ");
        ssize_t chars_read = custom_getline(&line, &n, stdin);

        if (chars_read == -1) {
            perror("Error reading input");
            free(line);
            continue;
        }

        // Process the user input here
        // Implement your shell logic to parse and execute commands

        free(line);
    }

    return 0;
}

