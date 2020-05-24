/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:12:25 by marvin            #+#    #+#             */
/*   Updated: 2020/05/24 17:12:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(int ac, char* const* av)
{
	int i;
	int flagn;

	flagn = ac > 1 && ft_strcmp(av[1], "-n") == 0;
	i = flagn + 1;
	while (i < ac)
	{
		write(1, av[i], ft_strlen(av[i]));
		if (i != ac - 1)
			write(1, " ", 1);
		i++;
	}
	if (!flagn)
		write(1, "\n", 1);
	return (0);
}
