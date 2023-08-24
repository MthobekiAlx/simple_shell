#include "shell.h"

/**
 * built_in_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int built_in_list(program_data *data)
{
	int iterator;
	builtin options[] = {
		{"exit", built_in_exit},
		{"help", built_in_help},
		{"cd", built_in_cd},
		{"alias", built_in_alias},
		{"env", built_in_env},
		{"setenv", built_in_setenv},
		{"unsetenv", built_in_usetenv},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_comp(options[iterator].builtin, data->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[iterator].function(data));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
