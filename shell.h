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
//included almost all the libraries that I have come accross and please dont mind if/when some of them dont get used in the entirety(spelling) of the programm

#include "marcos.h" //remembered this one from this other project

typedef struct info
{
	char *var;
	struct list *next;
}list_t

int unsetenv(list_t **env, char **str);
int setenv(list_t *env, cahr **str);
int env(list_t *env, char *str);
int get_env(list_t *env, char *str);
int _exit(char **s,char **command, list_t *env, int num);
int execve(char *arg[], list_t *env, int num);
int __cd(char **str, list_t *env, int num);
int builtin(char **token, int num, list_t *env, char **command);
int _env(char **str, list_t *env);
int getline(char **str);


#endif
