/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:12:25 by marvin            #+#    #+#             */
/*   Updated: 2020/06/06 17:55:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dash_n(char *str)
{
	int i;

	i = 1;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[++i])
			if (str[i] != 'n')
				return (0);
	}
	else
		return (0);
	return (1);
}

int			builtin_echo(int ac, char *const *av)
{
	int i;
	int flagn;
	int skip;

	flagn = ac > 1 && dash_n(av[1]);
	i = flagn;
	skip = flagn;
	while (++i < ac)
	{
		if (skip && dash_n(av[i]))
			continue;
		else
			skip = 0;
		write(1, av[i], ft_strlen(av[i]));
		if (i != ac - 1)
			write(1, " ", 1);
	}
	if (!flagn)
		write(1, "\n", 1);
	return (0);
}
