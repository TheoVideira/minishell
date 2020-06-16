/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:14:42 by marvin            #+#    #+#             */
/*   Updated: 2020/05/30 15:33:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(int ac, char *const *av, t_dict *env)
{
	int i;

	i = 0;
	while (++i < ac)
		ft_dictrem(&env, av[i], free);
	return (0);
}
