/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:13:00 by marvin            #+#    #+#             */
/*   Updated: 2020/06/06 20:05:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_limits(char *n)
{
	int len;
	int min;

	len = ft_strlen(n);
	min = n[0] == '-';
	if ((min && len < 20) || (!min && len < 19))
		return (1);
	else if ((min && len > 20) || (!min && len > 19))
		return (0);
	else
	{
		if (min)
			return (strcmp(n, "-9223372036854775808") <= 0);
		else
			return (strcmp(n, "9223372036854775807") <= 0);
	}
}

static int	ft_isnum(char *n)
{
	int i;

	i = 0;
	if (!n)
		return (0);
	if (n[i] == '-')
		i++;
	while (n[i])
		if (!ft_isdigit(n[i++]))
			return (0);
	return (1);
}

int			builtin_exit(int ac, char *const *av)
{
	int exit_code;

	write(1, "exit\n", 5);
	if (ac == 1)
		exit(g_mini.lastcall);
	if (ft_isnum(av[1]) && ft_limits(av[1]))
		if (ac > 2)
			ft_perror_msg("minishell", "exit", NULL, "too many arguments");
		else
		{
			exit_code = ft_atoi(av[1]) % 256;
			exit_code = (exit_code < 0) ? 256 + exit_code : exit_code;
			exit(exit_code);
		}
	else
	{
		ft_perror_msg("minishell", "exit", av[1],
			"numeric argument required");
		exit(2);
	}
	return (1);
}
