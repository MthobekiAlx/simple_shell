#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INITIAL_BUFFER_SIZE 10

static char *input_buffer = NULL;
static size_t buffer_size = 0;
static size_t buffer_position = 0;

ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
    if (!input_buffer) {
        input_buffer = (char *)malloc(INITIAL_BUFFER_SIZE);
        if (!input_buffer) {
            return -1; // Error: memory allocation failed
        }
        buffer_size = INITIAL_BUFFER_SIZE;
    }

    size_t chars_read = 0;
    char *line = *lineptr;

    while (1) {
        if (buffer_position >= buffer_size) {
            ssize_t read_result = read(fileno(stream), input_buffer, buffer_size);
            if (read_result == 0) {
                if (chars_read == 0) {
                    return -1; // Error or end of file
                } else {
                    break; // Return what was read so far
                }
            } else if (read_result == -1) {
                return -1; // Error reading
            }
            buffer_position = 0;
        }

        char c = input_buffer[buffer_position++];
        
        if (chars_read + 1 >= *n) {
            *n *= 2;
            line = realloc(line, *n);
            if (!line) {
                return -1; // Error: memory allocation failed
            }
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

int main(void) {
    size_t n = 10;
    char *buf = (char *)malloc(n);

    ssize_t chars_read = _getline(&buf, &n, stdin);

    if (chars_read == -1) {
        perror("Error reading input");
    } else {
        printf("Read %zd characters:\n%s", chars_read, buf);
    }

    free(buf);
    free(input_buffer);
    return 0;
}
