 #include "shell.h"

/*
 * @av - argument vector
 * @ac - argument count
 * On succes return 0
 */

int main(int ac, char **av, char **env)
{
        (void)av;
        (void)ac;

        prompt(env);

        return (0);
}
