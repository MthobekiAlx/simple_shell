#include "shell.h"

/**
 * list_builtin - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int list_builtin(program_data *data)
{
	int iterator;
	builtins options[] = {
		{"exit", exit_builtin},
		{"help", builtin_help},
		{"cd", cd_builtin},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", _set_env},
		{"unsetenv", _unset_env},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[iterator].function(data));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
