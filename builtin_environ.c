#include "shell.h"

/**
 * env_builtin - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int env_builtin(program_data *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_envi(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{/* checks if exists a char = */
			if (data->tokens[1][i] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + i + 1, data);

				/* print the environ */
				print_envi(data);
				if (env_get_key(cpname, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_key(cpname, var_copy, data);
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
 * _set_env - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int _set_env(program_data *data)
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

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * _unset_env - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int _unset_env(program_data *data)
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
	env_remove_key(data->tokens[1], data);

	return (0);
}
