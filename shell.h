#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h> 
#include <stddef.h>
#include <errno.h> 
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <signal.h> 
#include <fcntl.h> 
#include "macros.h" 

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} program_data;

/**
 * struct builtin - struct for the builtin
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtin
{
	char *builtin;
	int (*function)(program_data *data);
} builtin;

void initialise_data(program_data *data, int arc, char *argv[], char **env);
void handle_ctrl(int opr UNUSED);
int getline(program_data *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);
void expand_variables(program_data *data);
void expand_alias(program_data *data);
int buffer_add(char *buffer, char *str_to_add);
void tokenize(program_data *data);
char *_strtok(char *line, char *delim);
int execve(program_data *data);
int built_in_list(program_data *data);
char **tokenize_path(program_data *data);
int find_program(program_data *data);
void free_array_of_pointers(char **directories);
void free_recurrent_data(program_data *data);
void free_all_data(program_data *data);
int built_in_exit(program_data *data);
int built_in_cd(program_data *data);
int set_work_directory(program_data *data, char *new_dir);
int built_in_help(program_data *data);
int built_in_alias(program_data *data);
int built_in_env(program_data *data);
int built_in_setenv(program_data *data);
int built_in_usetenv(program_data *data);
char *env_get_key(char *name, program_data *data);
int env_setkey(char *key, char *value, program_data *data);
int env_removekey(char *key, program_data *data);
void print_environm(program_data *data);
int _print(char *string);
int _printe(char *string);
int p_error(int errorcode, program_data *data);/*prints error-perror*/
int str_lngth(char *string);/*string length*/
char *str_dup(char *string);/*duplicates the string*/
int str_comp(char *string1, char *string2, int number);/*compares the string*/
char *str_concat(char *string1, char *string2);
void str_rev(char *string);/*reverses string*/
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char *character);
int p_alias(program_data *data, char *alias);/*prints alias*/
char *get_alias(program_data *data, char *alias);/*gets alias*/
int s_alias(char *alias_string, program_data *data);/*sets alias*/


#endif /* SHELL_H */
