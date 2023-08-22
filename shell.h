#define SHELL_H
#ifndef SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include "marcos.h"

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

#endif
