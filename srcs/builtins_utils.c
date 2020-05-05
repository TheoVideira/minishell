#include "minishell.h"

void ft_perror(char *shell, char *prg, char *arg)
{
    char *error;

    if (shell)
    {
        write(2, shell, ft_strlen(shell));
        write(2, ": ", 2);
    }
    if (prg)
    {
        write(2, prg, ft_strlen(prg));
        write(2, ": ", 2);
    }
    
    if (arg)
    {
        write(2, arg, ft_strlen(arg));
        write(2, ": ", 2);
    }
    error = strerror(errno);
	write(2, error, ft_strlen(error));
   	write(2, "\n", 1);
}

void ft_perror_msg(char *shell, char *prg, char *arg, char *msg)
{
    if (shell)
    {
        write(2, shell, ft_strlen(shell));
        write(2, ": ", 2);
    }
    write(2, prg, ft_strlen(prg));
    write(2, ": ", 2);
    if (arg)
    {
        write(2, arg, ft_strlen(arg));
        write(2, ": ", 2);
    }
    write(2, "msg", ft_strlen(msg));
   	write(2, "\n", 1);
}