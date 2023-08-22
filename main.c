#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
    program_data program_struct = {NULL}, *data = &program_struct;
    char *prompt = "";

    initialize_data(data, argc, argv, env);

    signal(SIGINT, handle_ctrl_c);

    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
    {
        errno = 2;
        prompt = PROMPT_MSG;
    }
    errno = 0;
    sisifo(prompt, data);
    return 0;
}

void handle_ctrl_c(int opr UNUSED)
{
    _print("\n");
    _print(PROMPT_MSG);
}

void initialize_data(program_data *data, int argc, char *argv[], char **env)
{
    int i = 0;

    data->program_name = argv[0];
    data->input_line = NULL;
    data->command_name = NULL;
    data->exec_counter = 0;

    if (argc == 1)
        data->file_descriptor = STDIN_FILENO;
    else
    {
        data->file_descriptor = open(argv[1], O_RDONLY);
        if (data->file_descriptor == -1)
        {
            _printe(data->program_name);
            _printe(": 0: Can't open ");
            _printe(argv[1]);
            _printe("\n");
            exit(127);
        }
    }
    data->tokens = NULL;

    data->env = malloc(sizeof(char *) * 50);
    if (env)
    {
        for (; env[i]; i++)
        {
            data->env[i] = str_duplicate(env[i]);
        }
    }
    data->env[i] = NULL;

    env = data->env;

    data->alias_list = malloc(sizeof(char *) * 20);
    for (i = 0; i < 20; i++)
    {
        data->alias_list[i] = NULL;
    }
}

