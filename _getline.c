#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INITIAL_BUFFER_SIZE 10

static char *input_buffer = NULL;
static size_t buffer_size = 0;
static size_t buffer_position = 0;

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

int main(void) {
    size_t n = 10;
    char *buf = (char *)malloc(n);
    ssize_t chars_read;

    if (!buf) {
        perror("Memory allocation failed");
        return 1;
    }

    chars_read = custom_getline(&buf, &n, stdin);

    if (chars_read == -1) {
        perror("Error reading input");
        free(buf);
        return 1;
    } else {
        printf("Read %ld characters:\n%s", (long)chars_read, buf);
    }

    free(buf);
    return 0;
}

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    size_t chars_read = 0;
    ssize_t read_result;
    char *line = *lineptr;
    char c;
    char *new_line;

    if (!input_buffer) {
        input_buffer = (char *)malloc(INITIAL_BUFFER_SIZE);
        if (!input_buffer) {
            perror("Memory allocation failed");
            return -1;
        }
        buffer_size = INITIAL_BUFFER_SIZE;
    }

    while (1) {
        if (buffer_position >= buffer_size) {
            read_result = read(fileno(stream), input_buffer, buffer_size);
            if (read_result == 0) {
                if (chars_read == 0) {
                    return -1;
                } else {
                    break;
                }
            } else if (read_result == -1) {
                perror("Error reading input");
                return -1;
            }
            buffer_position = 0;
        }

        c = input_buffer[buffer_position++];
        
        if (chars_read + 1 >= *n) {
            *n *= 2;
            new_line = realloc(line, *n);
            if (!new_line) {
                perror("Memory allocation failed");
                free(line);
                return -1;
            }
            line = new_line;
            *lineptr = line;
        }
        
        line[chars_read++] = c;
        
        if (c == '\n') {
            break;
        }
    }
    
    line[chars_read] = '\0';
    return chars_read;
}

