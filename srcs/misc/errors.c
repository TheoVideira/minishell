#include <minishell.h>

void alloc_error()
{
	ft_putstr_fd("minishell: allocation error while parsing\n", 2);
}

void fatal_error()
{
	ft_perror("minishell", "a weird error has occured", 0);
}

void command_not_found()
{

}