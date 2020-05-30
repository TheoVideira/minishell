/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:13:00 by marvin            #+#    #+#             */
/*   Updated: 2020/05/30 15:28:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			builtin_exit(int ac, char *const *av, t_minishell *mini)
{
	int exit_code;

	write(1, "exit\n", 5);
	if (ac == 1)
		exit(mini->lastreturn);
	if (ft_isnum(av[1]))
		if (ac > 2)
			ft_perror_msg("minishell", "exit", NULL, "too many arguments\n");
		else
		{
			exit_code = ft_atoi(av[1]) % 256;
			exit_code = (exit_code < 0) ? 256 + exit_code : exit_code;
			exit(exit_code);
		}
	else
	{
		ft_perror_msg("minishell", "exit", av[1],
			"numeric argument required\n");
		exit(2);
	}
	return (1);
}
