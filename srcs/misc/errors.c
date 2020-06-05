/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:49:12 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 03:25:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	alloc_error(void)
{
	ft_perror("minishell", 0, 0);
}

int		fatal_error(char *label)
{
	ft_perror("minishell", label, 0);
	return (FATAL_ERROR);
}

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

void	ft_perror(char *shell, char *prg, char *arg)
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

void	ft_perror_msg(char *shell, char *prg, char *arg, char *msg)
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
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
