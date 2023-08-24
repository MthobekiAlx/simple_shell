#include "shell.h"

/**
 * built_in_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int built_in_env(program_data *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environm(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{/* checks if exists a char = */
			if (data->tokens[1][i] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_setkey(cpname, data->tokens[1] + i + 1, data);

				/* print the environ */
				print_environm(data);
				if (env_get_key(cpname, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_setkey(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * built_in_setenv - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int built_in_setenv(program_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_setkey(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * built_in_usetenv - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int built_in_usetenv(program_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_removekey(data->tokens[1], data);

	return (0);
}
